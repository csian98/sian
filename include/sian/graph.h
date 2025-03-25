/**
 * @file		graph.h
 * @brief		Graph classes
 * @author		Jeong Hoon (Sian) Choi
 * @version		1.0.0
 * @date		2024-07-18
 */
	 
//#pragma once
//#pragma GCC diagnostic ignored "-Wstringop-truncation"
//#pragma comment(lib, "libpthread.so")

#ifndef _HEADER_GRAPH_H_
#define _HEADER_GRAPH_H_

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
#include <numeric>
#include <utility>

#include <list>
#include <vector>
#include <iterator>

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

namespace sian {
	namespace graph {
		class Graph {
		public:
			Graph(size_t, bool);

			virtual ~Graph(void) noexcept = default;

			virtual size_t get_vertex_size(void) const;
			
			virtual void connect(const int, const int) = 0;

			virtual bool is_connect(const int, const int) const = 0;
			
		protected:
			size_t vertex_size;

			bool has_direction;
		};

		class AdjacencyListGraph : public Graph {
		public:
			AdjacencyListGraph(size_t, bool);

			virtual ~AdjacencyListGraph(void) noexcept = default;

			virtual void connect(const int, const int) override;

			virtual bool is_connect(const int, const int) const override;
			
		protected:
			size_t get_vertex_size(const std::initializer_list<std::pair<int, int>>&);
		
			std::vector<std::list<int>> edges;
		};

		class AdjacencyMatrixGraph : public Graph {
		public:
			AdjacencyMatrixGraph(size_t, bool);

			virtual ~AdjacencyMatrixGraph(void) noexcept = default;

			virtual void connect(const int, const int) override;

			virtual bool is_connect(const int, const int) const override;

			virtual std::pair<std::vector<int>::iterator, std::vector<int>::iterator>
			adj_range(const int);
			
		protected:
			virtual void connect(const int);
			
			virtual int get_index(const int, const int) const;

			std::vector<int> init_index;

			std::vector<int> adjacent;
			
			std::vector<bool> edges;
		};

		template <typename T>
		class VertexGraph : public AdjacencyMatrixGraph {
		public:
			VertexGraph(size_t, bool);

			virtual void set_vertex(const int, const T&);
			
			virtual T& get_vertex(const int);
			
		private:
			std::vector<T> vertex;
		};

		template <typename T>
		class WeightGraph : public AdjacencyMatrixGraph {
		public:
			WeightGraph(size_t, bool);

			virtual ~WeightGraph(void) noexcept = default;

			virtual void connect(const int, const int, const T&);

			virtual const T& get_weight(const int, const int) const;
			
		protected:
			std::vector<T> weights;
		};

		template <typename T, typename U>
		class VertexWeightGraph : WeightGraph<U> {
		public:
			VertexWeightGraph(size_t, bool);

			virtual ~VertexWeightGraph(void) noexcept = default;

			virtual void set_vertex(const int, const T&);

			virtual T& get_vertex(const int);

		private:
			std::vector<T> vertex;
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
#include "sian/graph.hpp"

#endif // Header duplicate
