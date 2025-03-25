/**
 * @file		hash.h
 * @brief		Learning Objectives Basic Data Structures
 * @author		Jeong Hoon (Sian) Choi
 * @version		1.0.0
 * @date		2024-06-02
 */
	 
//#pragma once
//#pragma GCC diagnostic ignored "-Wstringop-truncation"
//#pragma comment(lib, "libpthread.so")

#ifndef _HEADER_HASHH_
#define _HEADER_HASHH_

/* OS dependent */
#define OS_WINDOWS	0
#define OS_LINUX	1

#ifdef _WIN32
#define _TARGET_OS	OS_WINDOWS
#else
	#define _TARGET_OS	OS_LINUX
#endif

/* Include */

#include <random>
#include <limits>
#include <optional>

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
		namespace hash_functions {
			template <typename T>
			class HashFunction {
			public:
				virtual size_t operator()(const T&) const = 0;

				virtual int hash_size(void) const = 0;
				
			protected:
				virtual int change_to_int(const T&) const;
			};

			template <typename T>
			class DefaultHashFunction : public HashFunction<T> {
			public:
				DefaultHashFunction(size_t hash_size = 128);

				virtual size_t operator()(const T&) const override;

				virtual int hash_size(void) const override;
				
			private:
				const size_t m_hash_size;
			};

			template <typename T>
			class MultiplyHashFunction : public HashFunction<T> {
			public:
				MultiplyHashFunction(size_t using_bits = 8);

				virtual size_t operator()(const T&) const override;

				virtual int hash_size(void) const override;

			private:
				int digits_count(int) const;
				
				const float A = (std::sqrt(5) - 1) / 2;

				const int prime = 511;
				
				const size_t using_bits, m_hash_size,
					int_bit_size;
				int int_maximum_digit;
			};

			template <typename T>
			class UniversalHashFunction : public HashFunction<T> {
			public:
				UniversalHashFunction(size_t, int prime = 1999);

				virtual size_t operator()(const T&) const override;

				virtual int hash_size(void) const override;
				
			private:
				const size_t m_hash_size;
				
				const int prime;

				int a = 0, b = 0;
			};

			template <typename T>
			class DuplicateHashFunction : public HashFunction<T> {
			public:
				DuplicateHashFunction(HashFunction<T>*, HashFunction<T>*);

				
				virtual size_t operator()(const T&) const override;

				virtual int hash_size(void) const override;
				
			private:
				HashFunction<T>* hash_function1;

				HashFunction<T>* hash_function2;
				
				const size_t m_hash_size;

				int c = 0;
			};
		}
		
		template <typename T>
		class HashTable {
		public:
			typedef T value_type;
			typedef Node<T>* element_pointer;
			typedef const Node<T>* const_element_pointer;
			
			HashTable(hash_functions::HashFunction<T>*);

			virtual ~HashTable(void) noexcept;

			void insert(T&);

			void remove(T&);

			void remove(Node<T>*);

			Node<T>* find(T&) const;

			size_t hash_size(void) const;

			int bucket_num(T&) const;

		private:
			int hash_wrapper(T&) const;
			
			hash_functions::HashFunction<T>* hash_function;
			//int (*hash_function)(int) = &default_hash_function;

			List<T>* buckets;
		};

		template <typename T>
		class OpenAddressing {
		public:
			typedef T value_type;
			
			OpenAddressing(hash_functions::HashFunction<T>*);

			virtual ~OpenAddressing(void) noexcept;

			void insert(T&);

			std::optional<int> search(T&) const;

			size_t hash_size(void) const;

			int bucket_num(T&, int idx = 0) const;

			void set_c1_c2(void);
			
			void set_c1_c2(const int c1, const int c2);

			T operator[](const int) const;
			
		private:
			int hash_wrapper(T&, int) const;
			
			hash_functions::HashFunction<T>* hash_function;

			const size_t m_hash_size;

			int c1 = 1, c2 = 0;
			
			std::optional<T>* vector;
		};

		template <typename T>
		class DoubleHashTable {
		public:
			typedef T value_type;
			typedef Node<T>* element_pointer;
			typedef const Node<T>* const_element_pointer;
			
			DoubleHashTable(hash_functions::HashFunction<T>*, hash_functions::HashFunction<T>*);

			virtual ~DoubleHashTable(void) noexcept = default;

			void insert(T&);

			void remove(T&);

			void remove(Node<T>*);

			Node<T>* find(T&) const;

			size_t hash_size(void) const;

			int bucket_num(T&) const;
			
		private:
			int hash_wrapper(T&) const;

		    hash_functions::HashFunction<T>* hash_function;

			const size_t m_hash_size;
			
			std::vector<HashTable<T>> hash_tables;
		};
	}
}

/* Functions declaration */


/*
#ifdef __cplusplus
}
#endif
*/

#endif // OS dependency

/* Inline & Template Define Header */
#include "sian/hash.hpp"

#endif // Header duplicate
