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

inline void Add(double* source, double* destination, int num_samples,
                double volume) {
  --source;
  --destination;
  do { *++destination += *++source * volume; } while (--num_samples);
}

inline void Multiply(double* source, int num_samples, double multiplier) {
  --source;
  do { *++source *= multiplier; } while (--num_samples);
}

inline void MoveMultiply( double* source, double* destination, int num_samples,
                          double multiplier) {
  --source;
  --destination;
  do { *++destination = *++source*multiplier; } while (--num_samples);
}

inline void Move( double* source, double* destination, int num_samples) {
  std::memcpy(destination, source, num_samples*sizeof(*source));
}

} // namespace dsp
} // namespace utility
} // namespace construct

#endif
