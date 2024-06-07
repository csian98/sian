/**
 * @file		functional_tree.hpp
 * @brief		Selection and Interval tree; extension of Red Black tree
 * @author		Jeong Hoon (Sian) Choi
 * @version 	1.0.0
 * @date		2024-06-06
 */

//#pragma once
//#pragma GCC diagnostic ignored "-Wstringop-truncation"

#ifndef _HEADER_FUNCTIONAL_TREEHPP_
#define _HEADER_FUNCTIONAL_TREEHPP_

#include "sian/functional_tree.h"

#if _TARGET_OS == OS_WINDOWS

#elif _TARGET_OS == OS_LINUX

/* Inline & Template Definition */

template <typename T>
sian::data_structure::SelectionTree<T>::SelectionTree(void) {
	set_size_leaf(this->nil_leaf, 0);
}

template <typename T>
void sian::data_structure::SelectionTree<T>::insert(const T& value) {
	SelectionLeaf<T>* ptr = new SelectionLeaf<T>;
	ptr->value = value;
	ptr->left = this->nil_leaf;
	ptr->right = this->nil_leaf;

    Leaf<T>* p_ptr = this->nil_leaf;
    Leaf<T>* c_ptr = this->root;

    while (c_ptr != this->nil_leaf) {
		p_ptr = c_ptr;
		if (ptr->value < p_ptr->value) {
			c_ptr = c_ptr->left;
		} else {
			c_ptr = c_ptr->right;
		}
		increase_size_leaf(p_ptr);
	}

	ptr->parent = p_ptr;
	if (p_ptr == this->nil_leaf) {
		this->root = ptr;
	} else if (ptr->value < p_ptr->value) {
		p_ptr->left = ptr;
	} else {
		p_ptr->right = ptr;
	}

    this->insert_fixup(ptr);
}

template <typename T>
void sian::data_structure::SelectionTree<T>::remove(Leaf<T>* ptr) {
    Leaf<T>* suc_ptr = ptr;
	Leaf<T>* sub_ptr = nullptr;
	bool suc_is_black = is_black(suc_ptr);

	if (ptr->left == this->nil_leaf) {
		sub_ptr = ptr->right;
		this->transplant(ptr, ptr->right);
	} else if (ptr->right == this->nil_leaf) {
		sub_ptr = ptr->left;
		this->transplant(ptr, ptr->left);
	} else {
		suc_ptr = this->min(ptr->right);
		suc_is_black = is_black(suc_ptr);

		sub_ptr = suc_ptr->right;

		if (suc_ptr->parent == ptr) {
			sub_ptr->parent = suc_ptr;
		} else {
			this->transplant(suc_ptr, suc_ptr->right);
			suc_ptr->right = ptr->right;
			suc_ptr->right->parent = suc_ptr;
		}
		this->transplant(ptr, suc_ptr);
		suc_ptr->left = ptr->left;
		suc_ptr->left->parent = suc_ptr;
		if (is_black(ptr)) {
			color_black(suc_ptr);
		} else {
			color_red(suc_ptr);
		}
	}

	this->climb_up_decrease(sub_ptr);

	if (suc_is_black) this->remove_fixup(sub_ptr);
	
	delete ptr;
}

template <typename T>
sian::data_structure::Leaf<T>*
sian::data_structure::SelectionTree<T>::select(Leaf<T>* ptr, int idx) const {
	int r = size_of_leaf(ptr->left) + 1;
	if (r == idx) {
		return ptr;
	} else if (idx < r) {
		return this->select(ptr->left, idx);
	} else {
		return this->select(ptr->right, idx - r);
	}
}

template <typename T>
int sian::data_structure::SelectionTree<T>::rank(Leaf<T>* ptr) const {
	int r = size_of_leaf(ptr->left) + 1;
	Leaf<T>* op_ptr = ptr;
	while (op_ptr != this->root) {
		if (op_ptr == op_ptr->parent->right) {
			r += size_of_leaf(op_ptr->parent->left) + 1;
		}
		op_ptr = op_ptr->parent;
	}
	return r;
}

template <typename T>
void sian::data_structure::SelectionTree<T>::left_rotate(Leaf<T>* ptr) {
	RedBlackTree<T>::left_rotate(ptr);

	Leaf<T>* p_ptr = ptr->parent;
	set_size_leaf(p_ptr, size_of_leaf(ptr));
	set_size_leaf(ptr, size_of_parent(ptr->left, ptr->right));
}

template <typename T>
void sian::data_structure::SelectionTree<T>::right_rotate(Leaf<T>* ptr) {
    RedBlackTree<T>::right_rotate(ptr);

	Leaf<T>* p_ptr = ptr->parent;
	set_size_leaf(p_ptr, size_of_leaf(ptr));
	set_size_leaf(ptr, size_of_parent(ptr->left, ptr->right));
}

template <typename T>
void sian::data_structure::SelectionTree<T>::climb_up_decrease(Leaf<T>* leaf) {
    Leaf<T>* ptr = leaf;
	while (ptr != this->root) {
		if (ptr != this->nil_leaf)
			set_size_leaf(ptr, size_of_parent(ptr->left, ptr->right));
		ptr = ptr->parent;
	}
}

template <typename T>
sian::data_structure::Interval<T>::Interval(void) {}

template <typename T>
sian::data_structure::Interval<T>::Interval(const T& low, const T& high) : low(low), high(high) {}

template <typename T>
sian::data_structure::Interval<T>::Interval(const Interval<T>& other) {
	this->low = other.low;
	this->high = other.high;
}

template <typename T>
bool sian::data_structure::Interval<T>::is_overlap(const Interval<T>& other) const {
	if (this->righ_closed) {
		return (this->low <= other.high && other.low <= this->high);
	} else {
		return (this->low <= other.high && other.low < this->high);
	}
}

template <typename T>
bool sian::data_structure::Interval<T>::operator<(const Interval<T>& other) const {
	return this->high < other.high;
}

template <typename T>
bool sian::data_structure::Interval<T>::operator==(const Interval<T>& other) const {
	return (this->high == other.high && this->low == other.low) ? true : false;
}

template <typename T>
sian::data_structure::IntervalTree<T>::IntervalTree(void) {}

template <typename T>
void sian::data_structure::IntervalTree<T>::insert(const Interval<T>& value) {
	IntervalLeaf<T>* ptr = new IntervalLeaf<T>;
	ptr->value = value;
	ptr->left = this->nil_leaf;
	ptr->right = this->nil_leaf;

    Leaf<Interval<T>>* p_ptr = this->nil_leaf;
    Leaf<Interval<T>>* c_ptr = this->root;

    while (c_ptr != this->nil_leaf) {
		p_ptr = c_ptr;
		if (ptr->value < p_ptr->value) {
			c_ptr = c_ptr->left;
		} else {
			c_ptr = c_ptr->right;
		}
		compare_update_max(p_ptr, value.high);
	}

	ptr->parent = p_ptr;
	if (p_ptr == this->nil_leaf) {
		this->root = ptr;
	} else if (ptr->value < p_ptr->value) {
		p_ptr->left = ptr;
	} else {
		p_ptr->right = ptr;
	}

    this->insert_fixup(ptr);
}

template <typename T>
void sian::data_structure::IntervalTree<T>::insert(const T& low, const T& high) {
	Interval<T> interval(low, high);
	this->insert(interval);
}

template <typename T>
void sian::data_structure::IntervalTree<T>::remove(Leaf<Interval<T>>* ptr) {
    Leaf<Interval<T>>* suc_ptr = ptr;
	Leaf<Interval<T>>* sub_ptr = nullptr;
	bool suc_is_black = is_black(suc_ptr);

	if (ptr->left == this->nil_leaf) {
		sub_ptr = ptr->right;
		this->transplant(ptr, ptr->right);
	} else if (ptr->right == this->nil_leaf) {
		sub_ptr = ptr->left;
		this->transplant(ptr, ptr->left);
	} else {
		suc_ptr = this->min(ptr->right);
		suc_is_black = is_black(suc_ptr);

		sub_ptr = suc_ptr->right;

		if (suc_ptr->parent == ptr) {
			sub_ptr->parent = suc_ptr;
		} else {
			this->transplant(suc_ptr, suc_ptr->right);
			suc_ptr->right = ptr->right;
			suc_ptr->right->parent = suc_ptr;
		}
		this->transplant(ptr, suc_ptr);
		suc_ptr->left = ptr->left;
		suc_ptr->left->parent = suc_ptr;
		if (is_black(ptr)) {
			color_black(suc_ptr);
		} else {
			color_red(suc_ptr);
		}
	}

	this->climb_up_update_max(sub_ptr);

	if (suc_is_black) this->remove_fixup(sub_ptr);
	
	delete ptr;
}

template <typename T>
sian::data_structure::Leaf<sian::data_structure::Interval<T>>*
sian::data_structure::IntervalTree<T>::find(const Interval<T>& interval) const {
	Leaf<Interval<T>>* ptr = this->root;

	while (ptr != this->nil_leaf && !interval.is_overlap(ptr->value)) {
		if (ptr->left != this->nil_leaf && max_of_leaf(ptr->left) >= interval.low)
			ptr = ptr->left;
		else
			ptr = ptr->right;
	}
	
	return ptr != this->nil_leaf ? ptr : nullptr;
}

template <typename T>
sian::data_structure::Leaf<sian::data_structure::Interval<T>>*
sian::data_structure::IntervalTree<T>::find(const T& low, const T& high) const {
    Interval<T> interval(low, high);
	return this->find(interval);
}

template <typename T>
void sian::data_structure::IntervalTree<T>::left_rotate(Leaf<Interval<T>>* ptr) {
	RedBlackTree<Interval<T>>::left_rotate(ptr);

	update_max(ptr);
}

template <typename T>
void sian::data_structure::IntervalTree<T>::right_rotate(Leaf<Interval<T>>* ptr) {
    RedBlackTree<Interval<T>>::right_rotate(ptr);

	Leaf<Interval<T>>* p_ptr = ptr->parent;
	update_max(p_ptr);
}

template <typename T>
void sian::data_structure::IntervalTree<T>::climb_up_update_max(Leaf<Interval<T>>* leaf) {
    Leaf<Interval<T>>* ptr = leaf;
	while (ptr != this->root) {
		if (ptr != this->nil_leaf)
			update_max(ptr);
		ptr = ptr->parent;
	}
}

template <typename T>
size_t sian::data_structure::size_of_leaf(Leaf<T>* leaf) {
	return static_cast<SelectionLeaf<T>*>(leaf)->size;
}

template <typename T>
size_t sian::data_structure::size_of_parent(Leaf<T>* left, Leaf<T>* right) {
	return static_cast<SelectionLeaf<T>*>(left)->size + static_cast<SelectionLeaf<T>*>(right)->size + 1;
}

template <typename T>
void sian::data_structure::set_size_leaf(Leaf<T>* leaf, size_t size) {
	static_cast<SelectionLeaf<T>*>(leaf)->size = size;
}

template <typename T>
void sian::data_structure::increase_size_leaf(Leaf<T>* leaf) {
	set_size_leaf(leaf, size_of_leaf(leaf) + 1);
}

template <typename T>
T sian::data_structure::max_of_leaf(Leaf<Interval<T>>* leaf) {
	return static_cast<IntervalLeaf<T>*>(leaf)->max;
}

template <typename T>
void sian::data_structure::update_max(Leaf<Interval<T>>* leaf) {
	IntervalLeaf<T>* ptr = static_cast<IntervalLeaf<T>*>(leaf);

	ptr->max = std::max({ptr->value.high, max_of_leaf(ptr->left), max_of_leaf(ptr->right)});
}

template <typename T>
void sian::data_structure::compare_update_max(Leaf<Interval<T>>* leaf, T high) {
	IntervalLeaf<T>* ptr = static_cast<IntervalLeaf<T>*>(leaf);

	ptr->max = ptr->max < high ? high : ptr->max;
}

#endif // OS dependency

#endif // Header duplicate
