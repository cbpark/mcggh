/*
 *  Copyright (C) 2017 Chan Beom Park <cbpark@gmail.com>
 *
 *  This file is part of MCGGH, which is released under the GNU General
 *  Public License. See file LICENSE in the top directory of this project or
 *  go to <http://www.gnu.org/licenses/> for full license details.
 */

#include "sigma_gghh.h"
#include <cmath>
#include <complex>
#include <memory>
#include "LHAPDF/LHAPDF.h"
#include "constants.h"
#include "couplings.h"
#include "gluons.h"
#include "kinematics.h"
#include "loops.h"

namespace mcggh {
double dsigmaLO_dt(const HiggsCoupl &c, const CM22 &k, const double alphas) {
    const double tau_t = 4.0 * MT * MT / k.shat(),
                 tau_b = 4.0 * MB * MB / k.shat();

    // top quark loops
    LoopParams pars(k, MT);
    std::complex<double> box = fBox(pars);
    std::complex<double> arg1 = c.triangle(QuarkType::TOP) * fTriangle(tau_t) +
                                c.box(QuarkType::TOP) * box;
    box = gBox(pars);
    std::complex<double> arg2 = c.box(QuarkType::TOP) * box;

    // bottom quark loops
    pars = LoopParams(k, MB);
    box = fBox(pars);
    arg1 += c.triangle(QuarkType::BOTTOM) * fTriangle(tau_b) +
            c.box(QuarkType::BOTTOM) * box;
    box = gBox(pars);
    arg2 += c.box(QuarkType::BOTTOM) * box;

    const double loopfn = std::norm(arg1) + std::norm(arg2);
    return GF * GF * alphas * alphas / (512 * std::pow(2 * PI, 3)) * loopfn;
}

double dsigmaLO_dcosth(const HiggsCoupl &c, const CM22 &k,
                       const double alphas) {
    const double s = k.shat();
    if (s <= 0) { return 0; }

    const double thres = 4 * k.mh2();
    if (thres > s) { return 0; }
    const double beta = std::sqrt(1 - thres / s);

    return dsigmaLO_dt(c, k, alphas) * beta * s / 2;
}

double dsigma(std::shared_ptr<LHAPDF::PDF> pdf, const InitGluon &glu,
              const HiggsCoupl &c, const CM22 &k, const double mu,
              const double alphas) {
    const double x1 = glu.x1(), x2 = glu.x2();
    const double sigma = pdf->xfxQ(21, x1, mu) * pdf->xfxQ(21, x2, mu) *
                         dsigmaLO_dcosth(c, k, alphas);
    return sigma / (x1 * x2);
}
}  // namespace mcggh
