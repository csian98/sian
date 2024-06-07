/**
 * @file		red_black_tree.hpp
 * @brief		Red-Black Tree
 * @author		Jeong Hoon (Sian) Choi
 * @version 	1.0.0
 * @date		2024-06-05
 */
	 
//#pragma once
//#pragma GCC diagnostic ignored "-Wstringop-truncation"

#ifndef _HEADER_RED_BLACK_TREEHPP_
#define _HEADER_RED_BLACK_TREEHPP_

#include "sian/red_black_tree.h"

#if _TARGET_OS == OS_WINDOWS

#elif _TARGET_OS == OS_LINUX

/* Inline & Template Definition */

template <typename T>
sian::data_structure::RedBlackTree<T>::RedBlackTree(void) : nil_leaf(new RedBlackLeaf<T>) {
	color_black(this->nil_leaf);
	this->root = this->nil_leaf;
}

template <typename T>
sian::data_structure::RedBlackTree<T>::RedBlackTree(std::initializer_list<T> list) : BinaryTree<T>(), nil_leaf(new RedBlackTree<T>) {
	color_black(this->nil_leaf);
	this->root = this->nil_leaf;

	for (auto iter = list.begin(); iter != list.end(); ++iter) {
		this->insert(*iter);
	}
}

template <typename T>
sian::data_structure::RedBlackTree<T>::~RedBlackTree(void) noexcept {
    this->inorder_tree_delete(this->root);
	
	delete this->nil_leaf;

	this->root = nullptr;
	this->nil_leaf = nullptr;
}

template <typename T>
void sian::data_structure::RedBlackTree<T>::insert(const T& value) {
	RedBlackLeaf<T>* ptr = new RedBlackLeaf<T>;
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
void sian::data_structure::RedBlackTree<T>::remove(Leaf<T>* ptr) {
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

	if (suc_is_black) this->remove_fixup(sub_ptr);
	
	delete ptr;
}

template <typename T>
sian::data_structure::Leaf<T>*
sian::data_structure::RedBlackTree<T>::find(const T& value) const {
	Leaf<T>* ptr = this->root;
	while (ptr != this->nil_leaf && ptr->value != value) {
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
sian::data_structure::RedBlackTree<T>::min(Leaf<T>* leaf) const {
	Leaf<T>* ptr = leaf;
	while (ptr->left != this->nil_leaf) {
		ptr = ptr->left;
	}
	return ptr;
}

template <typename T>
sian::data_structure::Leaf<T>*
sian::data_structure::RedBlackTree<T>::max(Leaf<T>* leaf) const {
	Leaf<T>* ptr = leaf;
	while (ptr->right != this->nil_leaf) {
		ptr = ptr->right;
	}
	return ptr;
}

template <typename T>
sian::data_structure::Leaf<T>*
sian::data_structure::RedBlackTree<T>::max(void) const {
	if (this->is_empty())
		return nullptr;
	else
		return this->max(this->root);
}

template <typename T>
sian::data_structure::Leaf<T>*
sian::data_structure::RedBlackTree<T>::min(void) const {
	if (this->is_empty())
		return nullptr;
	else
		return this->min(this->root);
}

template <typename T>
sian::data_structure::Leaf<T>*
sian::data_structure::RedBlackTree<T>::successor(Leaf<T>* ptr) const {
	if (ptr->right != this->nil_leaf) {
		return this->min(ptr->right);
	}
	Leaf<T>* c_ptr = ptr;
	Leaf<T>* p_ptr = ptr->parent;
	while (p_ptr != this->nil_leaf && c_ptr == p_ptr->right) {
		c_ptr = p_ptr;
		p_ptr = c_ptr->parent;
	}
	return p_ptr != this->nil_leaf ? p_ptr : nullptr;
}

template <typename T>
sian::data_structure::Leaf<T>*
sian::data_structure::RedBlackTree<T>::predecessor(Leaf<T>* ptr) const {
	if (ptr->left != this->nil_leaf) {
		return this->max(ptr->left);
	}
	Leaf<T>* c_ptr = ptr;
	Leaf<T>* p_ptr = ptr->parent;
	while (p_ptr != this->nil_leaf && c_ptr == p_ptr->left) {
		c_ptr = p_ptr;
		p_ptr = c_ptr->parent;
	}
	return p_ptr != this->nil_leaf ? p_ptr : nullptr;
}

template <typename T>
bool sian::data_structure::RedBlackTree<T>::is_empty(void) const {
	return this->root == this->nil_leaf;
}

template <typename T>
void sian::data_structure::RedBlackTree<T>::inorder_tree_delete(Leaf<T>* ptr) {
	if (ptr != this->nil_leaf) {
		this->inorder_tree_delete(ptr->left);
		Leaf<T>* right_ptr = ptr->right;
		delete ptr;
		this->inorder_tree_delete(right_ptr);
	}
}

template <typename T>
void sian::data_structure::RedBlackTree<T>::transplant(Leaf<T>* dst, Leaf<T>* src) {
    if (dst->parent == this->nil_leaf) {
		this->root = src;
	} else if (dst == dst->parent->left) {
		dst->parent->left = src;
	} else {
		dst->parent->right = src;
	}
	
	src->parent = dst->parent;
}

template <typename T>
void sian::data_structure::RedBlackTree<T>::left_rotate(Leaf<T>* ptr) {
    Leaf<T>* r_ptr = ptr->right;
	ptr->right = r_ptr->left;
	if (r_ptr->left != this->nil_leaf) {
		r_ptr->left->parent = ptr;
	}

	r_ptr->parent = ptr->parent;
	if (ptr->parent == this->nil_leaf) {
		this->root = r_ptr;
	} else if (ptr == ptr->parent->left) {
		ptr->parent->left = r_ptr;
	} else {
		ptr->parent->right = r_ptr;
	}

	r_ptr->left = ptr;
	ptr->parent = r_ptr;
}

template <typename T>
void sian::data_structure::RedBlackTree<T>::right_rotate(Leaf<T>* ptr) {
    Leaf<T>* l_ptr = ptr->left;
	ptr->left = l_ptr->right;
	if (l_ptr->right != this->nil_leaf) {
		l_ptr->right->parent = ptr;
	}

	l_ptr->parent = ptr->parent;
	if (ptr->parent == this->nil_leaf) {
		this->root = l_ptr;
	} else if (ptr == ptr->parent->left) {
		ptr->parent->left = l_ptr;
	} else {
		ptr->parent->right = l_ptr;
	}

	l_ptr->right = ptr;
	ptr->parent = l_ptr;
}

template <typename T>
void sian::data_structure::RedBlackTree<T>::insert_fixup(Leaf<T>* ptr) {
	Leaf<T>* op_ptr = nullptr;
	while (!is_black(ptr->parent)) {
		if (ptr->parent == ptr->parent->parent->left) {
			op_ptr = ptr->parent->parent->right;
			if (!is_black(op_ptr)) {
				color_black(ptr->parent);
				color_black(op_ptr);
				color_red(ptr->parent->parent);
				ptr = ptr->parent->parent;
			} else if (ptr == ptr->parent->right) {
				ptr = ptr->parent;
				this->left_rotate(ptr);
			} else {
				color_black(ptr->parent);
				color_red(ptr->parent->parent);
				this->right_rotate(ptr->parent->parent);
			}
		} else {
			op_ptr = ptr->parent->parent->left;
			if (!is_black(op_ptr)) {
				color_black(ptr->parent);
				color_black(op_ptr);
				color_red(ptr->parent->parent);
				ptr = ptr->parent->parent;
			} else if (ptr == ptr->parent->left) {
				ptr = ptr->parent;
				this->right_rotate(ptr);
			} else {
				color_black(ptr->parent);
				color_red(ptr->parent->parent);
				this->left_rotate(ptr->parent->parent);
			}
		}
	}
	color_black(this->root);
}

template <typename T>
void sian::data_structure::RedBlackTree<T>::remove_fixup(Leaf<T>* ptr) {
	while (ptr != this->root && is_black(ptr)) {
		Leaf<T>* op_ptr = nullptr;	
		if (ptr == ptr->parent->left) {
			op_ptr = ptr->parent->right;
			if (!is_black(op_ptr)) {
				color_black(op_ptr);
				color_red(ptr->parent);
				this->left_rotate(ptr->parent);
				op_ptr = ptr->parent->right;
			}

			if (is_black(op_ptr->left) && is_black(op_ptr->right)) {
				color_red(op_ptr);
				ptr = ptr->parent;
			} else if (is_black(op_ptr->right)) {
				color_black(op_ptr->left);
				color_red(op_ptr);
				this->right_rotate(op_ptr);
				op_ptr = ptr->parent->right;
			} else {
				if (is_black(ptr->parent)) {
					color_black(op_ptr);
				} else {
					color_red(op_ptr);
				}
				color_black(ptr->parent);
				color_black(op_ptr->right);
				this->left_rotate(ptr->parent);
				ptr = this->root;
			}
		} else {
			op_ptr = ptr->parent->left;
			if (!is_black(op_ptr)) {
				color_black(op_ptr);
				color_red(ptr->parent);
				this->right_rotate(ptr->parent);
				op_ptr = ptr->parent->left;
			}

			if (is_black(op_ptr->left) && is_black(op_ptr->right)) {
				color_red(op_ptr);
				ptr = ptr->parent;
			} else if (is_black(op_ptr->left)) {
				color_black(op_ptr->right);
				color_red(op_ptr);
				this->left_rotate(op_ptr);
				op_ptr = ptr->parent->left;
			} else {
				if (is_black(ptr->parent)) {
					color_black(op_ptr);
				} else {
					color_red(op_ptr);
				}
				color_black(ptr->parent);
				color_black(op_ptr->left);
				this->right_rotate(ptr->parent);
				ptr = this->root;
			}
		}
	}
	color_black(ptr);
}

template <typename T>
bool sian::data_structure::is_black(Leaf<T>* leaf) {
	if (!leaf) {
		return true;
	} else {
		return static_cast<RedBlackLeaf<T>*>(leaf)->is_black;
	}
}

template <typename T>
void sian::data_structure::color_black(Leaf<T>* leaf) {
	if (leaf)
		static_cast<RedBlackLeaf<T>*>(leaf)->is_black = true;
}

template <typename T>
void sian::data_structure::color_red(Leaf<T>* leaf) {
	if (leaf)
		static_cast<RedBlackLeaf<T>*>(leaf)->is_black = false;
}

#endif // OS dependency

#endif // Header duplicate
