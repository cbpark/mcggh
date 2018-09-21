/*
 *  Copyright (C) 2017 Chan Beom Park <cbpark@gmail.com>
 *
 *  This file is part of mcggh, which is released under the GNU General
 *  Public License. See file LICENSE in the top directory of this project or
 *  go to <http://www.gnu.org/licenses/> for full license details.
 */

#ifndef SRC_GGH2_RESULT_H_
#define SRC_GGH2_RESULT_H_

#include <ostream>

namespace mcggh {
class Result {
private:
    double mhh_, pT_, dR_;

public:
    Result() = delete;
    Result(const double mhh, const double pT, const double dR)
        : mhh_{mhh}, pT_{pT}, dR_{dR} {}

    double mhh() const { return mhh_; }
    double pT() const { return pT_; }
    double dR() const { return dR_; }

    friend std::ostream &operator<<(std::ostream &os, const Result &re);
};
}  // namespace mcggh

#endif  // SRC_GGH2_RESULT_H_
