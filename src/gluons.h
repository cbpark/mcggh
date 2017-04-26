/*
 *  Copyright (C) 2017 Chan Beom Park <cbpark@gmail.com>
 *
 *  This file is part of MCGGH, which is released under the GNU General
 *  Public License. See file LICENSE in the top directory of this project or
 *  go to <http://www.gnu.org/licenses/> for full license details.
 */

#ifndef SRC_GLUONS_H_
#define SRC_GLUONS_H_

#include <cmath>
#include "utils.h"

namespace mcggh {
class InitGluon {
private:
    double x1_, x2_;
    double shat_;
    double ymax_;

public:
    InitGluon() = delete;
    InitGluon(const double s, const double shat)
        : shat_(shat), ymax_(-0.5 * std::log(shat_ / s)) {
        const double y = (2 * getRandom() - 1.0) * ymax_;
        const double tau = shat_ / s;
        x1_ = std::sqrt(tau) * std::exp(y);
        x2_ = std::sqrt(tau) * std::exp(-y);
    }

    double x1() const { return x1_; }
    double x2() const { return x2_; }
    double shat() const { return shat_; }
    double delta_y() const { return 2 * ymax_; }
};
}  // namespace mcggh

#endif  // SRC_GLUONS_H_
