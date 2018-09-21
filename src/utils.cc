/*
 *  Copyright (C) 2017 Chan Beom Park <cbpark@gmail.com>
 *
 *  This file is part of mcggh, which is released under the GNU General
 *  Public License. See file LICENSE in the top directory of this project or
 *  go to <http://www.gnu.org/licenses/> for full license details.
 */

#include "utils.h"
#include <random>

namespace mcggh {
double getRandom() {
    static std::random_device rd;
    static std::mt19937_64 gen{rd()};  // mersenne_twistor_engine
    static std::uniform_real_distribution<double> dr{0.0, 1.0};
    return dr(gen);
}
}  // namespace mcggh
