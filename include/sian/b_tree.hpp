/**
 * @file	    b_tree.hpp
 * @brief		B Tree
 * @author		Jeong Hoon (Sian) Choi
 * @version 	1.0.0
 * @date		2024-06-11
 */
	 
//#pragma once
//#pragma GCC diagnostic ignored "-Wstringop-truncation"

#ifndef _HEADER_B_TREEHPP_
#define _HEADER_B_TREEHPP_

#include "sian/b_tree.h"

#if _TARGET_OS == OS_WINDOWS

#elif _TARGET_OS == OS_LINUX

/* Inline & Template Definition */

template <typename T>
const size_t sian::data_structure::BTreeNode<T>::t = 1001;

template <typename T>
sian::data_structure::BTreeNode<T>::BTreeNode(void)
	: keys(2 * t - 1), branches(2 * t) {}

template <typename T>
sian::data_structure::BTreeNode<T>::BTreeNode(BTreeNode<T>* ptr)
	: BTreeNode() {
	this->branches[0] = ptr;
}

template <typename T>
int sian::data_structure::BTreeNode<T>::find(const T& value) const {
	for (int i = 0; i < this->size; ++i) {
		if (this->keys[i] == value) {
			return i;
		} else if (this->keys[i] > value) {
			return -i - 1;
		}
	}
	return -(this->size) - 1;
}

template <typename T>
void sian::data_structure::BTreeNode<T>::insert(const T& value) {
	int index = this->negative_index(this->find(value));
	
	this->insert(value, index);
}

template <typename T>
void sian::data_structure::BTreeNode<T>::insert(const T& value, int idx) {
	for (int i = this->size; i > idx ; --i) {
		this->keys[i] = this->keys[i - 1];
	}
	this->keys[idx] = value;

	this->size++;
}

template <typename T>
void sian::data_structure::BTreeNode<T>::insert(const T& value, BTreeNode<T>* ptr) {
	int index = this->negative_index(this->find(value));

	this->insert(value, index);
	
	for (int i = this->size + 1; i > index + 1; --i) {
		this->branches[i] = this->branches[i - 1];
	}

	this->branches[index + 1] = ptr;
}

template <typename T>
void sian::data_structure::BTreeNode<T>::insert_front(const T& value, BTreeNode<T>* ptr) {
	int index = this->negative_index(this->find(value));

	this->insert(value, index);

	for (int i = this->size + 1; i > index; --i) {
		this->branches[i] = this->branches[i - 1];
	}

	this->branches[index] = ptr;
}

template <typename T>
void sian::data_structure::BTreeNode<T>::remove(const T& value) {
	int index = this->find(value);

	if (index < 0) {
		throw btree_exception("BTreeNode do not have value");
	}

	for (int i = index; i < this->size - 1; ++i) {
		this->keys[i] = this->keys[i + 1];
	}

	if (this->branches[index + 1]) {
		throw btree_exception("BTreeNode need to handle right brances before delete");
	}

	for (int i = index + 1; i < this->size; ++i) {
		this->branches[i] = this->branches[i + 1];
	}

	this->size--;
}

template <typename T>
const T& sian::data_structure::BTreeNode<T>::medium(void) const {
	return this->keys[BTreeNode<T>::t - 1];
}

template <typename T>
sian::data_structure::BTreeNode<T>*
sian::data_structure::BTreeNode<T>::split(void) {
	BTreeNode<T>* ptr
		= new BTreeNode<T>(this->branches[BTreeNode<T>::t]);

	for (int i = 0; i < BTreeNode<T>::t - 1; ++i) {
		int index = BTreeNode<T>::t + i;
		T value = this->keys[index];
		ptr->insert(value, this->branches[index + 1]);
	}
	this->size = BTreeNode<T>::t - 1;
	return ptr;
}

template <typename T>
void sian::data_structure::BTreeNode<T>::merge(BTreeNode<T>* ptr) {
	for (int i = 0; i < ptr->size; ++i) {
		this->insert(ptr->keys[i], ptr->branches[i + 1]);
	}
	delete ptr;
}

template <typename T>
void sian::data_structure::BTreeNode<T>::split_child(int idx) {
	BTreeNode<T>* l_ptr = this->branches[idx];
	int value = l_ptr->medium();
	BTreeNode<T>* r_ptr = l_ptr->split();

	r_ptr->leaf = l_ptr->leaf;
	this->insert(value, r_ptr);
}

template <typename T>
void sian::data_structure::BTreeNode<T>::merge_child(int idx) {
	BTreeNode<T>* l_ptr = this->branches[idx];
	BTreeNode<T>* r_ptr = this->branches[idx + 1];

	l_ptr->insert(this->keys[idx], r_ptr->branches[0]);
	l_ptr->merge(r_ptr);

	this->branches[idx + 1] = nullptr;
	this->remove(this->keys[idx]);
}

template <typename T>
void sian::data_structure::BTreeNode<T>::left_rotate(int idx) {
	BTreeNode<T>* l_ptr = this->branches[idx];
	BTreeNode<T>* r_ptr = this->branches[idx + 1];

	l_ptr->insert(this->keys[idx], r_ptr->branches[0]);

	this->keys[idx] = r_ptr->keys[0];

	std::swap(r_ptr->branches[0], r_ptr->branches[1]);
	r_ptr->branches[1] = nullptr;
	r_ptr->remove(r_ptr->keys[0]);
}

template <typename T>
void sian::data_structure::BTreeNode<T>::right_rotate(int idx) {
	BTreeNode<T>* l_ptr = this->branches[idx];
	BTreeNode<T>* r_ptr = this->branches[idx + 1];

	r_ptr->insert_front(this->keys[idx], l_ptr->branches[l_ptr->size]);

	this->keys[idx] = l_ptr->keys[l_ptr->size - 1];
	l_ptr->branches[l_ptr->size] = nullptr;
	l_ptr->remove(l_ptr->keys[l_ptr->size - 1]);
}

template <typename T>
int sian::data_structure::BTreeNode<T>::negative_index(const int index) {
	if (index > -1) {
		throw btree_exception("branches used negative index");
	} else {
		return std::abs(index) - 1;
	}
}

template <typename T>
T sian::data_structure::BTreeNode<T>::remove_predecessor(BTreeNode<T>* ptr) {
    if (!ptr->leaf) {
		return BTreeNode<T>::remove_predecessor(ptr->branches[ptr->size]);
	} else {
		int value = ptr->keys[ptr->size - 1];
		ptr->remove(value);
		return value;
	}
}

template <typename T>
T sian::data_structure::BTreeNode<T>::remove_successor(BTreeNode<T>* ptr) {
	if (!ptr->leaf) {
		return BTreeNode<T>::remove_successor(ptr->branches[0]);
	} else {
		int value = ptr->keys[0];
		ptr->remove(value);
		return value;
	}
}

template <typename T>
sian::data_structure::BTree<T>::BTree(void) {
	this->root = new BTreeNode<T>;
}

template <typename T>
sian::data_structure::BTree<T>::~BTree(void) noexcept {
	
}

template <typename T>
sian::data_structure::BTreeNode<T>*
sian::data_structure::BTree<T>::find(const T& value) const {
	return this->recursive_find(this->root, value);
}

template <typename T>
void sian::data_structure::BTree<T>::insert(const T& value) {
	if (this->root->size == BTreeNode<T>::t * 2 - 1) {
		BTreeNode<T>* new_ptr = new BTreeNode<T>(this->root);
		this->root = new_ptr;
		new_ptr->leaf = false;

		new_ptr->split_child(0);
	}
	this->recursive_insert(this->root, value);
}

template <typename T>
void sian::data_structure::BTree<T>::remove(const T& value) {
	this->recursive_remove(this->root, value);
}

template <typename T>
sian::data_structure::BTreeNode<T>*
sian::data_structure::BTree<T>::recursive_find(BTreeNode<T>* ptr,
											   const T& value) const {
	if (ptr) {
		int index = ptr->find(value);
		if (index > -1) {
			return ptr;
		} else {
			return recursive_find(
				ptr->branches[BTreeNode<T>::negative_index(index)],
				value);
		}
	} else {
		return nullptr;
	}
}

template <typename T>
void sian::data_structure::BTree<T>::recursive_insert(BTreeNode<T>* ptr, const T& value) {
	if (ptr->leaf) {
		ptr->insert(value);
	} else {
	    int idx = BTreeNode<T>::negative_index(ptr->find(value));
		if (ptr->branches[idx]->size == BTreeNode<T>::t * 2 - 1) {
			ptr->split_child(idx);
			idx = BTreeNode<T>::negative_index(ptr->find(value));
		}
		this->recursive_insert(ptr->branches[idx], value);
	}
}

template <typename T>
void sian::data_structure::BTree<T>::recursive_remove(BTreeNode<T>* ptr, const T& value) {
	if (ptr->leaf) {
		ptr->remove(value);
	} else {
	    int idx = ptr->find(value);
		if (idx > -1) {
			if (ptr->branches[idx]->size > BTreeNode<T>::t - 1) {
				T new_value = BTreeNode<T>::remove_predecessor(ptr->branches[idx]);
				ptr->keys[idx] = new_value;
			} else if (ptr->branches[idx + 1]->size > BTreeNode<T>::t - 1) {
				T new_value = BTreeNode<T>::remove_successor(ptr->branches[idx + 1]);
				ptr->keys[idx] = new_value;
			} else {
				BTreeNode<T>* c_ptr = ptr->branches[idx];
				ptr->merge_child(idx);
				if (ptr->size == 0)
					this->delete_empty_node(value);
				
				this->recursive_remove(c_ptr, value);
			}
		} else {
			idx = BTreeNode<T>::negative_index(idx);
			BTreeNode<T>* c_ptr = ptr->branches[idx];
			if (c_ptr->size == BTreeNode<T>::t - 1) {
				if (idx > 0 &&
					ptr->branches[idx - 1]->size > BTreeNode<T>::t - 1) {
					ptr->right_rotate(idx - 1);
					this->recursive_remove(c_ptr, value);
				} else if (idx < ptr->size &&
						   ptr->branches[idx + 1]->size > BTreeNode<T>::t - 1) {
				    ptr->left_rotate(idx);
					this->recursive_remove(c_ptr, value);
				} else {
					if (idx != ptr->size) {
						ptr->merge_child(idx);
						c_ptr = ptr->branches[idx];
					} else {
						ptr->merge_child(idx - 1);
						c_ptr = ptr->branches[idx - 1];
					}

					if (ptr->size == 0)
						this->delete_empty_node(value);
					
					this->recursive_remove(c_ptr, value);
				}
			} else {
				this->recursive_remove(c_ptr, value);
			}
		}
	}
}

template <typename T>
void sian::data_structure::BTree<T>::delete_empty_node(const T& value) {
    BTreeNode<T>* ptr = this->root;
	BTreeNode<T>* p_ptr = nullptr;
	int idx = 0;
	while (ptr->size != 0) {
	    idx = BTreeNode<T>::negative_index(ptr->find(value));
		p_ptr = ptr;
		ptr = p_ptr->branches[idx];
	}
	if (ptr != this->root) {
		idx = BTreeNode<T>::negative_index(p_ptr->find(value));
		p_ptr->branches[idx] = ptr->branches[0];
	} else {
		this->root = ptr->branches[0];
	}

	delete ptr;
}

#endif // OS dependency

#endif // Header duplicate
