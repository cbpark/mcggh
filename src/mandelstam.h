/*
 *  Copyright (C) 2017 Chan Beom Park <cbpark@gmail.com>
 *
 *  This file is part of MCGGH, which is released under the GNU General
 *  Public License. See file LICENSE in the top directory of this project or
 *  go to <http://www.gnu.org/licenses/> for full license details.
 */

#ifndef SRC_MANDELSTAM_H_
#define SRC_MANDELSTAM_H_

#include <cmath>

namespace mcggh {
class STU {
private:
    double s_, mh2_;
    double costh_;

public:
    STU() = delete;
    STU(const double s, const double mh, const double costh)
        : s_(s), mh2_(mh * mh), costh_(costh) {}

    double s() const { return s_; }
    double t() const;
    double u() const;

    double pT() const;
};
}  // namespace mcggh

#endif  // SRC_MANDELSTAM_H_
