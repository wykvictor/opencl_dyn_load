/*
 * Copyright (C) 2010 - Alexandru Gagniuc - <mr.nuke.me@gmail.com>
 * This file is part of ElectroMag.
 *
 * ElectroMag is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * ElectroMag is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 *  along with ElectroMag.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef _OPENCL_DYN_LOAD_H
#define _OPENCL_DYN_LOAD_H

#ifdef __APPLE__
#include <OpenCL/cl_platform.h>
#else
#include "cl_platform.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

/**************************************************************************/

typedef struct _cl_platform_id *cl_platform_id;
typedef struct _cl_device_id *cl_device_id;
typedef struct _cl_context *cl_context;
typedef struct _cl_command_queue *cl_command_queue;
typedef struct _cl_mem *cl_mem;
typedef struct _cl_event *cl_event;

/* WARNING!  Unlike cl_ types in cl_platform.h, cl_bool is not guaranteed to
 *be the same size as the bool in kernels. */
typedef cl_uint cl_bool;
typedef cl_ulong cl_bitfield;
typedef cl_bitfield cl_device_type;
typedef cl_uint cl_platform_info;
typedef cl_uint cl_device_info;
typedef intptr_t cl_context_properties;

/**************************************************************************/

/* cl_platform_info */
#define CL_PLATFORM_NAME 0x0902

/* cl_device_type - bitfield */
#define CL_DEVICE_TYPE_GPU (1 << 2)

/* cl_device_info */
#define CL_DEVICE_MAX_COMPUTE_UNITS 0x1002
#define CL_DEVICE_MAX_CLOCK_FREQUENCY 0x100C
#define CL_DEVICE_EXTENSIONS 0x1030

/* cl_context_info + cl_context_properties */
#define CL_CONTEXT_PLATFORM 0x1084

/* Error Codes */
#define CL_SUCCESS 0
#define CL_DEVICE_NOT_FOUND -1
#define CL_DEVICE_NOT_AVAILABLE -2

/* cl_bool */
#define CL_FALSE 0
#define CL_TRUE 1

/**************************************************************************/

// Platform API
typedef CL_API_ENTRY cl_int CL_API_CALL
__clGetPlatformIDs(cl_uint /* num_entries */, cl_platform_id * /* platforms */,
                   cl_uint * /* num_platforms */) CL_API_SUFFIX__VERSION_1_0;

typedef CL_API_ENTRY cl_int CL_API_CALL
__clGetPlatformInfo(cl_platform_id /* platform */, cl_platform_info /* param_name */,
                    size_t /* param_value_size */, void * /* param_value */,
                    size_t * /* param_value_size_ret */) CL_API_SUFFIX__VERSION_1_0;

// Device APIs
typedef CL_API_ENTRY cl_int CL_API_CALL
__clGetDeviceIDs(cl_platform_id /* platform */, cl_device_type /* device_type */,
                 cl_uint /* num_entries */, cl_device_id * /* devices */,
                 cl_uint * /* num_devices */) CL_API_SUFFIX__VERSION_1_0;

typedef CL_API_ENTRY cl_int CL_API_CALL
__clGetDeviceInfo(cl_device_id /* device */, cl_device_info /* param_name */,
                  size_t /* param_value_size */, void * /* param_value */,
                  size_t * /* param_value_size_ret */) CL_API_SUFFIX__VERSION_1_0;

typedef CL_API_ENTRY cl_context CL_API_CALL __clCreateContextFromType(
    const cl_context_properties * /* properties */, cl_device_type /* device_type */,
    void (*pfn_notify)(const char *, const void *, size_t, void *) /* pfn_notify */,
    void * /* user_data */, cl_int * /* errcode_ret */) CL_API_SUFFIX__VERSION_1_0;

#ifdef CL_USE_DEPRECATED_OPENCL_1_0_APIS
#error CL_USE_DEPRECATED_OPENCL_1_0_APIS is defined. These APIs are unsupported in OpenCL 1.1! by dynamic linking
#endif /* CL_USE_DEPRECATED_OPENCL_1_0_APIS */

typedef CL_API_ENTRY cl_int CL_API_CALL
    __clFinish(cl_command_queue /* command_queue */) CL_API_SUFFIX__VERSION_1_0;

// Enqueued Commands APIs
typedef CL_API_ENTRY cl_int CL_API_CALL
__clEnqueueReadBuffer(cl_command_queue /* command_queue */, cl_mem /* buffer */,
                      cl_bool /* blocking_read */, size_t /* offset */, size_t /* cb */,
                      void * /* ptr */, cl_uint /* num_events_in_wait_list */,
                      const cl_event * /* event_wait_list */,
                      cl_event * /* event */) CL_API_SUFFIX__VERSION_1_0;

typedef CL_API_ENTRY cl_int CL_API_CALL
__clEnqueueReadBufferRect(cl_command_queue /* command_queue */, cl_mem /* buffer */,
                          cl_bool /* blocking_read */, const size_t * /* buffer_origin */,
                          const size_t * /* host_origin */, const size_t * /* region */,
                          size_t /* buffer_row_pitch */, size_t /* buffer_slice_pitch */,
                          size_t /* host_row_pitch */, size_t /* host_slice_pitch */,
                          void * /* ptr */, cl_uint /* num_events_in_wait_list */,
                          const cl_event * /* event_wait_list */,
                          cl_event * /* event */) CL_API_SUFFIX__VERSION_1_1;

extern __clFinish *clFinish;
extern __clEnqueueReadBuffer *clEnqueueReadBuffer;
extern __clEnqueueReadBufferRect *clEnqueueReadBufferRect;
extern __clGetPlatformIDs *clGetPlatformIDs;
extern __clGetPlatformInfo *clGetPlatformInfo;
extern __clGetDeviceIDs *clGetDeviceIDs;
extern __clGetDeviceInfo *clGetDeviceInfo;
extern __clCreateContextFromType *clCreateContextFromType;

/// Loads the OpenCL library if available
///
/// This function must be called prior to calling anu other cl*() function
/// @return Returns CL_DEVICE_NOT_AVAILABLE if the OpenCL Library is not found
/// @return CL_DEVICE_NOT_AVAILABLE  if a library function is not found.
/// @return and CL_SUCCESS if all modules are loaded succesfully.
extern cl_int clLibLoad();

#ifdef __cplusplus
}
#endif

#endif /* _OPENCL_DYN_LOAD_H */
