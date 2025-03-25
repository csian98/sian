/**
 * @file		sample_cuda.h
 * @brief		
 * @author		Jeong Hoon (Sian) Choi
 * @version		1.0.0
 * @date		2024-04-03
 */

//#pragma once
//#pragma GCC diagnostic ignored "-Wstringop-truncation"
//#pragma comment(lib, "libpthread.so")

#ifndef _HEADER_SAMPLE_CUDAH_
#define _HEADER_SAMPLE_CUDAH_

/* OS dependent */
#define OS_WINDOWS	0
#define OS_LINUX	1

#ifdef _WIN32
#define _TARGET_OS	OS_WINDOWS
#else
	#define _TARGET_OS	OS_LINUX
#endif

/* Include */

#include <cuda.h>
#include <cuda_runtime.h>
#include <device_launch_parameters.h>

#if __has_include(<iostream>)
#include <iostream>
#endif

#if _TARGET_OS == OS_WINDOWS
// Windows header
#include <Windows.h>

#elif _TARGET_OS == OS_LINUX
// Linux header
#include <sys/types.h>
#include <unistd.h>

/* C & CPP */
/*
#ifdef __cplusplus
extern "C" {
#endif
*/

/* defines typedef & constant */

#define BID_X	blockIdx.x
#define BID_Y	blockIdx.y
#define BID_Z	blockIdx.z

#define TID_X	threadIdx.x
#define TID_Y	threadIdx.y
#define TID_Z	threadIdx.z

#define GDIM_X	gridDim.x
#define GDIM_Y	gridDim.y
#define GDIM_Z	gridDim.z

#define BDIM_X	blockDim.x
#define BDIM_Y	blockDim.y
#define BDIM_Z	blockDim.z

#define TID_IN_BLOCK		(TID_Z * (BDIM_X * BDIM_Y) + TID_Y * BDIM_X + TID_X)
#define NUM_THREAD_IN_BLOCK	(BDIM_X * BDIM_Y * BDIM_Z)

#define GRID_1D_TID			((BID_X * NUM_THREAD_IN_BLOCK) + TID_IN_BLOCK)
#define GRID_2D_TID			(BID_Y * (GDIM_X * NUM_THREAD_IN_BLOCK) + GRID_1D_TID)
#define GROBAL_TID			(BID_Z * (GDIM_X * GDIM_Y * NUM_THREAD_IN_BLOCK) + GRID_2D_TID)

/* MACRO functions */

#ifndef MIN
#define MIN(a, b)	(a > b ? b : a)
#endif

#ifndef MAX
#define MAX(a, b)	(a > b ? a : b)
#endif

/* Inline define */

/* Attributes */
/*
[[noreturn]]
[[deprecated]]
[[fallthrough]]
[[nodiscard]]
[[maybe_unused]]
*/

/* Declaration */

/* Functions declaration */

void kernel_call(void);

/*
#ifdef __cplusplus
}
#endif
*/

#endif // OS dependency

/* Inline & Template Define Header */
//#include "sample.hpp"

#endif // Header duplicate
