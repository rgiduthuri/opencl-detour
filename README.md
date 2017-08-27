# OpenCL API Detour
Useful to trace OpenCL calls to help debug your application. 
Set environment variable `OPENCL_DUMP_FLAGS=1` to print the OpenCL API call trace to console.

Either add `opencl-detour.cpp` to your project or use create a separate shared library using `CMakeLists.txt` in this project.

Also make sure to specify original OpenCL shared library location in your system using `#define OPENCL_TRACE_LIBRARY` in `opencl-detour.cpp`.

The `opencl-detour.cpp` was generated using OpenCL 1.2 header file [opencl12/CL/cl.h](https://github.com/KhronosGroup/OpenCL-Headers/blob/master/opencl12/CL/cl.h)
with additional support of clCreateCommandQueueWithProperties API.

# Want to contribute?
Feel free to submit issues and/or pull requests for contributions.
