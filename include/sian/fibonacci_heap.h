/**
 * @file		fibonacci_heap.h
 * @brief		Fibonacci Heap
 * @author		Jeong Hoon (Sian) Choi
 * @version		1.0.0
 * @date		2024-06-15
 */
	 
//#pragma once
//#pragma GCC diagnostic ignored "-Wstringop-truncation"
//#pragma comment(lib, "libpthread.so")

#ifndef _HEADER_FIBONACCI_HEAPH_
#define _HEADER_FIBONACCI_HEAPH_

/* OS dependent */
#define OS_WINDOWS	0
#define OS_LINUX	1

#ifdef _WIN32
#define _TARGET_OS	OS_WINDOWS
#else
	#define _TARGET_OS	OS_LINUX
#endif

/* Include */

#include <vector>

#include "binary_tree.h"

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
		struct FibonacciNode : public Leaf<T> {
			FibonacciNode(void);

			FibonacciNode(const T&);

			void insert(Leaf<T>*);

			Leaf<T>* child = nullptr;

			size_t degree = 0;

			bool mark = false;
		};

		template <typename T>
		class FibonacciHeap {
		public:
			typedef Leaf<T>* element_pointer;
			typedef const Leaf<T>* const_element_pointer;
			
			FibonacciHeap(void);

			virtual ~FibonacciHeap(void) noexcept;

		    void insert(const T&);

			FibonacciHeap<T>* make_union(FibonacciHeap<T>*);

			T minimum(void) const;

			bool empty(void) const;

			static FibonacciHeap<T>* make_new_heap(void);

		private:
			size_t size = 0;

			Leaf<T>* min = nullptr;
		};
	}
}

/* Functions declaration */

namespace sian {
	namespace data_structure {
		template <typename T>
		bool fibonaccinode_get_mark(Leaf<T>*);

		template <typename T>
		void fibonaccinode_set_mark(Leaf<T>*, bool);

		template <typename T>
		const Leaf<T>* fibonacciheap_get_child(Leaf<T>*);

		template <typename T>
		Leaf<T>* fibonacciheap_set_child(Leaf<T>*, Leaf<T>*);
	}
}

/*
#ifdef __cplusplus
}
#endif
*/

#endif // OS dependency

/* Inline & Template Define Header */
#include "fibonacci_heap.hpp"

#endif // Header duplicate
