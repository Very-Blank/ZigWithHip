#ifndef HIP
#define HIP

#include <stdint.h>

typedef void *HipStream;

#ifdef __cplusplus
extern "C" {
#endif

uint32_t add(uint32_t a, uint32_t b);

uint32_t createHipStream(HipStream *stream);
void destroyHipStream(HipStream stream);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // HIP
