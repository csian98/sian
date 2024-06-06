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
		class RedBlackTree : public BinaryTree<T> {
		public:
			RedBlackTree(void);

			RedBlackTree(std::initializer_list<T>);

			virtual ~RedBlackTree(void) noexcept;

			virtual void insert(const T&) override;

			virtual void remove(Leaf<T>*) override;

			virtual Leaf<T>* find(const T&) const override;

			virtual Leaf<T>* min(Leaf<T>*) const override;

			virtual Leaf<T>* max(Leaf<T>*) const override;

			virtual Leaf<T>* min(void) const override;

			virtual Leaf<T>* max(void) const override;

			virtual Leaf<T>* successor(Leaf<T>*) const override;
			
			virtual Leaf<T>* predecessor(Leaf<T>*) const override;

			virtual bool is_empty(void) const override;
			
		private:

			virtual void transplant(Leaf<T>*, Leaf<T>*) override;
			
			virtual void left_rotate(Leaf<T>*);

			virtual void right_rotate(Leaf<T>*);

			virtual void insert_fixup(Leaf<T>*);

			virtual void remove_fixup(Leaf<T>*);

			virtual void cut_leaf(Leaf<T>*);

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
