/**
 * @file		sorting.cpp
 * @brief		compare sorting speed
 * @author		Jeong Hoon (Sian) Choi
 * @version 	1.0.0
 * @date		2024-05-30
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

#include "sian/timer.h"
#include "sian/algorithm.h"

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


template <typename T>
void print(T* list, int size) {
	for (int i = 0; i < size; ++i) std::cout << list[i] << " ";
	std::cout << std::endl;
}

template <typename T>
void check(T* list, int size) {
	bool result = true;
	for (int i = 0; i < size - 1; ++i) {
		if (list[i] > list[i + 1]) result = false;
	}

	std::cout << "result : " << std::boolalpha << result << std::endl;
}

template <typename T>
void copy(T* dst, const T* src, int size) {
	for (int i = 0; i < size; ++i) dst[i] = src[i];
}

int main(int argc, char* argv[]) {
// 	std::terminate_handler default_terminate =
//	std::set_terminate(&custom_terminate_fnct);
	sian::Timer timer(9);
	
	int size = 2048;
	int* list = new int[size];
	int* tmp = new int[size];

	int min = 0, max = 10000;

	std::random_device rd;
	std::mt19937 engine(rd());
	std::uniform_int_distribution<int> dist(min, max);

	for (int i = 0; i < size; ++i) list[i] = dist(engine);
	
	//
	copy(tmp, list, size);
	timer[0].set_name("insert sorting");
	timer[0].start();
	sian::sort::insert_sort(tmp, size);
	timer[0].stop();
	check(tmp, size);
	//
	copy(tmp, list, size);
	timer[1].set_name("bubble sorting");
	timer[1].start();
	sian::sort::bubble_sort(tmp, size);
	timer[1].stop();
	check(tmp, size);
	//
	copy(tmp, list, size);
	timer[2].set_name("selection sorting");
	timer[2].start();
	sian::sort::selection_sort(tmp, size);
	timer[2].stop();
	check(tmp, size);
	//
	copy(tmp, list, size);
	timer[3].set_name("merge sorting");
	timer[3].start();
	sian::sort::merge_sort(tmp, 0, size);
	timer[3].stop();
	check(tmp, size);
	//
	copy(tmp, list, size);
	timer[4].set_name("heap sorting");
	timer[4].start();
	sian::sort::heap_sort(tmp, size);
	timer[4].stop();
	check(tmp, size);
	//
	copy(tmp, list, size);
	timer[5].set_name("quick sorting");
	timer[5].start();
	sian::sort::quick_sort(tmp, 0, size);
	timer[5].stop();
	check(tmp, size);
	//
	copy(tmp, list, size);
	timer[6].set_name("counting sorting");
	timer[6].start();
	sian::sort::counting_sort(tmp, list, size, min, max);
	timer[6].stop();
    check(tmp, size);
	//
	copy(tmp, list, size);
	timer[7].set_name("radix sorting");
	timer[7].start();
	sian::sort::radix_sort(tmp, size);
	timer[7].stop();
	check(tmp, size);
	//
	copy(tmp, list, size);
	timer[8].set_name("bucket sorting");
	timer[8].start();
	sian::sort::bucket_sort(tmp, size);
	timer[8].stop();
	check(tmp, size);
	
	std::cout << timer;

	delete[] tmp;
	delete[] list;
	
	return 0;
}

#endif // OS dependency
