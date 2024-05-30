/**
 * @file		data_structure.h
 * @brief		basic data structures (learning purpose source codes)
 * @author		Jeong Hoon (Sian) Choi
 * @version		1.0.0
 * @date		2024-05-29
 */
	 
//#pragma once
//#pragma GCC diagnostic ignored "-Wstringop-truncation"
//#pragma comment(lib, "libpthread.so")

#ifndef _HEADER_DATA_STRUCTUREH_
#define _HEADER_DATA_STRUCTUREH_

/* OS dependent */
#define OS_WINDOWS	0
#define OS_LINUX	1

#ifdef _WIN32
#define _TARGET_OS	OS_WINDOWS
#else
	#define _TARGET_OS	OS_LINUX
#endif

/* Include */

#include <algorithm>
#include <utility>
#include <numeric>
#include <cmath>

#include <optional>

#include <initializer_list>
#include <vector>
#include <list>

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

namespace sian {
    namespace data_structure {
		template <typename T>
		class Heap {
		public:
			Heap(void);
			
			Heap(std::initializer_list<T>);

			Heap(T*, int);

			~Heap(void) noexcept;

			int get_heap_size(void) const;

			void push(T);

			T pop(void);

			void sort(T*, int, bool heapify = true);
		private:
			void realloc(void);

			void max_heapify(int);

			void build_max_heap(void);
			
			T* tree;

			int heap_size, heap_max;
		};

		template <typename T>
		struct Node {
			Node* prev = nullptr;
			Node* next = nullptr;
			T value = 0;
		};

		template <typename T>
		class List {
		public:
			List(void);

			List(std::initializer_list<T>);

			~List(void) noexcept;

			Node<T>* front(void) const;

			Node<T>* back(void) const;

			void push_back(T value);

			void insert_next(Node<T>*, T);

			void insert_sorted(T);

			Node<T>* operator[](int) const;
		private:
			Node<T>* begin = nullptr;
			
			Node<T>* end = nullptr;
		};
	}
}

/* Functions declaration */

// void swap(Sample&, Sample&) noexcept;

/*
#ifdef __cplusplus
}
#endif
*/

#endif // OS dependency

/* Inline & Template Define Header */
#include "sian/data_structure.hpp"

#endif // Header duplicate
