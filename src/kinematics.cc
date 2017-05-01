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

FourMomentum CM22::pa() const {
    const double e = std::sqrt(s_) / 2;
    return FourMomentum(e, 0, 0, e);
}

FourMomentum CM22::pb() const {
    const double e = std::sqrt(s_) / 2;
    return FourMomentum(e, 0, 0, -e);
}

FourMomentum CM22::pc() const {
    const double e = std::sqrt(s_) / 2;
    return FourMomentum(e, e * beta_ * sinth_, 0, e * beta_ * costh_);
}

FourMomentum CM22::pd() const {
    const double e = std::sqrt(s_) / 2;
    return FourMomentum(e, -e * beta_ * sinth_, 0, -e * beta_ * costh_);
}
}  // namespace mcggh
