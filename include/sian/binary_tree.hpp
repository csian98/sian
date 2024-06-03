/**
 * @file		binary_tree.hpp
 * @brief		Learning Objectives Basic Data Structures
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
		this->insert(list);
	}
}

template <typename T>
sian::data_structure::BinaryTree<T>::~BinaryTree(void) noexcept {
    this->inorder_tree_delete();
}

template <typename T>
void sian::data_structure::BinaryTree<T>::insert(const T& value) {
    

}

template <typename T>
void sian::data_structure::BinaryTree<T>::remove(Leaf<T>* leaf) {
	
}

template <typename T>
void sian::data_structure::BinaryTree<T>::remove(T& value) {
	Leaf<T>* ptr = this->find(value);
	this->remove(ptr);
}

template <typename T>
sian::data_structure::Leaf<T>* sian::data_structure::BinaryTree<T>::find(const T& value) const {
	Leaf<T>* ptr = this->root;



	return ptr;
}


template <typename T>
sian::data_structure::Leaf<T>* sian::data_structure::BinaryTree<T>::min(void) const {
	Leaf<T>* ptr = root;
	while (ptr->left) {
		ptr = ptr->left;
	}
	return ptr;
}

template <typename T>
sian::data_structure::Leaf<T>* sian::data_structure::BinaryTree<T>::max(void) const {
	Leaf<T>* ptr = root;
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
void sian::data_structure::BinaryTree<T>::inorder_tree_delete(Leaf<T>* ptr) {
	if (ptr) {
		this->inorder_tree_delete(ptr->left);
		Leaf<T>* right_ptr = ptr->right;
		delete ptr;
		this->inorder_tree_delete(right_ptr);
	}
}

#endif // OS dependency

#endif // Header duplicate
