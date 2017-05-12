/*
 *  Copyright (C) 2017 Chan Beom Park <cbpark@gmail.com>
 *
 *  This file is part of MCGGH, which is released under the GNU General
 *  Public License. See file LICENSE in the top directory of this project or
 *  go to <http://www.gnu.org/licenses/> for full license details.
 */

#include "breit_wigner.h"
#include <cmath>
#include "utils.h"

namespace mcggh {
void Rho::init(const double qmin2, const double qmax2) {
    const double gm{gamma_ * m_};
    rho1_ = std::atan((qmin2 - m_ * m_) / gm);
    rho2_ = std::atan((qmax2 - m_ * m_) / gm);
}

double Rho::jacobian(const double val) const {
    const double cosrho{std::cos(val)};
    return m_ * gamma_ / (cosrho * cosrho * s_);
}

double Rho::shat(const double val) const {
    return m_ * gamma_ * std::tan(val) + m_ * m_;
}

double rhoValue(const Rho &rho) {
    return rho.rho1_ + getRandom() * (rho.rho2_ - rho.rho1_);
}
}  // namespace mcggh
