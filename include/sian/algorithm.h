/**
 * @file		algorithm.h
 * @brief		Learning Objectives Basic Algorithms
 * @author		Jeong Hoon (Sian) Choi
 * @version		1.0.0
 * @date		2024-05-29
 */
	 
//#pragma once
//#pragma GCC diagnostic ignored "-Wstringop-truncation"
//#pragma comment(lib, "libpthread.so")

#ifndef _HEADER_ALGORITHMH_
#define _HEADER_ALGORITHMH_

/* OS dependent */
#define OS_WINDOWS	0
#define OS_LINUX	1

#ifdef _WIN32
#define _TARGET_OS	OS_WINDOWS
#else
	#define _TARGET_OS	OS_LINUX
#endif

/* Include */

#include <utility>
#include <algorithm>
#include <numeric>

#include <random>
#include <limits>
#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>

#include <stack>
#include <queue>

#include "sian/data_structure.h"

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

/* MACRO functions */

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

/* ASM codes */
// extern "C" int func(int x, int y);

/* Data structures declaration - struct & class */

/* Functions declaration */

namespace sian {
	namespace sort {
		template <typename T>
		void selection_sort(T*, int);

		template <typename T>
		void insert_sort(T*, int);

		template <typename T>
		void bubble_sort(T*, int);

		template <typename T>
		void _merge(T*, int, int, int);

		template <typename T>
		void merge_sort(T*, int, int);

		template <typename T>
		void heap_sort(T*, int);

		template <typename T>
		[[nodiscard]] int _partition(T*, int, int);
		
		template <typename T>
		void quick_sort(T*, int, int);

		void counting_sort(int*, const int*, int, int, int);

		void _stable_inner_radix(int*, int, int digit = 1);

		void radix_sort(int*, int);

		void bucket_sort(int*, int);
	}

	namespace shuffle {
		template <typename T>
		void permute_by_sorting(T*, int);

		template <typename T>
		void randomized_in_place(T*, int);
	}

	namespace selection {
		template <typename T>
		[[nodiscard]] T min(T*, int);

		template <typename T>
		[[nodiscard]] T max(T*, int);

		template <typename T>
		[[nodiscard]] std::pair<T, T> minmax(T*, int);

		template <typename T>
	    [[nodiscard]] T select(T*, int, int, int);

		template <typename T>
		[[nodiscard]] T _median(T*, const int);

		template <typename T>
		[[nodiscard]] T _get_median(T*, const int);

		template <typename T>
		[[nodiscard]] T _partition_with_crt(T*, int, int);
		
		template <typename T>
		[[nodiscard]] T improved_select(T*, int, int);
	}
}

// void swap(Sample&, Sample&) noexcept;

/*
#ifdef __cplusplus
}
#endif
*/

#endif // OS dependency

/* Inline & Template Define Header */
#include "sian/algorithm.hpp"

#endif // Header duplicate
