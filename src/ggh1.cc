/*
 *  Copyright (C) 2017 Chan Beom Park <cbpark@gmail.com>
 *
 *  This file is part of MCGGH, which is released under the GNU General
 *  Public License. See file LICENSE in the top directory of this project or
 *  go to <http://www.gnu.org/licenses/> for full license details.
 */

#include <cmath>
#include <cstdlib>
#include <iostream>
#include "breit_wigner.h"
#include "constants.h"
#include "gluons.h"
#include "pdf.h"
#include "sigma_ggh.h"
#include "utils.h"

const char appname[] = "ggh1";

const unsigned int N = 4000000;
const char PDFNAME[] = "NNPDF23_lo_as_0130_qed";

int main(int argc, char *argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: " << appname << " <ECM in GeV> <MH in GeV>\n";
        return 1;
    }

    const double eCM = std::atof(argv[1]), mH = std::atof(argv[2]);
    std::cout << "* p p --> g g --> h (ECM = " << eCM / 1000.0
              << " TeV, MH = " << mH << " GeV)\n";

    const double s = eCM * eCM;
    // the result seems to be not much sensitive to Gamma_H.
    const double gammaH = mH / 25000.0;
    // parameters for random \hat{s}.
    const double qmin = 0.0, qmax = std::sqrt(s), mtr = mH, gtr = mH;
    const double mu = mH;  // scale for PDF
    const mcggh::Rho rho{qmin, qmax, mtr, gtr, s};

    // alpha_s and PDF settings (using LHAPDF).
    const auto pdf = mcggh::mkPdf(PDFNAME);
    const double alphas = pdf->alphasQ(mu);

    double sum_w = 0, sum_w_sq = 0;  // for the variance
    std::cout << "-- Integrating for cross section ...\n";
    for (auto itry = 0; itry != N; ++itry) {
        mcggh::printProgress(itry, N);

        const double rho_val = mcggh::rhoValue(rho);
        const double shat = rho.shat(rho_val);
        const mcggh::InitGluon glu{s, shat};
        const double w = mcggh::dsigma(pdf, glu, alphas, mu, mH, gammaH) *
                         rho.delta() * glu.delta_y() * rho.jacobian(rho_val);
        sum_w += w;
        sum_w_sq += w * w;
    }

    // cross section
    const double sigma = sum_w / N;

    // error
    const double variance = sum_w_sq / N - sigma * sigma;
    const double error = std::sqrt(variance / N);

    std::cout << "-- Done integrating.\n";
    std::cout << "-- Total cross section = " << sigma * PBCONV << " +- "
              << error * PBCONV << " pb\n";
}
