/*
 *  Copyright (C) 2017 Chan Beom Park <cbpark@gmail.com>
 *
 *  This file is part of mcggh, which is released under the GNU General
 *  Public License. See file LICENSE in the top directory of this project or
 *  go to <http://www.gnu.org/licenses/> for full license details.
 */

#ifndef SRC_COUPLINGS_H_
#define SRC_COUPLINGS_H_

namespace mcggh {
enum class QuarkType { TOP, BOTTOM };

class HHCoupling {
private:
    double s_, mh_;
    double ctri_t_, cbox_t_;
    double ctri_b_, cbox_b_;

public:
    HHCoupling() = delete;
    HHCoupling(const double s, const double mh, const double xi_lambda,
               const double xi_t, const double xi_b, const double ghhtt,
               const double ghhbb)
        : s_{s}, mh_{mh} {
        init(xi_lambda, xi_t, xi_b, ghhtt, ghhbb);
    }

    double triangle(const QuarkType &typ) const;
    double box(const QuarkType &typ) const;

private:
    void init(const double xi_lambda, const double xi_t, const double xi_b,
              const double ghhtt, const double ghhbb);
};
}  // namespace mcggh

#endif  // SRC_COUPLINGS_H_
