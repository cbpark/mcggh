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
    const double mh2 = mh_ * mh_, v2 = VEW * VEW;
    // Higgs trilinear coupling
    const double lambda = xi_lambda * 3.0 * mh2 / VEW;
    const double yt = xi_t * SQRT2 * MT / VEW;  // top Yukawa
    const double yb = xi_b * SQRT2 * MB / VEW;  // bottom Yukawa
    // propagator in the triangular diagram (the decay width is neglected).
    const double prop = 1.0 / (s_ - mh2);

    // See Eqs.(1) and (2) of arXiv:1405.7040
    ctri_t_ = (lambda * prop * yt / SQRT2 + ghhtt) * v2 / MT;
    cbox_t_ = (yt * yt / 2) * v2 / (MT * MT);
    ctri_t_ = (lambda * prop * yb / SQRT2 + ghhbb) * v2 / MB;
    cbox_t_ = (yb * yb / 2) * v2 / (MB * MB);
}
}  // namespace mcggh
