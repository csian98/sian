/**
 * @file		binary_tree.h
 * @brief		Learning Objectives Basic Data Structures
 * @author		Jeong Hoon (Sian) Choi
 * @version		1.0.0
 * @date		2024-06-03
 */
	 
//#pragma once
//#pragma GCC diagnostic ignored "-Wstringop-truncation"
//#pragma comment(lib, "libpthread.so")

#ifndef _HEADER_BINARY_TREEH_
#define _HEADER_BINARY_TREEH_

/* OS dependent */
#define OS_WINDOWS	0
#define OS_LINUX	1

#ifdef _WIN32
#define _TARGET_OS	OS_WINDOWS
#else
	#define _TARGET_OS	OS_LINUX
#endif

/* Include */

#include <initializer_list>

#include "sian/data_structure.h"
#include "sian/algorithm.h"

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
		struct Leaf {
			Leaf* left = nullptr;
			Leaf* right = nullptr;
			Leaf* parent = nullptr;
			
			T value = 0;
		};

		template <typename T>
		class BinaryTree {
		public:
			typedef Leaf<T>* element_pointer;
			typedef const Leaf<T>* const_element_pointer;

			BinaryTree(void);

			BinaryTree(std::initializer_list<T>);

			virtual ~BinaryTree(void) noexcept;

			void insert(const T&);

			void remove(Leaf<T>*);

			void remove(T&);

		    Leaf<T>* find(const T&) const;

			Leaf<T>* min(void) const;

			Leaf<T>* max(void) const;

			T min_value(void) const;

			T max_value(void) const;

		private:
			void inorder_tree_delete(Leaf<T>* ptr);
			
			Leaf<T>* root;
		};
	}
}

#endif // OS dependency

/* Inline & Template Define Header */
#include "sian/binary_tree.hpp"

#endif // Header duplicate
