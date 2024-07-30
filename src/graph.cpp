/**
 * @file		graph.cpp
 * @brief		Graph clases
 * @author		Jeong Hoon (Sian) Choi
 * @version		1.0.0
 * @date		2024-07-18
 */

#include "sian/graph.h"

/* C & CPP */
/*
#ifdef __cplusplus
extern "C" {
#endif
*/

#if _TARGET_OS == OS_WINDOWS

#elif _TARGET_OS == OS_LINUX

/* Definition */

/* ASM codes */
/*
asm(R"ASM(
  ; assembly code x86-64 AT&T(fastcall-cdecl)
func:
  .cfi_startproc
        pushq %rbp
        .cfi_def_cfa_offset 16
        .cfi_offset 6, -16
        movq %rsp, %rbp
        .cfi_def_cfa_register 6
        movl %edi, -4(%rbp)  ; %rdi -> %rsi -> %rdx -> %rcx ->
        movl %esi, -8(%rbp)  ; %r8  -> %r9  -> stack
; return value %eax
        popq %rbp
				.cf_def_cfa 7, 8
				ret
				.cfi_endproc
)ASM");
*/

/* Data structures definition - struct & class */

sian::graph::Graph::Graph(size_t vertex_size, bool has_direction)
	: vertex_size(vertex_size), has_direction(has_direction) {}

size_t sian::graph::Graph::get_vertex_size(void) const {
	return this->vertex_size;
}

sian::graph::AdjacencyListGraph::AdjacencyListGraph(size_t vertex_size,
													bool has_direction)
	: Graph(vertex_size, has_direction), edges(vertex_size) {}

void sian::graph::AdjacencyListGraph::connect(const int from, const int to) {
	this->edges[from].push_back(to);
	
	if (!this->has_direction) {
		this->edges[to].push_back(from);
	}
}

bool sian::graph::AdjacencyListGraph::is_connect(const int from, const int to) const {
	auto list = this->edges[from];

	return std::find(list.begin(), list.end(), to) != list.end();
}

size_t sian::graph::AdjacencyListGraph::get_vertex_size(const std::initializer_list<std::pair<int, int>>& list) {
	size_t maximum = -1, maxedge;
	for (const auto& edge : list) {
		maxedge = edge.first > edge.second ? edge.first : edge.second;
		maximum = maxedge < maximum ? maximum : maxedge;
	}
	return maximum;
}

sian::graph::AdjacencyMatrixGraph::AdjacencyMatrixGraph(size_t vertex_size,
														bool has_direction)
	: Graph(vertex_size, has_direction),
	  edges((vertex_size * (vertex_size + 1)) / 2, false) {
	if (this->has_direction)
		this->edges.resize(vertex_size * vertex_size, false);
	else {
		int init = 0, gap = 0;
		for (int i = 0; i < this->vertex_size; ++i) {
			init += gap;
			this->init_index.push_back(init);
			gap++;
		}
	}

	for (int i = 0; i < this->vertex_size; ++i) {
		this->edges[this->get_index(i, i)] = true;
	}
}

void sian::graph::AdjacencyMatrixGraph::connect(const int from, const int to) {
	int index = this->get_index(from, to);
	this->edges[index] = true;
}

bool sian::graph::AdjacencyMatrixGraph::is_connect(const int from, const int to) const {
	int index = this->get_index(from, to);
	return this->edges[index];
}

std::pair<std::vector<int>::iterator, std::vector<int>::iterator>
sian::graph::AdjacencyMatrixGraph::adj_range(const int vertex_idx) {
	this->adjacent.clear();
	int idx;
	for (int idx = 0; idx < this->vertex_size; ++idx) {
		if (idx != vertex_idx) {
			if (this->is_connect(vertex_idx, idx))
				this->adjacent.push_back(idx);
		}
	}
	return std::make_pair(this->adjacent.begin(), this->adjacent.end());
}

void sian::graph::AdjacencyMatrixGraph::connect(const int index) {
	this->edges[index] = true;
}

int sian::graph::AdjacencyMatrixGraph::get_index(const int from, const int to) const {
	int index;
	if (has_direction) {
		index = from * this->vertex_size + to;
	} else {
		int min_value = from < to ? from : to;
		int max_value = from < to ? to : from;
		index = this->init_index[max_value] + min_value;
	}
	return index;
}

/* Functions definition */

/*

void swap(Sample& lhs, Sample& rhs) noexcept {
	// shallow copy
    // using std::swap;
}

*/

#endif // OS dependency

/*
#ifdef __cplusplus
}
#endif
*/
