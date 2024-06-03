/**
 * @file		data_structure.hpp
 * @brief		Learning Objectives Basic Data Structures
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
	this->heap_max = static_cast<int>(std::log2(this->heap_size)) + 1;

	this->tree = new T[this->heap_max];

	for (int i = 0; i < this->heap_size; ++i) {
		tree[i] = list[i];
	}

	this->build_max_heap();
}

template <typename T>
sian::data_structure::Heap<T>::Heap(T* list, int size) {
	this->heap_size = size;
	this->heap_max = static_cast<int>(std::log2(this->heap_size)) + 1;

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
void sian::data_structure::List<T>::push_front(T value) {
	Node<T>* new_node = new Node<T>;

	new_node->value = value;

	if (this->begin) {
		new_node->next = this->begin;
		this->begin->prev = new_node;
		this->begin = new_node;
	} else {
		this->begin = new_node;
		this->end = new_node;
	}
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

	while (ptr) {
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
void sian::data_structure::List<T>::remove(Node<T>* node) {
	if (this->begin == node) {
		if (node->next) {
			this->begin = node->next;
			node->next->prev = nullptr;
		} else {
			this->begin = nullptr;
			this->end = nullptr;
		}
	} else if (this->end == node) {
		if (node->prev) {
			this->end = node->prev;
			node->prev->next = nullptr;
		} else {
			this->begin = nullptr;
			this->end = nullptr;
		}
	} else {
		node->prev->next = node->next;
		node->next->prev = node->prev;
	}
	delete node;
}

template <typename T>
sian::data_structure::Node<T>*
sian::data_structure::List<T>::find_value(T value) const {
	Node<T>* ptr = this->begin;

	while (ptr) {
		if (ptr->value == value) return ptr;
		ptr = ptr->next;
	}
	return nullptr;
}

template <typename T>
sian::data_structure::Node<T>*
sian::data_structure::List<T>::find_index(int idx) const {
	Node<T>* ptr = this->begin;
	for (int i = 0; i < idx && ptr; ++i) {
		ptr = ptr->next;
	}
	return ptr;
}

template <typename T>
sian::data_structure::Node<T>*
sian::data_structure::List<T>::operator[](int idx) const {
	return this->find_index(idx);
}

template <typename T>
sian::data_structure::Vector<T>::Vector(void) {
	realloc(1);
}

template <typename T>
sian::data_structure::Vector<T>::Vector(std::initializer_list<T> list) {
	realloc(1);
	for (auto iter = list.begin(); iter != list.end(); ++iter) {
		this->push_back(*iter);
	}
}

template <typename T>
sian::data_structure::Vector<T>::~Vector(void) noexcept {
	delete[] this->vector;
}

template <typename T>
void sian::data_structure::Vector<T>::push_back(T value) {
	this->size++;
	
	realloc();
	
	this->vector[this->size - 1] = value;
}

template <typename T>
void sian::data_structure::Vector<T>::push_front(T value) {
	this->size++;

	realloc();

	for (int i = this->size - 1; i > 0; --i) {
		this->vector[i] = this->vector[i - 1];
	}
	this->vector[0] = value;
}

template <typename T>
T sian::data_structure::Vector<T>::pop_back(void) {
	this->size--;
	int value = this->vector[this->size];

	realloc();

	return value;
}

template <typename T>
T sian::data_structure::Vector<T>::pop_front(void) {
	this->size--;
	int value = this->vector[0];

	realloc();

	return value;
}

template <typename T>
bool sian::data_structure::Vector<T>::is_empty(void) const {
	return this->size == 0;
}

template <typename T>
T sian::data_structure::Vector<T>::operator[](int idx) const {
	if (this->size > idx) {
		return this->vector[idx];
	}
	throw data_structure_error("Out of Index Error");
}

template <typename T>
void sian::data_structure::Vector<T>::realloc(void) {
	if (this->capacity <= this->size) {
		this->capacity *= 2;
	} else if (this->capacity / 2 > this->size) {
		this->capacity /= 2;
	} else {
		return;
	}

	T* new_vector = new T[this->capacity];
	for (int i = 0; i < this->size; ++i) {
		new_vector[i] = this->vector[i];
	}
	delete[] this->vector;
	this->vector = new_vector;
}

template <typename T>
void sian::data_structure::Vector<T>::realloc(int size) {
	int new_capacity = this->binary_round_up(size);

	if (this->capacity == new_capacity) return;
	
	this->capacity = this->binary_round_up(size);
	T* new_vector = new T[this->capacity];
	for (int i = 0; i < this->size; ++i) {
		new_vector[i] = this->vector[i];
	}
	delete[] this->vector;
	this->vector = new_vector;
}

template <typename T>
int sian::data_structure::Vector<T>::binary_round_up(int num) {
	return static_cast<int>(log2(num)) + 1;
}

template <typename T>
sian::data_structure::Circle<T>::Circle(void) {
	this->realloc(1);
}

template <typename T>
sian::data_structure::Circle<T>::Circle(std::initializer_list<T> list) {
	this->realloc(1);
	for (auto iter = list.begin(); iter != list.end(); ++iter) {
		this->push_back(*iter);
	}
}

template <typename T>
sian::data_structure::Circle<T>::~Circle(void) noexcept {
	delete[] this->vector;
}

template <typename T>
void sian::data_structure::Circle<T>::push_back(T value) {
	this->size++;
	this->realloc();

	this->tail++;
	this->vector[this->tail - 1] = value;
	
	if (this->tail == this->capacity) {
		this->tail = 0;
	}
}

template <typename T>
void sian::data_structure::Circle<T>::push_front(T value) {
	this->size++;
	this->realloc();

	this->head--;
	if (this->head == -1) {
		this->head = this->capacity - 1;
	}
	this->vector[this->head] = value;
}

template <typename T>
T sian::data_structure::Circle<T>::pop_back(void) {
	this->size--;
	this->realloc();
	
	this->tail--;

	if (this->tail == -1) {
		this->tail = this->capacity - 1;
	}
	int value = this->vector[this->tail];

	return value;
}

template <typename T>
T sian::data_structure::Circle<T>::pop_front(void) {
	this->size--;
	this->realloc();

	T value = this->vector[this->head];
	this->head++;
	if (this->head == this->capacity) {
		this->head = 0;
	}

	return value;
}

template <typename T>
bool sian::data_structure::Circle<T>::is_empty(void) const {
	return this->size == 0;
}

template <typename T>
T sian::data_structure::Circle<T>::operator[](int idx) const {
	int new_index = 0;
	if (idx > this->size - 1) {
		throw data_structure_error("Out of Index Error");
	} else {
		new_index = this->head + idx;
		if (new_index > this->capacity - 1) {
			new_index -= this->tail + 1;
		}
	}
	return this->vector[new_index];
}

template <typename T>
void sian::data_structure::Circle<T>::realloc(void) {
	size_t orig_capacity = this->capacity;
	bool is_extend = true;
	if (this->capacity <= this->size) {
		this->capacity *= 2;
		is_extend = true;
	} else if (this->capacity / 2 > this->size) {
		this->capacity /= 2;
		is_extend = false;
	} else {
		return;
	}
	
	T* new_vector = new T[this->capacity];
	int head_to_tail = this->head;
	for (int i = 0; i < this->size; ++i) {
		new_vector[i] = this->vector[head_to_tail];
		head_to_tail++;
		if (head_to_tail == orig_capacity) head_to_tail = 0;
	}
	if (!is_extend) {
		new_vector[this->size] = this->vector[head_to_tail];
	}
	delete[] this->vector;
	this->vector = new_vector;

	this->head = 0;
	this->tail = is_extend ? this->size - 1 : this->size + 1;
}

template <typename T>
void sian::data_structure::Circle<T>::realloc(int new_size) {
	int new_capacity = this->binary_round_up(new_size);

	if (this->capacity == new_capacity) return;

	size_t orig_capacity = this->capacity;
	this->capacity = std::pow(2, this->binary_round_up(new_size));
	T* new_vector = new T[this->capacity];
	int head_to_tail = this->head;
	for (int i = 0; i < this->size; ++i) {
		new_vector[i] = this->vector[head_to_tail];
		head_to_tail++;
		if (head_to_tail == orig_capacity) head_to_tail = 0;
	}
	delete[] this->vector;
	this->vector = new_vector;

	this->head = 0; this->tail = this->size;
}

template <typename T>
int sian::data_structure::Circle<T>::binary_round_up(int num) {
	return static_cast<int>(log2(num)) + 1;
}

template <typename T, typename U>
sian::data_structure::Stack<T, U>::Stack(void) {}

template <typename T, typename U>
T sian::data_structure::Stack<T, U>::pop(void) {
	return this->stack.pop_back();
}

template <typename T, typename U>
void sian::data_structure::Stack<T, U>::push(T value) {
	this->stack.push_back(value);
}

template <typename T, typename U>
bool sian::data_structure::Stack<T, U>::is_empty(void) const {
	return this->stack.is_empty();
}

template <typename T, typename U>
sian::data_structure::Queue<T, U>::Queue(void) {}

template <typename T, typename U>
T sian::data_structure::Queue<T, U>::pop(void) {
	return this->queue.pop_front();
}

template <typename T, typename U>
void sian::data_structure::Queue<T, U>::push(T value) {
	this->queue.push_back(value);
}

template <typename T, typename U>
bool sian::data_structure::Queue<T, U>::is_empty(void) const {
	return this->queue.is_empty();
}

#endif // OS dependency

#endif // Header duplicate
