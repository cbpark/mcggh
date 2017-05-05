/*
 *  Copyright (C) 2017 Chan Beom Park <cbpark@gmail.com>
 *
 *  This file is part of MCGGH, which is released under the GNU General
 *  Public License. See file LICENSE in the top directory of this project or
 *  go to <http://www.gnu.org/licenses/> for full license details.
 */

#ifndef SRC_KINEMATICS_H_
#define SRC_KINEMATICS_H_

#include <cmath>
#include <ostream>

namespace mcggh {
class FourMomentum {
private:
    double e_, px_, py_, pz_;

public:
    FourMomentum() = delete;
    FourMomentum(const double e, const double px, const double py,
                 const double pz)
        : e_(e), px_(px), py_(py), pz_(pz) {}

    double mag2() const { return e_ * e_ - px_ * px_ - py_ * py_ - pz_ * pz_; }

    FourMomentum operator-() const {
        return FourMomentum(-e_, -px_, -py_, -pz_);
    }

    friend FourMomentum operator+(FourMomentum lhs, const FourMomentum &rhs) {
        lhs.e_ += rhs.e_;
        lhs.px_ += rhs.px_;
        lhs.py_ += rhs.py_;
        lhs.pz_ += rhs.pz_;
        return lhs;
    }

    friend FourMomentum operator-(FourMomentum lhs, const FourMomentum &rhs) {
        lhs.e_ -= rhs.e_;
        lhs.px_ -= rhs.px_;
        lhs.py_ -= rhs.py_;
        lhs.pz_ -= rhs.pz_;
        return lhs;
    }

    friend std::ostream &operator<<(std::ostream &os, const FourMomentum &p);
};

/**
 *  Particle momenta of 2 --> 2 process at the CM frame.
 *
 *  pa pb --> pc pd
 *
 *  The initial particles are massless and final-state particles are identical.
 */
class CM22 {
private:
    double s_, mh2_, e_;
    double costh_, sinth_;
    double beta_;
    double pT_, pL_;

public:
    CM22() = delete;
    CM22(const double s, const double mh, const double costh)
        : s_(s), mh2_(mh * mh), e_(std::sqrt(s) / 2.0), costh_(costh) {
        init();
    }

    double shat() const { return s_; }
    double mhh() const { return std::sqrt(s_); }
    double mh2() const { return mh2_; }
    double pT() const { return std::abs(pT_); }

    FourMomentum pa() const;
    FourMomentum pb() const;
    FourMomentum pc() const;
    FourMomentum pd() const;

private:
    void init();
};
}  // namespace mcggh

#endif  // SRC_KINEMATICS_H_
