/**
 * @file		server.h
 * @brief		SERVER
 * @author		Jeong Hoon (Sian) Choi
 * @version		1.0.0
 * @date		2024-04-30
 */
	 
//#pragma once
//#pragma GCC diagnostic ignored "-Wstringop-truncation"
//#pragma comment(lib, "libpthread.so")

#ifndef _HEADER_SERVERH_
#define _HEADER_SERVERH_

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
#include <memory>
#include <thread>

#include <filesystem>

#include <string>
#include <string_view>
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
#include <sys/select.h>
#include <sys/poll.h>

/* C & CPP */
/*
#ifdef __cplusplus
extern "C" {
#endif
*/

/* defines typedef & constant */
#define MAX_CLIENTS 64

/* MACRO functions */

#ifndef MIN
#define MIN(a, b)	(a > b ? b : a)
#endif

#ifndef MAX
#define MAX(a, b) (a > b ? a : b)
#endif

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
	class Server {
	public:
		Server(const IPv4&,
			   std::ostream& ostrm = std::cout,
			   std::istream& istrm = std::cin);

		virtual ~Server(void) noexcept;

		virtual void run(void);
	private:
		static void thread_accept(Server*);

		static void thread_read(Server*);

		T tcpssl;

		std::ostream& ostrm;

		std::istream& istrm;

		bool status = false;
		
		std::vector<U*> clients;

		std::mutex mtx;
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
#include "sian/server.hpp"

#endif // Header duplicate
