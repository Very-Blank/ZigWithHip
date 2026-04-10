#ifndef HIP
#define HIP

#include <stdint.h>

typedef void *HipStream;

// This is a in between for real hip errors and zig errors.
typedef enum HipError : uint32_t {
  hip_success = 0, ///< Successful completion.
  hip_error_invalid_value =
      1, ///< One or more of the parameters passed to the API
         ///< call is NULL or not in an acceptable range.
  hip_error_out_of_memory = 2,   ///< out of memory range.
  hip_error_not_initialized = 3, ///< Invalid not initialized
  hip_error_deinitialized = 4,   ///< Deinitialized
  hip_error_profiler_disabled = 5,
  hip_error_profiler_not_initialized = 6,
  hip_error_profiler_already_started = 7,
  hip_error_profiler_already_stopped = 8,
  hip_error_invalid_configuration = 9,     ///< Invalide configuration
  hip_error_invalid_pitch_value = 12,      ///< Invalid pitch value
  hip_error_invalid_symbol = 13,           ///< Invalid symbol
  hip_error_invalid_device_pointer = 17,   ///< Invalid Device Pointer
  hip_error_invalid_memcpy_direction = 21, ///< Invalid memory copy direction
  hip_error_insufficient_driver = 35,
  hip_error_missing_configuration = 52,
  hip_error_prior_launch_failure = 53,
  hip_error_invalid_device_function = 98, ///< Invalid device function
  hip_error_no_device = 100, ///< Call to hipGetDeviceCount returned 0 devices
  hip_error_invalid_device =
      101, ///< DeviceID must be in range from 0 to compute-devices.
  hip_error_invalid_image = 200,   ///< Invalid image
  hip_error_invalid_context = 201, ///< Produced when input context is invalid.
  hip_error_context_already_current = 202,
  hip_error_map_failed = 205,
  hip_error_unmap_failed = 206,
  hip_error_array_is_mapped = 207,
  hip_error_already_mapped = 208,
  hip_error_no_binary_for_gpu = 209,
  hip_error_already_acquired = 210,
  hip_error_not_mapped = 211,
  hip_error_not_mapped_as_array = 212,
  hip_error_not_mapped_as_pointer = 213,
  hip_error_e_c_c_not_correctable = 214,
  hip_error_unsupported_limit = 215,      ///< Unsupported limit
  hip_error_context_already_in_use = 216, ///< The context is already in use
  hip_error_peer_access_unsupported = 217,
  hip_error_invalid_kernel_file =
      218, ///< In CUDA DRV, it is CUDA_ERROR_INVALID_PTX
  hip_error_invalid_graphics_context = 219,
  hip_error_invalid_source = 300, ///< Invalid source.
  hip_error_file_not_found = 301, ///< the file is not found.
  hip_error_shared_object_symbol_not_found = 302,
  hip_error_shared_object_init_failed =
      303,                          ///< Failed to initialize shared object.
  hip_error_operating_system = 304, ///< Not the correct operating system
  hip_error_invalid_handle = 400,   ///< Invalide handle
  hip_error_illegal_state = 401, ///< Resource required is not in a valid state
                                 ///< to perform operation.
  hip_error_not_found = 500,     ///< Not found
  hip_error_not_ready =
      600, ///< Indicates that asynchronous operations enqueued earlier are
           ///< not ready.  This is not actually an error, but is used to
           ///< distinguish from hipSuccess (which indicates completion). APIs
           ///< that return this error include hipEventQuery and
           ///< hipStreamQuery.
  hip_error_illegal_address = 700,
  hip_error_launch_out_of_resources = 701, ///< Out of resources error.
  hip_error_launch_time_out = 702,         ///< Timeout for the launch.
  hip_error_peer_access_already_enabled =
      704, ///< Peer access was already enabled
           ///< from the current device.
  hip_error_peer_access_not_enabled =
      705, ///< Peer access was never enabled from the current device.
  hip_error_set_on_active_process = 708, ///< The process is active.
  hip_error_context_is_destroyed = 709,  ///< The context is already destroyed
  hip_error_assert = 710, ///< Produced when the kernel calls assert.
  hip_error_host_memory_already_registered =
      712, ///< Produced when trying to lock
           ///< a page-locked memory.
  hip_error_host_memory_not_registered =
      713, ///< Produced when trying to unlock a
           ///< non-page-locked memory.
  hip_error_launch_failure =
      719, ///< An exception occurred on the device while executing a kernel.
  hip_error_cooperative_launch_too_large =
      720, ///< This error indicates that the number of blocks
           ///< launched per grid for a kernel that was launched
           ///< via cooperative launch APIs exceeds the maximum
           ///< number of allowed blocks for the current device.
  hip_error_not_supported =
      801, ///< Produced when the hip API is not supported/implemented
  hip_error_stream_capture_unsupported =
      900, ///< The operation is not permitted
           ///< when the stream is capturing.
  hip_error_stream_capture_invalidated =
      901, ///< The current capture sequence on the stream
           ///< has been invalidated due to a previous error.
  hip_error_stream_capture_merge =
      902, ///< The operation would have resulted in a merge of
           ///< two independent capture sequences.
  hip_error_stream_capture_unmatched =
      903, ///< The capture was not initiated in this stream.
  hip_error_stream_capture_unjoined =
      904, ///< The capture sequence contains a fork that was not
           ///< joined to the primary stream.
  hip_error_stream_capture_isolation =
      905, ///< A dependency would have been created which crosses
           ///< the capture sequence boundary. Only implicit
           ///< in-stream ordering dependencies  are allowed
           ///< to cross the boundary
  hip_error_stream_capture_implicit =
      906, ///< The operation would have resulted in a disallowed
           ///< implicit dependency on a current capture sequence
           ///< from hipStreamLegacy.
  hip_error_captured_event =
      907, ///< The operation is not permitted on an event which was last
           ///< recorded in a capturing stream.
  hip_error_stream_capture_wrong_thread =
      908, ///< A stream capture sequence not initiated with
           ///< the hipStreamCaptureModeRelaxed argument to
           ///< hipStreamBeginCapture was passed to
           ///< hipStreamEndCapture in a different thread.
  hip_error_graph_exec_update_failure =
      910, ///< This error indicates that the graph update
           ///< not performed because it included changes which
           ///< violated constraintsspecific to instantiated graph
           ///< update.
  hip_error_invalid_channel_descriptor = 911, ///< Invalid channel descriptor.
  hip_error_invalid_texture = 912,            ///< Invalid texture.
  hip_error_unknown = 999,                    ///< Unknown error.
  // HSA Runtime Error Codes start here.
  hip_error_runtime_memory =
      1052, ///< HSA runtime memory call returned error.
            ///< Typically not seen in production systems.
  hip_error_runtime_other =
      1053, ///< HSA runtime call other than memory returned error.  Typically
            ///< not seen in production systems.
  hip_error_tbd ///< Marker that more error codes are needed.
} HipError;

#ifdef __cplusplus
extern "C" {
#endif

uint32_t add(uint32_t a, uint32_t b);

HipError createHipStream(HipStream *stream);
void destroyHipStream(HipStream stream);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // HIP
