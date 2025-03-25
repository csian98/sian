/**
 * @file		binary_tree.hpp
 * @brief	    Binary Tree
 * @author		Jeong Hoon (Sian) Choi
 * @version 	1.0.0
 * @date		2024-06-03
 */
	 
//#pragma once
//#pragma GCC diagnostic ignored "-Wstringop-truncation"

#ifndef _HEADER_BINARY_TREEHPP_
#define _HEADER_BINARY_TREEHPP_

#include "sian/binary_tree.h"

#if _TARGET_OS == OS_WINDOWS

#elif _TARGET_OS == OS_LINUX

/* Inline & Template Definition */

template <typename T>
sian::data_structure::BinaryTree<T>::BinaryTree(void) {}

template <typename T>
sian::data_structure::BinaryTree<T>::BinaryTree(std::initializer_list<T> list) {
    for (auto iter = list.begin(); iter != list.end(); ++iter) {
		this->insert(*iter);
	}
}

template <typename T>
sian::data_structure::BinaryTree<T>::~BinaryTree(void) noexcept {
    this->inorder_tree_delete(this->root);
}

template <typename T>
void sian::data_structure::BinaryTree<T>::insert(const T& value) {
    Leaf<T>* ptr = new Leaf<T>;
	ptr->value = value;

	Leaf<T>* p_ptr = nullptr;
	Leaf<T>* c_ptr = this->root;

	while (c_ptr) {
		p_ptr = c_ptr;
		if (ptr->value < p_ptr->value) {
			c_ptr = p_ptr->left;
		} else {
			c_ptr = p_ptr->right;
		}
	}
	
    ptr->parent = p_ptr;
	if (!p_ptr) {
		this->root = ptr;
	} else if (ptr->value < p_ptr->value) {
		p_ptr->left = ptr;
	} else {
		p_ptr->right = ptr;
	}
	
}

template <typename T>
void sian::data_structure::BinaryTree<T>::remove(Leaf<T>* ptr) {
	if (!ptr->left) {
		this->transplant(ptr, ptr->right);
	} else if (!ptr->right) {
		this->transplant(ptr, ptr->left);
	} else {
		Leaf<T>* suc_ptr = this->min(ptr->right);
		if (suc_ptr->parent != ptr) {
			this->transplant(suc_ptr, suc_ptr->right);
			suc_ptr->right = ptr->right;
			suc_ptr->right->parent = suc_ptr;
		}
		this->transplant(ptr, suc_ptr);
		suc_ptr->left = ptr->left;
		suc_ptr->left->parent = suc_ptr;
	}
	delete ptr;
}

template <typename T>
void sian::data_structure::BinaryTree<T>::remove(const T& value) {
	Leaf<T>* ptr = this->find(value);
	this->remove(ptr);
}

template <typename T>
sian::data_structure::Leaf<T>*
sian::data_structure::BinaryTree<T>::find(const T& value) const {
	Leaf<T>* ptr = this->root;
	while (ptr && ptr->value != value) {
		if (value < ptr->value) {
			ptr = ptr->left;
		} else {
			ptr = ptr->right;
		}
	}
	return ptr;
}


template <typename T>
sian::data_structure::Leaf<T>*
sian::data_structure::BinaryTree<T>::min(void) const {
	if (!this->is_empty())
		return min(this->root);
	else
		return nullptr;
}

template <typename T>
sian::data_structure::Leaf<T>*
sian::data_structure::BinaryTree<T>::max(void) const {
	if (!this->is_empty())
		return max(this->root);
	else
		return nullptr;
}

template <typename T>
sian::data_structure::Leaf<T>*
sian::data_structure::BinaryTree<T>::min(Leaf<T>* leaf) const {
	Leaf<T>* ptr = leaf;
	while (ptr->left) {
		ptr = ptr->left;
	}
	return ptr;
}

template <typename T>
sian::data_structure::Leaf<T>*
sian::data_structure::BinaryTree<T>::max(Leaf<T>* leaf) const {
	Leaf<T>* ptr = leaf;
	while (ptr->right) {
		ptr = ptr->right;
	}
	return ptr;
}

template <typename T>
T sian::data_structure::BinaryTree<T>::min_value(void) const {
	return this->min()->value;
}

template <typename T>
T sian::data_structure::BinaryTree<T>::max_value(void) const {
	return this->max()->value;
}

template <typename T>
sian::data_structure::Leaf<T>*
sian::data_structure::BinaryTree<T>::successor(Leaf<T>* ptr) const {
	if (ptr->right) {
		return this->min(ptr->right);
	}
	Leaf<T>* c_ptr = ptr;
	Leaf<T>* p_ptr = ptr->parent;
	while (p_ptr && c_ptr == p_ptr->right) {
		c_ptr = p_ptr;
		p_ptr = c_ptr->parent;
	}
	return p_ptr;
}

template <typename T>
sian::data_structure::Leaf<T>*
sian::data_structure::BinaryTree<T>::predecessor(Leaf<T>* ptr) const {
	if (ptr->left) {
		return this->max(ptr->left);
	}
	Leaf<T>* c_ptr = ptr;
	Leaf<T>* p_ptr = ptr->parent;
	while (p_ptr && c_ptr == p_ptr->left) {
		c_ptr = p_ptr;
		p_ptr = c_ptr->parent;
	}
	return p_ptr;
}

template <typename T>
bool sian::data_structure::BinaryTree<T>::is_empty(void) const {
	return !this->root;
}

template <typename T>
void sian::data_structure::BinaryTree<T>::inorder_tree_delete(Leaf<T>* ptr) {
	if (ptr) {
		this->inorder_tree_delete(ptr->left);
		Leaf<T>* right_ptr = ptr->right;
		delete ptr;
		this->inorder_tree_delete(right_ptr);
	}
}

template <typename T>
void sian::data_structure::BinaryTree<T>::transplant(Leaf<T>* dst, Leaf<T>* src) {
	if (!dst->parent) {
		this->root = src;
	} else if (dst == dst->parent->left) {
		dst->parent->left = src;
	} else {
		dst->parent->right = src;
	}

	if (src) {
		src->parent = dst->parent;
	}
}

#endif // OS dependency

#endif // Header duplicate
