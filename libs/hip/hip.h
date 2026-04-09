#ifndef HIP
#define HIP

#include <stdint.h>

typedef struct HipStream {
  void *pointer;
} HipStream;

enum State {
  OK,
  ERROR,
};

#ifdef __cplusplus
extern "C" {
#endif

uint32_t add(uint32_t a, uint32_t b);

enum State createHipStream(HipStream *stream);
void destroyHipStream(HipStream *stream);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // HIP
