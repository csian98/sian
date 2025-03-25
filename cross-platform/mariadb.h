/**
 * @file	    mariadb.h
 * @brief		mariadb connector wrapper
 * @author		Jeong Hoon (Sian) Choi
 * @version		1.0.0
 * @date		2024-06-08
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

#include <string>
#include <string_view>
#include <vector>

#include <memory>

#include "mariadb/conncpp.hpp"

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
	class MariaDB {
	public:
		typedef std::shared_ptr<sql::ResultSet> sql_type;
		typedef std::shared_ptr<sql::ResultSet> result_type;
		
		MariaDB(const std::string, const std::string,
				const std::string, int port = 3306);

		virtual ~MariaDB(void) noexcept;

		void sql(std::string_view);
		
	private:
		std::unique_ptr<sql::Connection> conn;

		std::shared_ptr<sql::ResultSet> result;

		std::shared_ptr<sql::Statement> statement;

		bool result_ready = false;
	};
}



/* Functions declaration */

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
