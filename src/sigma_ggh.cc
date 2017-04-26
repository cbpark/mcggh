/*
 *  Copyright (C) 2017 Chan Beom Park <cbpark@gmail.com>
 *
 *  This file is part of MCGGH, which is released under the GNU General
 *  Public License. See file LICENSE in the top directory of this project or
 *  go to <http://www.gnu.org/licenses/> for full license details.
 */

#include "sigma_ggh.h"
#include <cmath>
#include <complex>
#include <memory>
#include "constants.h"

namespace mcggh {
// Eq.(2.47) in arXiv:hep-ph/0503172
std::complex<double> ftau(const double tau) {
    if (tau > 1) {
        const double beta = std::sqrt(1 - 1.0 / tau);
        const std::complex<double> arg(std::log((1 + beta) / (1 - beta)), -PI);
        return -0.25 * std::pow(arg, 2);
    }
    const double arg = std::asin(std::sqrt(tau));
    return std::complex<double>(arg * arg, 0);
}

// Eq.(2.46) in arXiv:hep-ph/0503172
std::complex<double> a12tau(const double tau) {
    return 2.0 * (tau + (tau - 1) * ftau(tau)) / (tau * tau);
}

// Eq.(3.57) in arXiv:hep-ph/0503172
double sigma0(const double mh, const double alphas) {
    const double coeff = GF * alphas * alphas / (288 * std::sqrt(2) * PI);

    const double mh2 = mh * mh;
    std::complex<double> a12tau_sum = a12tau(mh2 / (4 * MT * MT));
    a12tau_sum += a12tau(mh2 / (4 * MB * MB));
    const double a12tau_sum_sq = std::norm(a12tau_sum);

    return coeff * (9.0 / 16) * a12tau_sum_sq;
}

// Eq.(3.56) in arXiv:hep-ph/0503172
double delta(const double shat, const double mh, const double gammah) {
    const double sgammah = shat * gammah / mh;
    return (1.0 / PI) * sgammah /
           (std::pow(shat - mh * mh, 2) + std::pow(sgammah, 2));
}

// Eq.(3.55) in arXiv:hep-ph/0503172
double sigmaLO(const double shat, const double mh, const double gammah,
               const double alphas) {
    return mh * mh * sigma0(mh, alphas) * delta(shat, mh, gammah);
}

double dsigma(std::shared_ptr<LHAPDF::PDF> pdf, const InitGluon &glu,
              const double alphas, const double mu, const double mh,
              const double gammah) {
    const double x1 = glu.x1(), x2 = glu.x2();
    const double sigma = pdf->xfxQ(21, x1, mu) * pdf->xfxQ(21, x2, mu) *
                         sigmaLO(glu.shat(), mh, gammah, alphas);
    return sigma / (x1 * x2);
}
}  // namespace mcggh
