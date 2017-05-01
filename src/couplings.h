/*
 *  Copyright (C) 2017 Chan Beom Park <cbpark@gmail.com>
 *
 *  This file is part of MCGGH, which is released under the GNU General
 *  Public License. See file LICENSE in the top directory of this project or
 *  go to <http://www.gnu.org/licenses/> for full license details.
 */

#ifndef SRC_COUPLINGS_H_
#define SRC_COUPLINGS_H_

namespace mcggh {
class HiggsCoupl {
private:
    double ctri_t_, cbox_t_;
    double ctri_b_, cbox_b_;

public:
    HiggsCoupl() = delete;
    HiggsCoupl(const double s, const double mh, const double xi_lambda,
               const double xi_t, const double xi_b, const double ghhtt,
               const double ghhbb) {
        init(s, mh, xi_lambda, xi_t, xi_b, ghhtt, ghhbb);
    }

private:
    void init(const double s, const double mh, const double xi_lambda,
              const double xi_t, const double xi_b, const double ghhtt,
              const double ghhbb);
};
}  // namespace mcggh

#endif  // SRC_COUPLINGS_H_
