#ifndef TRANSPORT_H
#define TRANSPORT_H

#include <input.h>
#include <vec.h>

namespace transport {
struct dd_out {
  double psi_out_j; // outgoing flux, x-direction
  double psi_i_out; // outgoing flux, y-direction
  double psi_i_j;   // cell-centered flux
};

dd_out ddsolve(double dx, double dy, double mu, double eta, double sigma,
               double source, double psi_in_j, double psi_i_in);
vec2d sweep(Parameters params, vec2d source); // sweep given ANGULAR SOURCE
vec2d loop_mesh(double mu, double eta, const Parameters params,
                vec2d angular_source);
} // namespace transport

#endif