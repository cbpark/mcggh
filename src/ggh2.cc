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
#include <memory>
#include <streambuf>
#include <tuple>
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

const double M = 1.0e+3;
const double M2 = M * M;
const double KLAMBDA = 1.0;
const double KYT = 1.0;
const double KYB = 1.0 - (MT / MB) * VEW2 / (2.0 * M2);
const double GHHTT = 0;
const double GHHBB = -3.0 * VEW / (2 * SQRT2 * M2);

using MCResult = std::tuple<double, double, mcggh::CM22>;
MCResult weight(const mcggh::Rho &rho, const std::shared_ptr<LHAPDF::PDF> &pdf,
                const double s, const double mh);

int main(int argc, char *argv[]) {
    if (argc < 3 || argc > 5) {
        std::cerr << "Usage: " << appname
                  << " <ECM in GeV> <MH in GeV> [nevent] [output]\n";
        return 1;
    }

    const double eCM = std::atof(argv[1]), mH = std::atof(argv[2]);
    std::cout << "* p p --> g g --> h h (ECM = " << eCM / 1000.0
              << " TeV, MH = " << mH << " GeV)\n";

    const double s = eCM * eCM;
    // parameters for random \hat{s}.
    const double thres = 2 * mH;
    const double qmin = thres, qmax = std::sqrt(s), mtr = thres, gtr = thres;
    const mcggh::Rho rho{qmin, qmax, mtr, gtr, s};

    // PDF from LHAPDF.
    const std::shared_ptr<LHAPDF::PDF> pdf(mcggh::mkPdf(PDFNAME));

    double sum_w = 0, sum_w_sq = 0, w_max = 0;  // for the variance
    std::cout << "-- Integrating for cross section ...\n";
    for (auto itry = 0; itry != N; ++itry) {
        mcggh::printProgress(itry, N);

        const MCResult mc_result = weight(rho, pdf, s, mH);
        const double w = std::get<0>(mc_result);
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
        const MCResult mc_result = weight(rho, pdf, s, mH);
        const double w = std::get<0>(mc_result);
        const double prob = w / w_max;

        // accept the event if the random number is less than the probability of
        // the phase space point
        const double r = mcggh::getRandom();
        if (r < prob) {
            mcggh::printProgress(iev, nev);

            ++iev;
            const double beta = std::get<1>(mc_result);
            const mcggh::CM22 k(std::get<2>(mc_result));
            const mcggh::FourMomentum h1(mcggh::boostZ(k.pc(), beta));
            const mcggh::FourMomentum h2(mcggh::boostZ(k.pd(), beta));
            const mcggh::Result result{k.mhh(), k.pT(), mcggh::deltaR(h1, h2)};
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

MCResult weight(const mcggh::Rho &rho, const std::shared_ptr<LHAPDF::PDF> &pdf,
                const double s, const double mh) {
    const double rho_val = mcggh::rhoValue(rho);
    const double shat = rho.shat(rho_val);

    const mcggh::HHCoupling c{shat, mh, KLAMBDA, KYT, KYB, GHHTT, GHHBB};
    const mcggh::CM22 k{shat, mh, mcggh::costh(DELTATH)};

    const double mu = k.mhh();  // renormalization and factorization scales
    const mcggh::InitGluon glu{s, shat};
    const double alphas = pdf->alphasQ(mu);

    const double w = mcggh::dsigma(pdf, glu, c, k, mu, alphas) * DELTATH *
                     rho.delta() * glu.delta_y() * rho.jacobian(rho_val);

    return std::make_tuple(w, glu.beta(), k);
}
