### Dynamic Linking opencl.so at Runtime

> Based on OpenCL_Dyn_Load from [code.google](https://code.google.com/archive/p/electromag-with-cuda/source/default/source)

To build project which depends on OpenCL, we do not need to use libopencl.so when linking.

When excuting at runtime, it will dynamicly load the libOpenCL.so/OpenCl.dll.

For example, different Android devices may have different opencl.so from different vendors, it can load the right lib correspondingly. 