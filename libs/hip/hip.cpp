#include "hip.h"

#include <hip/hip_runtime.h>

uint32_t add(uint32_t a, uint32_t b) { return a + b; }

State createHipStream(HipStream *stream) {
  hipStream_t hip_stream = nullptr;
  const hipError_t error = hipStreamCreate(&hip_stream);
  if (error != hipSuccess) {
    return State::ERROR;
  }

  stream->pointer = (void *)hip_stream;

  return State::OK;
}

void destroyHipStream(HipStream *stream) {
  static_cast<void>(hipStreamDestroy((hipStream_t)stream->pointer));
}
