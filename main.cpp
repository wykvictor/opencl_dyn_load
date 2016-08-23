#ifdef HAVE_OPENCL

#include <iostream>
#include "opencl_dyn_load.hpp"

bool init() {
  // Load the driver
  if (clLibLoad() != CL_SUCCESS) {
    std::cout << " Failed to load OpenCL Library" << std::endl;
    return false;
  }
  std::cout << " Load OpenCL Library Successfully" << std::endl;
  return true;
}

int main() {
  init();  // clLibLoad must be called prior to calling anu other cl*() function

  // Example to use opencl: these functions must be decalared in opencl_dyn_load.hpp
  cl_uint platformCount;
  cl_platform_id* platforms;
  cl_uint deviceCount;
  cl_device_id* devices;
  char* platformName;
  size_t size;
  char extension[1024];

  // get all platforms
  clGetPlatformIDs(0, NULL, &platformCount);
  platforms = new cl_platform_id[platformCount];
  clGetPlatformIDs(platformCount, platforms, NULL);

  for (int i = 0; i < platformCount; i++) {
    // get all devices
    clGetDeviceIDs(platforms[i], CL_DEVICE_TYPE_GPU, 0, NULL, &deviceCount);
    devices = new cl_device_id[deviceCount];
    clGetDeviceIDs(platforms[i], CL_DEVICE_TYPE_GPU, deviceCount, devices, NULL);

    clGetPlatformInfo(platforms[i], CL_PLATFORM_NAME, 0, NULL, &size);
    platformName = new char[size];
    clGetPlatformInfo(platforms[i], CL_PLATFORM_NAME, size, platformName, NULL);

    for (int j = 0; j < deviceCount; j++) {
      int maxComputeUnits, maxClockFrequency;
      clGetDeviceInfo(devices[j], CL_DEVICE_MAX_COMPUTE_UNITS, sizeof(maxComputeUnits),
                      &maxComputeUnits, NULL);
      clGetDeviceInfo(devices[j], CL_DEVICE_MAX_CLOCK_FREQUENCY, sizeof(maxClockFrequency),
                      &maxClockFrequency, NULL);

      int score = maxComputeUnits * maxClockFrequency;
      std::cout << platformName << " " << score << std::endl;
    }

    delete platformName;
    delete devices;
  }
  delete platforms;

  return 0;
}

#endif