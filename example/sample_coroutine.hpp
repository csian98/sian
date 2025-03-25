/**
 * @file		sample_coroutine.hpp
 * @brief		
 * @author		Jeong Hoon (Sian) Choi
 * @version 	1.0.0
 * @date		2024-04-03
 */
	 
//#pragma once
//#pragma GCC diagnostic ignored "-Wstringop-truncation"

#ifndef _HEADER_SAMPLE_HPP_
#define _HEADER_SAMPLE_HPP_

#include "sample_coroutine.h"

#if _TARGET_OS == OS_WINDOWS

#elif _TARGET_OS == OS_LINUX

/* Inline & Template Definition */

template <typename T>
Generator<T>::Generator(handle_type coro) : coro(coro) {}

template <typename T>
Generator<T>::~Generator(void) {
	if (this->coro) {
		this->coro.destry();
	}
}

template <typename T>
Generator<T>::operator bool(void) {
	this->fill();
	return !this->coro.done();
}

template <typename T>
T Generator<T>::operator()(void) {
	this->fill();
	this->full = false;
	return std::move(this->coro.promise().value);
}

template <typename T>
void Generator<T>::fill(void) {
	if (!this->full) {
		this->coro();
		if (this->coro.promise().exception)
			std::rethrow_exception(this->coro.promise().exception);

		this->full = true;
	}
}

#endif // OS dependency

#endif // Header duplicate
