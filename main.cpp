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
  init();
  return 0;
}

#endif