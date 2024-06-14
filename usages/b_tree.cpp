/**
 * @file		main.cpp
 * @brief		
 * @author		Jeong Hoon (Sian) Choi
 * @version 	1.0.0
 * @date		2024-06-03
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

#include <limits>
#include <random>
#include <map>

#include <thread>
#include <mutex>
#include <shared_mutex>
#include <condition_variable>


#include "sian/timer.h"
#include "sian/algorithm.h"
#include "sian/hash.h"
#include "sian/binary_tree.h"
#include "sian/red_black_tree.h"
#include "sian/functional_tree.h"

#include "sian/b_tree.h"

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

int main(int argc, char* argv[]) {
// 	std::terminate_handler default_terminate =
//	std::set_terminate(&custom_terminate_fnct);
	sian::Timer timer(1);
	sian::data_structure::BTree<int> b_tree;
	const size_t size = 10000;
	int* list = new int[size];
	std::iota(list, list + size, 1);
	sian::shuffle::randomized_in_place(list, size);

	timer[0].set_name("B-Tree");
	timer[0].start();

	for (int i = 0; i < size; ++i) {
		b_tree.insert(list[i]);
	}

	std::cout << b_tree.find(list[size - 3]) << std::endl;
	std::cout << b_tree.find(list[size - 1]) << std::endl;

	for (int i = 0; i < size - 2; ++i) {
		b_tree.remove(list[i]);
	}

	std::cout << b_tree.find(list[size - 3]) << std::endl;
	std::cout << b_tree.find(list[size - 1]) << std::endl;
	
	timer[0].stop();

	std::cout << timer;
    
	return 0;
}

#endif // OS dependency
