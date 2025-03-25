/**
 * @file		graph_algorithm.cpp
 * @brief		Graph Algorithms
 * @author		Jeong Hoon (Sian) Choi
 * @version		1.0.0
 * @date		2024-04-03
 */

#include "sian/graph_algorithm.h"

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

sian::graph::BFS::BFS(size_t vertex_size)
	: graph(vertex_size, false) {}

void sian::graph::BFS::connect(int from, int to) {
	this->graph.connect(from, to);
}

void sian::graph::BFS::run(int start) {
	std::queue<int> queue;
	this->graph.get_vertex(start).set_color(Vertex::Color::GREY);
	this->graph.get_vertex(start).set_distance(0);

	queue.push(start);
	while (!queue.empty()) {
		int vertex_idx = queue.front();
		queue.pop();
		auto [begin, end] = this->graph.adj_range(vertex_idx);
		for (auto iter = begin; iter != end; ++iter) {
			if (this->graph.get_vertex(*iter).get_color() ==
				Vertex::Color::WHITE) {
				this->graph.get_vertex(*iter).set_color(Vertex::Color::GREY);
				this->graph.get_vertex(*iter).set_distance(
					this->graph.get_vertex(vertex_idx).get_distance() + 1);
				this->graph.get_vertex(*iter).set_pi(
					&this->graph.get_vertex(vertex_idx));
				queue.push(*iter);
			}
		}
		this->graph.get_vertex(vertex_idx).set_color(Vertex::Color::BLACK);
	}
}

int sian::graph::BFS::get_distance(int index) {
	return this->graph.get_vertex(index).get_distance();
}

void sian::graph::BFS::Vertex::set_color(Color new_color) {
	this->color = new_color;
}

const sian::graph::BFS::Vertex::Color&
sian::graph::BFS::Vertex::get_color(void) const {
	return this->color;
}

void sian::graph::BFS::Vertex::set_distance(int new_distance) {
	this->distance = new_distance;
}

const int& sian::graph::BFS::Vertex::get_distance(void) const {
	return this->distance;
}

void sian::graph::BFS::Vertex::set_pi(Vertex* other_pi) {
	this->pi = other_pi;
}

sian::graph::BFS::Vertex*
sian::graph::BFS::Vertex::get_pi(void) const {
	return this->pi;
}

sian::graph::DFS::DFS(size_t vertex_size)
	: graph(vertex_size, true) {}

void sian::graph::DFS::connect(int from, int to) {
	this->graph.connect(from, to);
}

void sian::graph::DFS::run(void) {
    size_t vertex_size = this->graph.Graph::get_vertex_size();
	for (int i = 0; i < vertex_size; ++i) {
		if (this->graph.get_vertex(i).get_color() == Vertex::Color::WHITE) {
			this->visit(i);
		}
	}
}

std::pair<int, int> sian::graph::DFS::get_range(int index) {
	return std::make_pair(this->graph.get_vertex(index).get_start(),
						  this->graph.get_vertex(index).get_end());
}

void sian::graph::DFS::visit(int index) {
	this->time++;
	this->graph.get_vertex(index).set_start(this->time);
	this->graph.get_vertex(index).set_color(Vertex::Color::GREY);
	auto [begin, end] = this->graph.adj_range(index);
	for (auto iter = begin; iter != end; ++iter) {
		if (this->graph.get_vertex(*iter).get_color() ==
			Vertex::Color::WHITE) {
			this->graph.get_vertex(*iter).set_pi(
				&this->graph.get_vertex(index));
			this->visit(*iter);
		}
	}
	this->graph.get_vertex(index).set_color(Vertex::Color::BLACK);
	this->time++;
	this->graph.get_vertex(index).set_end(this->time);
}

void sian::graph::DFS::Vertex::set_color(Color new_color) {
	this->color = new_color;
}

const sian::graph::DFS::Vertex::Color&
sian::graph::DFS::Vertex::get_color(void) const {
	return this->color;
}

void sian::graph::DFS::Vertex::set_distance(int new_distance) {
	this->distance = new_distance;
}

const int& sian::graph::DFS::Vertex::get_distance(void) const {
	return this->distance;
}

void sian::graph::DFS::Vertex::set_start(int time) {
	this->start = time;
}

const int& sian::graph::DFS::Vertex::get_start(void) const {
	return this->start;
}

void sian::graph::DFS::Vertex::set_end(int time) {
	this->end = time;
}

const int& sian::graph::DFS::Vertex::get_end(void) const {
	return this->end;
}

void sian::graph::DFS::Vertex::set_pi(Vertex* other_pi) {
	this->pi = other_pi;
}

sian::graph::DFS::Vertex*
sian::graph::DFS::Vertex::get_pi(void) const {
	return this->pi;
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
