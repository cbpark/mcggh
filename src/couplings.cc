/*
 *  Copyright (C) 2017 Chan Beom Park <cbpark@gmail.com>
 *
 *  This file is part of MCGGH, which is released under the GNU General
 *  Public License. See file LICENSE in the top directory of this project or
 *  go to <http://www.gnu.org/licenses/> for full license details.
 */

#include "couplings.h"
#include <cmath>
#include "constants.h"

namespace mcggh {
void HiggsCoupl::init(const double xi_lambda, const double xi_t,
                      const double xi_b, const double ghhtt,
                      const double ghhbb) {
    const double mh2 = mh_ * mh_;
    const double lambda = xi_lambda * 3.0 * mh2 / VEW;
    const double yt = xi_t * SQRT2 * MT / VEW;
    const double yb = xi_b * SQRT2 * MB / VEW;
    const double prop = 1.0 / (s_ - mh2);

    ctri_t_ = lambda * prop * yt / SQRT2 + ghhtt;
    cbox_t_ = yt * yt / 2.0;
    ctri_b_ = lambda * prop * yb / SQRT2 + ghhbb;
    cbox_b_ = yb * yb / 2.0;
}
}  // namespace mcggh
