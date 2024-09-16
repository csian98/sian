/**
 * @file		graph.hpp
 * @brief		Graph classes
 * @author		Jeong Hoon (Sian) Choi
 * @version 	1.0.0
 * @date		2024-04-03
 */
	 
//#pragma once
//#pragma GCC diagnostic ignored "-Wstringop-truncation"

#ifndef _HEADER_GRAPH_HPP_
#define _HEADER_GRAPH_HPP_

#include "sian/graph.h"

#if _TARGET_OS == OS_WINDOWS

#elif _TARGET_OS == OS_LINUX

/* Inline & Template Definition */

template <typename T>
sian::graph::VertexGraph<T>::VertexGraph(size_t vertex_size,
										 bool has_direction)
	: AdjacencyMatrixGraph(vertex_size, has_direction),
	  vertex(vertex_size) {}

template <typename T>
void sian::graph::VertexGraph<T>::set_vertex(const int index, const T& vtx) {
	this->vertex[index] = vtx;
}

template <typename T>
T& sian::graph::VertexGraph<T>::get_vertex(const int index) {
	return this->vertex[index];
}

template <typename T>
sian::graph::WeightGraph<T>::WeightGraph(size_t vertex_size,
										 bool has_direction)
	: AdjacencyMatrixGraph(vertex_size, has_direction),
	  weights(this->edges.size()) {}

template <typename T>
void sian::graph::WeightGraph<T>::connect(const int from, const int to,
										  const T& weight) {
	int index = this->get_index(from, to);
	AdjacencyMatrixGraph::connect(index);
	this->weights[index] = weight;
}

template <typename T>
const T& sian::graph::WeightGraph<T>::get_weight(const int from, const int to) const {
	int index = this->get_index(from, to);
	return weights[index];
}

template <typename T, typename U>
sian::graph::VertexWeightGraph<T, U>::VertexWeightGraph(size_t vertex_size,
														bool has_direction)
	: WeightGraph<U>(vertex_size, has_direction),
	  vertex(vertex_size) {}

template <typename T, typename U>
void sian::graph::VertexWeightGraph<T, U>::set_vertex(const int index,
													  const T& vtx) {
	this->vertex[index] = vtx;
}

template <typename T, typename U>
T& sian::graph::VertexWeightGraph<T, U>::get_vertex(const int index) {
	return this->vertex[index];
}

#endif // OS dependency

#endif // Header duplicate
