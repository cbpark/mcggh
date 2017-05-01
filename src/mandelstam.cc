/*
 *  Copyright (C) 2017 Chan Beom Park <cbpark@gmail.com>
 *
 *  This file is part of MCGGH, which is released under the GNU General
 *  Public License. See file LICENSE in the top directory of this project or
 *  go to <http://www.gnu.org/licenses/> for full license details.
 */

#include "mandelstam.h"
#include <cmath>

namespace mcggh {
double STU::t() const {
    const double s_half = s_ / 2.0;
    return mh2_ - s_half + s_half * std::sqrt(1 - 2.0 * mh2_ / s_half) * costh_;
}

double STU::u() const {
    const double s_half = s_ / 2.0;
    return mh2_ - s_half - s_half * std::sqrt(1 - 2.0 * mh2_ / s_half) * costh_;
}

double STU::pT() const {
    double pT2 = (t() * u() - mh2_ * mh2_) / s_;
    if (pT2 < 0) { return 0; }
    return std::sqrt(pT2);
}
}  // namespace mcggh
