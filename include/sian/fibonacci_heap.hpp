/**
 * @file		fibonacci_heap.hpp
 * @brief		Fibonacci Heap
 * @author		Jeong Hoon (Sian) Choi
 * @version 	1.0.0
 * @date		2024-06-15
 */
	 
//#pragma once
//#pragma GCC diagnostic ignored "-Wstringop-truncation"

#ifndef _HEADER_FIBONACCI_HEAPHPP_
#define _HEADER_FIBONACCI_HEAPHPP_

#include "sian/fibonacci_heap.h"

#if _TARGET_OS == OS_WINDOWS

#elif _TARGET_OS == OS_LINUX

/* Inline & Template Definition */

template <typename T>
sian::data_structure::FibonacciNode<T>::FibonacciNode(void) {
	this->left = this;
	this->right = this;
}

template <typename T>
sian::data_structure::FibonacciNode<T>::FibonacciNode(const T& value)
	: FibonacciNode() {
	this->value = value;
}

template <typename T>
void sian::data_structure::FibonacciNode<T>::insert(Leaf<T>* ptr) {
	Leaf<T>* orig_ptr = this->right;
	this->right = ptr;
	orig_ptr->left = ptr;
	
	ptr->left = this;
	ptr->right = orig_ptr;
}

template <typename T>
sian::data_structure::FibonacciHeap<T>::FibonacciHeap(void) {}

template <typename T>
sian::data_structure::FibonacciHeap<T>::~FibonacciHeap(void) noexcept {
	
}

template <typename T>
void sian::data_structure::FibonacciHeap<T>::insert(const T& key) {
	Leaf<T>* ptr = new FibonacciNode<T>(key);

	if (!this->min) {
		this->min = ptr;
	} else {
		this->min->insert(ptr);
		if (key < this->min->value) {
			this->min = ptr;
		}
	}
	
	this->size++;
}

template <typename T>
sian::data_structure::FibonacciHeap<T>*
sian::data_structure::FibonacciHeap<T>::make_union(FibonacciHeap<T>* other) {
	
	
}

template <typename T>
T sian::data_structure::FibonacciHeap<T>::minimum(void) const {
	return this->min->value;
}

template <typename T>
bool sian::data_structure::FibonacciHeap<T>::empty(void) const {
	return !this->min;
}

template <typename T>
sian::data_structure::FibonacciHeap<T>*
sian::data_structure::FibonacciHeap<T>::make_new_heap(void) {
	return new FibonacciHeap<T>;
}


template <typename T>
bool sian::data_structure::fibonaccinode_get_mark(Leaf<T>* ptr) {
	return static_cast<FibonacciNode<T>*>(ptr)->mark;
}

template <typename T>
void sian::data_structure::fibonaccinode_set_mark(Leaf<T>* ptr,
												   bool mark) {
	static_cast<FibonacciNode<T>*>(ptr)->mark = mark;
}

template <typename T>
const sian::data_structure::Leaf<T>*
sian::data_structure::fibonacciheap_get_child(Leaf<T>* ptr) {
	return static_cast<FibonacciNode<T>*>(ptr)->child;
}

template <typename T>
sian::data_structure::Leaf<T>*
sian::data_structure::fibonacciheap_set_child(Leaf<T>* ptr,
													   Leaf<T>* new_child) {
	static_cast<FibonacciNode<T>*>(ptr)->child = new_child;
}


#endif // OS dependency

#endif // Header duplicate
