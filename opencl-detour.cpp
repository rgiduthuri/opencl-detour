// Source: https://github.com/rgiduthuri/opencl-detour
// Author: Radhakrishna Giduthuri
// Date: Aug 26, 2017

#ifndef OPENCL_TRACE_ENV_NAME
#define OPENCL_TRACE_ENV_NAME "OPENCL_DUMP_FLAGS"
#endif

#ifndef OPENCL_TRACE_LIBRARY
#if defined(_WIN32)
#define OPENCL_TRACE_LIBRARY "OpenCL.dll"
#elif defined(__APPLE__)
#define OPENCL_TRACE_LIBRARY "/System/Library/Frameworks/OpenCL.framework/Versions/A/OpenCL"
#else
#define OPENCL_TRACE_LIBRARY "/opt/rocm/opencl/lib/x86_64/libOpenCL.so.1"
#endif
#endif

#if defined(__APPLE__)
#include <opencl.h>
#else
#include <CL/cl.h>
#endif

#include <stdio.h>
#if defined(_WIN32)
#include <windows.h>
#define GetFunctionAddr(h,name) GetProcAddress(h,name)
#else
#include <string.h>
#include <dlfcn.h>
#define GetFunctionAddr(h,name) dlsym(h,name)
#endif

#ifdef __APPLE__
#define FMTU64 "%llu"
#else
#define FMTU64 "%lu"
#endif

#ifdef __cplusplus
extern "C" {
#endif

typedef CL_API_ENTRY cl_int CL_API_CALL
__clGetPlatformIDs(cl_uint          /* num_entries */,
                 cl_platform_id * /* platforms */,
                 cl_uint *        /* num_platforms */);

typedef CL_API_ENTRY cl_int CL_API_CALL
__clGetPlatformInfo(cl_platform_id   /* platform */,
                  cl_platform_info /* param_name */,
                  size_t           /* param_value_size */,
                  void *           /* param_value */,
                  size_t *         /* param_value_size_ret */);

typedef CL_API_ENTRY cl_int CL_API_CALL
__clGetDeviceIDs(cl_platform_id   /* platform */,
               cl_device_type   /* device_type */,
               cl_uint          /* num_entries */,
               cl_device_id *   /* devices */,
               cl_uint *        /* num_devices */);

typedef CL_API_ENTRY cl_int CL_API_CALL
__clGetDeviceInfo(cl_device_id    /* device */,
                cl_device_info  /* param_name */,
                size_t          /* param_value_size */,
                void *          /* param_value */,
                size_t *        /* param_value_size_ret */);

typedef CL_API_ENTRY cl_int CL_API_CALL
__clCreateSubDevices(cl_device_id                         /* in_device */,
                   const cl_device_partition_property * /* properties */,
                   cl_uint                              /* num_devices */,
                   cl_device_id *                       /* out_devices */,
                   cl_uint *                            /* num_devices_ret */);

typedef CL_API_ENTRY cl_int CL_API_CALL
__clRetainDevice(cl_device_id /* device */);

typedef CL_API_ENTRY cl_int CL_API_CALL
__clReleaseDevice(cl_device_id /* device */);

typedef CL_API_ENTRY cl_context CL_API_CALL
__clCreateContext(const cl_context_properties * /* properties */,
                cl_uint                 /* num_devices */,
                const cl_device_id *    /* devices */,
                void (CL_CALLBACK * /* pfn_notify */)(const char *, const void *, size_t, void *),
                void *                  /* user_data */,
                cl_int *                /* errcode_ret */);

typedef CL_API_ENTRY cl_context CL_API_CALL
__clCreateContextFromType(const cl_context_properties * /* properties */,
                        cl_device_type          /* device_type */,
                        void (CL_CALLBACK *     /* pfn_notify*/ )(const char *, const void *, size_t, void *),
                        void *                  /* user_data */,
                        cl_int *                /* errcode_ret */);

typedef CL_API_ENTRY cl_int CL_API_CALL
__clRetainContext(cl_context /* context */);

typedef CL_API_ENTRY cl_int CL_API_CALL
__clReleaseContext(cl_context /* context */);

typedef CL_API_ENTRY cl_int CL_API_CALL
__clGetContextInfo(cl_context         /* context */,
                 cl_context_info    /* param_name */,
                 size_t             /* param_value_size */,
                 void *             /* param_value */,
                 size_t *           /* param_value_size_ret */);

typedef CL_API_ENTRY cl_command_queue CL_API_CALL
__clCreateCommandQueue(cl_context                     /* context */,
                     cl_device_id                   /* device */,
                     cl_command_queue_properties    /* properties */,
                     cl_int *                       /* errcode_ret */);

#if defined(CL_VERSION_2_0)
typedef CL_API_ENTRY cl_command_queue CL_API_CALL
__clCreateCommandQueueWithProperties(cl_context               /* context */,
                                   cl_device_id             /* device */,
                                   const cl_queue_properties *    /* properties */,
                                   cl_int *                 /* errcode_ret */);
#endif

typedef CL_API_ENTRY cl_int CL_API_CALL
__clRetainCommandQueue(cl_command_queue /* command_queue */);

typedef CL_API_ENTRY cl_int CL_API_CALL
__clReleaseCommandQueue(cl_command_queue /* command_queue */);

typedef CL_API_ENTRY cl_int CL_API_CALL
__clGetCommandQueueInfo(cl_command_queue      /* command_queue */,
                      cl_command_queue_info /* param_name */,
                      size_t                /* param_value_size */,
                      void *                /* param_value */,
                      size_t *              /* param_value_size_ret */);

typedef CL_API_ENTRY cl_mem CL_API_CALL
__clCreateBuffer(cl_context   /* context */,
               cl_mem_flags /* flags */,
               size_t       /* size */,
               void *       /* host_ptr */,
               cl_int *     /* errcode_ret */);

typedef CL_API_ENTRY cl_mem CL_API_CALL
__clCreateSubBuffer(cl_mem                   /* buffer */,
                  cl_mem_flags             /* flags */,
                  cl_buffer_create_type    /* buffer_create_type */,
                  const void *             /* buffer_create_info */,
                  cl_int *                 /* errcode_ret */);

typedef CL_API_ENTRY cl_mem CL_API_CALL
__clCreateImage(cl_context              /* context */,
              cl_mem_flags            /* flags */,
              const cl_image_format * /* image_format */,
              const cl_image_desc *   /* image_desc */,
              void *                  /* host_ptr */,
              cl_int *                /* errcode_ret */);

typedef CL_API_ENTRY cl_int CL_API_CALL
__clRetainMemObject(cl_mem /* memobj */);

typedef CL_API_ENTRY cl_int CL_API_CALL
__clReleaseMemObject(cl_mem /* memobj */);

typedef CL_API_ENTRY cl_int CL_API_CALL
__clGetSupportedImageFormats(cl_context           /* context */,
                           cl_mem_flags         /* flags */,
                           cl_mem_object_type   /* image_type */,
                           cl_uint              /* num_entries */,
                           cl_image_format *    /* image_formats */,
                           cl_uint *            /* num_image_formats */);

typedef CL_API_ENTRY cl_int CL_API_CALL
__clGetMemObjectInfo(cl_mem           /* memobj */,
                   cl_mem_info      /* param_name */,
                   size_t           /* param_value_size */,
                   void *           /* param_value */,
                   size_t *         /* param_value_size_ret */);

typedef CL_API_ENTRY cl_int CL_API_CALL
__clGetImageInfo(cl_mem           /* image */,
               cl_image_info    /* param_name */,
               size_t           /* param_value_size */,
               void *           /* param_value */,
               size_t *         /* param_value_size_ret */);

typedef CL_API_ENTRY cl_int CL_API_CALL
__clSetMemObjectDestructorCallback(  cl_mem /* memobj */,
                                    void (CL_CALLBACK * /*pfn_notify*/)( cl_mem /* memobj */, void* /*user_data*/),
                                    void * /*user_data */ )            ;

typedef CL_API_ENTRY cl_sampler CL_API_CALL
__clCreateSampler(cl_context          /* context */,
                cl_bool             /* normalized_coords */,
                cl_addressing_mode  /* addressing_mode */,
                cl_filter_mode      /* filter_mode */,
                cl_int *            /* errcode_ret */);

typedef CL_API_ENTRY cl_int CL_API_CALL
__clRetainSampler(cl_sampler /* sampler */);

typedef CL_API_ENTRY cl_int CL_API_CALL
__clReleaseSampler(cl_sampler /* sampler */);

typedef CL_API_ENTRY cl_int CL_API_CALL
__clGetSamplerInfo(cl_sampler         /* sampler */,
                 cl_sampler_info    /* param_name */,
                 size_t             /* param_value_size */,
                 void *             /* param_value */,
                 size_t *           /* param_value_size_ret */);

typedef CL_API_ENTRY cl_program CL_API_CALL
__clCreateProgramWithSource(cl_context        /* context */,
                          cl_uint           /* count */,
                          const char **     /* strings */,
                          const size_t *    /* lengths */,
                          cl_int *          /* errcode_ret */);

typedef CL_API_ENTRY cl_program CL_API_CALL
__clCreateProgramWithBinary(cl_context                     /* context */,
                          cl_uint                        /* num_devices */,
                          const cl_device_id *           /* device_list */,
                          const size_t *                 /* lengths */,
                          const unsigned char **         /* binaries */,
                          cl_int *                       /* binary_status */,
                          cl_int *                       /* errcode_ret */);

typedef CL_API_ENTRY cl_program CL_API_CALL
__clCreateProgramWithBuiltInKernels(cl_context            /* context */,
                                  cl_uint               /* num_devices */,
                                  const cl_device_id *  /* device_list */,
                                  const char *          /* kernel_names */,
                                  cl_int *              /* errcode_ret */);

typedef CL_API_ENTRY cl_int CL_API_CALL
__clRetainProgram(cl_program /* program */);

typedef CL_API_ENTRY cl_int CL_API_CALL
__clReleaseProgram(cl_program /* program */);

typedef CL_API_ENTRY cl_int CL_API_CALL
__clBuildProgram(cl_program           /* program */,
               cl_uint              /* num_devices */,
               const cl_device_id * /* device_list */,
               const char *         /* options */,
               void (CL_CALLBACK *  /* pfn_notify */)(cl_program /* program */, void * /* user_data */),
               void *               /* user_data */);

typedef CL_API_ENTRY cl_int CL_API_CALL
__clCompileProgram(cl_program           /* program */,
                 cl_uint              /* num_devices */,
                 const cl_device_id * /* device_list */,
                 const char *         /* options */,
                 cl_uint              /* num_input_headers */,
                 const cl_program *   /* input_headers */,
                 const char **        /* header_include_names */,
                 void (CL_CALLBACK *  /* pfn_notify */)(cl_program /* program */, void * /* user_data */),
                 void *               /* user_data */);

typedef CL_API_ENTRY cl_program CL_API_CALL
__clLinkProgram(cl_context           /* context */,
              cl_uint              /* num_devices */,
              const cl_device_id * /* device_list */,
              const char *         /* options */,
              cl_uint              /* num_input_programs */,
              const cl_program *   /* input_programs */,
              void (CL_CALLBACK *  /* pfn_notify */)(cl_program /* program */, void * /* user_data */),
              void *               /* user_data */,
              cl_int *             /* errcode_ret */ );

typedef CL_API_ENTRY cl_int CL_API_CALL
__clUnloadPlatformCompiler(cl_platform_id /* platform */);

typedef CL_API_ENTRY cl_int CL_API_CALL
__clGetProgramInfo(cl_program         /* program */,
                 cl_program_info    /* param_name */,
                 size_t             /* param_value_size */,
                 void *             /* param_value */,
                 size_t *           /* param_value_size_ret */);

typedef CL_API_ENTRY cl_int CL_API_CALL
__clGetProgramBuildInfo(cl_program            /* program */,
                      cl_device_id          /* device */,
                      cl_program_build_info /* param_name */,
                      size_t                /* param_value_size */,
                      void *                /* param_value */,
                      size_t *              /* param_value_size_ret */);

typedef CL_API_ENTRY cl_kernel CL_API_CALL
__clCreateKernel(cl_program      /* program */,
               const char *    /* kernel_name */,
               cl_int *        /* errcode_ret */);

typedef CL_API_ENTRY cl_int CL_API_CALL
__clCreateKernelsInProgram(cl_program     /* program */,
                         cl_uint        /* num_kernels */,
                         cl_kernel *    /* kernels */,
                         cl_uint *      /* num_kernels_ret */);

typedef CL_API_ENTRY cl_int CL_API_CALL
__clRetainKernel(cl_kernel    /* kernel */);

typedef CL_API_ENTRY cl_int CL_API_CALL
__clReleaseKernel(cl_kernel   /* kernel */);

typedef CL_API_ENTRY cl_int CL_API_CALL
__clSetKernelArg(cl_kernel    /* kernel */,
               cl_uint      /* arg_index */,
               size_t       /* arg_size */,
               const void * /* arg_value */);

typedef CL_API_ENTRY cl_int CL_API_CALL
__clGetKernelInfo(cl_kernel       /* kernel */,
                cl_kernel_info  /* param_name */,
                size_t          /* param_value_size */,
                void *          /* param_value */,
                size_t *        /* param_value_size_ret */);

typedef CL_API_ENTRY cl_int CL_API_CALL
__clGetKernelArgInfo(cl_kernel       /* kernel */,
                   cl_uint         /* arg_indx */,
                   cl_kernel_arg_info  /* param_name */,
                   size_t          /* param_value_size */,
                   void *          /* param_value */,
                   size_t *        /* param_value_size_ret */);

typedef CL_API_ENTRY cl_int CL_API_CALL
__clGetKernelWorkGroupInfo(cl_kernel                  /* kernel */,
                         cl_device_id               /* device */,
                         cl_kernel_work_group_info  /* param_name */,
                         size_t                     /* param_value_size */,
                         void *                     /* param_value */,
                         size_t *                   /* param_value_size_ret */);

typedef CL_API_ENTRY cl_int CL_API_CALL
__clWaitForEvents(cl_uint             /* num_events */,
                const cl_event *    /* event_list */);

typedef CL_API_ENTRY cl_int CL_API_CALL
__clGetEventInfo(cl_event         /* event */,
               cl_event_info    /* param_name */,
               size_t           /* param_value_size */,
               void *           /* param_value */,
               size_t *         /* param_value_size_ret */);

typedef CL_API_ENTRY cl_event CL_API_CALL
__clCreateUserEvent(cl_context    /* context */,
                  cl_int *      /* errcode_ret */);

typedef CL_API_ENTRY cl_int CL_API_CALL
__clRetainEvent(cl_event /* event */);

typedef CL_API_ENTRY cl_int CL_API_CALL
__clReleaseEvent(cl_event /* event */);

typedef CL_API_ENTRY cl_int CL_API_CALL
__clSetUserEventStatus(cl_event   /* event */,
                     cl_int     /* execution_status */);

typedef CL_API_ENTRY cl_int CL_API_CALL
__clSetEventCallback( cl_event    /* event */,
                    cl_int      /* command_exec_callback_type */,
                    void (CL_CALLBACK * /* pfn_notify */)(cl_event, cl_int, void *),
                    void *      /* user_data */);

typedef CL_API_ENTRY cl_int CL_API_CALL
__clGetEventProfilingInfo(cl_event            /* event */,
                        cl_profiling_info   /* param_name */,
                        size_t              /* param_value_size */,
                        void *              /* param_value */,
                        size_t *            /* param_value_size_ret */);

typedef CL_API_ENTRY cl_int CL_API_CALL
__clFlush(cl_command_queue /* command_queue */);

typedef CL_API_ENTRY cl_int CL_API_CALL
__clFinish(cl_command_queue /* command_queue */);

typedef CL_API_ENTRY cl_int CL_API_CALL
__clEnqueueReadBuffer(cl_command_queue    /* command_queue */,
                    cl_mem              /* buffer */,
                    cl_bool             /* blocking_read */,
                    size_t              /* offset */,
                    size_t              /* size */,
                    void *              /* ptr */,
                    cl_uint             /* num_events_in_wait_list */,
                    const cl_event *    /* event_wait_list */,
                    cl_event *          /* event */);

typedef CL_API_ENTRY cl_int CL_API_CALL
__clEnqueueReadBufferRect(cl_command_queue    /* command_queue */,
                        cl_mem              /* buffer */,
                        cl_bool             /* blocking_read */,
                        const size_t *      /* buffer_offset */,
                        const size_t *      /* host_offset */,
                        const size_t *      /* region */,
                        size_t              /* buffer_row_pitch */,
                        size_t              /* buffer_slice_pitch */,
                        size_t              /* host_row_pitch */,
                        size_t              /* host_slice_pitch */,
                        void *              /* ptr */,
                        cl_uint             /* num_events_in_wait_list */,
                        const cl_event *    /* event_wait_list */,
                        cl_event *          /* event */);

typedef CL_API_ENTRY cl_int CL_API_CALL
__clEnqueueWriteBuffer(cl_command_queue   /* command_queue */,
                     cl_mem             /* buffer */,
                     cl_bool            /* blocking_write */,
                     size_t             /* offset */,
                     size_t             /* size */,
                     const void *       /* ptr */,
                     cl_uint            /* num_events_in_wait_list */,
                     const cl_event *   /* event_wait_list */,
                     cl_event *         /* event */);

typedef CL_API_ENTRY cl_int CL_API_CALL
__clEnqueueWriteBufferRect(cl_command_queue    /* command_queue */,
                         cl_mem              /* buffer */,
                         cl_bool             /* blocking_write */,
                         const size_t *      /* buffer_offset */,
                         const size_t *      /* host_offset */,
                         const size_t *      /* region */,
                         size_t              /* buffer_row_pitch */,
                         size_t              /* buffer_slice_pitch */,
                         size_t              /* host_row_pitch */,
                         size_t              /* host_slice_pitch */,
                         const void *        /* ptr */,
                         cl_uint             /* num_events_in_wait_list */,
                         const cl_event *    /* event_wait_list */,
                         cl_event *          /* event */);

typedef CL_API_ENTRY cl_int CL_API_CALL
__clEnqueueFillBuffer(cl_command_queue   /* command_queue */,
                    cl_mem             /* buffer */,
                    const void *       /* pattern */,
                    size_t             /* pattern_size */,
                    size_t             /* offset */,
                    size_t             /* size */,
                    cl_uint            /* num_events_in_wait_list */,
                    const cl_event *   /* event_wait_list */,
                    cl_event *         /* event */);

typedef CL_API_ENTRY cl_int CL_API_CALL
__clEnqueueCopyBuffer(cl_command_queue    /* command_queue */,
                    cl_mem              /* src_buffer */,
                    cl_mem              /* dst_buffer */,
                    size_t              /* src_offset */,
                    size_t              /* dst_offset */,
                    size_t              /* size */,
                    cl_uint             /* num_events_in_wait_list */,
                    const cl_event *    /* event_wait_list */,
                    cl_event *          /* event */);

typedef CL_API_ENTRY cl_int CL_API_CALL
__clEnqueueCopyBufferRect(cl_command_queue    /* command_queue */,
                        cl_mem              /* src_buffer */,
                        cl_mem              /* dst_buffer */,
                        const size_t *      /* src_origin */,
                        const size_t *      /* dst_origin */,
                        const size_t *      /* region */,
                        size_t              /* src_row_pitch */,
                        size_t              /* src_slice_pitch */,
                        size_t              /* dst_row_pitch */,
                        size_t              /* dst_slice_pitch */,
                        cl_uint             /* num_events_in_wait_list */,
                        const cl_event *    /* event_wait_list */,
                        cl_event *          /* event */);

typedef CL_API_ENTRY cl_int CL_API_CALL
__clEnqueueReadImage(cl_command_queue     /* command_queue */,
                   cl_mem               /* image */,
                   cl_bool              /* blocking_read */,
                   const size_t *       /* origin[3] */,
                   const size_t *       /* region[3] */,
                   size_t               /* row_pitch */,
                   size_t               /* slice_pitch */,
                   void *               /* ptr */,
                   cl_uint              /* num_events_in_wait_list */,
                   const cl_event *     /* event_wait_list */,
                   cl_event *           /* event */);

typedef CL_API_ENTRY cl_int CL_API_CALL
__clEnqueueWriteImage(cl_command_queue    /* command_queue */,
                    cl_mem              /* image */,
                    cl_bool             /* blocking_write */,
                    const size_t *      /* origin[3] */,
                    const size_t *      /* region[3] */,
                    size_t              /* input_row_pitch */,
                    size_t              /* input_slice_pitch */,
                    const void *        /* ptr */,
                    cl_uint             /* num_events_in_wait_list */,
                    const cl_event *    /* event_wait_list */,
                    cl_event *          /* event */);

typedef CL_API_ENTRY cl_int CL_API_CALL
__clEnqueueFillImage(cl_command_queue   /* command_queue */,
                   cl_mem             /* image */,
                   const void *       /* fill_color */,
                   const size_t *     /* origin[3] */,
                   const size_t *     /* region[3] */,
                   cl_uint            /* num_events_in_wait_list */,
                   const cl_event *   /* event_wait_list */,
                   cl_event *         /* event */);

typedef CL_API_ENTRY cl_int CL_API_CALL
__clEnqueueCopyImage(cl_command_queue     /* command_queue */,
                   cl_mem               /* src_image */,
                   cl_mem               /* dst_image */,
                   const size_t *       /* src_origin[3] */,
                   const size_t *       /* dst_origin[3] */,
                   const size_t *       /* region[3] */,
                   cl_uint              /* num_events_in_wait_list */,
                   const cl_event *     /* event_wait_list */,
                   cl_event *           /* event */);

typedef CL_API_ENTRY cl_int CL_API_CALL
__clEnqueueCopyImageToBuffer(cl_command_queue /* command_queue */,
                           cl_mem           /* src_image */,
                           cl_mem           /* dst_buffer */,
                           const size_t *   /* src_origin[3] */,
                           const size_t *   /* region[3] */,
                           size_t           /* dst_offset */,
                           cl_uint          /* num_events_in_wait_list */,
                           const cl_event * /* event_wait_list */,
                           cl_event *       /* event */);

typedef CL_API_ENTRY cl_int CL_API_CALL
__clEnqueueCopyBufferToImage(cl_command_queue /* command_queue */,
                           cl_mem           /* src_buffer */,
                           cl_mem           /* dst_image */,
                           size_t           /* src_offset */,
                           const size_t *   /* dst_origin[3] */,
                           const size_t *   /* region[3] */,
                           cl_uint          /* num_events_in_wait_list */,
                           const cl_event * /* event_wait_list */,
                           cl_event *       /* event */);

typedef CL_API_ENTRY void * CL_API_CALL
__clEnqueueMapBuffer(cl_command_queue /* command_queue */,
                   cl_mem           /* buffer */,
                   cl_bool          /* blocking_map */,
                   cl_map_flags     /* map_flags */,
                   size_t           /* offset */,
                   size_t           /* size */,
                   cl_uint          /* num_events_in_wait_list */,
                   const cl_event * /* event_wait_list */,
                   cl_event *       /* event */,
                   cl_int *         /* errcode_ret */);

typedef CL_API_ENTRY void * CL_API_CALL
__clEnqueueMapImage(cl_command_queue  /* command_queue */,
                  cl_mem            /* image */,
                  cl_bool           /* blocking_map */,
                  cl_map_flags      /* map_flags */,
                  const size_t *    /* origin[3] */,
                  const size_t *    /* region[3] */,
                  size_t *          /* image_row_pitch */,
                  size_t *          /* image_slice_pitch */,
                  cl_uint           /* num_events_in_wait_list */,
                  const cl_event *  /* event_wait_list */,
                  cl_event *        /* event */,
                  cl_int *          /* errcode_ret */);

typedef CL_API_ENTRY cl_int CL_API_CALL
__clEnqueueUnmapMemObject(cl_command_queue /* command_queue */,
                        cl_mem           /* memobj */,
                        void *           /* mapped_ptr */,
                        cl_uint          /* num_events_in_wait_list */,
                        const cl_event *  /* event_wait_list */,
                        cl_event *        /* event */);

typedef CL_API_ENTRY cl_int CL_API_CALL
__clEnqueueMigrateMemObjects(cl_command_queue       /* command_queue */,
                           cl_uint                /* num_mem_objects */,
                           const cl_mem *         /* mem_objects */,
                           cl_mem_migration_flags /* flags */,
                           cl_uint                /* num_events_in_wait_list */,
                           const cl_event *       /* event_wait_list */,
                           cl_event *             /* event */);

typedef CL_API_ENTRY cl_int CL_API_CALL
__clEnqueueNDRangeKernel(cl_command_queue /* command_queue */,
                       cl_kernel        /* kernel */,
                       cl_uint          /* work_dim */,
                       const size_t *   /* global_work_offset */,
                       const size_t *   /* global_work_size */,
                       const size_t *   /* local_work_size */,
                       cl_uint          /* num_events_in_wait_list */,
                       const cl_event * /* event_wait_list */,
                       cl_event *       /* event */);

typedef CL_API_ENTRY cl_int CL_API_CALL
__clEnqueueTask(cl_command_queue  /* command_queue */,
              cl_kernel         /* kernel */,
              cl_uint           /* num_events_in_wait_list */,
              const cl_event *  /* event_wait_list */,
              cl_event *        /* event */);

typedef CL_API_ENTRY cl_int CL_API_CALL
__clEnqueueNativeKernel(cl_command_queue  /* command_queue */,
					  void (CL_CALLBACK * /*user_func*/)(void *),
                      void *            /* args */,
                      size_t            /* cb_args */,
                      cl_uint           /* num_mem_objects */,
                      const cl_mem *    /* mem_list */,
                      const void **     /* args_mem_loc */,
                      cl_uint           /* num_events_in_wait_list */,
                      const cl_event *  /* event_wait_list */,
                      cl_event *        /* event */);

typedef CL_API_ENTRY cl_int CL_API_CALL
__clEnqueueMarkerWithWaitList(cl_command_queue /* command_queue */,
                            cl_uint           /* num_events_in_wait_list */,
                            const cl_event *  /* event_wait_list */,
                            cl_event *        /* event */);

typedef CL_API_ENTRY cl_int CL_API_CALL
__clEnqueueBarrierWithWaitList(cl_command_queue /* command_queue */,
                             cl_uint           /* num_events_in_wait_list */,
                             const cl_event *  /* event_wait_list */,
                             cl_event *        /* event */);

typedef CL_API_ENTRY void * CL_API_CALL
__clGetExtensionFunctionAddressForPlatform(cl_platform_id /* platform */,
                                         const char *   /* func_name */);

typedef CL_API_ENTRY cl_mem CL_API_CALL
__clCreateImage2D(cl_context              /* context */,
                cl_mem_flags            /* flags */,
                const cl_image_format * /* image_format */,
                size_t                  /* image_width */,
                size_t                  /* image_height */,
                size_t                  /* image_row_pitch */,
                void *                  /* host_ptr */,
                cl_int *                /* errcode_ret */);

typedef CL_API_ENTRY cl_mem CL_API_CALL
__clCreateImage3D(cl_context              /* context */,
                cl_mem_flags            /* flags */,
                const cl_image_format * /* image_format */,
                size_t                  /* image_width */,
                size_t                  /* image_height */,
                size_t                  /* image_depth */,
                size_t                  /* image_row_pitch */,
                size_t                  /* image_slice_pitch */,
                void *                  /* host_ptr */,
                cl_int *                /* errcode_ret */);

typedef CL_API_ENTRY cl_int CL_API_CALL
__clEnqueueMarker(cl_command_queue    /* command_queue */,
                cl_event *          /* event */);

typedef CL_API_ENTRY cl_int CL_API_CALL
__clEnqueueWaitForEvents(cl_command_queue /* command_queue */,
                        cl_uint          /* num_events */,
                        const cl_event * /* event_list */);

typedef CL_API_ENTRY cl_int CL_API_CALL
__clEnqueueBarrier(cl_command_queue /* command_queue */);

typedef CL_API_ENTRY cl_int CL_API_CALL
__clUnloadCompiler(void);

typedef CL_API_ENTRY void * CL_API_CALL
__clGetExtensionFunctionAddress(const char * /* func_name */);


#ifdef __cplusplus
};
#endif

typedef struct {
#if defined(_WIN32)
    HMODULE h;
#else
    void * h;
#endif

    int dumpFlags;

    __clGetPlatformIDs                         * clGetPlatformIDs;
    __clGetPlatformInfo                        * clGetPlatformInfo;
    __clGetDeviceIDs                           * clGetDeviceIDs;
    __clGetDeviceInfo                          * clGetDeviceInfo;
    __clCreateSubDevices                       * clCreateSubDevices;
    __clRetainDevice                           * clRetainDevice;
    __clReleaseDevice                          * clReleaseDevice;
    __clCreateContext                          * clCreateContext;
    __clCreateContextFromType                  * clCreateContextFromType;
    __clRetainContext                          * clRetainContext;
    __clReleaseContext                         * clReleaseContext;
    __clGetContextInfo                         * clGetContextInfo;
    __clCreateCommandQueue                     * clCreateCommandQueue;
#if defined(CL_VERSION_2_0)
    __clCreateCommandQueueWithProperties       * clCreateCommandQueueWithProperties;
#endif
    __clRetainCommandQueue                     * clRetainCommandQueue;
    __clReleaseCommandQueue                    * clReleaseCommandQueue;
    __clGetCommandQueueInfo                    * clGetCommandQueueInfo;
    __clCreateBuffer                           * clCreateBuffer;
    __clCreateSubBuffer                        * clCreateSubBuffer;
    __clCreateImage                            * clCreateImage;
    __clRetainMemObject                        * clRetainMemObject;
    __clReleaseMemObject                       * clReleaseMemObject;
    __clGetSupportedImageFormats               * clGetSupportedImageFormats;
    __clGetMemObjectInfo                       * clGetMemObjectInfo;
    __clGetImageInfo                           * clGetImageInfo;
    __clSetMemObjectDestructorCallback         * clSetMemObjectDestructorCallback;
    __clCreateSampler                          * clCreateSampler;
    __clRetainSampler                          * clRetainSampler;
    __clReleaseSampler                         * clReleaseSampler;
    __clGetSamplerInfo                         * clGetSamplerInfo;
    __clCreateProgramWithSource                * clCreateProgramWithSource;
    __clCreateProgramWithBinary                * clCreateProgramWithBinary;
    __clCreateProgramWithBuiltInKernels        * clCreateProgramWithBuiltInKernels;
    __clRetainProgram                          * clRetainProgram;
    __clReleaseProgram                         * clReleaseProgram;
    __clBuildProgram                           * clBuildProgram;
    __clCompileProgram                         * clCompileProgram;
    __clLinkProgram                            * clLinkProgram;
    __clUnloadPlatformCompiler                 * clUnloadPlatformCompiler;
    __clGetProgramInfo                         * clGetProgramInfo;
    __clGetProgramBuildInfo                    * clGetProgramBuildInfo;
    __clCreateKernel                           * clCreateKernel;
    __clCreateKernelsInProgram                 * clCreateKernelsInProgram;
    __clRetainKernel                           * clRetainKernel;
    __clReleaseKernel                          * clReleaseKernel;
    __clSetKernelArg                           * clSetKernelArg;
    __clGetKernelInfo                          * clGetKernelInfo;
    __clGetKernelArgInfo                       * clGetKernelArgInfo;
    __clGetKernelWorkGroupInfo                 * clGetKernelWorkGroupInfo;
    __clWaitForEvents                          * clWaitForEvents;
    __clGetEventInfo                           * clGetEventInfo;
    __clCreateUserEvent                        * clCreateUserEvent;
    __clRetainEvent                            * clRetainEvent;
    __clReleaseEvent                           * clReleaseEvent;
    __clSetUserEventStatus                     * clSetUserEventStatus;
    __clSetEventCallback                       * clSetEventCallback;
    __clGetEventProfilingInfo                  * clGetEventProfilingInfo;
    __clFlush                                  * clFlush;
    __clFinish                                 * clFinish;
    __clEnqueueReadBuffer                      * clEnqueueReadBuffer;
    __clEnqueueReadBufferRect                  * clEnqueueReadBufferRect;
    __clEnqueueWriteBuffer                     * clEnqueueWriteBuffer;
    __clEnqueueWriteBufferRect                 * clEnqueueWriteBufferRect;
    __clEnqueueFillBuffer                      * clEnqueueFillBuffer;
    __clEnqueueCopyBuffer                      * clEnqueueCopyBuffer;
    __clEnqueueCopyBufferRect                  * clEnqueueCopyBufferRect;
    __clEnqueueReadImage                       * clEnqueueReadImage;
    __clEnqueueWriteImage                      * clEnqueueWriteImage;
    __clEnqueueFillImage                       * clEnqueueFillImage;
    __clEnqueueCopyImage                       * clEnqueueCopyImage;
    __clEnqueueCopyImageToBuffer               * clEnqueueCopyImageToBuffer;
    __clEnqueueCopyBufferToImage               * clEnqueueCopyBufferToImage;
    __clEnqueueMapBuffer                       * clEnqueueMapBuffer;
    __clEnqueueMapImage                        * clEnqueueMapImage;
    __clEnqueueUnmapMemObject                  * clEnqueueUnmapMemObject;
    __clEnqueueMigrateMemObjects               * clEnqueueMigrateMemObjects;
    __clEnqueueNDRangeKernel                   * clEnqueueNDRangeKernel;
    __clEnqueueTask                            * clEnqueueTask;
    __clEnqueueNativeKernel                    * clEnqueueNativeKernel;
    __clEnqueueMarkerWithWaitList              * clEnqueueMarkerWithWaitList;
    __clEnqueueBarrierWithWaitList             * clEnqueueBarrierWithWaitList;
    __clGetExtensionFunctionAddressForPlatform * clGetExtensionFunctionAddressForPlatform;
    __clCreateImage2D                          * clCreateImage2D;
    __clCreateImage3D                          * clCreateImage3D;
    __clEnqueueMarker                          * clEnqueueMarker;
    __clEnqueueWaitForEvents                   * clEnqueueWaitForEvents;
    __clEnqueueBarrier                         * clEnqueueBarrier;
    __clUnloadCompiler                         * clUnloadCompiler;
    __clGetExtensionFunctionAddress            * clGetExtensionFunctionAddress;

} OpenCLAPI;

static OpenCLAPI api = { 0 };

CL_API_ENTRY cl_int CL_API_CALL
clInit(void)
{
printf("LOADING ... %s\n", OPENCL_TRACE_LIBRARY);
#if defined(_WIN32)
    if((api.h = LoadLibrary(TEXT(OPENCL_TRACE_LIBRARY))) == NULL) return CL_INVALID_PLATFORM;
#else
    if((api.h = dlopen(OPENCL_TRACE_LIBRARY, RTLD_NOW)) == NULL) return CL_INVALID_PLATFORM;
#endif

#if defined(_WIN32)
    const char dumpFlags[64] = { 0 };
    GetEnvironmentVariableA(OPENCL_TRACE_ENV_NAME, dumpFlags, (DWORD)sizeof(dumpFlags));
#else
    const char * dumpFlags = getenv(OPENCL_TRACE_ENV_NAME);
#endif
    api.dumpFlags = dumpFlags ? atoi(dumpFlags) : 0;

    api.clGetPlatformIDs                         = (__clGetPlatformIDs                         *) GetFunctionAddr(api.h, "clGetPlatformIDs");
    api.clGetPlatformInfo                        = (__clGetPlatformInfo                        *) GetFunctionAddr(api.h, "clGetPlatformInfo");
    api.clGetDeviceIDs                           = (__clGetDeviceIDs                           *) GetFunctionAddr(api.h, "clGetDeviceIDs");
    api.clGetDeviceInfo                          = (__clGetDeviceInfo                          *) GetFunctionAddr(api.h, "clGetDeviceInfo");
    api.clCreateSubDevices                       = (__clCreateSubDevices                       *) GetFunctionAddr(api.h, "clCreateSubDevices");
    api.clRetainDevice                           = (__clRetainDevice                           *) GetFunctionAddr(api.h, "clRetainDevice");
    api.clReleaseDevice                          = (__clReleaseDevice                          *) GetFunctionAddr(api.h, "clReleaseDevice");
    api.clCreateContext                          = (__clCreateContext                          *) GetFunctionAddr(api.h, "clCreateContext");
    api.clCreateContextFromType                  = (__clCreateContextFromType                  *) GetFunctionAddr(api.h, "clCreateContextFromType");
    api.clRetainContext                          = (__clRetainContext                          *) GetFunctionAddr(api.h, "clRetainContext");
    api.clReleaseContext                         = (__clReleaseContext                         *) GetFunctionAddr(api.h, "clReleaseContext");
    api.clGetContextInfo                         = (__clGetContextInfo                         *) GetFunctionAddr(api.h, "clGetContextInfo");
    api.clCreateCommandQueue                     = (__clCreateCommandQueue                     *) GetFunctionAddr(api.h, "clCreateCommandQueue");
#if defined(CL_VERSION_2_0)
    api.clCreateCommandQueueWithProperties       = (__clCreateCommandQueueWithProperties       *) GetFunctionAddr(api.h, "clCreateCommandQueueWithProperties");
#endif
    api.clRetainCommandQueue                     = (__clRetainCommandQueue                     *) GetFunctionAddr(api.h, "clRetainCommandQueue");
    api.clReleaseCommandQueue                    = (__clReleaseCommandQueue                    *) GetFunctionAddr(api.h, "clReleaseCommandQueue");
    api.clGetCommandQueueInfo                    = (__clGetCommandQueueInfo                    *) GetFunctionAddr(api.h, "clGetCommandQueueInfo");
    api.clCreateBuffer                           = (__clCreateBuffer                           *) GetFunctionAddr(api.h, "clCreateBuffer");
    api.clCreateSubBuffer                        = (__clCreateSubBuffer                        *) GetFunctionAddr(api.h, "clCreateSubBuffer");
    api.clCreateImage                            = (__clCreateImage                            *) GetFunctionAddr(api.h, "clCreateImage");
    api.clRetainMemObject                        = (__clRetainMemObject                        *) GetFunctionAddr(api.h, "clRetainMemObject");
    api.clReleaseMemObject                       = (__clReleaseMemObject                       *) GetFunctionAddr(api.h, "clReleaseMemObject");
    api.clGetSupportedImageFormats               = (__clGetSupportedImageFormats               *) GetFunctionAddr(api.h, "clGetSupportedImageFormats");
    api.clGetMemObjectInfo                       = (__clGetMemObjectInfo                       *) GetFunctionAddr(api.h, "clGetMemObjectInfo");
    api.clGetImageInfo                           = (__clGetImageInfo                           *) GetFunctionAddr(api.h, "clGetImageInfo");
    api.clSetMemObjectDestructorCallback         = (__clSetMemObjectDestructorCallback         *) GetFunctionAddr(api.h, "clSetMemObjectDestructorCallback");
    api.clCreateSampler                          = (__clCreateSampler                          *) GetFunctionAddr(api.h, "clCreateSampler");
    api.clRetainSampler                          = (__clRetainSampler                          *) GetFunctionAddr(api.h, "clRetainSampler");
    api.clReleaseSampler                         = (__clReleaseSampler                         *) GetFunctionAddr(api.h, "clReleaseSampler");
    api.clGetSamplerInfo                         = (__clGetSamplerInfo                         *) GetFunctionAddr(api.h, "clGetSamplerInfo");
    api.clCreateProgramWithSource                = (__clCreateProgramWithSource                *) GetFunctionAddr(api.h, "clCreateProgramWithSource");
    api.clCreateProgramWithBinary                = (__clCreateProgramWithBinary                *) GetFunctionAddr(api.h, "clCreateProgramWithBinary");
    api.clCreateProgramWithBuiltInKernels        = (__clCreateProgramWithBuiltInKernels        *) GetFunctionAddr(api.h, "clCreateProgramWithBuiltInKernels");
    api.clRetainProgram                          = (__clRetainProgram                          *) GetFunctionAddr(api.h, "clRetainProgram");
    api.clReleaseProgram                         = (__clReleaseProgram                         *) GetFunctionAddr(api.h, "clReleaseProgram");
    api.clBuildProgram                           = (__clBuildProgram                           *) GetFunctionAddr(api.h, "clBuildProgram");
    api.clCompileProgram                         = (__clCompileProgram                         *) GetFunctionAddr(api.h, "clCompileProgram");
    api.clLinkProgram                            = (__clLinkProgram                            *) GetFunctionAddr(api.h, "clLinkProgram");
    api.clUnloadPlatformCompiler                 = (__clUnloadPlatformCompiler                 *) GetFunctionAddr(api.h, "clUnloadPlatformCompiler");
    api.clGetProgramInfo                         = (__clGetProgramInfo                         *) GetFunctionAddr(api.h, "clGetProgramInfo");
    api.clGetProgramBuildInfo                    = (__clGetProgramBuildInfo                    *) GetFunctionAddr(api.h, "clGetProgramBuildInfo");
    api.clCreateKernel                           = (__clCreateKernel                           *) GetFunctionAddr(api.h, "clCreateKernel");
    api.clCreateKernelsInProgram                 = (__clCreateKernelsInProgram                 *) GetFunctionAddr(api.h, "clCreateKernelsInProgram");
    api.clRetainKernel                           = (__clRetainKernel                           *) GetFunctionAddr(api.h, "clRetainKernel");
    api.clReleaseKernel                          = (__clReleaseKernel                          *) GetFunctionAddr(api.h, "clReleaseKernel");
    api.clSetKernelArg                           = (__clSetKernelArg                           *) GetFunctionAddr(api.h, "clSetKernelArg");
    api.clGetKernelInfo                          = (__clGetKernelInfo                          *) GetFunctionAddr(api.h, "clGetKernelInfo");
    api.clGetKernelArgInfo                       = (__clGetKernelArgInfo                       *) GetFunctionAddr(api.h, "clGetKernelArgInfo");
    api.clGetKernelWorkGroupInfo                 = (__clGetKernelWorkGroupInfo                 *) GetFunctionAddr(api.h, "clGetKernelWorkGroupInfo");
    api.clWaitForEvents                          = (__clWaitForEvents                          *) GetFunctionAddr(api.h, "clWaitForEvents");
    api.clGetEventInfo                           = (__clGetEventInfo                           *) GetFunctionAddr(api.h, "clGetEventInfo");
    api.clCreateUserEvent                        = (__clCreateUserEvent                        *) GetFunctionAddr(api.h, "clCreateUserEvent");
    api.clRetainEvent                            = (__clRetainEvent                            *) GetFunctionAddr(api.h, "clRetainEvent");
    api.clReleaseEvent                           = (__clReleaseEvent                           *) GetFunctionAddr(api.h, "clReleaseEvent");
    api.clSetUserEventStatus                     = (__clSetUserEventStatus                     *) GetFunctionAddr(api.h, "clSetUserEventStatus");
    api.clSetEventCallback                       = (__clSetEventCallback                       *) GetFunctionAddr(api.h, "clSetEventCallback");
    api.clGetEventProfilingInfo                  = (__clGetEventProfilingInfo                  *) GetFunctionAddr(api.h, "clGetEventProfilingInfo");
    api.clFlush                                  = (__clFlush                                  *) GetFunctionAddr(api.h, "clFlush");
    api.clFinish                                 = (__clFinish                                 *) GetFunctionAddr(api.h, "clFinish");
    api.clEnqueueReadBuffer                      = (__clEnqueueReadBuffer                      *) GetFunctionAddr(api.h, "clEnqueueReadBuffer");
    api.clEnqueueReadBufferRect                  = (__clEnqueueReadBufferRect                  *) GetFunctionAddr(api.h, "clEnqueueReadBufferRect");
    api.clEnqueueWriteBuffer                     = (__clEnqueueWriteBuffer                     *) GetFunctionAddr(api.h, "clEnqueueWriteBuffer");
    api.clEnqueueWriteBufferRect                 = (__clEnqueueWriteBufferRect                 *) GetFunctionAddr(api.h, "clEnqueueWriteBufferRect");
    api.clEnqueueFillBuffer                      = (__clEnqueueFillBuffer                      *) GetFunctionAddr(api.h, "clEnqueueFillBuffer");
    api.clEnqueueCopyBuffer                      = (__clEnqueueCopyBuffer                      *) GetFunctionAddr(api.h, "clEnqueueCopyBuffer");
    api.clEnqueueCopyBufferRect                  = (__clEnqueueCopyBufferRect                  *) GetFunctionAddr(api.h, "clEnqueueCopyBufferRect");
    api.clEnqueueReadImage                       = (__clEnqueueReadImage                       *) GetFunctionAddr(api.h, "clEnqueueReadImage");
    api.clEnqueueWriteImage                      = (__clEnqueueWriteImage                      *) GetFunctionAddr(api.h, "clEnqueueWriteImage");
    api.clEnqueueFillImage                       = (__clEnqueueFillImage                       *) GetFunctionAddr(api.h, "clEnqueueFillImage");
    api.clEnqueueCopyImage                       = (__clEnqueueCopyImage                       *) GetFunctionAddr(api.h, "clEnqueueCopyImage");
    api.clEnqueueCopyImageToBuffer               = (__clEnqueueCopyImageToBuffer               *) GetFunctionAddr(api.h, "clEnqueueCopyImageToBuffer");
    api.clEnqueueCopyBufferToImage               = (__clEnqueueCopyBufferToImage               *) GetFunctionAddr(api.h, "clEnqueueCopyBufferToImage");
    api.clEnqueueMapBuffer                       = (__clEnqueueMapBuffer                       *) GetFunctionAddr(api.h, "clEnqueueMapBuffer");
    api.clEnqueueMapImage                        = (__clEnqueueMapImage                        *) GetFunctionAddr(api.h, "clEnqueueMapImage");
    api.clEnqueueUnmapMemObject                  = (__clEnqueueUnmapMemObject                  *) GetFunctionAddr(api.h, "clEnqueueUnmapMemObject");
    api.clEnqueueMigrateMemObjects               = (__clEnqueueMigrateMemObjects               *) GetFunctionAddr(api.h, "clEnqueueMigrateMemObjects");
    api.clEnqueueNDRangeKernel                   = (__clEnqueueNDRangeKernel                   *) GetFunctionAddr(api.h, "clEnqueueNDRangeKernel");
    api.clEnqueueTask                            = (__clEnqueueTask                            *) GetFunctionAddr(api.h, "clEnqueueTask");
    api.clEnqueueNativeKernel                    = (__clEnqueueNativeKernel                    *) GetFunctionAddr(api.h, "clEnqueueNativeKernel");
    api.clEnqueueMarkerWithWaitList              = (__clEnqueueMarkerWithWaitList              *) GetFunctionAddr(api.h, "clEnqueueMarkerWithWaitList");
    api.clEnqueueBarrierWithWaitList             = (__clEnqueueBarrierWithWaitList             *) GetFunctionAddr(api.h, "clEnqueueBarrierWithWaitList");
    api.clGetExtensionFunctionAddressForPlatform = (__clGetExtensionFunctionAddressForPlatform *) GetFunctionAddr(api.h, "clGetExtensionFunctionAddressForPlatform");
    api.clCreateImage2D                          = (__clCreateImage2D                          *) GetFunctionAddr(api.h, "clCreateImage2D");
    api.clCreateImage3D                          = (__clCreateImage3D                          *) GetFunctionAddr(api.h, "clCreateImage3D");
    api.clEnqueueMarker                          = (__clEnqueueMarker                          *) GetFunctionAddr(api.h, "clEnqueueMarker");
    api.clEnqueueWaitForEvents                   = (__clEnqueueWaitForEvents                   *) GetFunctionAddr(api.h, "clEnqueueWaitForEvents");
    api.clEnqueueBarrier                         = (__clEnqueueBarrier                         *) GetFunctionAddr(api.h, "clEnqueueBarrier");
    api.clUnloadCompiler                         = (__clUnloadCompiler                         *) GetFunctionAddr(api.h, "clUnloadCompiler");
    api.clGetExtensionFunctionAddress            = (__clGetExtensionFunctionAddress            *) GetFunctionAddr(api.h, "clGetExtensionFunctionAddress");

    return CL_SUCCESS;
}

CL_API_ENTRY cl_int CL_API_CALL
clGetPlatformIDs(cl_uint           num_entries ,
                 cl_platform_id *  platforms ,
                 cl_uint *         num_platforms )
{
    if(!api.h) { cl_int r = clInit(); if(r) return r; }
    if(!api.clGetPlatformIDs) return CL_INVALID_OPERATION;
    else {
        cl_int v = api.clGetPlatformIDs(num_entries,platforms,num_platforms);
        if(api.dumpFlags) printf("OPENCL-TRACE: clGetPlatformIDs(%u, %p, %p) => %d\n", num_entries, platforms, num_platforms, v);
        return v;
    }
}

CL_API_ENTRY cl_int CL_API_CALL
clGetPlatformInfo(cl_platform_id    platform ,
                  cl_platform_info  param_name ,
                  size_t            param_value_size ,
                  void *            param_value ,
                  size_t *          param_value_size_ret )
{
    if(!api.h) { cl_int r = clInit(); if(r) return r; }
    if(!api.clGetPlatformInfo) return CL_INVALID_OPERATION;
    else {
        cl_int v = api.clGetPlatformInfo(platform,param_name,param_value_size,param_value,param_value_size_ret);
        if(api.dumpFlags) printf("OPENCL-TRACE: clGetPlatformInfo(%p, %u, %lu, %p, %p) => %d\n", platform, param_name, param_value_size, param_value, param_value_size_ret, v);
        return v;
    }
}

CL_API_ENTRY cl_int CL_API_CALL
clGetDeviceIDs(cl_platform_id    platform ,
               cl_device_type    device_type ,
               cl_uint           num_entries ,
               cl_device_id *    devices ,
               cl_uint *         num_devices )
{
    if(!api.h) { cl_int r = clInit(); if(r) return r; }
    if(!api.clGetDeviceIDs) return CL_INVALID_OPERATION;
    else {
        cl_int v = api.clGetDeviceIDs(platform,device_type,num_entries,devices,num_devices);
        if(api.dumpFlags) printf("OPENCL-TRACE: clGetDeviceIDs(%p, " FMTU64 ", %u, %p, %p) => %d\n", platform, device_type, num_entries, devices, num_devices, v);
        return v;
    }
}

CL_API_ENTRY cl_int CL_API_CALL
clGetDeviceInfo(cl_device_id     device ,
                cl_device_info   param_name ,
                size_t           param_value_size ,
                void *           param_value ,
                size_t *         param_value_size_ret )
{
    if(!api.h) { cl_int r = clInit(); if(r) return r; }
    if(!api.clGetDeviceInfo) return CL_INVALID_OPERATION;
    else {
        cl_int v = api.clGetDeviceInfo(device,param_name,param_value_size,param_value,param_value_size_ret);
        if(api.dumpFlags) printf("OPENCL-TRACE: clGetDeviceInfo(%p, %u, %lu, %p, %p) => %d\n", device, param_name, param_value_size, param_value, param_value_size_ret, v);
        return v;
    }
}

CL_API_ENTRY cl_int CL_API_CALL
clCreateSubDevices(cl_device_id                          in_device ,
                   const cl_device_partition_property *  properties ,
                   cl_uint                               num_devices ,
                   cl_device_id *                        out_devices ,
                   cl_uint *                             num_devices_ret )
{
    if(!api.h) { cl_int r = clInit(); if(r) return r; }
    if(!api.clCreateSubDevices) return CL_INVALID_OPERATION;
    else {
        cl_int v = api.clCreateSubDevices(in_device,properties,num_devices,out_devices,num_devices_ret);
        if(api.dumpFlags) printf("OPENCL-TRACE: clCreateSubDevices(%p, %p, %u, %p, %p) => %d\n", in_device, properties, num_devices, out_devices, num_devices_ret, v);
        return v;
    }
}

CL_API_ENTRY cl_int CL_API_CALL
clRetainDevice(cl_device_id  device )
{
    if(!api.h) { cl_int r = clInit(); if(r) return r; }
    if(!api.clRetainDevice) return CL_INVALID_OPERATION;
    else {
        cl_int v = api.clRetainDevice(device);
        if(api.dumpFlags) printf("OPENCL-TRACE: clRetainDevice(%p) => %d\n", device, v);
        return v;
    }
}

CL_API_ENTRY cl_int CL_API_CALL
clReleaseDevice(cl_device_id  device )
{
    if(!api.h) { cl_int r = clInit(); if(r) return r; }
    if(!api.clReleaseDevice) return CL_INVALID_OPERATION;
    else {
        cl_int v = api.clReleaseDevice(device);
        if(api.dumpFlags) printf("OPENCL-TRACE: clReleaseDevice(%p) => %d\n", device, v);
        return v;
    }
}

CL_API_ENTRY cl_context CL_API_CALL
clCreateContext(const cl_context_properties *  properties ,
                cl_uint                  num_devices ,
                const cl_device_id *     devices ,
                void (CL_CALLBACK *  pfn_notify )(const char *, const void *, size_t, void *),
                void *                   user_data ,
                cl_int *                 errcode_ret )
{
    if(!api.h) { cl_int r = clInit(); if(r) return 0; }
    if(!api.clCreateContext) return 0;
    else {
        cl_context v = api.clCreateContext(properties,num_devices,devices,pfn_notify,user_data,errcode_ret);
        if(api.dumpFlags) printf("OPENCL-TRACE: clCreateContext(%p, %u, %p, %p, %p, %p) => %p\n", properties, num_devices, devices, pfn_notify, user_data, errcode_ret, v);
        return v;
    }
}

CL_API_ENTRY cl_context CL_API_CALL
clCreateContextFromType(const cl_context_properties *  properties ,
                        cl_device_type           device_type ,
                        void (CL_CALLBACK *      pfn_notify )(const char *, const void *, size_t, void *),
                        void *                   user_data ,
                        cl_int *                 errcode_ret )
{
    if(!api.h) { cl_int r = clInit(); if(r) return 0; }
    if(!api.clCreateContextFromType) return 0;
    else {
        cl_context v = api.clCreateContextFromType(properties,device_type,pfn_notify,user_data,errcode_ret);
        if(api.dumpFlags) printf("OPENCL-TRACE: clCreateContextFromType(%p, " FMTU64 ", %p, %p, %p) => %p\n", properties, device_type, pfn_notify, user_data, errcode_ret, v);
        return v;
    }
}

CL_API_ENTRY cl_int CL_API_CALL
clRetainContext(cl_context  context )
{
    if(!api.h) { cl_int r = clInit(); if(r) return r; }
    if(!api.clRetainContext) return CL_INVALID_OPERATION;
    else {
        cl_int v = api.clRetainContext(context);
        if(api.dumpFlags) printf("OPENCL-TRACE: clRetainContext(%p) => %d\n", context, v);
        return v;
    }
}

CL_API_ENTRY cl_int CL_API_CALL
clReleaseContext(cl_context  context )
{
    if(!api.h) { cl_int r = clInit(); if(r) return r; }
    if(!api.clReleaseContext) return CL_INVALID_OPERATION;
    else {
        cl_int v = api.clReleaseContext(context);
        if(api.dumpFlags) printf("OPENCL-TRACE: clReleaseContext(%p) => %d\n", context, v);
        return v;
    }
}

CL_API_ENTRY cl_int CL_API_CALL
clGetContextInfo(cl_context          context ,
                 cl_context_info     param_name ,
                 size_t              param_value_size ,
                 void *              param_value ,
                 size_t *            param_value_size_ret )
{
    if(!api.h) { cl_int r = clInit(); if(r) return r; }
    if(!api.clGetContextInfo) return CL_INVALID_OPERATION;
    else {
        cl_int v = api.clGetContextInfo(context,param_name,param_value_size,param_value,param_value_size_ret);
        if(api.dumpFlags) printf("OPENCL-TRACE: clGetContextInfo(%p, %u, %lu, %p, %p) => %d\n", context, param_name, param_value_size, param_value, param_value_size_ret, v);
        return v;
    }
}

CL_API_ENTRY cl_command_queue CL_API_CALL
clCreateCommandQueue(cl_context                      context ,
                     cl_device_id                    device ,
                     cl_command_queue_properties     properties ,
                     cl_int *                        errcode_ret )
{
    if(!api.h) { cl_int r = clInit(); if(r) return 0; }
    if(!api.clCreateCommandQueue) return 0;
    else {
        cl_command_queue v = api.clCreateCommandQueue(context,device,properties,errcode_ret);
        if(api.dumpFlags) printf("OPENCL-TRACE: clCreateCommandQueue(%p, %p, " FMTU64 ", %p) => %p\n", context, device, properties, errcode_ret, v);
        return v;
    }
}

#if defined(CL_VERSION_2_0)
CL_API_ENTRY cl_command_queue CL_API_CALL
clCreateCommandQueueWithProperties(cl_context                  context,
                                   cl_device_id                device,
                                   const cl_queue_properties * properties,
                                   cl_int *                    errcode_ret)
{
    if(!api.h) { cl_int r = clInit(); if(r) return 0; }
    if(!api.clCreateCommandQueueWithProperties) { if(errcode_ret) *errcode_ret = CL_INVALID_COMMAND_QUEUE; return 0; }
    else {
        cl_command_queue v = api.clCreateCommandQueueWithProperties(context,device,properties,errcode_ret);
        if(api.dumpFlags) printf("OPENCL-TRACE: clCreateCommandQueueWithProperties(%p, %p, %p, %p) => %p\n", context, device, properties, errcode_ret, v);
        return v;
    }
}
#endif

CL_API_ENTRY cl_int CL_API_CALL
clRetainCommandQueue(cl_command_queue  command_queue )
{
    if(!api.h) { cl_int r = clInit(); if(r) return r; }
    if(!api.clRetainCommandQueue) return CL_INVALID_OPERATION;
    else {
        cl_int v = api.clRetainCommandQueue(command_queue);
        if(api.dumpFlags) printf("OPENCL-TRACE: clRetainCommandQueue(%p) => %d\n", command_queue, v);
        return v;
    }
}

CL_API_ENTRY cl_int CL_API_CALL
clReleaseCommandQueue(cl_command_queue  command_queue )
{
    if(!api.h) { cl_int r = clInit(); if(r) return r; }
    if(!api.clReleaseCommandQueue) return CL_INVALID_OPERATION;
    else {
        cl_int v = api.clReleaseCommandQueue(command_queue);
        if(api.dumpFlags) printf("OPENCL-TRACE: clReleaseCommandQueue(%p) => %d\n", command_queue, v);
        return v;
    }
}

CL_API_ENTRY cl_int CL_API_CALL
clGetCommandQueueInfo(cl_command_queue       command_queue ,
                      cl_command_queue_info  param_name ,
                      size_t                 param_value_size ,
                      void *                 param_value ,
                      size_t *               param_value_size_ret )
{
    if(!api.h) { cl_int r = clInit(); if(r) return r; }
    if(!api.clGetCommandQueueInfo) return CL_INVALID_OPERATION;
    else {
        cl_int v = api.clGetCommandQueueInfo(command_queue,param_name,param_value_size,param_value,param_value_size_ret);
        if(api.dumpFlags) printf("OPENCL-TRACE: clGetCommandQueueInfo(%p, %u, %lu, %p, %p) => %d\n", command_queue, param_name, param_value_size, param_value, param_value_size_ret, v);
        return v;
    }
}

CL_API_ENTRY cl_mem CL_API_CALL
clCreateBuffer(cl_context    context ,
               cl_mem_flags  flags ,
               size_t        size ,
               void *        host_ptr ,
               cl_int *      errcode_ret )
{
    if(!api.h) { cl_int r = clInit(); if(r) return 0; }
    if(!api.clCreateBuffer) return 0;
    else {
        cl_mem v = api.clCreateBuffer(context,flags,size,host_ptr,errcode_ret);
        if(api.dumpFlags) printf("OPENCL-TRACE: clCreateBuffer(%p, " FMTU64 ", %lu, %p, %p) => %p\n", context, flags, size, host_ptr, errcode_ret, v);
        return v;
    }
}

CL_API_ENTRY cl_mem CL_API_CALL
clCreateSubBuffer(cl_mem                    buffer ,
                  cl_mem_flags              flags ,
                  cl_buffer_create_type     buffer_create_type ,
                  const void *              buffer_create_info ,
                  cl_int *                  errcode_ret )
{
    if(!api.h) { cl_int r = clInit(); if(r) return 0; }
    if(!api.clCreateSubBuffer) return 0;
    else {
        cl_mem v = api.clCreateSubBuffer(buffer,flags,buffer_create_type,buffer_create_info,errcode_ret);
        if(api.dumpFlags) printf("OPENCL-TRACE: clCreateSubBuffer(%p, " FMTU64 ", %u, {%ld,%ld}, %p) => %p\n", buffer, flags, buffer_create_type, ((const cl_buffer_region *)buffer_create_info)->origin, ((const cl_buffer_region *)buffer_create_info)->size, errcode_ret, v);
        return v;
    }
}

CL_API_ENTRY cl_mem CL_API_CALL
clCreateImage(cl_context               context ,
              cl_mem_flags             flags ,
              const cl_image_format *  image_format ,
              const cl_image_desc *    image_desc ,
              void *                   host_ptr ,
              cl_int *                 errcode_ret )
{
    if(!api.h) { cl_int r = clInit(); if(r) return 0; }
    if(!api.clCreateImage) return 0;
    else {
        cl_mem v = api.clCreateImage(context,flags,image_format,image_desc,host_ptr,errcode_ret);
        if(api.dumpFlags) printf("OPENCL-TRACE: clCreateImage(%p, " FMTU64 ", %p, %p, %p, %p) => %p\n", context, flags, image_format, image_desc, host_ptr, errcode_ret, v);
        return v;
    }
}

CL_API_ENTRY cl_int CL_API_CALL
clRetainMemObject(cl_mem  memobj )
{
    if(!api.h) { cl_int r = clInit(); if(r) return r; }
    if(!api.clRetainMemObject) return CL_INVALID_OPERATION;
    else {
        cl_int v = api.clRetainMemObject(memobj);
        if(api.dumpFlags) printf("OPENCL-TRACE: clRetainMemObject(%p) => %d\n", memobj, v);
        return v;
    }
}

CL_API_ENTRY cl_int CL_API_CALL
clReleaseMemObject(cl_mem  memobj )
{
    if(!api.h) { cl_int r = clInit(); if(r) return r; }
    if(!api.clReleaseMemObject) return CL_INVALID_OPERATION;
    else {
        cl_int v = api.clReleaseMemObject(memobj);
        if(api.dumpFlags) printf("OPENCL-TRACE: clReleaseMemObject(%p) => %d\n", memobj, v);
        return v;
    }
}

CL_API_ENTRY cl_int CL_API_CALL
clGetSupportedImageFormats(cl_context            context ,
                           cl_mem_flags          flags ,
                           cl_mem_object_type    image_type ,
                           cl_uint               num_entries ,
                           cl_image_format *     image_formats ,
                           cl_uint *             num_image_formats )
{
    if(!api.h) { cl_int r = clInit(); if(r) return r; }
    if(!api.clGetSupportedImageFormats) return CL_INVALID_OPERATION;
    else {
        cl_int v = api.clGetSupportedImageFormats(context,flags,image_type,num_entries,image_formats,num_image_formats);
        if(api.dumpFlags) printf("OPENCL-TRACE: clGetSupportedImageFormats(%p, " FMTU64 ", %u, %u, %p, %p) => %d\n", context, flags, image_type, num_entries, image_formats, num_image_formats, v);
        return v;
    }
}

CL_API_ENTRY cl_int CL_API_CALL
clGetMemObjectInfo(cl_mem            memobj ,
                   cl_mem_info       param_name ,
                   size_t            param_value_size ,
                   void *            param_value ,
                   size_t *          param_value_size_ret )
{
    if(!api.h) { cl_int r = clInit(); if(r) return r; }
    if(!api.clGetMemObjectInfo) return CL_INVALID_OPERATION;
    else {
        cl_int v = api.clGetMemObjectInfo(memobj,param_name,param_value_size,param_value,param_value_size_ret);
        if(api.dumpFlags) printf("OPENCL-TRACE: clGetMemObjectInfo(%p, %u, %lu, %p, %p) => %d\n", memobj, param_name, param_value_size, param_value, param_value_size_ret, v);
        return v;
    }
}

CL_API_ENTRY cl_int CL_API_CALL
clGetImageInfo(cl_mem            image ,
               cl_image_info     param_name ,
               size_t            param_value_size ,
               void *            param_value ,
               size_t *          param_value_size_ret )
{
    if(!api.h) { cl_int r = clInit(); if(r) return r; }
    if(!api.clGetImageInfo) return CL_INVALID_OPERATION;
    else {
        cl_int v = api.clGetImageInfo(image,param_name,param_value_size,param_value,param_value_size_ret);
        if(api.dumpFlags) printf("OPENCL-TRACE: clGetImageInfo(%p, %u, %lu, %p, %p) => %d\n", image, param_name, param_value_size, param_value, param_value_size_ret, v);
        return v;
    }
}

CL_API_ENTRY cl_int CL_API_CALL
clSetMemObjectDestructorCallback(  cl_mem  memobj ,
                                    void (CL_CALLBACK * pfn_notify)( cl_mem  memobj , void* user_data),
                                    void * user_data  )            
{
    if(!api.h) { cl_int r = clInit(); if(r) return r; }
    if(!api.clSetMemObjectDestructorCallback) return CL_INVALID_OPERATION;
    else {
        cl_int v = api.clSetMemObjectDestructorCallback(memobj,pfn_notify,user_data);
        if(api.dumpFlags) printf("OPENCL-TRACE: clSetMemObjectDestructorCallback(%p, %p, %p) => %d\n", memobj, pfn_notify, user_data, v);
        return v;
    }
}

CL_API_ENTRY cl_sampler CL_API_CALL
clCreateSampler(cl_context           context ,
                cl_bool              normalized_coords ,
                cl_addressing_mode   addressing_mode ,
                cl_filter_mode       filter_mode ,
                cl_int *             errcode_ret )
{
    if(!api.h) { cl_int r = clInit(); if(r) return 0; }
    if(!api.clCreateSampler) return 0;
    else {
        cl_sampler v = api.clCreateSampler(context,normalized_coords,addressing_mode,filter_mode,errcode_ret);
        if(api.dumpFlags) printf("OPENCL-TRACE: clCreateSampler(%p, %d, %u, %u, %p) => %p\n", context, normalized_coords, addressing_mode, filter_mode, errcode_ret, v);
        return v;
    }
}

CL_API_ENTRY cl_int CL_API_CALL
clRetainSampler(cl_sampler  sampler )
{
    if(!api.h) { cl_int r = clInit(); if(r) return r; }
    if(!api.clRetainSampler) return CL_INVALID_OPERATION;
    else {
        cl_int v = api.clRetainSampler(sampler);
        if(api.dumpFlags) printf("OPENCL-TRACE: clRetainSampler(%p) => %d\n", sampler, v);
        return v;
    }
}

CL_API_ENTRY cl_int CL_API_CALL
clReleaseSampler(cl_sampler  sampler )
{
    if(!api.h) { cl_int r = clInit(); if(r) return r; }
    if(!api.clReleaseSampler) return CL_INVALID_OPERATION;
    else {
        cl_int v = api.clReleaseSampler(sampler);
        if(api.dumpFlags) printf("OPENCL-TRACE: clReleaseSampler(%p) => %d\n", sampler, v);
        return v;
    }
}

CL_API_ENTRY cl_int CL_API_CALL
clGetSamplerInfo(cl_sampler          sampler ,
                 cl_sampler_info     param_name ,
                 size_t              param_value_size ,
                 void *              param_value ,
                 size_t *            param_value_size_ret )
{
    if(!api.h) { cl_int r = clInit(); if(r) return r; }
    if(!api.clGetSamplerInfo) return CL_INVALID_OPERATION;
    else {
        cl_int v = api.clGetSamplerInfo(sampler,param_name,param_value_size,param_value,param_value_size_ret);
        if(api.dumpFlags) printf("OPENCL-TRACE: clGetSamplerInfo(%p, %u, %lu, %p, %p) => %d\n", sampler, param_name, param_value_size, param_value, param_value_size_ret, v);
        return v;
    }
}

CL_API_ENTRY cl_program CL_API_CALL
clCreateProgramWithSource(cl_context         context ,
                          cl_uint            count ,
                          const char **      strings ,
                          const size_t *     lengths ,
                          cl_int *           errcode_ret )
{
    if(!api.h) { cl_int r = clInit(); if(r) return 0; }
    if(!api.clCreateProgramWithSource) return 0;
    else {
        cl_program v = api.clCreateProgramWithSource(context,count,strings,lengths,errcode_ret);
        if(api.dumpFlags) printf("OPENCL-TRACE: clCreateProgramWithSource(%p, %u, %p, %p, %p) => %p\n", context, count, strings, lengths, errcode_ret, v);
        if(api.dumpFlags > 1) for (cl_uint i = 0; i < count; i++) { printf("OPENCL-TRACE: PROGRAM-SOURCE %p \"", v); for(size_t j = 0; strings[i][j]; j++) { int c = strings[i][j]; if(c == '\n') printf("\\n"); else if(c == '\r') printf("\\r"); else if(c == '\t') printf("\\t"); else if(c == '"') printf("\\\""); else if(c == '\\') printf("\\\\"); else printf("%c", c); } printf("\"\n"); }
        return v;
    }
}

CL_API_ENTRY cl_program CL_API_CALL
clCreateProgramWithBinary(cl_context                      context ,
                          cl_uint                         num_devices ,
                          const cl_device_id *            device_list ,
                          const size_t *                  lengths ,
                          const unsigned char **          binaries ,
                          cl_int *                        binary_status ,
                          cl_int *                        errcode_ret )
{
    if(!api.h) { cl_int r = clInit(); if(r) return 0; }
    if(!api.clCreateProgramWithBinary) return 0;
    else {
        cl_program v = api.clCreateProgramWithBinary(context,num_devices,device_list,lengths,binaries,binary_status,errcode_ret);
        if(api.dumpFlags) printf("OPENCL-TRACE: clCreateProgramWithBinary(%p, %u, %p, %p, %p, %p, %p) => %p\n", context, num_devices, device_list, lengths, binaries, binary_status, errcode_ret, v);
        if(api.dumpFlags > 1) for (cl_uint i = 0; i < num_devices; i++) { printf("OPENCL-TRACE: PROGRAM-BINARY %p %p %ld", v, device_list[i], lengths[i]); for(size_t j = 0; j < (lengths[i]+sizeof(cl_uint)-1)/sizeof(cl_uint); j++) printf(" 0x%08x", ((const cl_uint *)binaries[i])[j]); printf("\n"); }
        return v;
    }
}

CL_API_ENTRY cl_program CL_API_CALL
clCreateProgramWithBuiltInKernels(cl_context             context ,
                                  cl_uint                num_devices ,
                                  const cl_device_id *   device_list ,
                                  const char *           kernel_names ,
                                  cl_int *               errcode_ret )
{
    if(!api.h) { cl_int r = clInit(); if(r) return 0; }
    if(!api.clCreateProgramWithBuiltInKernels) return 0;
    else {
        cl_program v = api.clCreateProgramWithBuiltInKernels(context,num_devices,device_list,kernel_names,errcode_ret);
        if(api.dumpFlags) printf("OPENCL-TRACE: clCreateProgramWithBuiltInKernels(%p, %u, %p, '%s', %p) => %p\n", context, num_devices, device_list, kernel_names, errcode_ret, v);
        return v;
    }
}

CL_API_ENTRY cl_int CL_API_CALL
clRetainProgram(cl_program  program )
{
    if(!api.h) { cl_int r = clInit(); if(r) return r; }
    if(!api.clRetainProgram) return CL_INVALID_OPERATION;
    else {
        cl_int v = api.clRetainProgram(program);
        if(api.dumpFlags) printf("OPENCL-TRACE: clRetainProgram(%p) => %d\n", program, v);
        return v;
    }
}

CL_API_ENTRY cl_int CL_API_CALL
clReleaseProgram(cl_program  program )
{
    if(!api.h) { cl_int r = clInit(); if(r) return r; }
    if(!api.clReleaseProgram) return CL_INVALID_OPERATION;
    else {
        cl_int v = api.clReleaseProgram(program);
        if(api.dumpFlags) printf("OPENCL-TRACE: clReleaseProgram(%p) => %d\n", program, v);
        return v;
    }
}

CL_API_ENTRY cl_int CL_API_CALL
clBuildProgram(cl_program            program ,
               cl_uint               num_devices ,
               const cl_device_id *  device_list ,
               const char *          options ,
               void (CL_CALLBACK *   pfn_notify )(cl_program  program , void *  user_data ),
               void *                user_data )
{
    if(!api.h) { cl_int r = clInit(); if(r) return r; }
    if(!api.clBuildProgram) return CL_INVALID_OPERATION;
    else {
        cl_int v = api.clBuildProgram(program,num_devices,device_list,options,pfn_notify,user_data);
        if(api.dumpFlags) printf("OPENCL-TRACE: clBuildProgram(%p, %u, %p, '%s', %p, %p) => %d\n", program, num_devices, device_list, options, pfn_notify, user_data, v);
        if(api.dumpFlags > 1) { printf("OPENCL-TRACE: PROGRAM-BUILD %p", program); for(size_t i = 0; i < num_devices; i++) { printf(" %p", device_list[i]); } printf("\n"); }
        if(api.dumpFlags > 2 && v == CL_SUCCESS && num_devices == 1) {
            size_t program_size = 0;
            api.clGetProgramInfo(program, CL_PROGRAM_BINARY_SIZES, sizeof(size_t), &program_size, NULL);
            if(program_size) {
                unsigned char * program_bin = new unsigned char [program_size];
                if(!api.clGetProgramInfo(program, CL_PROGRAM_BINARIES, sizeof(unsigned char *), &program_bin, NULL)) { printf("OPENCL-TRACE: PROGRAM-BUILD-BINARY %p %p %ld", program, device_list[0], program_size); for(size_t j = 0; j < (program_size+sizeof(cl_uint)-1)/sizeof(cl_uint); j++) printf(" 0x%08x", ((const cl_uint *)program_bin)[j]); printf("\n"); }
                delete[] program_bin;
            }
        }
        return v;
    }
}

CL_API_ENTRY cl_int CL_API_CALL
clCompileProgram(cl_program            program ,
                 cl_uint               num_devices ,
                 const cl_device_id *  device_list ,
                 const char *          options ,
                 cl_uint               num_input_headers ,
                 const cl_program *    input_headers ,
                 const char **         header_include_names ,
                 void (CL_CALLBACK *   pfn_notify )(cl_program  program , void *  user_data ),
                 void *                user_data )
{
    if(!api.h) { cl_int r = clInit(); if(r) return r; }
    if(!api.clCompileProgram) return CL_INVALID_OPERATION;
    else {
        cl_int v = api.clCompileProgram(program,num_devices,device_list,options,num_input_headers,input_headers,header_include_names,pfn_notify,user_data);
        if(api.dumpFlags) printf("OPENCL-TRACE: clCompileProgram(%p, %u, %p, '%s', %u, %p, %p, %p, %p) => %d\n", program, num_devices, device_list, options, num_input_headers, input_headers, header_include_names, pfn_notify, user_data, v);
        return v;
    }
}

CL_API_ENTRY cl_program CL_API_CALL
clLinkProgram(cl_context            context ,
              cl_uint               num_devices ,
              const cl_device_id *  device_list ,
              const char *          options ,
              cl_uint               num_input_programs ,
              const cl_program *    input_programs ,
              void (CL_CALLBACK *   pfn_notify )(cl_program  program , void *  user_data ),
              void *                user_data ,
              cl_int *              errcode_ret  )
{
    if(!api.h) { cl_int r = clInit(); if(r) return 0; }
    if(!api.clLinkProgram) return 0;
    else {
        cl_program v = api.clLinkProgram(context,num_devices,device_list,options,num_input_programs,input_programs,pfn_notify,user_data,errcode_ret);
        if(api.dumpFlags) printf("OPENCL-TRACE: clLinkProgram(%p, %u, %p, '%s', %u, %p, %p, %p, %p) => %p\n", context, num_devices, device_list, options, num_input_programs, input_programs, pfn_notify, user_data, errcode_ret, v);
        return v;
    }
}

CL_API_ENTRY cl_int CL_API_CALL
clUnloadPlatformCompiler(cl_platform_id  platform )
{
    if(!api.h) { cl_int r = clInit(); if(r) return r; }
    if(!api.clUnloadPlatformCompiler) return CL_INVALID_OPERATION;
    else {
        cl_int v = api.clUnloadPlatformCompiler(platform);
        if(api.dumpFlags) printf("OPENCL-TRACE: clUnloadPlatformCompiler(%p) => %d\n", platform, v);
        return v;
    }
}

CL_API_ENTRY cl_int CL_API_CALL
clGetProgramInfo(cl_program          program ,
                 cl_program_info     param_name ,
                 size_t              param_value_size ,
                 void *              param_value ,
                 size_t *            param_value_size_ret )
{
    if(!api.h) { cl_int r = clInit(); if(r) return r; }
    if(!api.clGetProgramInfo) return CL_INVALID_OPERATION;
    else {
        cl_int v = api.clGetProgramInfo(program,param_name,param_value_size,param_value,param_value_size_ret);
        if(api.dumpFlags) printf("OPENCL-TRACE: clGetProgramInfo(%p, %u, %lu, %p, %p) => %d\n", program, param_name, param_value_size, param_value, param_value_size_ret, v);
        return v;
    }
}

CL_API_ENTRY cl_int CL_API_CALL
clGetProgramBuildInfo(cl_program             program ,
                      cl_device_id           device ,
                      cl_program_build_info  param_name ,
                      size_t                 param_value_size ,
                      void *                 param_value ,
                      size_t *               param_value_size_ret )
{
    if(!api.h) { cl_int r = clInit(); if(r) return r; }
    if(!api.clGetProgramBuildInfo) return CL_INVALID_OPERATION;
    else {
        cl_int v = api.clGetProgramBuildInfo(program,device,param_name,param_value_size,param_value,param_value_size_ret);
        if(api.dumpFlags) printf("OPENCL-TRACE: clGetProgramBuildInfo(%p, %p, %u, %lu, %p, %p) => %d\n", program, device, param_name, param_value_size, param_value, param_value_size_ret, v);
        return v;
    }
}

CL_API_ENTRY cl_kernel CL_API_CALL
clCreateKernel(cl_program       program ,
               const char *     kernel_name ,
               cl_int *         errcode_ret )
{
    if(!api.h) { cl_int r = clInit(); if(r) return 0; }
    if(!api.clCreateKernel) return 0;
    else {
        cl_kernel v = api.clCreateKernel(program,kernel_name,errcode_ret);
        if(api.dumpFlags) printf("OPENCL-TRACE: clCreateKernel(%p, '%s', %p) => %p\n", program, kernel_name, errcode_ret, v);
        return v;
    }
}

CL_API_ENTRY cl_int CL_API_CALL
clCreateKernelsInProgram(cl_program      program ,
                         cl_uint         num_kernels ,
                         cl_kernel *     kernels ,
                         cl_uint *       num_kernels_ret )
{
    if(!api.h) { cl_int r = clInit(); if(r) return r; }
    if(!api.clCreateKernelsInProgram) return CL_INVALID_OPERATION;
    else {
        cl_int v = api.clCreateKernelsInProgram(program,num_kernels,kernels,num_kernels_ret);
        if(api.dumpFlags) printf("OPENCL-TRACE: clCreateKernelsInProgram(%p, %u, %p, %p) => %d\n", program, num_kernels, kernels, num_kernels_ret, v);
        return v;
    }
}

CL_API_ENTRY cl_int CL_API_CALL
clRetainKernel(cl_kernel     kernel )
{
    if(!api.h) { cl_int r = clInit(); if(r) return r; }
    if(!api.clRetainKernel) return CL_INVALID_OPERATION;
    else {
        cl_int v = api.clRetainKernel(kernel);
        if(api.dumpFlags) printf("OPENCL-TRACE: clRetainKernel(%p) => %d\n", kernel, v);
        return v;
    }
}

CL_API_ENTRY cl_int CL_API_CALL
clReleaseKernel(cl_kernel    kernel )
{
    if(!api.h) { cl_int r = clInit(); if(r) return r; }
    if(!api.clReleaseKernel) return CL_INVALID_OPERATION;
    else {
        cl_int v = api.clReleaseKernel(kernel);
        if(api.dumpFlags) printf("OPENCL-TRACE: clReleaseKernel(%p) => %d\n", kernel, v);
        return v;
    }
}

CL_API_ENTRY cl_int CL_API_CALL
clSetKernelArg(cl_kernel     kernel ,
               cl_uint       arg_index ,
               size_t        arg_size ,
               const void *  arg_value )
{
    if(!api.h) { cl_int r = clInit(); if(r) return r; }
    if(!api.clSetKernelArg) return CL_INVALID_OPERATION;
    else {
        cl_int v = api.clSetKernelArg(kernel,arg_index,arg_size,arg_value);
        if(api.dumpFlags) printf("OPENCL-TRACE: clSetKernelArg(%p, %u, %lu, %p) => %d\n", kernel, arg_index, arg_size, arg_value, v);
        if(api.dumpFlags > 1) { printf("OPENCL-TRACE: KERNARG %p %d %ld", kernel, arg_index, arg_size); if(arg_size == 8) printf(" %p", *(const void **)arg_value); else for (cl_uint i = 0; i < arg_size/sizeof(cl_uint); i++) printf(" 0x%08x", ((const cl_uint*)arg_value)[i]); printf("\n"); }
        return v;
    }
}

CL_API_ENTRY cl_int CL_API_CALL
clGetKernelInfo(cl_kernel        kernel ,
                cl_kernel_info   param_name ,
                size_t           param_value_size ,
                void *           param_value ,
                size_t *         param_value_size_ret )
{
    if(!api.h) { cl_int r = clInit(); if(r) return r; }
    if(!api.clGetKernelInfo) return CL_INVALID_OPERATION;
    else {
        cl_int v = api.clGetKernelInfo(kernel,param_name,param_value_size,param_value,param_value_size_ret);
        if(api.dumpFlags) printf("OPENCL-TRACE: clGetKernelInfo(%p, %u, %lu, %p, %p) => %d\n", kernel, param_name, param_value_size, param_value, param_value_size_ret, v);
        return v;
    }
}

CL_API_ENTRY cl_int CL_API_CALL
clGetKernelArgInfo(cl_kernel        kernel ,
                   cl_uint          arg_indx ,
                   cl_kernel_arg_info   param_name ,
                   size_t           param_value_size ,
                   void *           param_value ,
                   size_t *         param_value_size_ret )
{
    if(!api.h) { cl_int r = clInit(); if(r) return r; }
    if(!api.clGetKernelArgInfo) return CL_INVALID_OPERATION;
    else {
        cl_int v = api.clGetKernelArgInfo(kernel,arg_indx,param_name,param_value_size,param_value,param_value_size_ret);
        if(api.dumpFlags) printf("OPENCL-TRACE: clGetKernelArgInfo(%p, %u, %u, %lu, %p, %p) => %d\n", kernel, arg_indx, param_name, param_value_size, param_value, param_value_size_ret, v);
        return v;
    }
}

CL_API_ENTRY cl_int CL_API_CALL
clGetKernelWorkGroupInfo(cl_kernel                   kernel ,
                         cl_device_id                device ,
                         cl_kernel_work_group_info   param_name ,
                         size_t                      param_value_size ,
                         void *                      param_value ,
                         size_t *                    param_value_size_ret )
{
    if(!api.h) { cl_int r = clInit(); if(r) return r; }
    if(!api.clGetKernelWorkGroupInfo) return CL_INVALID_OPERATION;
    else {
        cl_int v = api.clGetKernelWorkGroupInfo(kernel,device,param_name,param_value_size,param_value,param_value_size_ret);
        if(api.dumpFlags) printf("OPENCL-TRACE: clGetKernelWorkGroupInfo(%p, %p, %u, %lu, %p, %p) => %d\n", kernel, device, param_name, param_value_size, param_value, param_value_size_ret, v);
        return v;
    }
}

CL_API_ENTRY cl_int CL_API_CALL
clWaitForEvents(cl_uint              num_events ,
                const cl_event *     event_list )
{
    if(!api.h) { cl_int r = clInit(); if(r) return r; }
    if(!api.clWaitForEvents) return CL_INVALID_OPERATION;
    else {
        cl_int v = api.clWaitForEvents(num_events,event_list);
        if(api.dumpFlags) printf("OPENCL-TRACE: clWaitForEvents(%u, %p) => %d\n", num_events, event_list, v);
        return v;
    }
}

CL_API_ENTRY cl_int CL_API_CALL
clGetEventInfo(cl_event          event ,
               cl_event_info     param_name ,
               size_t            param_value_size ,
               void *            param_value ,
               size_t *          param_value_size_ret )
{
    if(!api.h) { cl_int r = clInit(); if(r) return r; }
    if(!api.clGetEventInfo) return CL_INVALID_OPERATION;
    else {
        cl_int v = api.clGetEventInfo(event,param_name,param_value_size,param_value,param_value_size_ret);
        if(api.dumpFlags) printf("OPENCL-TRACE: clGetEventInfo(%p, %u, %lu, %p, %p) => %d\n", event, param_name, param_value_size, param_value, param_value_size_ret, v);
        return v;
    }
}

CL_API_ENTRY cl_event CL_API_CALL
clCreateUserEvent(cl_context     context ,
                  cl_int *       errcode_ret )
{
    if(!api.h) { cl_int r = clInit(); if(r) return 0; }
    if(!api.clCreateUserEvent) return 0;
    else {
        cl_event v = api.clCreateUserEvent(context,errcode_ret);
        if(api.dumpFlags) printf("OPENCL-TRACE: clCreateUserEvent(%p, %p) => %p\n", context, errcode_ret, v);
        return v;
    }
}

CL_API_ENTRY cl_int CL_API_CALL
clRetainEvent(cl_event  event )
{
    if(!api.h) { cl_int r = clInit(); if(r) return r; }
    if(!api.clRetainEvent) return CL_INVALID_OPERATION;
    else {
        cl_int v = api.clRetainEvent(event);
        if(api.dumpFlags) printf("OPENCL-TRACE: clRetainEvent(%p) => %d\n", event, v);
        return v;
    }
}

CL_API_ENTRY cl_int CL_API_CALL
clReleaseEvent(cl_event  event )
{
    if(!api.h) { cl_int r = clInit(); if(r) return r; }
    if(!api.clReleaseEvent) return CL_INVALID_OPERATION;
    else {
        cl_int v = api.clReleaseEvent(event);
        if(api.dumpFlags) printf("OPENCL-TRACE: clReleaseEvent(%p) => %d\n", event, v);
        return v;
    }
}

CL_API_ENTRY cl_int CL_API_CALL
clSetUserEventStatus(cl_event    event ,
                     cl_int      execution_status )
{
    if(!api.h) { cl_int r = clInit(); if(r) return r; }
    if(!api.clSetUserEventStatus) return CL_INVALID_OPERATION;
    else {
        cl_int v = api.clSetUserEventStatus(event,execution_status);
        if(api.dumpFlags) printf("OPENCL-TRACE: clSetUserEventStatus(%p, %d) => %d\n", event, execution_status, v);
        return v;
    }
}

CL_API_ENTRY cl_int CL_API_CALL
clSetEventCallback( cl_event     event ,
                    cl_int       command_exec_callback_type ,
                    void (CL_CALLBACK *  pfn_notify )(cl_event, cl_int, void *),
                    void *       user_data )
{
    if(!api.h) { cl_int r = clInit(); if(r) return r; }
    if(!api.clSetEventCallback) return CL_INVALID_OPERATION;
    else {
        cl_int v = api.clSetEventCallback(event,command_exec_callback_type,pfn_notify,user_data);
        if(api.dumpFlags) printf("OPENCL-TRACE: clSetEventCallback(%p, %d, %p, %p) => %d\n", event, command_exec_callback_type, pfn_notify, user_data, v);
        return v;
    }
}

CL_API_ENTRY cl_int CL_API_CALL
clGetEventProfilingInfo(cl_event             event ,
                        cl_profiling_info    param_name ,
                        size_t               param_value_size ,
                        void *               param_value ,
                        size_t *             param_value_size_ret )
{
    if(!api.h) { cl_int r = clInit(); if(r) return r; }
    if(!api.clGetEventProfilingInfo) return CL_INVALID_OPERATION;
    else {
        cl_int v = api.clGetEventProfilingInfo(event,param_name,param_value_size,param_value,param_value_size_ret);
        if(api.dumpFlags) printf("OPENCL-TRACE: clGetEventProfilingInfo(%p, %u, %lu, %p, %p) => %d\n", event, param_name, param_value_size, param_value, param_value_size_ret, v);
        return v;
    }
}

CL_API_ENTRY cl_int CL_API_CALL
clFlush(cl_command_queue  command_queue )
{
    if(!api.h) { cl_int r = clInit(); if(r) return r; }
    if(!api.clFlush) return CL_INVALID_OPERATION;
    else {
        cl_int v = api.clFlush(command_queue);
        if(api.dumpFlags) printf("OPENCL-TRACE: clFlush(%p) => %d\n", command_queue, v);
        return v;
    }
}

CL_API_ENTRY cl_int CL_API_CALL
clFinish(cl_command_queue  command_queue )
{
    if(!api.h) { cl_int r = clInit(); if(r) return r; }
    if(!api.clFinish) return CL_INVALID_OPERATION;
    else {
        cl_int v = api.clFinish(command_queue);
        if(api.dumpFlags) printf("OPENCL-TRACE: clFinish(%p) => %d\n", command_queue, v);
        return v;
    }
}

CL_API_ENTRY cl_int CL_API_CALL
clEnqueueReadBuffer(cl_command_queue     command_queue ,
                    cl_mem               buffer ,
                    cl_bool              blocking_read ,
                    size_t               offset ,
                    size_t               size ,
                    void *               ptr ,
                    cl_uint              num_events_in_wait_list ,
                    const cl_event *     event_wait_list ,
                    cl_event *           event )
{
    if(!api.h) { cl_int r = clInit(); if(r) return r; }
    if(!api.clEnqueueReadBuffer) return CL_INVALID_OPERATION;
    else {
        cl_int v = api.clEnqueueReadBuffer(command_queue,buffer,blocking_read,offset,size,ptr,num_events_in_wait_list,event_wait_list,event);
        if(api.dumpFlags) printf("OPENCL-TRACE: clEnqueueReadBuffer(%p, %p, %d, %lu, %lu, %p, %u, %p, %p) => %d\n", command_queue, buffer, blocking_read, offset, size, ptr, num_events_in_wait_list, event_wait_list, event, v);
        return v;
    }
}

CL_API_ENTRY cl_int CL_API_CALL
clEnqueueReadBufferRect(cl_command_queue     command_queue ,
                        cl_mem               buffer ,
                        cl_bool              blocking_read ,
                        const size_t *       buffer_offset ,
                        const size_t *       host_offset ,
                        const size_t *       region ,
                        size_t               buffer_row_pitch ,
                        size_t               buffer_slice_pitch ,
                        size_t               host_row_pitch ,
                        size_t               host_slice_pitch ,
                        void *               ptr ,
                        cl_uint              num_events_in_wait_list ,
                        const cl_event *     event_wait_list ,
                        cl_event *           event )
{
    if(!api.h) { cl_int r = clInit(); if(r) return r; }
    if(!api.clEnqueueReadBufferRect) return CL_INVALID_OPERATION;
    else {
        cl_int v = api.clEnqueueReadBufferRect(command_queue,buffer,blocking_read,buffer_offset,host_offset,region,buffer_row_pitch,buffer_slice_pitch,host_row_pitch,host_slice_pitch,ptr,num_events_in_wait_list,event_wait_list,event);
        if(api.dumpFlags) printf("OPENCL-TRACE: clEnqueueReadBufferRect(%p, %p, %d, %p, %p, %p, %lu, %lu, %lu, %lu, %p, %u, %p, %p) => %d\n", command_queue, buffer, blocking_read, buffer_offset, host_offset, region, buffer_row_pitch, buffer_slice_pitch, host_row_pitch, host_slice_pitch, ptr, num_events_in_wait_list, event_wait_list, event, v);
        return v;
    }
}

CL_API_ENTRY cl_int CL_API_CALL
clEnqueueWriteBuffer(cl_command_queue    command_queue ,
                     cl_mem              buffer ,
                     cl_bool             blocking_write ,
                     size_t              offset ,
                     size_t              size ,
                     const void *        ptr ,
                     cl_uint             num_events_in_wait_list ,
                     const cl_event *    event_wait_list ,
                     cl_event *          event )
{
    if(!api.h) { cl_int r = clInit(); if(r) return r; }
    if(!api.clEnqueueWriteBuffer) return CL_INVALID_OPERATION;
    else {
        cl_int v = api.clEnqueueWriteBuffer(command_queue,buffer,blocking_write,offset,size,ptr,num_events_in_wait_list,event_wait_list,event);
        if(api.dumpFlags) printf("OPENCL-TRACE: clEnqueueWriteBuffer(%p, %p, %d, %lu, %lu, %p, %u, %p, %p) => %d\n", command_queue, buffer, blocking_write, offset, size, ptr, num_events_in_wait_list, event_wait_list, event, v);
        if(api.dumpFlags > 1) { printf("OPENCL-TRACE: BUFFER-WRITE %p %p %ld %ld", command_queue, buffer, offset, size); for (cl_uint i = 0; i < size/sizeof(cl_uint); i++) printf(" 0x%08x", ((const cl_uint*)ptr)[i + offset/sizeof(cl_uint)]); printf("\n"); }
        return v;
    }
}

CL_API_ENTRY cl_int CL_API_CALL
clEnqueueWriteBufferRect(cl_command_queue     command_queue ,
                         cl_mem               buffer ,
                         cl_bool              blocking_write ,
                         const size_t *       buffer_offset ,
                         const size_t *       host_offset ,
                         const size_t *       region ,
                         size_t               buffer_row_pitch ,
                         size_t               buffer_slice_pitch ,
                         size_t               host_row_pitch ,
                         size_t               host_slice_pitch ,
                         const void *         ptr ,
                         cl_uint              num_events_in_wait_list ,
                         const cl_event *     event_wait_list ,
                         cl_event *           event )
{
    if(!api.h) { cl_int r = clInit(); if(r) return r; }
    if(!api.clEnqueueWriteBufferRect) return CL_INVALID_OPERATION;
    else {
        cl_int v = api.clEnqueueWriteBufferRect(command_queue,buffer,blocking_write,buffer_offset,host_offset,region,buffer_row_pitch,buffer_slice_pitch,host_row_pitch,host_slice_pitch,ptr,num_events_in_wait_list,event_wait_list,event);
        if(api.dumpFlags) printf("OPENCL-TRACE: clEnqueueWriteBufferRect(%p, %p, %d, %p, %p, %p, %lu, %lu, %lu, %lu, %p, %u, %p, %p) => %d\n", command_queue, buffer, blocking_write, buffer_offset, host_offset, region, buffer_row_pitch, buffer_slice_pitch, host_row_pitch, host_slice_pitch, ptr, num_events_in_wait_list, event_wait_list, event, v);
        return v;
    }
}

CL_API_ENTRY cl_int CL_API_CALL
clEnqueueFillBuffer(cl_command_queue    command_queue ,
                    cl_mem              buffer ,
                    const void *        pattern ,
                    size_t              pattern_size ,
                    size_t              offset ,
                    size_t              size ,
                    cl_uint             num_events_in_wait_list ,
                    const cl_event *    event_wait_list ,
                    cl_event *          event )
{
    if(!api.h) { cl_int r = clInit(); if(r) return r; }
    if(!api.clEnqueueFillBuffer) return CL_INVALID_OPERATION;
    else {
        cl_int v = api.clEnqueueFillBuffer(command_queue,buffer,pattern,pattern_size,offset,size,num_events_in_wait_list,event_wait_list,event);
        if(api.dumpFlags) printf("OPENCL-TRACE: clEnqueueFillBuffer(%p, %p, %p, %lu, %lu, %lu, %u, %p, %p) => %d\n", command_queue, buffer, pattern, pattern_size, offset, size, num_events_in_wait_list, event_wait_list, event, v);
        return v;
    }
}

CL_API_ENTRY cl_int CL_API_CALL
clEnqueueCopyBuffer(cl_command_queue     command_queue ,
                    cl_mem               src_buffer ,
                    cl_mem               dst_buffer ,
                    size_t               src_offset ,
                    size_t               dst_offset ,
                    size_t               size ,
                    cl_uint              num_events_in_wait_list ,
                    const cl_event *     event_wait_list ,
                    cl_event *           event )
{
    if(!api.h) { cl_int r = clInit(); if(r) return r; }
    if(!api.clEnqueueCopyBuffer) return CL_INVALID_OPERATION;
    else {
        cl_int v = api.clEnqueueCopyBuffer(command_queue,src_buffer,dst_buffer,src_offset,dst_offset,size,num_events_in_wait_list,event_wait_list,event);
        if(api.dumpFlags) printf("OPENCL-TRACE: clEnqueueCopyBuffer(%p, %p, %p, %lu, %lu, %lu, %u, %p, %p) => %d\n", command_queue, src_buffer, dst_buffer, src_offset, dst_offset, size, num_events_in_wait_list, event_wait_list, event, v);
        return v;
    }
}

CL_API_ENTRY cl_int CL_API_CALL
clEnqueueCopyBufferRect(cl_command_queue     command_queue ,
                        cl_mem               src_buffer ,
                        cl_mem               dst_buffer ,
                        const size_t *       src_origin ,
                        const size_t *       dst_origin ,
                        const size_t *       region ,
                        size_t               src_row_pitch ,
                        size_t               src_slice_pitch ,
                        size_t               dst_row_pitch ,
                        size_t               dst_slice_pitch ,
                        cl_uint              num_events_in_wait_list ,
                        const cl_event *     event_wait_list ,
                        cl_event *           event )
{
    if(!api.h) { cl_int r = clInit(); if(r) return r; }
    if(!api.clEnqueueCopyBufferRect) return CL_INVALID_OPERATION;
    else {
        cl_int v = api.clEnqueueCopyBufferRect(command_queue,src_buffer,dst_buffer,src_origin,dst_origin,region,src_row_pitch,src_slice_pitch,dst_row_pitch,dst_slice_pitch,num_events_in_wait_list,event_wait_list,event);
        if(api.dumpFlags) printf("OPENCL-TRACE: clEnqueueCopyBufferRect(%p, %p, %p, %p, %p, %p, %lu, %lu, %lu, %lu, %u, %p, %p) => %d\n", command_queue, src_buffer, dst_buffer, src_origin, dst_origin, region, src_row_pitch, src_slice_pitch, dst_row_pitch, dst_slice_pitch, num_events_in_wait_list, event_wait_list, event, v);
        return v;
    }
}

CL_API_ENTRY cl_int CL_API_CALL
clEnqueueReadImage(cl_command_queue      command_queue ,
                   cl_mem                image ,
                   cl_bool               blocking_read ,
                   const size_t *        origin ,
                   const size_t *        region ,
                   size_t                row_pitch ,
                   size_t                slice_pitch ,
                   void *                ptr ,
                   cl_uint               num_events_in_wait_list ,
                   const cl_event *      event_wait_list ,
                   cl_event *            event )
{
    if(!api.h) { cl_int r = clInit(); if(r) return r; }
    if(!api.clEnqueueReadImage) return CL_INVALID_OPERATION;
    else {
        cl_int v = api.clEnqueueReadImage(command_queue,image,blocking_read,origin,region,row_pitch,slice_pitch,ptr,num_events_in_wait_list,event_wait_list,event);
        if(api.dumpFlags) printf("OPENCL-TRACE: clEnqueueReadImage(%p, %p, %d, %p, %p, %lu, %lu, %p, %u, %p, %p) => %d\n", command_queue, image, blocking_read, origin, region, row_pitch, slice_pitch, ptr, num_events_in_wait_list, event_wait_list, event, v);
        return v;
    }
}

CL_API_ENTRY cl_int CL_API_CALL
clEnqueueWriteImage(cl_command_queue     command_queue ,
                    cl_mem               image ,
                    cl_bool              blocking_write ,
                    const size_t *       origin ,
                    const size_t *       region ,
                    size_t               input_row_pitch ,
                    size_t               input_slice_pitch ,
                    const void *         ptr ,
                    cl_uint              num_events_in_wait_list ,
                    const cl_event *     event_wait_list ,
                    cl_event *           event )
{
    if(!api.h) { cl_int r = clInit(); if(r) return r; }
    if(!api.clEnqueueWriteImage) return CL_INVALID_OPERATION;
    else {
        cl_int v = api.clEnqueueWriteImage(command_queue,image,blocking_write,origin,region,input_row_pitch,input_slice_pitch,ptr,num_events_in_wait_list,event_wait_list,event);
        if(api.dumpFlags) printf("OPENCL-TRACE: clEnqueueWriteImage(%p, %p, %d, %p, %p, %lu, %lu, %p, %u, %p, %p) => %d\n", command_queue, image, blocking_write, origin, region, input_row_pitch, input_slice_pitch, ptr, num_events_in_wait_list, event_wait_list, event, v);
        return v;
    }
}

CL_API_ENTRY cl_int CL_API_CALL
clEnqueueFillImage(cl_command_queue    command_queue ,
                   cl_mem              image ,
                   const void *        fill_color ,
                   const size_t *      origin ,
                   const size_t *      region ,
                   cl_uint             num_events_in_wait_list ,
                   const cl_event *    event_wait_list ,
                   cl_event *          event )
{
    if(!api.h) { cl_int r = clInit(); if(r) return r; }
    if(!api.clEnqueueFillImage) return CL_INVALID_OPERATION;
    else {
        cl_int v = api.clEnqueueFillImage(command_queue,image,fill_color,origin,region,num_events_in_wait_list,event_wait_list,event);
        if(api.dumpFlags) printf("OPENCL-TRACE: clEnqueueFillImage(%p, %p, %p, %p, %p, %u, %p, %p) => %d\n", command_queue, image, fill_color, origin, region, num_events_in_wait_list, event_wait_list, event, v);
        return v;
    }
}

CL_API_ENTRY cl_int CL_API_CALL
clEnqueueCopyImage(cl_command_queue      command_queue ,
                   cl_mem                src_image ,
                   cl_mem                dst_image ,
                   const size_t *        src_origin ,
                   const size_t *        dst_origin ,
                   const size_t *        region ,
                   cl_uint               num_events_in_wait_list ,
                   const cl_event *      event_wait_list ,
                   cl_event *            event )
{
    if(!api.h) { cl_int r = clInit(); if(r) return r; }
    if(!api.clEnqueueCopyImage) return CL_INVALID_OPERATION;
    else {
        cl_int v = api.clEnqueueCopyImage(command_queue,src_image,dst_image,src_origin,dst_origin,region,num_events_in_wait_list,event_wait_list,event);
        if(api.dumpFlags) printf("OPENCL-TRACE: clEnqueueCopyImage(%p, %p, %p, %p, %p, %p, %u, %p, %p) => %d\n", command_queue, src_image, dst_image, src_origin, dst_origin, region, num_events_in_wait_list, event_wait_list, event, v);
        return v;
    }
}

CL_API_ENTRY cl_int CL_API_CALL
clEnqueueCopyImageToBuffer(cl_command_queue  command_queue ,
                           cl_mem            src_image ,
                           cl_mem            dst_buffer ,
                           const size_t *    src_origin ,
                           const size_t *    region ,
                           size_t            dst_offset ,
                           cl_uint           num_events_in_wait_list ,
                           const cl_event *  event_wait_list ,
                           cl_event *        event )
{
    if(!api.h) { cl_int r = clInit(); if(r) return r; }
    if(!api.clEnqueueCopyImageToBuffer) return CL_INVALID_OPERATION;
    else {
        cl_int v = api.clEnqueueCopyImageToBuffer(command_queue,src_image,dst_buffer,src_origin,region,dst_offset,num_events_in_wait_list,event_wait_list,event);
        if(api.dumpFlags) printf("OPENCL-TRACE: clEnqueueCopyImageToBuffer(%p, %p, %p, %p, %p, %lu, %u, %p, %p) => %d\n", command_queue, src_image, dst_buffer, src_origin, region, dst_offset, num_events_in_wait_list, event_wait_list, event, v);
        return v;
    }
}

CL_API_ENTRY cl_int CL_API_CALL
clEnqueueCopyBufferToImage(cl_command_queue  command_queue ,
                           cl_mem            src_buffer ,
                           cl_mem            dst_image ,
                           size_t            src_offset ,
                           const size_t *    dst_origin ,
                           const size_t *    region ,
                           cl_uint           num_events_in_wait_list ,
                           const cl_event *  event_wait_list ,
                           cl_event *        event )
{
    if(!api.h) { cl_int r = clInit(); if(r) return r; }
    if(!api.clEnqueueCopyBufferToImage) return CL_INVALID_OPERATION;
    else {
        cl_int v = api.clEnqueueCopyBufferToImage(command_queue,src_buffer,dst_image,src_offset,dst_origin,region,num_events_in_wait_list,event_wait_list,event);
        if(api.dumpFlags) printf("OPENCL-TRACE: clEnqueueCopyBufferToImage(%p, %p, %p, %lu, %p, %p, %u, %p, %p) => %d\n", command_queue, src_buffer, dst_image, src_offset, dst_origin, region, num_events_in_wait_list, event_wait_list, event, v);
        return v;
    }
}

CL_API_ENTRY void * CL_API_CALL
clEnqueueMapBuffer(cl_command_queue  command_queue ,
                   cl_mem            buffer ,
                   cl_bool           blocking_map ,
                   cl_map_flags      map_flags ,
                   size_t            offset ,
                   size_t            size ,
                   cl_uint           num_events_in_wait_list ,
                   const cl_event *  event_wait_list ,
                   cl_event *        event ,
                   cl_int *          errcode_ret )
{
    if(!api.h) { cl_int r = clInit(); if(r) return 0; }
    if(!api.clEnqueueMapBuffer) return 0;
    else {
        void * v = api.clEnqueueMapBuffer(command_queue,buffer,blocking_map,map_flags,offset,size,num_events_in_wait_list,event_wait_list,event,errcode_ret);
        if(api.dumpFlags) printf("OPENCL-TRACE: clEnqueueMapBuffer(%p, %p, %d, " FMTU64 ", %lu, %lu, %u, %p, %p, %p) => %p\n", command_queue, buffer, blocking_map, map_flags, offset, size, num_events_in_wait_list, event_wait_list, event, errcode_ret, v);
        return v;
    }
}

CL_API_ENTRY void * CL_API_CALL
clEnqueueMapImage(cl_command_queue   command_queue ,
                  cl_mem             image ,
                  cl_bool            blocking_map ,
                  cl_map_flags       map_flags ,
                  const size_t *     origin ,
                  const size_t *     region ,
                  size_t *           image_row_pitch ,
                  size_t *           image_slice_pitch ,
                  cl_uint            num_events_in_wait_list ,
                  const cl_event *   event_wait_list ,
                  cl_event *         event ,
                  cl_int *           errcode_ret )
{
    if(!api.h) { cl_int r = clInit(); if(r) return 0; }
    if(!api.clEnqueueMapImage) return 0;
    else {
        void * v = api.clEnqueueMapImage(command_queue,image,blocking_map,map_flags,origin,region,image_row_pitch,image_slice_pitch,num_events_in_wait_list,event_wait_list,event,errcode_ret);
        if(api.dumpFlags) printf("OPENCL-TRACE: clEnqueueMapImage(%p, %p, %d, " FMTU64 ", %p, %p, %p, %p, %u, %p, %p, %p) => %p\n", command_queue, image, blocking_map, map_flags, origin, region, image_row_pitch, image_slice_pitch, num_events_in_wait_list, event_wait_list, event, errcode_ret, v);
        return v;
    }
}

CL_API_ENTRY cl_int CL_API_CALL
clEnqueueUnmapMemObject(cl_command_queue  command_queue ,
                        cl_mem            memobj ,
                        void *            mapped_ptr ,
                        cl_uint           num_events_in_wait_list ,
                        const cl_event *   event_wait_list ,
                        cl_event *         event )
{
    if(!api.h) { cl_int r = clInit(); if(r) return r; }
    if(!api.clEnqueueUnmapMemObject) return CL_INVALID_OPERATION;
    else {
        cl_int v = api.clEnqueueUnmapMemObject(command_queue,memobj,mapped_ptr,num_events_in_wait_list,event_wait_list,event);
        if(api.dumpFlags) printf("OPENCL-TRACE: clEnqueueUnmapMemObject(%p, %p, %p, %u, %p, %p) => %d\n", command_queue, memobj, mapped_ptr, num_events_in_wait_list, event_wait_list, event, v);
        return v;
    }
}

CL_API_ENTRY cl_int CL_API_CALL
clEnqueueMigrateMemObjects(cl_command_queue        command_queue ,
                           cl_uint                 num_mem_objects ,
                           const cl_mem *          mem_objects ,
                           cl_mem_migration_flags  flags ,
                           cl_uint                 num_events_in_wait_list ,
                           const cl_event *        event_wait_list ,
                           cl_event *              event )
{
    if(!api.h) { cl_int r = clInit(); if(r) return r; }
    if(!api.clEnqueueMigrateMemObjects) return CL_INVALID_OPERATION;
    else {
        cl_int v = api.clEnqueueMigrateMemObjects(command_queue,num_mem_objects,mem_objects,flags,num_events_in_wait_list,event_wait_list,event);
        if(api.dumpFlags) printf("OPENCL-TRACE: clEnqueueMigrateMemObjects(%p, %u, %p, " FMTU64 ", %u, %p, %p) => %d\n", command_queue, num_mem_objects, mem_objects, flags, num_events_in_wait_list, event_wait_list, event, v);
        return v;
    }
}

CL_API_ENTRY cl_int CL_API_CALL
clEnqueueNDRangeKernel(cl_command_queue  command_queue ,
                       cl_kernel         kernel ,
                       cl_uint           work_dim ,
                       const size_t *    global_work_offset ,
                       const size_t *    global_work_size ,
                       const size_t *    local_work_size ,
                       cl_uint           num_events_in_wait_list ,
                       const cl_event *  event_wait_list ,
                       cl_event *        event )
{
    if(!api.h) { cl_int r = clInit(); if(r) return r; }
    if(!api.clEnqueueNDRangeKernel) return CL_INVALID_OPERATION;
    else {
        cl_int v = api.clEnqueueNDRangeKernel(command_queue,kernel,work_dim,global_work_offset,global_work_size,local_work_size,num_events_in_wait_list,event_wait_list,event);
        if(api.dumpFlags) printf("OPENCL-TRACE: clEnqueueNDRangeKernel(%p, %p, %u, {%ld,%ld,%ld}, {%ld,%ld,%ld}, {%ld,%ld,%ld}, %u, %p, %p) => %d\n", command_queue, kernel, work_dim, (global_work_offset && work_dim > 0) ? global_work_offset[0] : -1, (global_work_offset && work_dim > 1) ? global_work_offset[1] : -1, (global_work_offset && work_dim > 2) ? global_work_offset[2] : -1, (global_work_size && work_dim > 0) ? global_work_size[0] : -1, (global_work_size && work_dim > 1) ? global_work_size[1] : -1, (global_work_size && work_dim > 2) ? global_work_size[2] : -1, (local_work_size && work_dim > 0) ? local_work_size[0] : -1, (local_work_size && work_dim > 1) ? local_work_size[1] : -1, (local_work_size && work_dim > 2) ? local_work_size[2] : -1, num_events_in_wait_list, event_wait_list, event, v);
        return v;
    }
}

CL_API_ENTRY cl_int CL_API_CALL
clEnqueueTask(cl_command_queue   command_queue ,
              cl_kernel          kernel ,
              cl_uint            num_events_in_wait_list ,
              const cl_event *   event_wait_list ,
              cl_event *         event )
{
    if(!api.h) { cl_int r = clInit(); if(r) return r; }
    if(!api.clEnqueueTask) return CL_INVALID_OPERATION;
    else {
        cl_int v = api.clEnqueueTask(command_queue,kernel,num_events_in_wait_list,event_wait_list,event);
        if(api.dumpFlags) printf("OPENCL-TRACE: clEnqueueTask(%p, %p, %u, %p, %p) => %d\n", command_queue, kernel, num_events_in_wait_list, event_wait_list, event, v);
        return v;
    }
}

CL_API_ENTRY cl_int CL_API_CALL
clEnqueueNativeKernel(cl_command_queue   command_queue ,
					  void (CL_CALLBACK * user_func)(void *),
                      void *             args ,
                      size_t             cb_args ,
                      cl_uint            num_mem_objects ,
                      const cl_mem *     mem_list ,
                      const void **      args_mem_loc ,
                      cl_uint            num_events_in_wait_list ,
                      const cl_event *   event_wait_list ,
                      cl_event *         event )
{
    if(!api.h) { cl_int r = clInit(); if(r) return r; }
    if(!api.clEnqueueNativeKernel) return CL_INVALID_OPERATION;
    else {
        cl_int v = api.clEnqueueNativeKernel(command_queue,user_func,args,cb_args,num_mem_objects,mem_list,args_mem_loc,num_events_in_wait_list,event_wait_list,event);
        if(api.dumpFlags) printf("OPENCL-TRACE: clEnqueueNativeKernel(%p, %p, %p, %lu, %u, %p, %p, %u, %p, %p) => %d\n", command_queue, user_func, args, cb_args, num_mem_objects, mem_list, args_mem_loc, num_events_in_wait_list, event_wait_list, event, v);
        return v;
    }
}

CL_API_ENTRY cl_int CL_API_CALL
clEnqueueMarkerWithWaitList(cl_command_queue  command_queue ,
                            cl_uint            num_events_in_wait_list ,
                            const cl_event *   event_wait_list ,
                            cl_event *         event )
{
    if(!api.h) { cl_int r = clInit(); if(r) return r; }
    if(!api.clEnqueueMarkerWithWaitList) return CL_INVALID_OPERATION;
    else {
        cl_int v = api.clEnqueueMarkerWithWaitList(command_queue,num_events_in_wait_list,event_wait_list,event);
        if(api.dumpFlags) printf("OPENCL-TRACE: clEnqueueMarkerWithWaitList(%p, %u, %p, %p) => %d\n", command_queue, num_events_in_wait_list, event_wait_list, event, v);
        return v;
    }
}

CL_API_ENTRY cl_int CL_API_CALL
clEnqueueBarrierWithWaitList(cl_command_queue  command_queue ,
                             cl_uint            num_events_in_wait_list ,
                             const cl_event *   event_wait_list ,
                             cl_event *         event )
{
    if(!api.h) { cl_int r = clInit(); if(r) return r; }
    if(!api.clEnqueueBarrierWithWaitList) return CL_INVALID_OPERATION;
    else {
        cl_int v = api.clEnqueueBarrierWithWaitList(command_queue,num_events_in_wait_list,event_wait_list,event);
        if(api.dumpFlags) printf("OPENCL-TRACE: clEnqueueBarrierWithWaitList(%p, %u, %p, %p) => %d\n", command_queue, num_events_in_wait_list, event_wait_list, event, v);
        return v;
    }
}

CL_API_ENTRY void * CL_API_CALL
clGetExtensionFunctionAddressForPlatform(cl_platform_id  platform ,
                                         const char *    func_name )
{
    if(!api.h) { cl_int r = clInit(); if(r) return 0; }
    if(!api.clGetExtensionFunctionAddressForPlatform) return 0;
    else {
        void * v = api.clGetExtensionFunctionAddressForPlatform(platform,func_name);
        if(api.dumpFlags) printf("OPENCL-TRACE: clGetExtensionFunctionAddressForPlatform(%p, '%s') => %p\n", platform, func_name, v);
        return v;
    }
}

CL_API_ENTRY cl_mem CL_API_CALL
clCreateImage2D(cl_context               context ,
                cl_mem_flags             flags ,
                const cl_image_format *  image_format ,
                size_t                   image_width ,
                size_t                   image_height ,
                size_t                   image_row_pitch ,
                void *                   host_ptr ,
                cl_int *                 errcode_ret )
{
    if(!api.h) { cl_int r = clInit(); if(r) return 0; }
    if(!api.clCreateImage2D) return 0;
    else {
        cl_mem v = api.clCreateImage2D(context,flags,image_format,image_width,image_height,image_row_pitch,host_ptr,errcode_ret);
        if(api.dumpFlags) printf("OPENCL-TRACE: clCreateImage2D(%p, " FMTU64 ", %p, %lu, %lu, %lu, %p, %p) => %p\n", context, flags, image_format, image_width, image_height, image_row_pitch, host_ptr, errcode_ret, v);
        return v;
    }
}

CL_API_ENTRY cl_mem CL_API_CALL
clCreateImage3D(cl_context               context ,
                cl_mem_flags             flags ,
                const cl_image_format *  image_format ,
                size_t                   image_width ,
                size_t                   image_height ,
                size_t                   image_depth ,
                size_t                   image_row_pitch ,
                size_t                   image_slice_pitch ,
                void *                   host_ptr ,
                cl_int *                 errcode_ret )
{
    if(!api.h) { cl_int r = clInit(); if(r) return 0; }
    if(!api.clCreateImage3D) return 0;
    else {
        cl_mem v = api.clCreateImage3D(context,flags,image_format,image_width,image_height,image_depth,image_row_pitch,image_slice_pitch,host_ptr,errcode_ret);
        if(api.dumpFlags) printf("OPENCL-TRACE: clCreateImage3D(%p, " FMTU64 ", %p, %lu, %lu, %lu, %lu, %lu, %p, %p) => %p\n", context, flags, image_format, image_width, image_height, image_depth, image_row_pitch, image_slice_pitch, host_ptr, errcode_ret, v);
        return v;
    }
}

CL_API_ENTRY cl_int CL_API_CALL
clEnqueueMarker(cl_command_queue     command_queue ,
                cl_event *           event )
{
    if(!api.h) { cl_int r = clInit(); if(r) return r; }
    if(!api.clEnqueueMarker) return CL_INVALID_OPERATION;
    else {
        cl_int v = api.clEnqueueMarker(command_queue,event);
        if(api.dumpFlags) printf("OPENCL-TRACE: clEnqueueMarker(%p, %p) => %d\n", command_queue, event, v);
        return v;
    }
}

CL_API_ENTRY cl_int CL_API_CALL
clEnqueueWaitForEvents(cl_command_queue  command_queue ,
                        cl_uint           num_events ,
                        const cl_event *  event_list )
{
    if(!api.h) { cl_int r = clInit(); if(r) return r; }
    if(!api.clEnqueueWaitForEvents) return CL_INVALID_OPERATION;
    else {
        cl_int v = api.clEnqueueWaitForEvents(command_queue,num_events,event_list);
        if(api.dumpFlags) printf("OPENCL-TRACE: clEnqueueWaitForEvents(%p, %u, %p) => %d\n", command_queue, num_events, event_list, v);
        return v;
    }
}

CL_API_ENTRY cl_int CL_API_CALL
clEnqueueBarrier(cl_command_queue  command_queue )
{
    if(!api.h) { cl_int r = clInit(); if(r) return r; }
    if(!api.clEnqueueBarrier) return CL_INVALID_OPERATION;
    else {
        cl_int v = api.clEnqueueBarrier(command_queue);
        if(api.dumpFlags) printf("OPENCL-TRACE: clEnqueueBarrier(%p) => %d\n", command_queue, v);
        return v;
    }
}

CL_API_ENTRY cl_int CL_API_CALL
clUnloadCompiler(void)
{
    if(!api.h) { cl_int r = clInit(); if(r) return r; }
    if(!api.clUnloadCompiler) return CL_INVALID_OPERATION;
    else {
        cl_int v = api.clUnloadCompiler();
        if(api.dumpFlags) printf("OPENCL-TRACE: clUnloadCompiler() => %d\n", v);
        return v;
    }
}

CL_API_ENTRY void * CL_API_CALL
clGetExtensionFunctionAddress(const char *  func_name )
{
    if(!api.h) { cl_int r = clInit(); if(r) return 0; }
    if(!api.clGetExtensionFunctionAddress) return 0;
    else {
        void * v = api.clGetExtensionFunctionAddress(func_name);
        if(api.dumpFlags) printf("OPENCL-TRACE: clGetExtensionFunctionAddress('%s') => %p\n", func_name, v);
        return v;
    }
}
