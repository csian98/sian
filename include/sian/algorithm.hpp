/**
 * @file	    algorithm.hpp
 * @brief		Learning Objectives Basic Algorithms
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

template <typename T>
void sian::shuffle::permute_by_sorting(T* list, int size) {
	T* tmp = new T[size];
	
	std::random_device rd;
	std::mt19937 engine(rd());
	std::uniform_int_distribution<int> dist(0, size * 10);

	std::multimap<int, int> priority;
	for (int i = 0; i < size; ++i) {
		tmp[i] = list[i];
		priority.insert(std::make_pair(dist(engine), i));
	}

	int idx = 0;
	for (auto iter = priority.begin(); iter != priority.end(); ++iter) {
		list[idx] = tmp[iter->second];
		idx++;
	}

	delete[] tmp;
}

template <typename T>
void sian::shuffle::randomized_in_place(T* list, int size) {
	std::random_device rd;
	std::mt19937 engine(rd());

	int idx = 0;
	for (int i = 0; i < size; ++i) {
		std::uniform_int_distribution<int> dist(i, size - 1);
		idx = dist(engine);
		std::swap(list[i], list[idx]);
	}
}

template <typename T>
T sian::selection::min(T* list, int size) {
	T min = std::numeric_limits<T>::max();
	for (int i = 0 ;i < size; ++i) {
		if (min > list[i]) min = list[i];
	}
	return min;
}

template <typename T>
T sian::selection::max(T* list, int size) {
	T max = std::numeric_limits<T>::min();
	for (int i = 0; i < size; ++i) {
		if (max < list[i]) max = list[i];
	}
	return max;
}

template <typename T>
std::pair<T, T> sian::selection::minmax(T* list, int size) {
	T min = std::numeric_limits<T>::max();
	T max = std::numeric_limits<T>::min();

	T* ptr1 = nullptr;
	T* ptr2 = nullptr;

	if (size % 2) { // odd
		for (int i = 0; i < size - 1; i += 2) {
			ptr1 = list[i] < list[i + 1] ? &list[i] : &list[i + 1];
			ptr2 = list[i] < list[i + 1] ? &list[i + 1] : &list[i + 1];
			if (min > *ptr1) min = *ptr1;
			if (max < *ptr2) max = *ptr2;
		}
		if (min > list[size - 1]) min = list[size - 1];
		if (max < list[size - 1]) max = list[size - 1];
	} else { // even
		for (int i = 0; i < size; i += 2) {
			ptr1 = list[i] < list[i + 1] ? &list[i] : &list[i + 1];
			ptr2 = list[i] < list[i + 1] ? &list[i + 1] : &list[i + 1];
			if (min > *ptr1) min = *ptr1;
			if (max < *ptr2) max = *ptr2;
		}
	}

	return std::make_pair(min, max);
}

template <typename T>
T sian::selection::select(T* list, int p, int r, int i) {
	if (p == r - 1) return list[p];
	int q = sian::sort::_partition(list, p, r);

	if (q == i) return list[q];
	else if (i < q)
		return select(list, p, q, i);
	else
		return select(list, q + 1, r, i);
}

template <typename T>
T sian::selection::_median(T* list, const int size) {
	sian::sort::insert_sort(list, size);
	return list[size / 2];
}

template <typename T>
T sian::selection::_get_median(T* list, const int size) {
	if (size < 5) {
		return _median(list, size);
	}
	
	T* mid = new T[size / 5 + 1];

	for (int i = 0; i < size / 5; ++i) {
		if (i == size - 1 && !(size % 5)) {
			mid[i] = _median(list + 5 * i, size % 5);
		} else {
			mid[i] = _median(list + 5 * i, 5);
		}
	}
	int return_value = _get_median(mid, size / 5 + 1);
	delete[] mid;
	
	return return_value;
}

template <typename T>
T sian::selection::_partition_with_crt(T* list, int size, int pivot) {
	int idx = -1, p_idx = 0;
	for (int i = 0; i < size; ++i) {
		if (list[i] < pivot) {
			idx++;
			std::swap(list[idx], list[i]);
		}

		if (list[i] == pivot) {
			p_idx = i;
		}
	}
	++idx;
	std::swap(list[idx], list[p_idx]);
	return idx;
}

template <typename T>
T sian::selection::improved_select(T* list, int size, int i) {
	int med, pivot, p_order;

	if (size == 1) return list[0];

	med = _get_median(list, size);
	pivot = _partition_with_crt(list, size, med);
	p_order = pivot + 1;

	if (i < p_order) {
		return select(list, 0, pivot, i);
	} else if (i > p_order) {
		return select(list, 0, size - pivot, i);
	} else {
		return list[pivot];
	}
}


#endif // OS dependency

#endif // Header duplicate
