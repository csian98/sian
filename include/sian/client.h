/**
 * @file		client.h
 * @brief		CLIENT
 * @author		Jeong Hoon (Sian) Choi
 * @version		1.0.0
 * @date		2024-04-30
 */
	 
//#pragma once
//#pragma GCC diagnostic ignored "-Wstringop-truncation"
//#pragma comment(lib, "libpthread.so")

#ifndef _HEADER_CLIENTH_
#define _HEADER_CLIENTH_

/* OS dependent */
#define OS_WINDOWS	0
#define OS_LINUX	1

#ifdef _WIN32
#define _TARGET_OS	OS_WINDOWS
#else
	#define _TARGET_OS	OS_LINUX
#endif

/* Include */

#include <string>
#include <string_view>
#include <sstream>

#include <utility>
#include <algorithm>

#include <vector>
#include <map>

#include <thread>
#include <mutex>

#include "sian/tcp.h"
#include "sian/ssl.h"

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
	template <typename T = sian::SSL, typename U = sian::ssl_client>
	class Client {
	public:
		Client(const IPv4&);

		virtual ~Client(void) noexcept;

		virtual void send(const std::string&);
	private:
		T tcpssl;

		bool status = false;
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
#include "sian/client.hpp"

#endif // Header duplicate
