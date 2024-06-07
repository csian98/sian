/**
 * @file		sample.h
 * @brief		Selection and Interval tree; extension of Red Black tree
 * @author		Jeong Hoon (Sian) Choi
 * @version		1.0.0
 * @date		2024-06-06
 */
	 
//#pragma once
//#pragma GCC diagnostic ignored "-Wstringop-truncation"
//#pragma comment(lib, "libpthread.so")

#ifndef _HEADER_SELECTION_TREEH_
#define _HEADER_SELECTION_TREEH_

/* OS dependent */
#define OS_WINDOWS	0
#define OS_LINUX	1

#ifdef _WIN32
#define _TARGET_OS	OS_WINDOWS
#else
	#define _TARGET_OS	OS_LINUX
#endif

/* Include */

#include <ostream>
#include <sstream>

#include "sian/binary_tree.h"
#include "sian/red_black_tree.h"

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
		struct SelectionLeaf : public RedBlackLeaf<T> {
			size_t size = 1;
		};

		template <typename T>
		class SelectionTree : public RedBlackTree<T> {
		public:
			typedef Leaf<T>* element_pointer;
			typedef const Leaf<T>* const_element_pointer;

			SelectionTree(void);

			virtual ~SelectionTree(void) noexcept = default;

			virtual void insert(const T& value) override;

			virtual void remove(element_pointer) override;

			virtual element_pointer select(element_pointer, int) const;

			virtual int rank(element_pointer) const;
			
		private:
			virtual void left_rotate(element_pointer) override;

			virtual void right_rotate(element_pointer) override;

			virtual void climb_up_decrease(element_pointer);
		};

		template <typename T>
		struct Interval final {
			friend std::ostream& operator<<(std::ostream& out, const Interval<T>& interval) {
				std::stringstream sstream;
				sstream << '[' << interval.low << ", " << interval.high;
				if (interval.righ_closed)
					sstream << ']';
				else
					sstream << ')';
				out << sstream.str();
				return out;
			}
			
			Interval(void);
			
			Interval(const T&, const T&);

			Interval(const Interval&);

			bool is_overlap(const Interval<T>&) const;

			bool operator<(const Interval<T>&) const;

			bool operator==(const Interval<T>&) const;

			T low , high;

			bool righ_closed = true;
		};

		template <typename T>
		struct IntervalLeaf : public RedBlackLeaf<Interval<T>> {
			T max;
		};

		template <typename T>
		class IntervalTree : public RedBlackTree<Interval<T>> {
		public:
			typedef Leaf<Interval<T>>* element_pointer;
			typedef const Leaf<Interval<T>>* const_element_pointer;

			IntervalTree(void);

			virtual ~IntervalTree(void) noexcept = default;

			virtual void insert(const Interval<T>&) override;
			
			virtual void insert(const T&, const T&);
			
			virtual void remove(element_pointer) override;

			virtual element_pointer find(const Interval<T>&) const override;

			virtual element_pointer find(const T&, const T&) const;

		private:
			virtual void left_rotate(element_pointer) override;

			virtual void right_rotate(element_pointer) override;
			
			virtual void climb_up_update_max(element_pointer);
		};
	}
}

/* Functions declaration */

namespace sian {
	namespace data_structure {
		template <typename T>
		size_t size_of_leaf(Leaf<T>*);

		template <typename T>
		size_t size_of_parent(Leaf<T>*, Leaf<T>*);

		template <typename T>
		void set_size_leaf(Leaf<T>*, size_t);

		template <typename T>
		void increase_size_leaf(Leaf<T>*);

		template <typename T>
		T max_of_leaf(Leaf<Interval<T>>*);
		
		template <typename T>
		void update_max(Leaf<Interval<T>>*);

		template <typename T>
		void compare_update_max(Leaf<Interval<T>>*, T);

		template <typename T>
		bool is_overlap(Leaf<Interval<T>>*, const Interval<T>&);
	}
}

/*
#ifdef __cplusplus
}
#endif
*/

#endif // OS dependency

/* Inline & Template Define Header */
#include "sian/functional_tree.hpp"

#endif // Header duplicate
