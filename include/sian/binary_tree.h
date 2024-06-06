/**
 * @file		binary_tree.h
 * @brief	    Binary Tree
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

			virtual void insert(const T&);

			virtual void remove(Leaf<T>*);

			virtual void remove(const T&);

		    virtual Leaf<T>* find(const T&) const;

			virtual Leaf<T>* min(void) const;

			virtual Leaf<T>* max(void) const;

			virtual Leaf<T>* min(Leaf<T>*) const;

			virtual Leaf<T>* max(Leaf<T>*) const;

			virtual T min_value(void) const;

			virtual T max_value(void) const;

			virtual Leaf<T>* successor(Leaf<T>*) const;

			virtual Leaf<T>* predecessor(Leaf<T>*) const;

			virtual bool is_empty(void) const;

		protected:
			virtual void inorder_tree_delete(Leaf<T>* ptr);

			virtual void transplant(Leaf<T>*, Leaf<T>*);
			
			Leaf<T>* root = nullptr;
		};
	}
}

#endif // OS dependency

/* Inline & Template Define Header */
#include "sian/binary_tree.hpp"

#endif // Header duplicate
