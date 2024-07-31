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

struct awaiter {
	bool await_ready(void) noexcept;

	void await_suspend(std::coroutine_handle<>) const;

	void await_resume(void) const noexcept;
};

class task {
public:
	struct promise_type;
	
	task(std::coroutine_handle<promise_type>);

	virtual ~task(void) noexcept;

	void next(void);
	
private:
	std::coroutine_handle<promise_type> coro;
};

struct task::promise_type {
	std::suspend_always initial_suspend(void);

	std::suspend_never final_suspend(void) noexcept;

	task get_return_object(void);

	void return_void(void);

	void unhandled_exception(void);
};

/* Functions declaration */

task coro_function(void);

/*
#ifdef __cplusplus
}
#endif
*/

#endif // OS dependency

/* Inline & Template Define Header */
//#include "sample.hpp"

#endif // Header duplicate
