#include <cmath>
#include <transport.h>

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