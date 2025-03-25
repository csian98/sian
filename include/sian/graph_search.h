/**
 * @file		graph_search.h
 * @brief		
 * @author		Jeong Hoon (Sian) Choi
 * @version		1.0.0
 * @date		2024-09-05
 */
	 
//#pragma once
//#pragma GCC diagnostic ignored "-Wstringop-truncation"
//#pragma comment(lib, "libpthread.so")

#ifndef _HEADER_GRAPH_SEARCH_H_
#define _HEADER_GRAPH_SEARCH_H_

/* OS dependent */
#define OS_WINDOWS	0
#define OS_LINUX	1

#ifdef _WIN32
#define _TARGET_OS	OS_WINDOWS
#else
	#define _TARGET_OS	OS_LINUX
#endif

/* Include */

#include <vector>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>

#include <stack>
#include <queue>

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

/*

class Sample {
	friend void swap(Sample&, Sample&) noexcept;

public:
	Sample(void) = default;
	
	Sample(std::initializer_list<int>);

	virtual ~Sample(void) noexcept = default;

	Sample(const Sample&);

	Sample& operator=(const Sample&);

	Sample(Sample&&) noexcept;

	Sample& operator=(Sample&&) noexcept;
protected:
	
private:
	
};

*/

/* Functions declaration */

namespace sian {
	// dfs (stack, recursive)

	// bfs (queue)

	// bellman-ford

	// dijkstra (priority_queue)

	// floyd-warshall

	// hierholzer & de bruijn
}

/*
#ifdef __cplusplus
}
#endif
*/

#endif // OS dependency

/* Inline & Template Define Header */
//#include "sample.hpp"

#endif // Header duplicate
