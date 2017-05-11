/*
 *  Copyright (C) 2017 Chan Beom Park <cbpark@gmail.com>
 *
 *  This file is part of MCGGH, which is released under the GNU General
 *  Public License. See file LICENSE in the top directory of this project or
 *  go to <http://www.gnu.org/licenses/> for full license details.
 */

#ifndef SRC_CONSTANTS_H_
#define SRC_CONSTANTS_H_

#include <cmath>

/** top quark mass */
const double MT = 173.0;
const double MT2 = MT * MT;

/** bottom quark mass */
const double MB = 4.7;
const double MB2 = MB * MB;

/** Z boson mass */
const double MZ = 91.188;

/** Fermi constant */
const double GF = 1.16639e-5;
const double GF2 = GF * GF;

const double SQRT2 = 1.4142135623730951;

/** VEV of Higgs field */
const double VEW = 1.0 / std::sqrt(SQRT2 * GF);
const double VEW2 = VEW * VEW;

/** alpha_s (MZ) */
const double ALPHAS = 0.118;

const double PI = 3.141592653589793238463;
const double TWOPI = 2.0 * PI;

/** conversion factor GeV^-2 -> pb */
const double PBCONV = 3.893793656e8;

/** conversion factor GeV^-2 -> fb */
const double FBCONV = PBCONV * 1000;

/** range of costh. 1 - (-1) = 2. */
const double DELTATH = 2;

#endif  // SRC_CONSTANTS_H_
