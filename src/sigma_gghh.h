/*
 *  Copyright (C) 2017 Chan Beom Park <cbpark@gmail.com>
 *
 *  This file is part of MCGGH, which is released under the GNU General
 *  Public License. See file LICENSE in the top directory of this project or
 *  go to <http://www.gnu.org/licenses/> for full license details.
 */

#ifndef SRC_SIGMA_GGHH_H_
#define SRC_SIGMA_GGHH_H_

#include "couplings.h"

namespace mcggh {
/** Eq.(13) of arXiv:hep-ph/9603205 */
double dsigmaLO_dt(const HiggsCoupl &c, const double costh,
                   const double alphas);
}  // namespace mcggh

#endif  // SRC_SIGMA_GGHH_H_
