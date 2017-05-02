/*
 *  Copyright (C) 2017 Chan Beom Park <cbpark@gmail.com>
 *
 *  This file is part of MCGGH, which is released under the GNU General
 *  Public License. See file LICENSE in the top directory of this project or
 *  go to <http://www.gnu.org/licenses/> for full license details.
 */

#ifndef SRC_SIGMA_GGHH_H_
#define SRC_SIGMA_GGHH_H_

#include <memory>
#include "LHAPDF/LHAPDF.h"
#include "couplings.h"
#include "gluons.h"

namespace mcggh {
/** Eq.(13) of arXiv:hep-ph/9603205
 *
 *  both top and bottom quark loops are included
 */
double dsigmaLO_dt(const HiggsCoupl &c, const double costh,
                   const double alphas);

double dsigmaLO_dcosth(const HiggsCoupl &c, const double costh,
                       const double alphas);

double dsigma(std::shared_ptr<LHAPDF::PDF> pdf, const InitGluon &glu,
              const HiggsCoupl &c, const double alphas, const double mu,
              const double costh);
}  // namespace mcggh

#endif  // SRC_SIGMA_GGHH_H_
