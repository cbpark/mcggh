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

void LoopParams::init(const double s, const double mh, const double mq,
                      const double costh) {
    const CM22 cm22(s, mh, costh);
    const FourMomentum pa = cm22.pa(), pb = cm22.pb();
    const FourMomentum pc = -cm22.pc(), pd = -cm22.pd();  // all incoming
    const double pa2 = pa.mag2(), pb2 = pb.mag2(), pc2 = pc.mag2(),
                 pd2 = pd.mag2();

    mQ2_ = mq * mq;
    s_ = s / mQ2_, t_ = (pc + pa).mag2() / mQ2_, u_ = (pc + pb).mag2() / mQ2_;

    const double mc2 = mh * mh, md2 = mh * mh;
    rhoc_ = mc2 / mQ2_, rhod_ = md2 / mQ2_;
    t1_ = t_ - rhoc_, u1_ = u_ - rhoc_;
    t2_ = t_ - rhod_, u2_ = u_ - rhod_;

    Cab_ = C0(pa2, pb2, (pa + pb).mag2(), mQ2_, mQ2_, mQ2_);
    Cac_ = C0(pa2, pc2, (pa + pc).mag2(), mQ2_, mQ2_, mQ2_);
    Cbc_ = C0(pb2, pc2, (pb + pc).mag2(), mQ2_, mQ2_, mQ2_);
    Cad_ = C0(pa2, pd2, (pa + pd).mag2(), mQ2_, mQ2_, mQ2_);
    Cbd_ = C0(pb2, pd2, (pb + pd).mag2(), mQ2_, mQ2_, mQ2_);
    Ccd_ = C0(pc2, pd2, (pc + pd).mag2(), mQ2_, mQ2_, mQ2_);

    Dabc_ = D0(pa2, pb2, pc2, (pa + pb + pc).mag2(), (pa + pb).mag2(),
               (pb + pc).mag2(), mQ2_, mQ2_, mQ2_, mQ2_);
    Dbac_ = D0(pb2, pa2, pc2, (pb + pa + pc).mag2(), (pb + pa).mag2(),
               (pa + pc).mag2(), mQ2_, mQ2_, mQ2_, mQ2_);
    Dacb_ = D0(pa2, pc2, pb2, (pa + pc + pb).mag2(), (pa + pc).mag2(),
               (pc + pb).mag2(), mQ2_, mQ2_, mQ2_, mQ2_);
}

complex<double> fBox(const LoopParams &p) {
    const double s2 = p.s_ * p.s_;
    if (s2 <= 0) { return complex<double>(0, 0); }

    auto box = complex<double>(4 * p.s_, 0) + 8 * p.s_ * p.mQ2_ * p.Cab_;
    box += -2 * p.s_ * (p.s_ + p.rhoc_ + p.rhod_ - 8) * p.mQ2_ * p.mQ2_ *
           (p.Dabc_ + p.Dbac_ + p.Dacb_);
    box += (p.rhoc_ + p.rhod_ - 8) * p.mQ2_ *
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
