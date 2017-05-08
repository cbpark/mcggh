/*
 *  Copyright (C) 2017 Chan Beom Park <cbpark@gmail.com>
 *
 *  This file is part of MCGGH, which is released under the GNU General
 *  Public License. See file LICENSE in the top directory of this project or
 *  go to <http://www.gnu.org/licenses/> for full license details.
 */

#include "loops.h"
#include <cmath>
#include <complex>
#include "clooptools.h"
#include "constants.h"
#include "kinematics.h"

using std::complex;

namespace mcggh {
complex<double> ftau(const double tau) {
    if (tau < 1) {
        const double beta = std::sqrt(1 - tau);
        const complex<double> arg(std::log((1 + beta) / (1 - beta)), -PI);
        return -0.25 * std::pow(arg, 2);
    }
    const double arg = std::asin(1.0 / std::sqrt(tau));
    return complex<double>(arg * arg, 0);
}

complex<double> fTriangle(const double tau) {
    return tau * (complex<double>(1.0, 0) + (1 - tau) * ftau(tau));
}

void LoopParams::init(const CM22 &k) {
    const FourMomentum pa = k.pa(), pb = k.pb();
    const FourMomentum pc = -k.pc(), pd = -k.pd();  // all incoming
    const double pa2 = pa.m2(), pb2 = pb.m2(), pc2 = pc.m2(), pd2 = pd.m2();

    const double pab2 = (pa + pb).m2();
    const double pac2 = (pa + pc).m2();
    const double pad2 = (pa + pd).m2();
    const double pbc2 = (pb + pc).m2();
    const double pbd2 = (pb + pd).m2();
    const double pcd2 = (pc + pd).m2();

    s_ = k.shat() / mQ2_, t_ = pac2 / mQ2_, u_ = pbc2 / mQ2_;

    const double mc2 = k.mh2(), md2 = k.mh2();
    rhoc_ = mc2 / mQ2_, rhod_ = md2 / mQ2_;
    t1_ = t_ - rhoc_, u1_ = u_ - rhoc_;
    t2_ = t_ - rhod_, u2_ = u_ - rhod_;

    ltini();  // initialize looptools

    Cab_ = C0(pa2, pb2, pab2, mQ2_, mQ2_, mQ2_);
    Cac_ = C0(pa2, pc2, pac2, mQ2_, mQ2_, mQ2_);
    Cbc_ = C0(pb2, pc2, pbc2, mQ2_, mQ2_, mQ2_);
    Cad_ = C0(pa2, pd2, pad2, mQ2_, mQ2_, mQ2_);
    Cbd_ = C0(pb2, pd2, pbd2, mQ2_, mQ2_, mQ2_);
    Ccd_ = C0(pc2, pd2, pcd2, mQ2_, mQ2_, mQ2_);

    Dabc_ = D0(pa2, pb2, pc2, pd2, pab2, pbc2, mQ2_, mQ2_, mQ2_, mQ2_);
    Dbac_ = D0(pb2, pa2, pc2, pd2, pab2, pac2, mQ2_, mQ2_, mQ2_, mQ2_);
    Dacb_ = D0(pa2, pc2, pb2, pd2, pac2, pbc2, mQ2_, mQ2_, mQ2_, mQ2_);

    clearcache();  // remove all integrals from the cache
}

complex<double> fBox(const LoopParams &p) {
    if (p.s_ <= 0) { return complex<double>(0, 0); }

    const double s2 = p.s_ * p.s_;
    const double rho8 = p.rhoc_ + p.rhod_ - 8;
    auto box = complex<double>(4 * p.s_, 0) + 8 * p.s_ * p.mQ2_ * p.Cab_;
    box += -2 * p.s_ * (p.s_ + rho8) * p.mQ2_ * p.mQ2_ *
           (p.Dabc_ + p.Dbac_ + p.Dacb_);
    box += rho8 * p.mQ2_ *
           (p.t1_ * p.Cac_ + p.u1_ * p.Cbc_ + p.u2_ * p.Cad_ + p.t2_ * p.Cbd_ -
            (p.t_ * p.u_ - p.rhoc_ * p.rhod_) * p.mQ2_ * p.Dacb_);

    return box / s2;
}

complex<double> gBox(const LoopParams &p) {
    if (p.s_ <= 0) { return complex<double>(0, 0); }

    const double rho2 = p.rhoc_ * p.rhod_;
    const double denom = p.s_ * (p.t_ * p.u_ - rho2);
    if (denom == 0) { return complex<double>(0, 0); }

    auto box = (p.t_ * p.t_ + rho2 - 8 * p.t_) * p.mQ2_ *
               (p.s_ * p.Cab_ + p.t1_ * p.Cac_ + p.t2_ * p.Cbd_ -
                p.s_ * p.t_ * p.mQ2_ * p.Dbac_);
    box += (p.u_ * p.u_ + rho2 - 8 * p.u_) * p.mQ2_ *
           (p.s_ * p.Cab_ + p.u1_ * p.Cbc_ + p.u2_ * p.Cad_ -
            p.s_ * p.u_ * p.mQ2_ * p.Dabc_);
    box += -(p.t_ * p.t_ + p.u_ * p.u_ - 2 * rho2) * (p.t_ + p.u_ - 8) *
           p.mQ2_ * p.Ccd_;
    box += -2 * (p.t_ + p.u_ - 8) * (p.t_ * p.u_ - rho2) * p.mQ2_ * p.mQ2_ *
           (p.Dabc_ + p.Dbac_ + p.Dacb_);

    return box / denom;
}
}  // namespace mcggh
