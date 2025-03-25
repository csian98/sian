/**
 * @file		binary_red_black_tree.cpp
 * @brief		binary_tree and red_black_tree speed check (AVL tree)
 * @author		Jeong Hoon (Sian) Choi
 * @version 	1.0.0
 * @date		2024-06-06
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

#include "sian/timer.h"
#include "sian/algorithm.h"
#include "sian/hash.h"
#include "sian/binary_tree.h"
#include "sian/red_black_tree.h"

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
struct Sample {
	Sample(void) {}

	Sample(int value) : value(value) {}
	T value;

	bool operator<(const Sample& other) const {
		return this->value < other.value;
	}

	bool operator!=(const Sample& other) const {
		return this->value != other.value;
	}
};

int main(int argc, char* argv[]) {
// 	std::terminate_handler default_terminate =
//	std::set_terminate(&custom_terminate_fnct);
	sian::Timer timer(4);

	sian::data_structure::BinaryTree<Sample<int>> binary_tree_ordered;
	sian::data_structure::RedBlackTree<Sample<int>> red_black_tree_ordered;
	sian::data_structure::BinaryTree<Sample<int>> binary_tree_unordered;
	sian::data_structure::RedBlackTree<Sample<int>> red_black_tree_unordered;
	
	size_t size = 1024;		// 1 KB
	int* list = new int[size];
	std::iota(list, list + size, 1);

	for (int i = 0; i < size; ++i) {
		binary_tree_ordered.insert(Sample<int>(list[i]));
		red_black_tree_ordered.insert(Sample<int>(list[i]));
	}

	sian::shuffle::randomized_in_place(list, size);
	
	for (int i = 0; i < size; ++i) {
		binary_tree_unordered.insert(Sample<int>(list[i]));
		red_black_tree_unordered.insert(Sample<int>(list[i]));
	}

	timer[0].set_name("binary tree searching ordered");
	timer[0].start();
	for (int i = 0; i < size; ++i) {
		sian::data_structure::BinaryTree<Sample<int>>::element_pointer ptr = binary_tree_ordered.find(Sample<int>(i));
	}
	timer[0].stop();
	
	timer[1].set_name("red black tree searching ordered");
	timer[1].start();
	for (int i = 0; i < size; ++i) {
		sian::data_structure::RedBlackTree<Sample<int>>::element_pointer ptr = red_black_tree_ordered.find(Sample<int>(i));
	}
	timer[1].stop();

	timer[2].set_name("binary tree searching disordered");
	timer[2].start();
	for (int i = 0; i < size; ++i) {
		sian::data_structure::BinaryTree<Sample<int>>::element_pointer ptr = binary_tree_unordered.find(Sample<int>(i));
	}
	timer[2].stop();

	timer[3].set_name("red black tree searching disordered");
	timer[3].start();
	for (int i = 0; i < size; ++i) {
		sian::data_structure::RedBlackTree<Sample<int>>::element_pointer ptr = red_black_tree_unordered.find(Sample<int>(i));
	}
	timer[3].stop();
	
	std::cout << timer;
	
	return 0;
}

#endif // OS dependency
