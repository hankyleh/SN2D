#include <cmath>
#include <msg.h>
#include <transport.h>

#include <filesystem>
#include <fstream>
#include <iostream>

const double PI = 3.14159265358979323;

transport::dd_out transport::ddsolve(double dx, double dy, double mu,
                                     double eta, double sigma, double source,
                                     double psi_in_j, double psi_i_in) {
  /*
    calculates cell-average and outgoing face-average fluxes for a single
    spatial cell, single ordinate, single energy group.

    INPUT:
        double dx -- local cell width, x-direction
        double dy -- local cell width, y-direction
        double mu -- ordinate cosine
        double eta -- ordinate sine
        double sigma -- cell average total cross section
        double source -- source into this ordinate,
                    i.e. q/2 + scattering
        double psi_in_j -- face-averaged flux on incoming side (left/right)
        double psi_i_in -- face-averaged flux on incoming side (top/bottom)

    RETURN:
        returns 'dd_out' struct, which contains:
             psi_i_j   : cell-centered flux
             psi_out_j : face-averaged flux on outgoing side (left/right)
             psi_i_out : face-averaged flux on outgoing side (top/bottom)
  */

  double cell_center;
  transport::dd_out result;

  cell_center = source + (2 * std::abs(mu) * psi_in_j / dx) +
                (2 * std::abs(eta) * psi_i_in / dy);
  cell_center /= (sigma + (2 * std::abs(mu) / dx) + (2 * std::abs(eta) / dy));

  result.psi_i_j = cell_center;
  result.psi_out_j = (2 * cell_center) - psi_in_j;
  result.psi_i_out = (2 * cell_center) - psi_i_in;

  return result;
}

vec2d transport::sweep(Parameters params, vec2d source) {

  vec2d scalar(params.I, params.J);
  vec2d angular = scalar;

  vec2d angular_source = source; // TODO check if angular or scalar source

  for (int k = 0; k < params.K; k++) {
    double mu = params.mu[k];
    double eta = params.eta[k];

    // sweep northeast; mu>0 eta>0
    angular = loop_mesh(mu, eta, params, angular_source);
    scalar += (angular * params.w[k]);
    // sweep southeast; mu>0 eta<0
    angular = loop_mesh(mu, -eta, params, angular_source);
    scalar += (angular * params.w[k]);
    // sweep southwest; mu<0 eta<0
    angular = loop_mesh(-mu, -eta, params, angular_source);
    scalar += (angular * params.w[k]);
    // sweep northwest; mu<0 eta>0
    angular = loop_mesh(-mu, eta, params, angular_source);
    scalar += (angular * params.w[k]);
  }
  return scalar;
}

vec2d transport::loop_mesh(double mu, double eta, Parameters params,
                           vec2d angular_source) {
  vec2d flux(params.I, params.J);

  double dx, dy, sigma, source, psi_i_in, psi_in_j;
  std::vector<double> psi_i_in_vec;

  int x_start = 0 + (params.I - 1) * (mu < 0);
  int y_start = 0 + (params.J - 1) * (eta < 0);
  int x_step = 1 - 2 * (mu < 0);
  int y_step = 1 - 2 * (eta < 0);
  int x_end = (params.I) - (params.I + 1) * (mu < 0);
  int y_end = (params.J) - (params.J + 1) * (eta < 0);

  transport::dd_out kernel_result;

  switch (params.bc_x[1 * (mu < 0)]) {
  case 0:
    // vacuum boundary
    psi_in_j = 0;
    break;
  case 1:
    // reflective boundary
    throw std::runtime_error("Reflective x BC not yet supported in loop_mesh");
  }
  switch (params.bc_y[1 * (eta < 0)]) {
  case 0:
    // vacuum boundary
    psi_i_in_vec = std::vector(params.I, 0.0);
    break;
  case 1:
    // reflective boundary
    throw std::runtime_error("Reflective y BC not yet supported in loop_mesh");
  }

  for (int j = y_start; j != y_end; j += y_step) {
    psi_in_j = 0; // TODO will need to change when refl bc is added
    for (int i = x_start; i != x_end; i += x_step) {
      dx = params.h_x[i];
      dy = params.h_y[j];
      sigma = params.sig_tot(i, j);
      source = angular_source(i, j);
      psi_i_in = psi_i_in_vec[i];
      kernel_result =
          ddsolve(dx, dy, mu, eta, sigma, source, psi_in_j, psi_i_in);
      psi_in_j = kernel_result.psi_out_j;
      psi_i_in_vec[i] = kernel_result.psi_i_out;
      flux(i, j) = kernel_result.psi_i_j;
    }
  }

  return flux;
}

vec2d transport::inner(Parameters params, std::filesystem::path output_path) {
  // inner -- conducts inner iterations given mesh and iteration data in
  // 'params' source iteration until l-infty change is < params.epsilon or until
  // number of iterations exceeds params.max_iterations

  vec2d result(params.I, params.J);

  vec2d old_scalar(params.I, params.J, 1.0);
  vec2d scalar(params.I, params.J);
  vec2d distributed_source(params.I, params.J);

  double change = 1;

  int n;

  std::ofstream outstream;
  for (n = 0; n < params.max_iterations; n++) { // performs single iteration
    // compute scattering source
    distributed_source = params.source + (params.sig_sca * old_scalar * 0.5);

    // perform iteration
    scalar = sweep(params, distributed_source);

    // compute change

    change = abs((scalar / old_scalar) + -1).linf_norm();

    if (change < params.epsilon) {
      break;
    }

    old_scalar = scalar;
  }

  outstream.open(output_path, std::ios::app);
  if (change > params.epsilon) {
    msg::print_and_record("\nTerminated UNSUCCESSFULLY after " +
                              std::to_string(params.max_iterations),
                          outstream);
    msg::print_and_record(" iterations.\ntol = ", outstream);
    msg::print_and_record(msg::sci_fmt(params.epsilon, 4), outstream);
    msg::print_and_record(", max. change = " + msg::sci_fmt(change, 4) + "\n",
                          outstream);
    msg::record("\nFinal iterate:\n\n", outstream);
  } else {
    msg::print_and_record("\nTerminated successfully after ", outstream);
    msg::print_and_record(std::to_string(n) + " iterations\n\n", outstream);
  }

  // print scalar after iteration has concluded

  msg::record("Discrete Ordinates Method Solution\n", outstream);
  msg::record("i    j    Cell-averaged Scalar Flux\n", outstream);
  for (int i = 0; i < params.I; i++) {
    for (int j = 0; j < params.J; j++) {
      msg::record(msg::add_spaces(i + 1, 5), outstream);
      msg::record(msg::add_spaces(j + 1, 5), outstream);
      msg::record(msg::sci_fmt(scalar(i, j), 8), outstream);
      msg::record("\n", outstream);
    }
  }
  outstream.close();
  return result;
}