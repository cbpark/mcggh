/*
 *  Copyright (C) 2017 Chan Beom Park <cbpark@gmail.com>
 *
 *  This file is part of MCGGH, which is released under the GNU General
 *  Public License. See file LICENSE in the top directory of this project or
 *  go to <http://www.gnu.org/licenses/> for full license details.
 */

#include <cmath>
#include <fstream>
#include <iostream>
#include <streambuf>
#include "breit_wigner.h"
#include "constants.h"
#include "couplings.h"
#include "ggh2_result.h"
#include "kinematics.h"
#include "pdf.h"
#include "sigma_gghh.h"
#include "utils.h"

const char appname[] = "ggh2";

const unsigned int N = 100000;
const char PDFNAME[] = "NNPDF23_lo_as_0130_qed";

const double KLAMBDA = 1.0;
const double KYT = 1.0;
const double KYB = 1.0;
const double GHHTT = 0.0;
const double GHHBB = 0.0;

int main(int argc, char *argv[]) {
    if (argc < 3 || argc > 5) {
        std::cerr << "Usage: " << appname
                  << " <ECM in GeV> <MH in GeV> [nevent] [output]\n";
        return 1;
    }

    const double eCM = std::atof(argv[1]);
    const double mH = std::atof(argv[2]);
    std::cout << "* p p --> g g --> h h (ECM = " << eCM / 1000.0
              << " TeV, MH = " << mH << " GeV)\n";

    const double s = eCM * eCM;
    // parameters for random \hat{s}.
    const double thres = 2 * mH;
    const double qmin = thres, qmax = std::sqrt(s), mtr = thres, gtr = thres;
    const mcggh::Rho rho(qmin, qmax, mtr, gtr, s);

    // PDF from LHAPDF.
    auto pdf = mcggh::mkPdf(PDFNAME);

    double sum_w = 0, sum_w_sq = 0;  // for the variance
    double w_max = 0;
    std::cout << "-- Integrating for cross section ...\n";
    for (auto itry = 0; itry != N; ++itry) {
        mcggh::printProgress(itry, N);

        double rho_val = mcggh::rhoValue(rho);
        double shat = rho.shat(rho_val);

        mcggh::HHCoupling c(shat, mH, KLAMBDA, KYT, KYB, GHHTT, GHHBB);
        mcggh::CM22 k(shat, mH, mcggh::costh(DELTATH));

        double mu = k.mhh();  // renormalization and factorization scales
        mcggh::InitGluon glu(s, shat);
        double alphas = pdf->alphasQ(mu);

        double w = mcggh::dsigma(pdf, glu, c, k, mu, alphas) * DELTATH *
                   rho.delta() * glu.delta_y() * rho.jacobian(rho_val);

        sum_w += w;
        sum_w_sq += w * w;
        if (w > w_max) { w_max = w; }
    }

    // cross section
    const double sigma = sum_w / N;

    // error
    const double variance = sum_w_sq / N - sigma * sigma;
    const double error = std::sqrt(variance / N);

    std::cout << "-- Done integrating.\n";
    std::cout << "-- Total cross section = " << sigma * FBCONV << " +- "
              << error * FBCONV << " fb\n";

    // if we want to calculate only the cross section, we've done.
    if (argc == 3) { return 0; }

    // prepare output
    std::streambuf *buf;
    std::ofstream of;
    const bool has_output = argc == 5;
    if (has_output) {
        of.open(argv[4]);
        buf = of.rdbuf();
    } else {
        buf = std::cout.rdbuf();
    }
    std::ostream out(buf);

    std::cout << "-- Generating events ...\n";
    const int nev = std::atoi(argv[3]);
    int iev = 0;  // counter for event generation
    while (iev < nev) {
        mcggh::printProgress(iev, nev);

        double rho_val = mcggh::rhoValue(rho);
        double shat = rho.shat(rho_val);

        mcggh::HHCoupling c(shat, mH, KLAMBDA, KYT, KYB, GHHTT, GHHBB);
        mcggh::CM22 k(shat, mH, mcggh::costh(DELTATH));

        double mu = k.mhh();
        mcggh::InitGluon glu(s, shat);
        double alphas = pdf->alphasQ(mu);

        double w = mcggh::dsigma(pdf, glu, c, k, mu, alphas) * DELTATH *
                   rho.delta() * glu.delta_y() * rho.jacobian(rho_val);
        double prob = w / w_max;

        // accept the event if the random number is less than the probability of
        // the phase space point
        double r = mcggh::getRandom();
        if (r < prob) {
            ++iev;
            double beta = glu.beta();
            auto h1 = boostZ(k.pc(), beta);
            auto h2 = boostZ(k.pd(), beta);
            mcggh::Result result(k.mhh(), k.pT(), h1.delta_R(h2));
            out << result << '\n';
        }
    }

    std::cout << "-- Done. ";
    if (has_output) {
        std::cout << "The output has been saved to `" << argv[4] << "'\n";
    } else {
        std::cout << "          \n";
    }
}
