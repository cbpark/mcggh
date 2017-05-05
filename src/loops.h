/*
 *  Copyright (C) 2017 Chan Beom Park <cbpark@gmail.com>
 *
 *  This file is part of MCGGH, which is released under the GNU General
 *  Public License. See file LICENSE in the top directory of this project or
 *  go to <http://www.gnu.org/licenses/> for full license details.
 */

#ifndef SRC_LOOPS_H_
#define SRC_LOOPS_H_

#include <complex>
#include "kinematics.h"

namespace mcggh {
std::complex<double> fTriangle(const double tau);

class LoopParams {
private:
    double mQ2_;
    double s_, t_, u_;
    double rhoc_, rhod_;
    double t1_, u1_, t2_, u2_;

    std::complex<double> Cab_, Cac_, Cbc_, Cad_, Cbd_, Ccd_;
    std::complex<double> Dabc_, Dbac_, Dacb_;

public:
    LoopParams() = delete;
    LoopParams(const CM22 &k, const double mq) : mQ2_(mq * mq) { init(k); }

    friend std::complex<double> fBox(const LoopParams &par);
    friend std::complex<double> gBox(const LoopParams &par);

private:
    void init(const CM22 &k);
};

std::complex<double> fBox(const LoopParams &par);
std::complex<double> gBox(const LoopParams &par);
}  // namespace mcggh

#endif  // SRC_LOOPS_H_
