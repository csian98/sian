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

#include <map>
#include <set>
#include <unordered_set>

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
		class BFS {
		public:
			BFS(size_t);

			virtual ~BFS(void) noexcept = default;

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
		class DFS {
		public:
			DFS(size_t);

			virtual ~DFS(void) noexcept = default;

			virtual void connect(int, int);

			virtual void run(void);

			virtual std::pair<int, int> get_range(int);
			
		private:
			virtual void visit(int);
			
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

				void set_start(int);

				const int& get_start(void) const;

				void set_end(int);

				const int& get_end(void) const;

				void set_pi(Vertex*);

				Vertex* get_pi(void) const;

			private:
				
			    Color color = Color::WHITE;

				int distance = std::numeric_limits<int>::max();

				int start = 0, end = 0;

				Vertex* pi = nullptr;
			};

			VertexGraph<Vertex> graph;

			int time = 0;
		};

		template <typename T>
		class MSTGraph : public WeightGraph<T> {
		public:
			MSTGraph(size_t);

			virtual ~MSTGraph(void) noexcept = default;

			std::map<int, int> get_ordered_weights(void) const;
		};

		template <typename T>
		class MSTKruskal {
		public:
			MSTKruskal(size_t);

			virtual ~MSTKruskal(void) noexcept = default;

			void connect(const int, const int, const T);

			void run(void);

		    bool is_connect(const int, const int) const;

		private:
			class Set {
			public:
				void make_set(const int);

				int find_set(const int) const;

				void union_set(const int, const int);
			private:
				std::vector<std::list<int>> sets;
			};
			
			MSTGraph<T> graph;

		    AdjacencyMatrixGraph checked_graph;
		};

		template <typename T>
		class MSTPrim {
		public:
			MSTPrim(size_t);
			
			void connect(const int, const int, const T);

			void run(const int);

			bool is_connect(const int, const int) const;
			
		private:
		    struct Vertex {
				int key = std::numeric_limits<int>::max();

				Vertex* pi = nullptr;
			};

			class WrapperQueue {
			public:
				void push(const std::pair<int*, int>&);

				std::pair<int, int> pop(void);

				bool has_index(const int);
				
			private:
			    struct KeyIdxPair {
					KeyIdxPair(int*, int);
					
					bool operator<(const KeyIdxPair&) const;
					
					int* first = nullptr;

					int second = -1;
				};
				
				std::priority_queue<std::pair<int, int>,
					std::vector<std::pair<int, int>>,
					std::greater<std::pair<int, int>>> queue;

				std::set<int> set;	
			};

			VertexWeightGraph<Vertex, T> graph;

			AdjacencyMatrixGraph checked_graph;
		};

		template <typename T>
		class SPGraph : public VertexWeightGraph<std::pair<int, int>, T> {
		public:
			SPGraph(size_t);

			virtual ~SPGraph(void) noexcept = default;
			
			void initialize_single_source(const int);

			void relax(const int, const int);
		};

		template <typename T>
		class SPBellmanFord {
		public:
			SPBellmanFord(size_t);

			virtual ~SPBellmanFord(void) noexcept = default;

			void connect(const int, const int, const T);

			void run(const int);

			bool is_connect(void) const;

		private:
			std::vector<std::pair<int, int>> get_edges(void) const;
			
			SPGraph<T> graph;
		};

		template <typename T>
		class SPDijkstra {
		public:
			SPDijkstra(size_t);

			virtual ~SPDijkstra(void) noexcept = default;

			void connect(const int, const int, const T);

			void run(const int);

		private:
		    struct KeyIdxPair {
				KeyIdxPair(int*, int);
				
				bool operator<(const KeyIdxPair&) const;
				
				int* first = nullptr;
				
				int second = -1;
			};
			
			SPGraph<T> graph;

			AdjacencyMatrixGraph checked_graph;
		};

		template <typename T>
		class SPFloydWarshall {
		public:
			SPFloydWarshall(size_t);
			
			virtual ~SPFloydWarshall(void) noexcept = default;

			void connect(const int, const int, const T);
			
			void run(void);
			
		private:
			template <typename U>
		    class Matrix {
			public:
				Matrix(size_t, size_t);

				Matrix(const Matrix&);

				Matrix<U>& operator=(const Matrix&);
				
				U& at(const int, const int);
				
			private:
				std::vector<std::vector<U>> matrix;

				size_t row_size, col_size;
			};

			void init_pi(void);

			void update_pi(const int);

			size_t vertex_size;
			
			Matrix<T> matrix;

			Matrix<std::optional<int>> pi;
		};

		std::string de_bruijn_sequence(int, int,
									   const std::string&);
	}
}

/* Functions declaration */

/*
#ifdef __cplusplus
}
#endif
*/

#endif // OS dependency

/* Inline & Template Define Header */
#include "sian/graph_algorithm.hpp"

#endif // Header duplicate
