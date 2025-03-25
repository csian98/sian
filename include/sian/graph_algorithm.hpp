/**
 * @file	    graph_algorithm.hpp
 * @brief		Graph Algorithms
 * @author		Jeong Hoon (Sian) Choi
 * @version 	1.0.0
 * @date		2024-04-03
 */
	 
//#pragma once
//#pragma GCC diagnostic ignored "-Wstringop-truncation"

#ifndef _HEADER_GRAPH_ALGORITHM_HPP_
#define _HEADER_GRAPH_ALGORITHM_HPP_

#include "sian/graph_algorithm.h"

#if _TARGET_OS == OS_WINDOWS

#elif _TARGET_OS == OS_LINUX

/* Inline & Template Definition */

template <typename T>
sian::graph::MSTGraph<T>::MSTGraph(size_t vertex_size)
	: WeightGraph<T>(vertex_size, false) {}

template <typename T>
std::map<int, int>
sian::graph::MSTGraph<T>::get_ordered_weights(void) const {
	int idx, vertex_size = this->get_vertex_size();
	std::map<int, int> weights;
	for (int i = 0; i < vertex_size; ++i) {
		for (int j = 0; j < vertex_size; ++j) {
			if (i != j) {
				if (this->is_connect(idx)) {
					weights.insert(std::make_pair(i, j));
				}
			}
		}
	}
	return weights;
}

template <typename T>
sian::graph::MSTKruskal<T>::MSTKruskal(size_t vertex_size)
	: graph(vertex_size), checked_graph(vertex_size, false) {}

template <typename T>
void sian::graph::MSTKruskal<T>::connect(const int from, const int to,
										 const T weight) {
	this->graph.connect(from, to, weight);
}

template <typename T>
void sian::graph::MSTKruskal<T>::run(void) {
	size_t vertex_size = this->graph.get_vertex_size();
	
	Set set;
	for (int i = 0; i < vertex_size; ++i)
		set.make_set(i);

	std::map<int, int> edges = this->graph.get_ordered_weights();
	for (auto iter = edges.begin(); iter != edges.end(); ++iter) {
		if (set.find_set(iter->first), set.find_set(iter->second)) {
			this->checked_graph.connect(iter->first, iter->second);
			set.union_set(iter->first, iter->second);
		}
	}
}

template <typename T>
bool sian::graph::MSTKruskal<T>::is_connect(const int from,
												const int to) const {
	return this->checked_graph.is_connect(from, to);
}

template <typename T>
void sian::graph::MSTKruskal<T>::Set::make_set(const int vertex_idx) {
	this->sets.push_back();
	this->sets[this->sets.size() - 1].push_back(vertex_idx);
}

template <typename T>
int sian::graph::MSTKruskal<T>::Set::find_set(const int vertex_idx) const {
	for (int i = 0; i < this->sets.size(); ++i) {
		auto iter = std::find(this->sets[i].begin(), this->sets[i].end(),
							  vertex_idx);
		if (iter != this->sets[i].end())
			return i;
	}
	return -1;
}

template <typename T>
void sian::graph::MSTKruskal<T>::Set::union_set(const int vertex_idx_1,
												const int vertex_idx_2) {
	int idx1 = this->find_set(vertex_idx_1);
	int idx2 = this->find_set(vertex_idx_2);
	this->sets[idx1].insert(this->sets[idx1].end(),
							this->sets[idx2].begin(),
							this->sets[idx2].end());

	this->sets.erase(this->sets.begin() + idx2);
}

template <typename T>
sian::graph::MSTPrim<T>::MSTPrim(size_t vertex_size)
	: graph(vertex_size, false), checked_graph(vertex_size, false) {}

template <typename T>
void sian::graph::MSTPrim<T>::run(const int vertex_idx) {
	size_t vertex_size = this->graph.get_vertex_size();
    WrapperQueue queue; 
	
	this->graph.get_vertex(vertex_idx).key = 0;
	for (int i = 0; i < vertex_size; ++i) {
		queue.push(std::make_pair(&this->graph.get_vertex(i).key, i));
	}

	while (!queue.empty()) {
		auto [key, idx] = queue.pop();
	    if (vertex_idx != idx)
			this->checked_graph.connect(
				this->graph.get_vertex(idx)->pi, idx);
		auto [begin, end] = this->graph.adj_range(idx);
		for (auto iter = begin; iter != end; ++iter) {
			if (queue.has_index(*iter) &&
				this->graph.get_weight(idx, *iter)
				< this->graph.get_vertex(*iter).key) {
				this->graph.get_vertex(*iter).pi =
					&this->graph.get_vertex(idx);
				this->graph.get_vertex(*iter).key =
					this->graph.get_weight(idx, *iter);
			}
		}
		
	}
}

template <typename T>
bool sian::graph::MSTPrim<T>::is_connect(const int from, const int to) const {
	return this->checked_graph.is_connect(from, to);
}

template <typename T>
void sian::graph::MSTPrim<T>::WrapperQueue::push(
	const std::pair<int*, int>& pair) {
	this->queue.push(pair.first, pair.second);
	this->set.insert(pair.second);
}

template <typename T>
std::pair<int, int> sian::graph::MSTPrim<T>::WrapperQueue::pop(void) {
	auto [first, second] = this->queue.top();
	this->queue.pop();
	this->set.erase(second);
	return std::make_pair(*first, second);
}

template <typename T>
bool sian::graph::MSTPrim<T>::WrapperQueue::has_index(const int idx) {
	return this->set.find(idx) != this->set.end();
}

template <typename T>
sian::graph::MSTPrim<T>::WrapperQueue::KeyIdxPair::KeyIdxPair(int* first,
															  int second)
	: first(first), second(second) {}

template <typename T>
bool sian::graph::MSTPrim<T>::WrapperQueue::KeyIdxPair::operator<(
	const KeyIdxPair& other) const {
	return *(this->first) < *(other.second);
}

template <typename T>
sian::graph::SPGraph<T>::SPGraph(size_t vertex_size)
	: VertexWeightGraph<std::pair<int, int>, T>(vertex_size) {}

template <typename T>
void sian::graph::SPGraph<T>::initialize_single_source(const int idx) {
	auto [begin, end] = this->adj_range(idx);
	for (auto iter = begin; iter != end; ++iter) {
		this->get_vertex(*iter).first = std::numeric_limits<int>::max();
		this->get_vertex(*iter).second = -1;
	}
	this->get_vertex(idx).first = 0;
}

template <typename T>
void sian::graph::SPGraph<T>::relax(const int idx_1, const int idx_2) {
	if (this->get_vertex(idx_1).first > this->get_vertex(idx_2).first +
		this->get_weight(idx_1, idx_2)) {
		this->get_vertex(idx_2).first = this->get_vertex(idx_1).first +
			this->get_weight(idx_1, idx_2);
		this->get_vertex(idx_2).second = idx_1;
	}
}

template <typename T>
sian::graph::SPBellmanFord<T>::SPBellmanFord(size_t vertex_size)
	: graph(vertex_size) {}

template <typename T>
void sian::graph::SPBellmanFord<T>::connect(const int from, const int to,
									  const T weight) {
	this->graph.connect(from, to, weight);
}

template <typename T>
void sian::graph::SPBellmanFord<T>::run(const int start) {
	this->graph.initialize_single_source(start);

	size_t vertex_size = this->graph.get_vertex_size();
	auto edges = this->get_edges();

	for (int i = 0; i < vertex_size; ++i)
	    for (auto iter = edges.begin(); iter != edges.end(); ++iter)
			this->graph.relax(iter.first, iter.second);
	
}

template <typename T>
bool sian::graph::SPBellmanFord<T>::is_connect(void) const {
	auto edges = this->get_edges();

	for (auto iter = edges.begin(); iter != edges.end(); ++iter) {
		if (this->graph.get_vertex(iter->second).first >
			this->graph.get_vertex(iter->first).first +
			this->graph.get_weight(iter->first))
			return false;
	}
	return true;
}

template <typename T>
std::vector<std::pair<int, int>>
sian::graph::SPBellmanFord<T>::get_edges(void) const {
	size_t vertex_size = this->graph.get_vertex_size();
	std::vector<std::pair<int, int>> edges;
	for (int i = 0; i < vertex_size; ++i) {
		for (int j = 0; j < vertex_size; ++j) {
			if (i != j)
				if (this->graph.is_connect(i, j))
					edges.push_back(std::make_pair(i, j));
		}
	}
	return edges;
}

template <typename T>
sian::graph::SPDijkstra<T>::SPDijkstra(size_t vertex_size)
	: graph(vertex_size), checked_graph(vertex_size, true) {}

template <typename T>
void sian::graph::SPDijkstra<T>::connect(const int from, const int to,
									const T weight) {
	this->graph.connect(from, to, weight);
}

template <typename T>
void sian::graph::SPDijkstra<T>::run(const int start) {
	this->graph.initialize_single_source(start);

	size_t vertex_size = this->graph.get_vertex_size();
	std::priority_queue<KeyIdxPair> queue;
	
    for (int i = 0; i < vertex_size; ++i) {
		queue.push(&this->graph.get_vertex(i).first, i);
	}

	while (!queue.empty()) {
		auto [key, idx] = queue.pop();
		auto [begin, end] = this->graph.adj_range(idx);
		for (auto iter = begin; iter != end; ++iter) {
			this->graph.relax(idx, *iter);
		}
	}
}

template <typename T>
sian::graph::SPDijkstra<T>::KeyIdxPair::KeyIdxPair(int* first,
												   int second)
	: first(first), second(second) {}

template <typename T>
bool sian::graph::SPDijkstra<T>::KeyIdxPair::operator<(
	const KeyIdxPair& other) const {
	return *(this->first) < *(other.second);
}

template <typename T>
sian::graph::SPFloydWarshall<T>::SPFloydWarshall(size_t vertex_size)
	: vertex_size(vertex_size), matrix(vertex_size, vertex_size),
	  pi(vertex_size, vertex_size) {}

template <typename T>
void sian::graph::SPFloydWarshall<T>::connect(const int from, const int to,
													  const T weight) {
	this->matrix.at(from, to) = weight;
}

template <typename T>
void sian::graph::SPFloydWarshall<T>::run(void) {
	this->init_pi();
	
	Matrix matrix(this->matrix);
	for (int k = 0; k < this->vertex_size; ++k) {
		Matrix n_matrix;
		for (int i = 0; i < this->vertex_size; ++i)
			for (int j = 0; j < this->vertex_size; ++j) 
				n_matrix.at(i, j) =
					matrix.at(i, j) < matrix.at(i, k) + matrix.at(k, j) ?
					matrix.at(i, j) : matrix.at(i, k) + matrix.at(k, j);

		this->update_pi(k);
		matrix = n_matrix;
	}
	this->matrix = matrix;
}

template <typename T>
template <typename U>
sian::graph::SPFloydWarshall<T>::Matrix<U>::Matrix(size_t row_size, size_t col_size)
	: row_size(row_size), col_size(col_size) {
	matrix.resize(row_size, std::numeric_limits<T>::max());
	for (auto vector : matrix) {
		vector.resize(col_size, std::numeric_limits<T>::max());
	}
}

template <typename T>
template <typename U>
sian::graph::SPFloydWarshall<T>::Matrix<U>::Matrix(const Matrix& other) {
	for (int i = 0; i < other.row_size; ++i) {
		for (int j = 0; j < other.col_size; ++j) {
			this->at(i, j) = other.at(i, j);
		}
	}
}

template <typename T>
template <typename U>
sian::graph::SPFloydWarshall<T>::Matrix<U>& sian::graph::SPFloydWarshall<T>::Matrix<U>::operator=(const Matrix& other) {
	if (this == &other)
		return;

	for (int i = 0; i < this->row_size; ++i)
		for (int j = 0; j < this->col_size; ++j)
			this->at(i, j) = other.at(i, j);

	return *this;
}

template <typename T>
template <typename U>
U& sian::graph::SPFloydWarshall<T>::Matrix<U>::at(const int row_idx, const int col_idx) {
	return this->matrix[row_idx][col_idx];
}

template <typename T>
void sian::graph::SPFloydWarshall<T>::init_pi(void) {
	for (int i = 0; i < this->vertex_size; ++i)
		for (int j = 0; j < this->vertex_size; ++j)
			if (i == j || this->matrix.at(i, j) == std::numeric_limits<T>::max())
				this->pi.at(i, j) = std::nullopt;
			else
				this->pi.at(i, j) = i;
}

template <typename T>
void sian::graph::SPFloydWarshall<T>::update_pi(const int k) {
    for (int i = 0; i < this->vertex_size; ++i)
		for (int j = 0; j < this->vertex_size; ++j)
			if (this->matrix.at(i, j)
				<= this->matrix.at(i, k) + this->matrix.at(k, j))
				this->pi.at(i, j) = this->pi.at(i, j);
			else
				this->pi.at(i, j) = this->pi.at(k, j);
}

#endif // OS dependency

#endif // Header duplicate
