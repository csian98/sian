/**
 * @file		allocator.h
 * @brief		allocator for standard container
 * @author		Jeong Hoon (Sian) Choi
 * @version		1.0.0
 * @date		2024-05-09
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

#include <memory>

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

/* Data structures definition - struct & class */

namespace sian {
	template <typename T>
	class custom_allocator: public std::allocator<T> {
	public:
		typedef size_t size_type;
		typedef T* pointer;
		typedef const T* const_pointer;

		template <typename _Tp1>
		struct rebind {
			typedef custom_allocator<_Tp1> other;
		};

		custom_allocator(void) noexcept;

		template <typename U>
		custom_allocator(const custom_allocator<T>&) noexcept;

		virtual pointer allocate(size_type n, const void* hint = 0) = 0;

		virtual void deallocate(pointer p, size_type n) = 0;
	};
}


/* Functions declare */

// void swap(Sample&, Sample&) noexcept;

/*
#ifdef __cplusplus
}
#endif
*/

#endif // OS dependency

/* Inline & Template Define Header */
//#include "sample.hpp"

#endif // Header duplicate
