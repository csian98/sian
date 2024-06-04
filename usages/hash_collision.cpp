/**
 * @file		hash_collision_check.cpp
 * @brief		hash tables collision test
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

#include <random>
#include <map>

#include <thread>
#include <mutex>
#include <shared_mutex>
#include <condition_variable>

#include "sian/timer.h"
#include "sian/algorithm.h"
#include "sian/hash.h"

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

class Sample {
public:
	Sample(double d, float f, int i) : d(d), f(f), i(i) {}

	Sample(int i): d(i * i), f(i * i), i(i) {}
private:
	double d;
	float f;
	int i;
};

template <typename T = sian::data_structure::HashTable<int>>
std::pair<int, int> collision_check(T& hash_table, int size = 10000) {
	std::map<int, int> counter;
	const int hash_size = hash_table.hash_size();
	for (int i = 0; i < hash_size; ++i) {
		counter[i] = 0;
	}

	for (int i = 0; i < size; ++i) {
		typename T::value_type element(i);
		counter[hash_table.bucket_num(element)]++;
	}

	int collision = 0, max_collision = -1;
	for (auto iter = counter.begin(); iter != counter.end(); ++iter) {
		if (iter->second > size / hash_size) collision++;

		if (iter->second > max_collision) {
			max_collision = iter->second;
		}
	}

	return std::make_pair(collision, max_collision);
}

template <typename T>
void print_hash_table(std::string_view msg, T& hash_table) {
	int hash_size = hash_table.hash_size();
	int collision_size = hash_size * hash_size;
	if (collision_size > 1000000) {
		collision_size = 1000000;
	}
	int alpha = collision_size / hash_size;
	
	auto [collision_time, max_collision] = collision_check(hash_table, collision_size);
	std::cout << "#####\n";
	std::cout << msg << "\n";
	std::cout << "Hash Size: " << hash_table.hash_size() << "\n";
	std::cout << "Collision aboout " << collision_size << " elements " << collision_time << " times [more than " << alpha << "]\n";
	std::cout << "load factor(alpha): " << alpha << ", maximum collision: " << max_collision << "\n";
	std::cout << "#####\n\n";
}

int main(int argc, char* argv[]) {
// 	std::terminate_handler default_terminate =
//	std::set_terminate(&custom_terminate_fnct);
	using namespace sian::data_structure;

	hash_functions::DefaultHashFunction<Sample> default_hash_function;
	hash_functions::MultiplyHashFunction<Sample> multiply_hash_function;
	hash_functions::UniversalHashFunction<Sample> universal_hash_function1(251);
	hash_functions::UniversalHashFunction<Sample> universal_hash_function2(191);
	hash_functions::DuplicateHashFunction<Sample> duplicate_hash_function(&universal_hash_function1, &universal_hash_function2);
	
	HashTable<Sample> hashtable1(&default_hash_function);
	HashTable<Sample> hashtable2(&multiply_hash_function);
	HashTable<Sample> hashtable3(&universal_hash_function1);
	HashTable<Sample> hashtable4(&duplicate_hash_function);
	
	print_hash_table("hashtable with default hash function", hashtable1);
	print_hash_table("hashtable with multiply hash function", hashtable2);
	print_hash_table("hashtable with universal hash function", hashtable3);
	print_hash_table("hashtable with duplicate hash function", hashtable4);

	HashTable<Sample> hashtable5(&universal_hash_function2);
	OpenAddressing<Sample> hashtable6(&universal_hash_function2);
	DoubleHashTable<Sample> hashtable7(&universal_hash_function2, &universal_hash_function1);

	std::cout << "\n" << std::endl;
	print_hash_table("hashtable with universal hash function", hashtable5);
	print_hash_table("open addressing with universal hash function", hashtable6);
	print_hash_table("double hashtable with universal hash function", hashtable7);

	return 0;
}

#endif // OS dependency
