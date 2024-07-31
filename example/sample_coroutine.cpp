/**
 * @file		sample_coroutine.cpp
 * @brief		
 * @author		Jeong Hoon (Sian) Choi
 * @version		1.0.0
 * @date		2024-04-03
 */

#include "sample_coroutine.h"

/* C & CPP */
/*
#ifdef __cplusplus
extern "C" {
#endif
*/

#if _TARGET_OS == OS_WINDOWS

#elif _TARGET_OS == OS_LINUX

/* Definition */

/* Data structures definition - struct & class */

task::task(std::coroutine_handle<promise_type> coro) : coro(coro) {}

task::~task(void) noexcept {
	if (this->coro) {
		coro.destroy();
	}
}

void task::next(void) {
	this->coro.resume();
}

std::suspend_always task::promise_type::initial_suspend(void) {
	return {};
}

std::suspend_never task::promise_type::final_suspend(void) noexcept {
	return {};
}

task task::promise_type::get_return_object(void) {
	return task{std::coroutine_handle<promise_type>::from_promise(*this)};
}

void task::promise_type::return_void(void) {}

void task::promise_type::unhandled_exception(void) {
	std::exit(1);
}

/* Functions definition */

task coro_function(void) {
//	co_await std::suspend_always{};
	co_return;
}

#endif // OS dependency

/*
#ifdef __cplusplus
}
#endif
*/
