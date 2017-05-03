/*
 *  Copyright (C) 2017 Chan Beom Park <cbpark@gmail.com>
 *
 *  This file is part of MCGGH, which is released under the GNU General
 *  Public License. See file LICENSE in the top directory of this project or
 *  go to <http://www.gnu.org/licenses/> for full license details.
 */

#include <cmath>
#include <iostream>
#include "breit_wigner.h"
#include "clooptools.h"
#include "constants.h"
#include "couplings.h"
#include "pdf.h"
#include "sigma_gghh.h"
#include "utils.h"

const int N = 100000;
const char PDFNAME[] = "NNPDF23_lo_as_0130_qed";

const double KLAMBDA = 1.0;
const double KYT = 1.0;
const double KYB = 1.0;
const double GHHTT = 0.0;
const double GHHBB = 0.0;

int main(int argc, char *argv[]) {
    const char appname[] = "ggh2";
    if (argc != 4) {
        std::cerr << "Usage: " << appname
                  << " <ECM in GeV> <MH in GeV> <nevent>\n";
        return 1;
    }

    const double eCM = std::atof(argv[1]);
    const double mH = std::atof(argv[2]);
    std::cout << "* p p --> g g --> H H (ECM = " << eCM << " GeV, MH = " << mH
              << " GeV)\n";

    const double s = eCM * eCM;
    // parameters for random \hat{s}.
    const double thres = 2 * mH;
    const double qmin = thres, qmax = std::sqrt(s), mtr = thres, gtr = thres;
    const mcggh::Rho rho(qmin, qmax, mtr, gtr, s);

    // PDF from LHAPDF.
    auto pdf = mcggh::mkPdf(PDFNAME);

    // for looptools
    ltini();

    double sum_w = 0, sum_w_sq = 0;  // for the variance
    std::cout << "-- Integrating for cross section ...\n";
    for (int i = 0; i != N; ++i) {
        mcggh::printProgress(i, N);

        double rho_val = mcggh::rhoValue(rho);
        double shat = rho.shat(rho_val);
        double mu = std::sqrt(shat);
        mcggh::InitGluon glu(s, shat);
        double alphas = pdf->alphasQ(mu);

        mcggh::HiggsCoupl c(shat, mH, KLAMBDA, KYT, KYB, GHHTT, GHHBB);
        double costh = mcggh::costh(DELTATH);

        double w = mcggh::dsigma(pdf, glu, c, alphas, mu, costh) * DELTATH *
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
