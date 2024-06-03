/**
 * @file		data_structure.h
 * @brief	    Learning Objectives Basic Data Structures
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

#include <ostream>
#include <optional>
#include <variant>

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
		class data_structure_error : std::exception {
		public:
			data_structure_error(const std::string& msg) : msg(msg) {}

			virtual const char* what(void) {
				return msg.c_str();
			}

		private:
			std::string msg;
		};
		
		template <typename T>
		class Heap {
		public:
			Heap(void);
			
			Heap(std::initializer_list<T>);

			Heap(T*, int);

			virtual ~Heap(void) noexcept;

			int get_heap_size(void) const;

			void push(T);

			T pop(void);

			void sort(T*, int, bool heapify = true);
		private:
			void realloc(void);

			void max_heapify(int);

			void build_max_heap(void);
			
			T* tree;

			size_t heap_size, heap_max;
		};

		template <typename T>
		struct Node {
			Node* prev = nullptr;
			Node* next = nullptr;
			T value = 0;
		};

		template <typename T>
		class List {
			friend std::ostream& operator<<(std::ostream& out, const List<T>& list) {
				Node<T>* ptr = list.begin;
				while (ptr) {
					out << ptr->value << " ";
					ptr = ptr->next;
				}
				out << std::endl;
				
				return out;
			}
		public:
			typedef Node<T>* element_pointer;
			typedef const Node<T>* const_element_pointer;
			
			List(void);

			List(std::initializer_list<T>);

			virtual ~List(void) noexcept;

			Node<T>* front(void) const;

			Node<T>* back(void) const;

			void push_front(T value);
			
			void push_back(T value);

			void insert_next(Node<T>*, T);

			void insert_sorted(T);

			void remove(Node<T>*);

			Node<T>* find_value(T) const;

			Node<T>* find_index(int) const;

			Node<T>* operator[](int) const;
		private:
			Node<T>* begin = nullptr;
			
			Node<T>* end = nullptr;
		};

		template <typename T>
		class Vector {
		public:
			Vector(void);

			Vector(std::initializer_list<T> list);

			virtual ~Vector(void) noexcept;
			
		    void push_back(T);

		    void push_front(T);

		    T pop_back(void);

		    T pop_front(void);

		    bool is_empty(void) const;

		    T operator[](int) const;
		private:
			void realloc(void);
			
			void realloc(int size);

			int binary_round_up(int);

			size_t size = 0, capacity = 0;
			
			T* vector = nullptr;;
		};

		template <typename T>
		class Circle {
		public:
			Circle(void);

			Circle(std::initializer_list<T>);

			virtual ~Circle(void) noexcept;

			void push_back(T);

			void push_front(T);

			T pop_back(void);

			T pop_front(void);

			bool is_empty(void) const;

			T operator[](int) const;
		private:
			void realloc(void);

			void realloc(int);

			int binary_round_up(int);

			size_t size = 0, capacity = 0;
			
			int head = 0, tail = 0;

			T* vector = nullptr;
		};

		template <typename T, typename U = Circle<T>>
		class Stack {
		public:
			Stack(void);

			virtual ~Stack(void) noexcept = default;

			T pop(void);

			void push(T);

			bool is_empty(void) const;
		private:
			U stack;
		};

		template <typename T, typename U = Circle<T>>
		class Queue {
		public:
			Queue(void);

			virtual ~Queue(void) noexcept = default;

			T pop(void);

			void push(T);

			bool is_empty(void) const;
		private:
			U queue;
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
