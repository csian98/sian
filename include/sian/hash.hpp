/**
 * @file		hash.hpp
 * @brief		Learning Objectives Basic Data Structures
 * @author		Jeong Hoon (Sian) Choi
 * @version 	1.0.0
 * @date		2024-06-02
 */
	 
//#pragma once
//#pragma GCC diagnostic ignored "-Wstringop-truncation"

#ifndef _HEADER_HASHHPP_
#define _HEADER_HASHHPP_

#include "sian/hash.h"

#if _TARGET_OS == OS_WINDOWS

#elif _TARGET_OS == OS_LINUX

/* Inline & Template Definition */

template <typename T>
int sian::data_structure::hash_functions::HashFunction<T>::change_to_int(const T& element) const {
	int t_type_size = sizeof(T);
	int trans_t_type = 0;
	const int* ptr = reinterpret_cast<const int*>(&element);
	if (t_type_size > sizeof(int)) {
		for (int i = 0; i < t_type_size / sizeof(int); ++i) {
			trans_t_type += *(ptr + i);
		}
	} else {
		trans_t_type += *ptr;
	}
	return trans_t_type;
}

template <typename T>
sian::data_structure::hash_functions::DefaultHashFunction<T>::DefaultHashFunction(size_t hash_size) : m_hash_size(hash_size) {}

template <typename T>
size_t sian::data_structure::hash_functions::DefaultHashFunction<T>::operator()(const T& key) const {
	int trans_key = this->change_to_int(key);
	return trans_key % this->m_hash_size;
}

template <typename T>
int sian::data_structure::hash_functions::DefaultHashFunction<T>::hash_size(void) const {
	return this->m_hash_size;
}

template <typename T>
sian::data_structure::hash_functions::MultiplyHashFunction<T>::MultiplyHashFunction(size_t using_bits) : using_bits(using_bits), m_hash_size(std::pow(2, using_bits)), int_bit_size(sizeof(unsigned int) * 8) {
	this->int_maximum_digit = std::pow(10.0, this->digits_count(std::numeric_limits<int>::max()) - 2);
}

template <typename T>
size_t sian::data_structure::hash_functions::MultiplyHashFunction<T>::operator()(const T& key) const {
	unsigned int trans_key = this->change_to_int(key);
	double decimal = static_cast<double>(trans_key) * this->A;
	decimal = decimal - static_cast<int>(decimal);
	decimal *= this->int_maximum_digit;

	int shift = this->int_bit_size - this->using_bits;
	return (static_cast<unsigned int>(decimal) << shift) >> shift;
}

template <typename T>
int sian::data_structure::hash_functions::MultiplyHashFunction<T>::hash_size(void) const {
	return this->m_hash_size;
}

template <typename T>
int sian::data_structure::hash_functions::MultiplyHashFunction<T>::digits_count(int num) const {
	int digit = 0;
	while(num) {
		digit++;
		num /= 10;
	}
	return digit;
}

template <typename T>
sian::data_structure::hash_functions::UniversalHashFunction<T>::UniversalHashFunction(size_t hash_size, int prime) : prime(prime), m_hash_size(hash_size) {
	std::random_device rd;
	std::mt19937 engine(rd());
	std::uniform_int_distribution<int> dist1(0, this->prime);
	std::uniform_int_distribution<int> dist2(1, this->prime);

	this->a = dist1(engine);
	this->b = dist2(engine);
}

template <typename T>
size_t sian::data_structure::hash_functions::UniversalHashFunction<T>::operator()(const T& key) const {
	int trans_key = this->change_to_int(key);
	return ((this->a * trans_key + this->b) % this->prime) % this->m_hash_size;
}

template <typename T>
int sian::data_structure::hash_functions::UniversalHashFunction<T>::hash_size(void) const {
	return this->m_hash_size;
}

template <typename T>
sian::data_structure::hash_functions::DuplicateHashFunction<T>::DuplicateHashFunction(HashFunction<T>* hash_function1, HashFunction<T>* hash_function2)
	: hash_function1(hash_function1), hash_function2(hash_function2),
	  m_hash_size(hash_function1->hash_size() < hash_function2->hash_size() ? hash_function1->hash_size() : hash_function2->hash_size()) {
	std::random_device rd;
	std::mt19937 engine(rd());
	std::uniform_int_distribution<int> dist(1, std::numeric_limits<int>::max());

	this->c = dist(engine);
}

template <typename T>
size_t sian::data_structure::hash_functions::DuplicateHashFunction<T>::operator()(const T& key) const {
	return ((*this->hash_function1)(key) + (*this->hash_function2)(key) * this->c) % this->m_hash_size;
}

template <typename T>
int sian::data_structure::hash_functions::DuplicateHashFunction<T>::hash_size(void) const {
	return this->m_hash_size;
}

template <typename T>
sian::data_structure::HashTable<T>::HashTable(hash_functions::HashFunction<T>* hash_function) {
	this->hash_function = hash_function;
	this->buckets = new List<T>[hash_function->hash_size()];
}

template <typename T>
sian::data_structure::HashTable<T>::~HashTable(void) noexcept {
	delete[] this->buckets;
}

template <typename T>
void sian::data_structure::HashTable<T>::insert(T& value) {
	int idx = this->hash_wrapper(value);
	this->buckets[idx].push_front(value);
}

template <typename T>
void sian::data_structure::HashTable<T>::remove(T& value) {
	int idx = this->hash_wrapper(value);
	Node<T>* ptr = this->buckets[idx].find_value(value);
	this->buckets[idx].remove(ptr);
}

template <typename T>
void sian::data_structure::HashTable<T>::remove(Node<T>* ptr) {
	int idx = this->hash_wrapper(ptr->value);
	this->buckets[idx].remove(ptr);
}

template <typename T>
sian::data_structure::Node<T>* sian::data_structure::HashTable<T>::find(T& value) const {
	int idx = this->hash_wrapper(value);
	return this->buckets[idx].find_value(value);
}

template <typename T>
size_t sian::data_structure::HashTable<T>::hash_size(void) const {
	return this->hash_function->hash_size();
}

template <typename T>
int sian::data_structure::HashTable<T>::bucket_num(T& key) const {
	return this->hash_wrapper(key);
}

template <typename T>
int sian::data_structure::HashTable<T>::hash_wrapper(T& key) const {
	return (*this->hash_function)(key);
}

template <typename T>
sian::data_structure::OpenAddressing<T>::OpenAddressing(hash_functions::HashFunction<T>* hash_function) : hash_function(hash_function), m_hash_size(hash_function->hash_size()) {
	this->vector = new std::optional<T>[this->m_hash_size];
}

template <typename T>
sian::data_structure::OpenAddressing<T>::~OpenAddressing(void) noexcept {
	delete[] this->vector;
}

template <typename T>
void sian::data_structure::OpenAddressing<T>::insert(T& key) {
	int idx = 0;
	do {
		int check = this->hash_wrapper(key, idx);
		if (!this->vector[check]) {
			this->vector[check] = key;
			return;
		} else {
			idx++;
		}
	} while (idx == this->m_hash_size);
	throw data_structure_error("OpenAddressing Overloaded");
}

template <typename T>
std::optional<int> sian::data_structure::OpenAddressing<T>::search(T& key) const {
	int idx = 0, check;
	do {
	    check = this->hash_wrapper(key, idx);
		if (this->vector[check] == key) return check;
		idx++;
	} while (this->vector[check] && idx == this->m_hash_size);
	return std::nullopt;
}

template <typename T>
size_t sian::data_structure::OpenAddressing<T>::hash_size(void) const {
	return this->m_hash_size;
}

template <typename T>
int sian::data_structure::OpenAddressing<T>::bucket_num(T& key, int idx) const {
	return this->hash_wrapper(key, idx);
}

template <typename T>
void sian::data_structure::OpenAddressing<T>::set_c1_c2(void) {
	std::random_device rd;
	std::mt19937 engine(rd());
	std::uniform_int_distribution<int> dist(0, std::numeric_limits<int>::max());

	c1 = dist(engine);
	c2 = dist(engine);
}

template <typename T>
void sian::data_structure::OpenAddressing<T>::set_c1_c2(const int c1, const int c2) {
	this->c1 = c1;
	this->c2 = c2;
}

template <typename T>
T sian::data_structure::OpenAddressing<T>::operator[](const int idx) const {
	if (this->vector[idx].has_value()) return this->vector[idx].value();
	else throw data_structure_error("OpenAddressing not a valid index");
}

template <typename T>
int sian::data_structure::OpenAddressing<T>::hash_wrapper(T& key, int idx) const {
	return ((*this->hash_function)(key) + this->c1 * idx + this->c2 * idx * idx) % this->m_hash_size;
}

template <typename T>
sian::data_structure::DoubleHashTable<T>::DoubleHashTable(hash_functions::HashFunction<T>* outer_hash_function, hash_functions::HashFunction<T>* inner_hash_function)
	: hash_function(outer_hash_function), m_hash_size(this->hash_function->hash_size()) {
	this->hash_tables.reserve(this->m_hash_size);
	for (int i = 0; i < this->m_hash_size; ++i) {
		this->hash_tables.emplace_back(inner_hash_function);
	}
}

template <typename T>
void sian::data_structure::DoubleHashTable<T>::insert(T& key) {
	this->hash_tables[this->hash_wrapper(key)].insert(key);
}

template <typename T>
void sian::data_structure::DoubleHashTable<T>::remove(T& key) {
	this->hash_tables[this->hash_wrapper(key)].remove(key);
}

template <typename T>
void sian::data_structure::DoubleHashTable<T>::remove(Node<T>* node) {
	this->hash_tables[this->hash_wrapper(node->value)].remove(node);
}

template <typename T>
sian::data_structure::Node<T>* sian::data_structure::DoubleHashTable<T>::find(T& key) const {
	return this->hash_tables[this->hash_wrapper(key)].find(key);
}

template <typename T>
size_t sian::data_structure::DoubleHashTable<T>::hash_size(void) const {
	return this->m_hash_size * this->hash_function->hash_size();
}

template <typename T>
int sian::data_structure::DoubleHashTable<T>::bucket_num(T& key) const {
	int idx = this->hash_wrapper(key);
	return idx * this->m_hash_size + this->hash_tables[idx].bucket_num(key);
}

template <typename T>
int sian::data_structure::DoubleHashTable<T>::hash_wrapper(T& key) const {
	return (*this->hash_function)(key);
}

#endif // OS dependency

#endif // Header duplicate
