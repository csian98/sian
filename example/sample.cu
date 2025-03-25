/**
 * @file		sample.cu
 * @brief		
 * @author		Jeong Hoon (Sian) Choi
 * @version 	1.0.0
 * @date		2024-04-03
 */

#include "sample_cuda.h"

/* C & CPP */
/*
#ifdef __cplusplus
extern "C" {
#endif
*/

#if _TARGET_OS == OS_WINDOWS

#elif _TARGET_OS == OS_LINUX

/* Definition */

/* Cuda Global & Device definition */

__global__ void kernel(void) {
//
}

/* Cuda Host Difinition */

void kernel_call(void) {	
	/*
	  // heterogeneous computing
	int ngpus;
	cudaGetDeviceCount(&ngpus);

	for (int device = 0; devcie < gpus; ++device) {
		cudaSetDevice(device);
		//
	}
	*/
	// kernel<<<dim3_grid, dim3_blk, dynamic_shared_size, stream>>>();
	
	// cudaDeviceSyncronize();
}

#endif // OS dependency

/*
#ifdef __cplusplus
}
#endif
*/
