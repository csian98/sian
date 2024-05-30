/**
 * @file	    algorithm.hpp
 * @brief		basic algorithms (learning purpose source codes)
 * @author		Jeong Hoon (Sian) Choi
 * @version 	1.0.0
 * @date		2024-05-29
 */
	 
//#pragma once
//#pragma GCC diagnostic ignored "-Wstringop-truncation"

#ifndef _HEADER_ALGORITHMHPP_
#define _HEADER_ALGORITHMHPP_

#include "sian/algorithm.h"

#if _TARGET_OS == OS_WINDOWS

#elif _TARGET_OS == OS_LINUX

/* Inline & Template Definition */

template <typename T>
void sian::sort::selection_sort(T* list, int size) {
	for (int i = 0; i < size; ++i) {
		int index = i;
		T criteria = std::numeric_limits<T>::max();
		for (int j = i; j < size; ++j) {
			if (list[j] < criteria) {
				index = j;
				criteria = list[j];
			}
		}
		std::swap(list[i], list[index]);
	}
}

template <typename T>
void sian::sort::insert_sort(T* list, int size) {
	for (int i = 0; i < size; ++i) {
		for (int j = i + 1; j < size; ++j) {
			if (list[i] > list[j]) std::swap(list[i], list[j]);
		}
	}
}

template <typename T>
void sian::sort::bubble_sort(T* list, int size) {
	for (int i = 0; i < size; ++i) {
		for (int j = 0; j < size - i - 1; ++j) {
			if (list[j] > list[j + 1]) std::swap(list[j], list[j + 1]);
		}
	}
}

template <typename T>
void sian::sort::_merge(T* dst, int p, int q, int r) {
	int n1 = q - p;
	int n2 = r - q;
	T front[n1 + 1];
	T back[n2 + 1];
	for (int i = 0; i < n1; ++i) {
		front[i] = dst[p + i];
	}
	for (int i = 0; i < n2; ++i) {
		back[i] = dst[q + i];
	}
	front[n1] = std::numeric_limits<T>::max();
	back[n2] = std::numeric_limits<T>::max();

	int i = 0, j = 0;
	for (int k = 0; k < n1 + n2; ++k) {
		if(front[i] <= back[j]) {
			dst[p + k] = front[i];
			++i;
		} else {
			dst[p + k] = back[j];
			++j;
		}
	}
}

template <typename T>
void sian::sort::merge_sort(T* dst, int p, int r) {
	if (p < r - 1) {
		int q = (p + r) / 2;
		merge_sort(dst, p, q);
		merge_sort(dst, q, r);
		_merge(dst, p, q, r);
	}
}

template <typename T>
void sian::sort::heap_sort(T* list, int size) {
	sian::data_structure::Heap<T> heap(list, size);
	heap.sort(list, size, false);
}

template <typename T>
int sian::sort::_partition(T* list, int p, int r) {
	int x = list[r - 1], i = p - 1;
	for (int j = p; j < r - 1; ++j) {
		if (list[j] <= x) {
			i++;
			std::swap(list[i], list[j]);
		}
	}
	std::swap(list[i + 1], list[r - 1]);
	return i + 1;
}

template <typename T>
void sian::sort::quick_sort(T* list, int p, int r) {
	if (p < r - 1) {
		int q = _partition(list, p, r);
		quick_sort(list, p, q);
		quick_sort(list, q, r);
	}
}

#endif // OS dependency

#endif // Header duplicate
