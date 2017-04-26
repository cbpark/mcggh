#include <cmath>
#include <cstdlib>
#include <iostream>
#include <string>
#include "breit_wigner.h"
#include "constants.h"
#include "gluons.h"
#include "pdf.h"
#include "sigma_ggh.h"
#include "utils.h"

const int N = 4000000;
const std::string PDFNAME = "NNPDF23_lo_as_0130_qed";
// const std::string PDFNAME = "cteq6l1";

int main(int argc, char *argv[]) {
    std::string appname("ggh1");
    if (argc != 3) {
        std::cerr << "Usage: " << appname << " <ECM in GeV> <MH in GeV>\n";
        return 1;
    }

    const double eCM = std::atof(argv[1]);
    const double mH = std::atof(argv[2]);
    std::cout << "* p p --> g g --> H (ECM = " << eCM << " GeV, MH = " << mH
              << " GeV)\n";

    const double s = eCM * eCM;
    const double gammaH = mH / 25000.0;
    const double qmin = 0.0, mtr = mH, gtr = mH;  // parameters for random shat
    const double mu = mH;                         // scale for PDF
    const mcggh::Rho rho(qmin, mtr, gtr, s);

    // alpha_s and PDF settings.
    auto pdf = mcggh::mkPdf(PDFNAME);
    const double alphas = pdf->alphasQ(mu);

    double sum_w = 0, sum_w_sq = 0;  // for the variance
    std::cout << "-- Integrating for cross section ...\n";
    for (int i = 0; i != N; ++i) {
        mcggh::printProgress(i, N);

        double rho_val = mcggh::rhoValue(rho);
        double shat = rho.shat(rho_val);

        mcggh::InitGluon glu(s, shat);
        double w = mcggh::dsigma(pdf, glu, alphas, mu, mH, gammaH) *
                   rho.delta() * glu.delta_y() * rho.jacobian(rho_val);
        sum_w += w;
        sum_w_sq += w * w;
    }

    // cross section
    const double sigma = sum_w / N;

    // error
    const double variance = sum_w_sq / N - std::pow(sigma, 2);
    const double error = std::sqrt(variance / N);

    std::cout << "-- Done integrating.\n";
    std::cout << "-- Total cross section = " << sigma * PBCONV << " +- "
              << error * PBCONV << " pb\n";
}
