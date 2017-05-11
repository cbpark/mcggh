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
#include "utils.h"

namespace mcggh {
std::ostream &operator<<(std::ostream &os, const FourMomentum &p) {
    os << "e = " << p.e_ << ", px = " << p.px_ << ", py = " << p.py_
       << ", pz = " << p.pz_;
    return os;
}

FourMomentum boostZ(const FourMomentum &p, const double beta) {
    const double gamma = 1.0 / std::sqrt(1 - beta * beta);
    const double gb = gamma * beta;
    FourMomentum boosted(gamma * p.e_ - gb * p.pz_, p.px_, p.py_,
                         -gb * p.e_ + gamma * p.pz_);
    return boosted;
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

    const double phi = 2.0 * PI * getRandom();
    sinphi_ = std::sin(phi);
    cosphi_ = std::cos(phi);
}

FourMomentum CM22::pa() const { return FourMomentum(e_, 0, 0, e_); }

FourMomentum CM22::pb() const { return FourMomentum(e_, 0, 0, -e_); }

FourMomentum CM22::pc() const {
    return FourMomentum(e_, pT_ * cosphi_, pT_ * sinphi_, pL_);
}

FourMomentum CM22::pd() const {
    return FourMomentum(e_, -pT_ * cosphi_, -pT_ * sinphi_, -pL_);
}
}  // namespace mcggh
