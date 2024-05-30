/**
 * @file		data_structure.hpp
 * @brief		basic data structures (learning purpose source codes)
 * @author		Jeong Hoon (Sian) Choi
 * @version 	1.0.0
 * @date		2024-05-29
 */
	 
//#pragma once
//#pragma GCC diagnostic ignored "-Wstringop-truncation"

#ifndef _HEADER_SAMPLEHPP_
#define _HEADER_SAMPLEHPP_

#include "sian/data_structure.h"

#if _TARGET_OS == OS_WINDOWS

#elif _TARGET_OS == OS_LINUX

/* Inline & Template Definition */

template <typename T>
sian::data_structure::Heap<T>::Heap(void) {
	this->heap_size = 0;
	this->heap_max = 8;

	this->tree = new T[this->heap_max];
}

template <typename T>
sian::data_structure::Heap<T>::Heap(std::initializer_list<T> list) {
	this->heap_size = list.size();
	this->heap_max = std::log2(this->heap_size) + 1;

	this->tree = new T[this->heap_max];

	for (int i = 0; i < this->heap_size; ++i) {
		tree[i] = list[i];
	}

	this->build_max_heap();
}

template <typename T>
sian::data_structure::Heap<T>::Heap(T* list, int size) {
	this->heap_size = size;
	this->heap_max = std::log2(this->heap_size) + 1;

	this->tree = new T[this->heap_max];

	for (int i = 0; i < this->heap_size; ++i) {
		tree[i] = list[i];
	}

	this->build_max_heap();
}

template <typename T>
sian::data_structure::Heap<T>::~Heap(void) noexcept {
	delete[] this->tree;
}

template <typename T>
int sian::data_structure::Heap<T>::get_heap_size(void) const {
	return this->heap_size;
}

template <typename T>
void sian::data_structure::Heap<T>::push(T almt) {
	this->heap_size += 1;
	this->realloc();

	this->tree[heap_size - 1] = almt;
	this->build_max_heap();
}

template <typename T>
T sian::data_structure::Heap<T>::pop(void) {
	int value = this->tree[0];

	std::swap(this->tree[0], this->tree[this->heap_size - 1]);

	this->heap_size -= 1;

	this->max_heapify(0);

	return value;
}

template <typename T>
void sian::data_structure::Heap<T>::sort(T* list, int size, bool heapify) {
	int index = size - 1;
	for (int i = size - 1; i >= 0; --i) {
		list[i] = pop();
	}

	if (heapify) {
		this->heap_size = size;
		this->build_max_heap();
	}
}

template <typename T>
void sian::data_structure::Heap<T>::realloc(void) {
	if (this->heap_size < this->heap_max) return;

	this->heap_max *= 2;

	T* new_tree = new T[this->heap_max];
	for (int i = 0; i < this->heap_size; ++i) {
		new_tree[i] = this->tree[i];
	}

	delete[] tree;
	tree = new_tree;
}

template <typename T>
void sian::data_structure::Heap<T>::max_heapify(int index) {
    int i = index + 1;
	int l = 2 * i, r = 2 * i + 1, largest = 0;

	if (l <= this->heap_size &&
		this->tree[l - 1] > this->tree[i - 1]) {
		largest = l;
	} else {
		largest = i;
	}
	if (r <= this->heap_size &&
		this->tree[r - 1] > this->tree[largest - 1]) {
		largest = r;
	}

	if (largest != i) {
		std::swap(tree[i - 1], tree[largest - 1]);
		this->max_heapify(largest - 1);
	}
}

template <typename T>
void sian::data_structure::Heap<T>::build_max_heap(void) {
	for (int i = (this->heap_size + 1) / 2; i > 0; --i) {
		this->max_heapify(i - 1);
	}
}

template <typename T>
sian::data_structure::List<T>::List(void) {}

template <typename T>
sian::data_structure::List<T>::List(std::initializer_list<T> list) {
	for (auto almt : list) {
		this->push_back(almt);
	}
}

template <typename T>
sian::data_structure::List<T>::~List(void) noexcept {
	Node<T>* ptr = this->begin;
	Node<T>* next = nullptr;
	while (ptr) {
		next = ptr->next;
		delete ptr;
		ptr = next;
	}
}

template <typename T>
sian::data_structure::Node<T>*
sian::data_structure::List<T>::front(void) const {
	return this->begin;
}

template <typename T>
sian::data_structure::Node<T>*
sian::data_structure::List<T>::back(void) const {
	return this->end;
}

template <typename T>
void sian::data_structure::List<T>::push_back(T value) {
	Node<T>* new_node = new Node<T>;
	
    new_node->value = value;

	if (this->begin) {
		new_node->prev = this->end;
		this->end->next = new_node;
		this->end = new_node;
	} else {
		this->begin = new_node;
		this->end = new_node;
	}
}

template <typename T>
void sian::data_structure::List<T>::insert_next(Node<T>* ptr, T value) {
	Node<T>* new_node= new Node<T>;
	new_node->value = value;

	if (!this->begin) {
		this->begin = new_node;
		this->end = new_node;
	} else if (ptr) {
		new_node->prev = ptr;
		new_node->next = ptr->next;
		
		if (ptr->next) {
			ptr->next->prev = new_node;
		} else {
			this->end = new_node;
		}

		ptr->next = new_node;
	} else {
		new_node->next = this->begin;
		this->begin->prev = new_node;
		this->begin = new_node;
	}
}

template <typename T>
void sian::data_structure::List<T>::insert_sorted(T value) {
	Node<T>* ptr = this->begin;

	while(ptr) {
		if (ptr->value < value) {
			ptr = ptr->next;
		} else {
			this->insert_next(ptr->prev, value);
			return;
		}
	}
	this->insert_next(this->end, value);
}

template <typename T>
sian::data_structure::Node<T>* sian::data_structure::List<T>::operator[](int idx) const {
	Node<T>* ptr = this->begin;
	for (int i = 0; i < idx; ++i) {
		ptr = ptr->next;
	}
	return ptr;
}

#endif // OS dependency

#endif // Header duplicate
