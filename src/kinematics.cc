/*
 *  Copyright (C) 2017 Chan Beom Park <cbpark@gmail.com>
 *
 *  This file is part of MCGGH, which is released under the GNU General
 *  Public License. See file LICENSE in the top directory of this project or
 *  go to <http://www.gnu.org/licenses/> for full license details.
 */

#include "kinematics.h"
#include <cmath>
#include <ostream>

namespace mcggh {
std::ostream &operator<<(std::ostream &os, const FourMomentum &p) {
    os << "e = " << p.e_ << ", px = " << p.px_ << ", py = " << p.py_
       << ", pz = " << p.pz_;
    return os;
}

void CM22::init() {
    const double thres = 4 * mh2_;
    if (thres > s_) {
        beta_ = 0;
    } else {
        beta_ = std::sqrt(1 - thres / s_);
    }

    if (costh_ < -1 || costh_ > 1) {
        sinth_ = -2;
        pT_ = pL_ = -1.0e+12;
    } else {
        sinth_ = std::sqrt(1 - costh_ * costh_);
        pT_ = e_ * beta_ * sinth_;
        pL_ = e_ * beta_ * costh_;
    }
}

FourMomentum CM22::pa() const { return FourMomentum(e_, 0, 0, e_); }

FourMomentum CM22::pb() const { return FourMomentum(e_, 0, 0, -e_); }

FourMomentum CM22::pc() const { return FourMomentum(e_, pT_, 0, pL_); }

FourMomentum CM22::pd() const { return FourMomentum(e_, -pT_, 0, -pL_); }
}  // namespace mcggh
