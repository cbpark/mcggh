#include "utils.h"
#include <random>

namespace mcggh {
double getRandom() {
    std::random_device rd;
    std::mt19937_64 gen(rd());  // mersenne_twistor_engine
    std::uniform_real_distribution<double> dr(0.0, 1.0);
    return dr(gen);
}
}  // namespace mcggh
