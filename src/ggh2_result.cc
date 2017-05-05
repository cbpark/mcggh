/*
 *  Copyright (C) 2017 Chan Beom Park <cbpark@gmail.com>
 *
 *  This file is part of MCGGH, which is released under the GNU General
 *  Public License. See file LICENSE in the top directory of this project or
 *  go to <http://www.gnu.org/licenses/> for full license details.
 */

#include "ggh2_result.h"
#include <iomanip>
#include <ostream>

namespace mcggh {
std::ostream &operator<<(std::ostream &os, const Result &re) {
    os << std::right << std::fixed << std::setw(10) << std::setprecision(3)
       << re.mhh_ << std::setw(13) << std::setprecision(3) << re.pT_;
    return os;
}
}  // namespace mcggh
