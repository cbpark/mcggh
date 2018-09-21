/*
 *  Copyright (C) 2017 Chan Beom Park <cbpark@gmail.com>
 *
 *  This file is part of mcggh, which is released under the GNU General
 *  Public License. See file LICENSE in the top directory of this project or
 *  go to <http://www.gnu.org/licenses/> for full license details.
 */

#include "ggh2_result.h"
#include <iomanip>
#include <ostream>

namespace mcggh {
std::ostream &operator<<(std::ostream &os, const Result &re) {
    using namespace std;

    os << right << fixed << setw(10) << setprecision(3) << re.mhh_ << setw(13)
       << setprecision(3) << re.pT_ << setw(11) << setprecision(3) << re.dR_;
    return os;
}
}  // namespace mcggh
