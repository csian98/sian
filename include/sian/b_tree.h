/**
 * @file		b_tree.h
 * @brief		B Tree
 * @author		Jeong Hoon (Sian) Choi
 * @version		1.0.0
 * @date		2024-06-11
 */
	 
//#pragma once
//#pragma GCC diagnostic ignored "-Wstringop-truncation"
//#pragma comment(lib, "libpthread.so")

#ifndef _HEADER_B_TREEH_
#define _HEADER_B_TREEH_

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
#include <memory>
#include <exception>

#include <vector>

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
		class btree_exception : public std::exception {
		public:
			btree_exception(const std::string&);

		    const char* what(void) const noexcept override;

		private:
			std::string msg;
		};
		
		template <typename T>
	    struct BTreeNode {
			BTreeNode(void);

			BTreeNode(BTreeNode<T>*);

		    int find(const T&) const;

			void insert(const T&);

			void insert(const T&, int);

			void insert(const T&, BTreeNode<T>*);

			void insert_front(const T&, BTreeNode<T>*);

			void remove(const T&);

			const T& medium(void) const;

			BTreeNode* split(void);

			void merge(BTreeNode<T>*);
			
			void split_child(int);

			void merge_child(int);

			void left_rotate(int);

			void right_rotate(int);

			static int negative_index(const int);

			static T remove_predecessor(BTreeNode<T>*);

			static T remove_successor(BTreeNode<T>*);
			
			std::vector<T> keys;

			std::vector<BTreeNode<T>*> branches;

			size_t size = 0;

			bool leaf = true;

			static const size_t t;
		};

		template <typename T>
		class BTree  {
		public:
			typedef BTreeNode<T>* element_pointer;
			typedef const BTreeNode<T>* const_element_pointer;
			
			BTree(void);

			virtual ~BTree(void) noexcept;

			element_pointer find(const T&) const;

			void insert(const T&);

			void remove(const T&);

		private:
			element_pointer recursive_find(element_pointer, const T&) const;

			void recursive_insert(element_pointer, const T&);

			void recursive_remove(element_pointer, const T&);

			void delete_empty_node(const T& value);
			
			BTreeNode<T>* root;
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
#include "sian/b_tree.hpp"

#endif // Header duplicate
