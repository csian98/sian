/**
 * @file		sample_coroutine.h
 * @brief		
 * @author		Jeong Hoon (Sian) Choi
 * @version		1.0.0
 * @date		2024-04-03
 */
	 
//#pragma once
//#pragma GCC diagnostic ignored "-Wstringop-truncation"
//#pragma comment(lib, "libpthread.so")

#ifndef _HEADER_SAMPLE_COROUTINE_H_
#define _HEADER_SAMPLE_COROUTINE_H_

/* OS dependent */
#define OS_WINDOWS	0
#define OS_LINUX	1

#ifdef _WIN32
#define _TARGET_OS	OS_WINDOWS
#else
	#define _TARGET_OS	OS_LINUX
#endif

/* Include */

#include <coroutine>

#include <variant>
#include <exception>

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

template <typename T>
class Generator {
public:	
    class promise_type;
	typedef std::coroutine_handle<promise_type> handle_type;

	Generator(handle_type);

	~Generator(void);

	explicit operator bool(void);

	T operator()(void);

private:
	void fill(void);
	
	bool full = false;
	
	handle_type coro;
};

template <typename T>
class Generator<T>::promise_type {
public:
	Generator<T> get_return_object(void) {
		return Generator(handle_type::from_promise(*this));
	}

	std::suspend_always initial_suspend(void) { return {}; }

	std::suspend_always final_suspend(void) noexcept { return {}; }

	void unhandled_exception(void) { this->exception = std::current_exception(); }

	template <std::convertible_to<T> From>
	std::suspend_always yield_value(From&& from) {
		this->value = std::forward<From>(from);
		return {};
	}

	void return_void(void) {}

private:
	T value;
	
	std::exception_ptr exception;
};

/* Functions declaration */



/*
#ifdef __cplusplus
}
#endif
*/

#endif // OS dependency

/* Inline & Template Define Header */
#include "sample_coroutine.hpp"

#endif // Header duplicate
