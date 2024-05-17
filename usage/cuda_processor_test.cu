/**
 * @file		main.cpp
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

#include <iostream>

#include <random>

#include <thread>
#include <mutex>
#include <shared_mutex>
#include <condition_variable>

#include "cuda.h"
#include "cuda_runtime.h"
#include "device_launch_parameters.h"


#include "sian/timer.h"

#define OS_WINDOWS	0
#define OS_LINUX	1

#ifdef _WIN32
#define _TARGET_OS	OS_WINDOWS
#else
	#define _TARGET_OS	OS_LINUX
#endif

#if _TARGET_OS == OS_WINDOWS

#elif _TARGET_OS == OS_LINUX

// void custom_terminate_fnct(void) {
//	exit(1);
// }

void single_matrix_multiply(const double* a, const double* b, double* c, int size) {
	for (int i = 0; i < size * size; ++i) {
		for (int j = 0; j < size; ++j) {
			int col = i % size;
			int row = i / size;
			c[i] += a[row * size + j] * b[size * j + col];
		}
	}
}

void thread_function(const double* a, const double* b, double* c, int size, int thread_num, int index) {
	int each = std::ceil(size / thread_num);
	for (int i = index * (each * size); i < (index + 1)* (each * size); ++i) {
		if (i >= size * size) return;
		for (int j = 0; j < size; ++j) {
			int col = i % size;
			int row = i / size;
			c[i] += a[row * size + j] * b[size * j + col];
		}
	}
}

__global__ void gpu_kernel(const double* a, const double* b, double* c, int size) {
	int col = blockDim.x * blockIdx.x + threadIdx.x;
	int row = blockDim.y * blockIdx.y + threadIdx.y;
    int index = size * row + col;
	if (index >= size * size) return;
    for (int i = 0; i < size; ++i) {
		c[index] += a[row * size + i] * b[size * i + col];
	}
}

int main(int argc, char* argv[]) {
// 	std::terminate_handler default_terminate =
//	std::set_terminate(&custom_terminate_fnct);
	const int matrix_size = 1024;

	sian::Timer timer(3);

	double* matrix_a = new double[matrix_size * matrix_size];
	double* matrix_b = new double[matrix_size * matrix_size];

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<double> dist(-1.0, 1.0);

	for (int i = 0; i < matrix_size * matrix_size; ++i) {
		matrix_a[i] = dist(gen);
		matrix_b[i] = dist(gen);
	}

	// CPU single processing
	timer[0].set_name("CPU Single Processing");
	double* matrix_c1 = new double[matrix_size * matrix_size];
	timer[0].start();
	single_matrix_multiply(matrix_a, matrix_b, matrix_c1, matrix_size);
	timer[0].stop();

	// CPU multi processing
	timer[1].set_name("CPU Multi Processing");
	int ncpus = std::thread::hardware_concurrency();
	std::vector<std::thread> threads;
	double* matrix_c2 = new double[matrix_size * matrix_size];
	timer[1].start();
	for (int i = 0; i < ncpus; ++i) {
		threads.emplace_back(&thread_function, matrix_a, matrix_b, matrix_c2, matrix_size, ncpus, i);
	}
	for (auto& thread : threads) thread.join();
	timer[1].stop();

	// GPU single instruction multi threads
	timer[2].set_name("GPU SIMT");
	double *d_matrix_a, *d_matrix_b, *d_matrix_c;
	double* matrix_c3 = new double[matrix_size * matrix_size];
	timer[2].start();
	cudaMalloc(&d_matrix_a, sizeof(double) * matrix_size * matrix_size);
	cudaMalloc(&d_matrix_b, sizeof(double) * matrix_size * matrix_size);
	cudaMalloc(&d_matrix_c, sizeof(double) * matrix_size * matrix_size);

	cudaMemset(d_matrix_c, 0.0, sizeof(double) * matrix_size * matrix_size);
	cudaMemcpy(d_matrix_a, matrix_a, sizeof(double) * matrix_size * matrix_size, cudaMemcpyHostToDevice);
	cudaMemcpy(d_matrix_b, matrix_b, sizeof(double) * matrix_size * matrix_size, cudaMemcpyHostToDevice);

	const int block_size = 16;
	dim3 grid_dim(std::ceil(static_cast<float>(matrix_size) / block_size),
				  std::ceil(static_cast<float>(matrix_size) / block_size));
	dim3 block_dim(block_size, block_size);
	gpu_kernel<<<grid_dim, block_dim>>>(d_matrix_a, d_matrix_b, d_matrix_c, matrix_size);
	
	cudaMemcpy(matrix_c3, d_matrix_c, sizeof(double) * matrix_size * matrix_size, cudaMemcpyDeviceToHost);

	cudaFree(d_matrix_c);
	cudaFree(d_matrix_b);
	cudaFree(d_matrix_a);
	
	cudaDeviceSynchronize();
	timer[2].stop();

	std::cout << timer << std::endl;

	delete[] matrix_c3;
	delete[] matrix_c2;
	delete[] matrix_c1;
	
	delete[] matrix_b;
	delete[] matrix_a;
	
	return 0;
}

#endif // OS dependency
