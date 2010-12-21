#ifndef CONSTRUCT_UTILITY_DSP_H_
#define CONSTRUCT_UTILITY_DSP_H_

#include <cstring>
#include <cmath>

namespace construct {
namespace utility {
namespace dsp {

inline void Clear(double* buffer, int num_samples) {
  std::memset(buffer, 0.0, num_samples*sizeof(*buffer));
}

} // namespace dsp
} // namespace utility
} // namespace construct

#endif
