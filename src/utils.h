/*
 *  Copyright (C) 2017 Chan Beom Park <cbpark@gmail.com>
 *
 *  This file is part of MCGGH, which is released under the GNU General
 *  Public License. See file LICENSE in the top directory of this project or
 *  go to <http://www.gnu.org/licenses/> for full license details.
 */

#ifndef SRC_UTILS_H_
#define SRC_UTILS_H_

#include <iostream>

namespace mcggh {
inline void printProgress(const int i, const int N) {
    std::cout << "progress: " << i * 100.0 / N << "%\r" << std::flush;
}
double getRandom();
}  // namespace mcggh

#endif  // SRC_UTILS_H_
