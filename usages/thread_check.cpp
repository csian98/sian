
/**
 * @file		thread_check.cpp
 * @brief		find efficient thread number
 * @author  	Jeong Hoon (Sian) Choi
 * @version 	1.0.0
 * @date		2024-05-23
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

#include <fstream>
#include <ios>

#include <utility>
#include <algorithm>
#include <numeric>
#include <vector>

#include <memory>
#include <random>
#include <iterator>
#include <execution>

#include <locale>
#include <regex>

#include <ratio>
#include <chrono>
#include <filesystem>

#include <thread>
#include <atomic>
#include <mutex>
#include <shared_mutex>
#include <condition_variable>
#include <future>

#include "sian/timer.h"

#if _TARGET_OS == OS_WINDOWS

#elif _TARGET_OS == OS_LINUX

#include <iostream>
#include <stdlib.h>

std::mutex mtx;

void thread_function(const double* v1, const double* v2, double& inner_product,
					 const int size, const int thread, const int ind) {
	thread_local int each = std::ceil((static_cast<float>(size) / thread));
	thread_local double local_inner_product = 0;
	for (int i = ind * each; i < (ind + 1) * each; ++i) {
		if (i < size) {
			for (int j = 0; j < size; ++j) {
				local_inner_product += v1[i * size + j] * v2[j * size + i];
			}
		}
	}
	mtx.lock();
	inner_product += local_inner_product;
	mtx.unlock();
}

int main(int argc, char* argv[]) {
	const int vector_size = 1024;
	const unsigned int ncpus = std::thread::hardware_concurrency();

	sian::Timer timer(ncpus * 2);

	double* v1 = new double[vector_size * vector_size];
	double* v2 = new double[vector_size * vector_size];
    double inner_product;

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<double> dist(-1.0, 1.0);
	timer[0].set_name("random initialize");
	timer[0].start();
	for(int i = 0; i < vector_size * vector_size; ++i) {
		v1[i] = dist(gen);
		v2[i] = dist(gen);
	}
	timer[0].stop();

	for (int i = 1; i < 2 * ncpus; i++) {
		timer[i].start();
		std::ostringstream str;
		str << i << " number of core";
		timer[i].set_name(str.view());
		std::vector<std::thread> threads;
		for (int j = 0; j < i; ++j) {
			threads.push_back(std::thread(thread_function, v1, v2, std::ref(inner_product),
										  vector_size, i, j));
		}
		for (auto& thread
				 : threads) {
			thread.join();
		}
		timer[i].stop();
	}

	std::cout << timer << std::endl;

	delete[] v2;
	delete[] v1;
	
	return 0;
}

#endif // OS dependency
