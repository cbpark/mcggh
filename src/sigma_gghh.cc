/*
 *  Copyright (C) 2017 Chan Beom Park <cbpark@gmail.com>
 *
 *  This file is part of MCGGH, which is released under the GNU General
 *  Public License. See file LICENSE in the top directory of this project or
 *  go to <http://www.gnu.org/licenses/> for full license details.
 */

#include "sigma_gghh.h"
#include <complex>
#include "constants.h"
#include "couplings.h"
#include "loops.h"

namespace mcggh {
double dsigmaLO_dt(const HiggsCoupl &c, const double costh,
                   const double alphas) {
    const double tau_t = 4.0 * MT * MT / c.shat(),
                 tau_b = 4.0 * MB * MB / c.shat();

    // top quark loops
    LoopParams pars(c.shat(), c.mh(), MT, costh);
    std::complex<double> box = fBox(pars);
    std::complex<double> arg1 = c.triangle(QuarkType::TOP) * fTriangle(tau_t) +
                                c.box(QuarkType::TOP) * box;
    box = gBox(pars);
    std::complex<double> arg2 = c.box(QuarkType::TOP) * box;

    // bottom quark loops
    pars = LoopParams(c.shat(), c.mh(), MB, costh);
    box = fBox(pars);
    arg1 += c.triangle(QuarkType::BOTTOM) * fTriangle(tau_b) +
            c.box(QuarkType::BOTTOM) * box;
    box = gBox(pars);
    arg2 += c.box(QuarkType::BOTTOM) * box;

    const double dsigma = std::norm(arg1) + std::norm(arg2);
    return GF * GF * alphas * alphas / (512 * std::pow(2 * PI, 3)) * dsigma;
}
}  // namespace mcggh
