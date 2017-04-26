/*
 *  Copyright (C) 2017 Chan Beom Park <cbpark@gmail.com>
 *
 *  This file is part of MCGGH, which is released under the GNU General
 *  Public License. See file LICENSE in the top directory of this project or
 *  go to <http://www.gnu.org/licenses/> for full license details.
 */

#ifndef SRC_BREIT_WIGNER_H_
#define SRC_BREIT_WIGNER_H_

#include <cmath>
#include "utils.h"

namespace mcggh {
class Rho {
private:
    double rho1_, rho2_;
    double m_, gamma_, s_;

public:
    Rho() = delete;
    Rho(const double qcut, const double m, const double gamma, const double s)
        : m_(m), gamma_(gamma), s_(s) {
        const double gm = gamma_ * m_;
        rho1_ = std::atan((qcut * qcut - m_ * m_) / gm);
        rho2_ = std::atan((s_ - m_ * m_) / gm);
    }

    double delta() const { return rho2_ - rho1_; }

    double jacobian(const double val) const {
        const double cosrho = std::cos(val);
        return m_ * gamma_ / (cosrho * cosrho * s_);
    }

    /** \hat{s} = M * Gamma * tan(rho) + M^2 */
    double shat(const double val) const {
        return m_ * gamma_ * std::tan(val) + m_ * m_;
    }

    friend double rhoValue(const Rho &rho);
};

inline double rhoValue(const Rho &rho) {
    return rho.rho1_ + getRandom() * (rho.rho2_ - rho.rho1_);
}
}  // namespace mcggh

#endif  // SRC_BREIT_WIGNER_H_
