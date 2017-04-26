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
