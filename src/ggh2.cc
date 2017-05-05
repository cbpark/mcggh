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

const int N = 10000;
const char PDFNAME[] = "NNPDF23_lo_as_0130_qed";

const double KLAMBDA = 1.0;
const double KYT = 1.0;
const double KYB = 1.0;
const double GHHTT = 0.0;
const double GHHBB = 0.0;

int main(int argc, char *argv[]) {
    const char appname[] = "ggh2";
    if (argc < 4 || argc > 5) {
        std::cerr << "Usage: " << appname
                  << " <ECM in GeV> <MH in GeV> <nevent> [output]\n";
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

    double sum_w = 0, sum_w_sq = 0;  // for the variance
    double w_max = 0;
    std::cout << "-- Integrating for cross section ...\n";
    for (int i = 0; i != N; ++i) {
        mcggh::printProgress(i, N);

        double rho_val = mcggh::rhoValue(rho);
        double shat = rho.shat(rho_val);

        mcggh::HiggsCoupl c(shat, mH, KLAMBDA, KYT, KYB, GHHTT, GHHBB);
        mcggh::CM22 k(shat, mH, mcggh::costh(DELTATH));

        double mu = k.mhh();
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

        mcggh::HiggsCoupl c(shat, mH, KLAMBDA, KYT, KYB, GHHTT, GHHBB);
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
            mcggh::Result r(k.mhh(), k.pT());
            out << r << '\n';
        }
    }

    std::cout << "-- Done. ";
    if (has_output) {
        std::cout << "The output has been saved to `" << argv[4] << "'\n";
    } else {
        std::cout << "          \n";
    }
}
