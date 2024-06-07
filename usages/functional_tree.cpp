/**
 * @file		functional_tree.cpp
 * @brief		selection tree and interval tree usage
 * @author		Jeong Hoon (Sian) Choi
 * @version 	1.0.0
 * @date		2024-06-07
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

std::pair<int, int> random_pair(std::mt19937& engine) {
	//static int low = std::numeric_limits<int>::min();
	//static int high = std::numeric_limits<int>::max();
	static int low = -1000;
	static int high = 1000;
	std::uniform_int_distribution<int> dist(low, high);
	int first = 0, second = 0;
	first = dist(engine);
	do {
		second = dist(engine);
	} while(first == second);
	
	if (first > second) {
		std::swap(first, second);
	}
	
	return std::make_pair(first, second);
}

int main(int argc, char* argv[]) {
// 	std::terminate_handler default_terminate =
//	std::set_terminate(&custom_terminate_fnct);
	sian::Timer timer(4);
	
	sian::data_structure::RedBlackTree<int> red_black_tree;
	sian::data_structure::SelectionTree<int> selection_tree;
	sian::data_structure::IntervalTree<int> interval_tree;
	
	const size_t size = 64;
	const int begin = 1;
	int* list = new int[size];
	std::iota(list, list + size, begin);
	sian::shuffle::randomized_in_place(list, size);

	std::random_device rd;
	std::mt19937 engine(rd());
	std::uniform_int_distribution<int> dist(begin, begin + size - 1);

	for (int i = 0; i < size; ++i) {
		selection_tree.insert(list[i]);
		red_black_tree.insert(list[i]);
	}
	timer[0].set_name("Red Black Tree find ranking");
	timer[0].start();
	for (int i = 0; i < 10; ++i) {
		int random_seq = dist(engine);
		sian::data_structure::RedBlackTree<int>::element_pointer ptr = red_black_tree.find(random_seq);
		int rank = 0;
		while (ptr) {
			rank++;
			ptr = red_black_tree.predecessor(ptr);
		}
	}
	timer[0].stop();
	
	timer[1].set_name("Selection Tree find ranking");
	timer[1].start();
	for (int i = 0; i < 10; ++i) {
		int random_seq = dist(engine);
		sian::data_structure::SelectionTree<int>::element_pointer ptr = selection_tree.find(random_seq);
	}
	timer[1].stop();

	timer[2].set_name("Interval find interval");
	timer[2].start();
	for (int i = 0; i < size; ++i) {
		auto [low, high] = random_pair(engine);
		interval_tree.insert(low, high);
	}
	for (int i = 0; i < size; ++i) {
		auto [low, high] = random_pair(engine);
		sian::data_structure::Interval<int> interval(low, high);
		sian::data_structure::IntervalTree<int>::element_pointer ptr = interval_tree.find(interval);
		if (ptr)
			std::cout << interval << " is overlapped by " << ptr->value << std::endl;
		else
			std::cout << interval << " has not be overlapped" << std::endl;
	}
	timer[2].stop();
	

	std::cout << timer;
	
	return 0;
}

#endif // OS dependency
