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

#include "opencl_dyn_load.hpp"

__clGetPlatformIDs *clGetPlatformIDs;
__clGetPlatformInfo *clGetPlatformInfo;
__clGetDeviceIDs *clGetDeviceIDs;
__clGetDeviceInfo *clGetDeviceInfo;
__clCreateContextFromType *clCreateContextFromType;
__clFinish *clFinish;
__clEnqueueReadBuffer *clEnqueueReadBuffer;
__clEnqueueReadBufferRect *clEnqueueReadBufferRect;

#if defined(_WIN32) || defined(_WIN64)

#include <Windows.h>

#ifdef UNICODE
static LPCWSTR __ClLibName = L"OpenCl.dll";
#else
static LPCSTR __ClLibName = "OpenCl.dll";
#endif

typedef HMODULE CL_LIBRARY;

cl_int CL_LOAD_LIBRARY(CL_LIBRARY *pInstance) {
  *pInstance = LoadLibrary(__ClLibName);
  if (*pInstance == NULL) {
    return CL_DEVICE_NOT_FOUND;
  }
  return CL_SUCCESS;
}

#define GET_PROC(name)                             \
  name = (__##name *)GetProcAddress(ClLib, #name); \
  if (name == NULL) return CL_DEVICE_NOT_AVAILABLE

#elif defined(__unix__) || defined(__APPLE__) || defined(__MACOSX)

#include <dlfcn.h>

#if defined(__APPLE__) || defined(__MACOSX)
static char __ClLibName[] = "/usr/lib/libOpenCL.dylib";
#else
static char __ClLibName[] = "libOpenCL.so";
#endif

typedef void *CL_LIBRARY;

cl_int CL_LOAD_LIBRARY(CL_LIBRARY *pInstance) {
  *pInstance = dlopen(__ClLibName, RTLD_NOW);
  if (*pInstance == NULL) {
    return CL_DEVICE_NOT_FOUND;
  }
  return CL_SUCCESS;
}

#define GET_PROC(name)                            \
  name = (__##name *)(size_t)dlsym(ClLib, #name); \
  if (name == NULL) return CL_DEVICE_NOT_AVAILABLE

#endif

cl_int CL_API_CALL clLibLoad() {
  CL_LIBRARY ClLib;
  cl_int result;
  result = CL_LOAD_LIBRARY(&ClLib);
  if (result != CL_SUCCESS) {
    return result;
  }
  GET_PROC(clGetPlatformIDs);
  GET_PROC(clGetPlatformInfo);
  GET_PROC(clGetDeviceIDs);
  GET_PROC(clGetDeviceInfo);
  GET_PROC(clCreateContextFromType);
  GET_PROC(clEnqueueReadBuffer);
  GET_PROC(clEnqueueReadBufferRect);
  GET_PROC(clFinish);

  return CL_SUCCESS;
}
