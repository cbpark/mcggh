/*
 *  Copyright (C) 2017 Chan Beom Park <cbpark@gmail.com>
 *
 *  This file is part of MCGGH, which is released under the GNU General
 *  Public License. See file LICENSE in the top directory of this project or
 *  go to <http://www.gnu.org/licenses/> for full license details.
 */

#include "loops.h"
#include <cmath>
#include <complex>
#include "constants.h"

namespace mcggh {
std::complex<double> ftau(const double tau) {
    if (tau < 1) {
        const double beta = std::sqrt(1 - tau);
        const std::complex<double> arg(std::log((1 + beta) / (1 - beta)), -PI);
        return -0.25 * std::pow(arg, 2);
    }
    const double arg = std::asin(1.0 / std::sqrt(tau));
    return std::complex<double>(arg * arg, 0);
}

std::complex<double> fTriangle(const double tau) {
    return tau * (std::complex<double>(1.0, 0) + (1 - tau) * ftau(tau));
}
}  // namespace mcggh
