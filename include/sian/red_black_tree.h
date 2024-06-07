/**
 * @file		red_black_tree.h
 * @brief		Red-Black Tree
 * @author		Jeong Hoon (Sian) Choi
 * @version		1.0.0
 * @date		2024-06-05
 */
	 
//#pragma once
//#pragma GCC diagnostic ignored "-Wstringop-truncation"
//#pragma comment(lib, "libpthread.so")

#ifndef _HEADER_RED_BLACK_TREEH_
#define _HEADER_RED_BLACK_TREEH_

/* OS dependent */
#define OS_WINDOWS	0
#define OS_LINUX	1

#ifdef _WIN32
#define _TARGET_OS	OS_WINDOWS
#else
	#define _TARGET_OS	OS_LINUX
#endif

/* Include */

#include "sian/binary_tree.h"

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
		struct RedBlackLeaf : public Leaf<T> {
			bool is_black = false;
		};

		template <typename T>
		class RedBlackTree : public Tree<T> {
		public:
			typedef Leaf<T>* element_pointer;
			typedef const Leaf<T>* const_element_pointer;
		
			RedBlackTree(void);

			RedBlackTree(std::initializer_list<T>);

			virtual ~RedBlackTree(void) noexcept;

			virtual void insert(const T&) override;

			virtual void remove(element_pointer) override;

			virtual element_pointer find(const T&) const override;

			virtual element_pointer min(element_pointer) const override;

			virtual element_pointer max(element_pointer) const override;
			
			virtual element_pointer min(void) const;

			virtual element_pointer max(void) const;

			virtual element_pointer successor(element_pointer) const;
			
			virtual element_pointer predecessor(element_pointer) const;

			virtual bool is_empty(void) const override;
			
		protected:
			virtual void inorder_tree_delete(element_pointer ptr) override;
			
			virtual void transplant(element_pointer, element_pointer);
			
			virtual void left_rotate(element_pointer);

			virtual void right_rotate(element_pointer);

			virtual void insert_fixup(element_pointer);

			virtual void remove_fixup(element_pointer);

			Leaf<T>* nil_leaf = nullptr;
		};
	}
}

/* Functions declaration */

namespace sian {
	namespace data_structure {
		template <typename T>
		bool is_black(Leaf<T>* leaf);

		template <typename T>
		void color_black(Leaf<T>* leaf);

		template <typename T>
		void color_red(Leaf<T>* leaf);
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
#include "sian/red_black_tree.hpp"

#endif // Header duplicate
