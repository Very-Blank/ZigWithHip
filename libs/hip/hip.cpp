#include "hip.h"

#include <hip/hip_runtime.h>

uint32_t add(uint32_t a, uint32_t b) { return a + b; }

uint32_t createHipStream(HipStream *stream) {
  hipStream_t hip_stream = nullptr;
  const hipError_t error = hipStreamCreate(&hip_stream);
  if (error != hipSuccess) {
    return 1;
  }

  *stream = (void *)hip_stream;

  return 0;
}

void destroyHipStream(HipStream stream) {
  static_cast<void>(hipStreamDestroy((hipStream_t)stream));
}
