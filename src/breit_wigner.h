/*
 *  Copyright (C) 2017 Chan Beom Park <cbpark@gmail.com>
 *
 *  This file is part of MCGGH, which is released under the GNU General
 *  Public License. See file LICENSE in the top directory of this project or
 *  go to <http://www.gnu.org/licenses/> for full license details.
 */

#ifndef SRC_BREIT_WIGNER_H_
#define SRC_BREIT_WIGNER_H_

namespace mcggh {
class Rho {
private:
    double m_, gamma_, s_;
    double rho1_, rho2_;

public:
    Rho() = delete;
    Rho(const double qmin, const double qmax, const double m,
        const double gamma, const double s)
        : m_{m}, gamma_{gamma}, s_{s} {
        init(qmin * qmin, qmax * qmax);
    }

    double delta() const { return rho2_ - rho1_; }

    double jacobian(const double val) const;

    /** \hat{s} = M * Gamma * tan(rho) + M^2 */
    double shat(const double val) const;

    friend double rhoValue(const Rho &rho);

private:
    void init(const double qmin2, const double qmax2);
};

double rhoValue(const Rho &rho);
}  // namespace mcggh

#endif  // SRC_BREIT_WIGNER_H_
