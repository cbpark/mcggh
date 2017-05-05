/*
 *  Copyright (C) 2017 Chan Beom Park <cbpark@gmail.com>
 *
 *  This file is part of MCGGH, which is released under the GNU General
 *  Public License. See file LICENSE in the top directory of this project or
 *  go to <http://www.gnu.org/licenses/> for full license details.
 */

#include "gluons.h"
#include <cmath>
#include "utils.h"

namespace mcggh {
void InitGluon::init(const double s) {
    const double y = (2 * getRandom() - 1.0) * ymax_;
    const double sqrt_tau = std::sqrt(shat_ / s);
    x1_ = sqrt_tau * std::exp(y);
    x2_ = sqrt_tau * std::exp(-y);
}
}  // namespace mcggh
