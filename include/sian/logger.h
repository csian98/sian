/**
 * @file		logger.h
 * @brief		multi thread logger
 * @author		Jeong Hoon (Sian) Choi
 * @version		1.0.0
 * @date		2024-05-13
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

#include <fstream>
#include <queue>
#include <string>
#include <string_view>
#include <filesystem>

#include <thread>
#include <mutex>
#include <condition_variable>

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
	class Logger {
	public:
		Logger(std::string_view file = "log.txt");

		virtual ~Logger(void);

		Logger(const Logger&) = delete;

		Logger& operator=(const Logger&) = delete;

		void log(std::string_view);
	private:
		void thread_process(void);

		bool m_exit = false;

		std::mutex m_mutex;
		std::condition_variable m_cond_var;
		std::thread m_thread;

		std::queue<std::string> m_queue;

		std::filesystem::path m_path;
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
