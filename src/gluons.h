/*
 *  Copyright (C) 2017 Chan Beom Park <cbpark@gmail.com>
 *
 *  This file is part of mcggh, which is released under the GNU General
 *  Public License. See file LICENSE in the top directory of this project or
 *  go to <http://www.gnu.org/licenses/> for full license details.
 */

#ifndef SRC_GLUONS_H_
#define SRC_GLUONS_H_

#include <cmath>

namespace mcggh {
class InitGluon {
private:
    double shat_;
    double ymax_;
    double x1_, x2_;

public:
    InitGluon() = delete;
    InitGluon(const double s, const double shat)
        : shat_{shat}, ymax_{-0.5 * std::log(shat_ / s)} {
        init(s);
    }

    double x1() const { return x1_; }
    double x2() const { return x2_; }
    double shat() const { return shat_; }
    double delta_y() const { return 2 * ymax_; }
    double beta() const { return (x2_ - x1_) / (x2_ + x1_); }

private:
    void init(const double s);
};
}  // namespace mcggh

#endif  // SRC_GLUONS_H_
