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
void HiggsCoupl::init(const double s, const double mh, const double xi_lambda,
                      const double xi_t, const double xi_b, const double ghhtt,
                      const double ghhbb) {
    const double sqrt2 = std::sqrt(2);
    const double mh2 = mh * mh;
    const double v = 1.0 / std::sqrt(sqrt2 * GF);
    const double lambda = xi_lambda * 3.0 * mh2 / v;
    const double yt = xi_t * sqrt2 * MT / v;
    const double yb = xi_b * sqrt2 * MB / v;
    const double prop = 1.0 / (s - mh2);

    ctri_t_ = lambda * prop * yt / sqrt2 + ghhtt;
    cbox_t_ = yt * yt / 2.0;
    ctri_b_ = lambda * prop * yb / sqrt2 + ghhbb;
    cbox_b_ = yb * yb / 2.0;
}
}  // namespace mcggh
