/**
 * @file		main.cu
 * @brief		
 * @author		Jeong Hoon (Sian) Choi
 * @version 	1.0.0
 * @date		2024-04-03
 */

/* Copyright (C)
 * 2024 - Jeong Hoon (Sian) Choi
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 */

#include <cuda.h>
#include <cuda_runtime.h>
#include <device_launch_parameters.h>

#include "sample.cuh"

#if _TARGET_OS == OS_WINDOWS

#elif _TARGET_OS == OS_LINUX

// void custom_terminate_fnct(void) {
//	exit(1);
// }

__host__ int main(int argc, char* argv[]) {
// 	std::terminate_handler default_terminate =
//	std::set_terminate(&custom_terminate_fnct);
	void *d_ptr, *h_ptr;
	size_t allocate = 4096;

	h_ptr = malloc(sizeof(std::byte)*allocate);
	memset(h_ptr, 0, sizeof(std::byte)*allocate);

	// memory processing in host
	
    if (auto error = cudaMalloc(&d_ptr, sizeof(std::byte)*allocate) != cudaSuccess) {
		std::cerr << cudaGetErrorName(error) << std::endl;
		exit(1);
	}
	
	if (auto error = cudaMemset(&d_ptr, 0, sizeof(std::byte)*allocate) != cudaSuccess) {
		std::cerr << cudaGetErrorName(error) << std::endl;
		exit(1);
	}

	if (auto error = cudaMemcpy(d_ptr, h_ptr, sizeof(std::byte)*allocate) != cudaSuccess) {
		std::cerr << cudaGetErrorName(error) << std::endl;
		exit(1);
	}

//	kernel<<<1, 10>>>();

    if (auto error = cudaDeviceSynchronize() != cudaSuccess) {
		std::cerr << cudaGetErrorName(error) << std::endl;
		exit(1);
	}

	if (auto error = cudaMemcpy(h_ptr, d_ptr, sizeof(std::byte)*allocate, cudaMemcpyDeviceToHost) != cudaSuccess) {
		std::cerr << cudaGetErrorName(error) << std::endl;
		exit(1);
	}
	
	if (auto error = cudaFree(d_ptr) != cudaSuccess) {
		std::cerr << cudaGetErrorName(error) << std::endl;
		exit(1);
	}
	free(h_ptr);

	return 0;
}

#endif // OS dependency
