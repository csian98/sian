/**
 * @file		timer.h
 * @brief		
 * @author		Jeong Hoon (Sian) Choi
 * @version		1.0.0
 * @date		2024-04-03
 */
	 
//#pragma once
//#pragma GCC diagnostic ignored "-Wstringop-truncation"
//#pragma comment(lib, "libpthread.so")

#ifndef _HEADER_SAMPLEH_
#define _HEADER_SAMPLEH_

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
#include <chrono>
#include <vector>

#include <exception>
#include <stdexcept>

#include <ios>
#include <iostream>
#include <iomanip>
#include <string>
#include <string_view>

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
#include <sys/resource.h>

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
	class timer_error : public std::exception {
	public:
		explicit timer_error(const std::string& msg) : msg(msg) {}

		virtual ~timer_error(void) noexcept = default;

		virtual const char* what(void) const noexcept {
			return msg.c_str();
		}
	private:
		std::string msg;
	};

	class Time {
		friend std::ostream& operator<<(std::ostream& out, const sian::Time& time);
	public:		
		Time(void);
		
		virtual ~Time(void) noexcept = default;
		
		void set_name(std::string_view);
		
		void reset(void);
		
		void start(void);
		
		void stop(void);

		long mem_usage(void) const;
		
		template <typename T = std::nano>
		[[nodiscard]] double time_casting(void) const {
			return std::chrono::
				duration_cast<std::chrono::duration<double, T>>(this->end - this->begin).count();
		}
	private:
		bool is_start = false;
		
		std::chrono::duration<double, std::nano> time;
		
		std::chrono::high_resolution_clock::time_point begin;
		std::chrono::high_resolution_clock::time_point end;
		
		std::string name;
	};
	
	class Timer {
		friend std::ostream& operator<<(std::ostream&, const Timer&);
	public:
		Timer(int);

		virtual ~Timer(void) = default;

		Timer(const Timer&) = delete;

		Timer& operator=(const Timer&) = delete;

		Timer(Timer&&) noexcept = delete;

		Timer& operator=(Timer&&) noexcept = delete;

		Time& operator[](int index);

		void initialize(void);

		void append(void);

		void append(std::string_view);

		void remove(int);
	private:
		int size;
		
		std::vector<Time> times;
	};
}

/* Functions declaration */


/*
#ifdef __cplusplus
}
#endif
*/

#endif // OS dependency

/* Inline & Template Define Header */
//#include "sample.hpp"

#endif // Header duplicate
