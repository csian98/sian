/**
 * @file		graph_algorithm.h
 * @brief		Graph Algorithms
 * @author		Jeong Hoon (Sian) Choi
 * @version		1.0.0
 * @date		2024-07-22
 */
	 
//#pragma once
//#pragma GCC diagnostic ignored "-Wstringop-truncation"
//#pragma comment(lib, "libpthread.so")

#ifndef _HEADER_GRAPH_ALGORITHM_H_
#define _HEADER_GRAPH_ALGORITHM_H_

/* OS dependent */
#define OS_WINDOWS	0
#define OS_LINUX	1

#ifdef _WIN32
#define _TARGET_OS	OS_WINDOWS
#else
	#define _TARGET_OS	OS_LINUX
#endif

/* Include */

#include <algorithm>

#include <queue>
#include <stack>

#include "sian/graph.h"

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
	namespace graph {
		class DFS {
		public:
			DFS(size_t);

			DFS(std::initializer_list<std::pair<int, int>>);

			virtual ~DFS(void) noexcept = default;

			virtual void connect(int, int);

			virtual void run(int);
			
			virtual int get_distance(int);
			
		private:
		    class Vertex {
			public:
				enum class Color {
					WHITE,
					GREY,
					BLACK
				};

				void set_color(Color);

				const Color& get_color(void) const;

				void set_distance(int);

				const int& get_distance(void) const;

				void set_pi(Vertex*);

				Vertex* get_pi(void) const;

			private:
				
			    Color color = Color::WHITE;

				int distance = std::numeric_limits<int>::max();

				Vertex* pi = nullptr;
			};

			VertexGraph<Vertex> graph;
		};
	}
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
