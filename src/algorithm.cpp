/**
 * @file		algorithm.cpp
 * @brief		basic algorithms (learning purpose source codes)
 * @author		Jeong Hoon (Sian) Choi
 * @version		1.0.0
 * @date		2024-05-29
 */

#include "sian/algorithm.h"

/* C & CPP */
/*
#ifdef __cplusplus
extern "C" {
#endif
*/

#if _TARGET_OS == OS_WINDOWS

#elif _TARGET_OS == OS_LINUX

/* Definition */

/* ASM codes */
/*
asm(R"ASM(
  ; assembly code x86-64 AT&T(fastcall-cdecl)
func:
  .cfi_startproc
        pushq %rbp
        .cfi_def_cfa_offset 16
        .cfi_offset 6, -16
        movq %rsp, %rbp
        .cfi_def_cfa_register 6
        movl %edi, -4(%rbp)  ; %rdi -> %rsi -> %rdx -> %rcx ->
        movl %esi, -8(%rbp)  ; %r8  -> %r9  -> stack
; return value %eax
        popq %rbp
				.cf_def_cfa 7, 8
				ret
				.cfi_endproc
)ASM");
*/

/* Data structures definition - struct & class */

/*

Sample::Sample(const Sample& src) {
	// Deep Copy
}

Sample& Sample::operator=(const Sample& src) {
	if(this == &src) {
		return *this;
	}
	
	Sample temp(src);
	swap(*this, temp);
	return *this;
}

Sample::Sample(Sample&& src) noexcept : Sample() {
	swap(*this, src);
}

Sample& Sample::operator=(Sample&& src) noexcept {
	Sample temp(std::move(src));
	swap(*this, temp);
	return *this;
}

*/

/* Functions definition */

void sian::sort::counting_sort(int* dst, const int* src,
							   int size, int min, int max) {
	int c_size = max - min + 1;
	int* c = new int[c_size];
	
	for (int i = 0; i < c_size; ++i) c[i] = 0;

	for (int i = 0; i < size; ++i) c[src[i]]++;

	for (int i = 1; i < c_size; ++i) c[i] = c[i] + c[i - 1];

	for (int i = size - 1; i >= 0; --i) {
		dst[c[src[i]] - 1] = src[i];
		c[src[i]]--;
	}

	delete[] c;
}

void sian::sort::_stable_inner_radix(int* dst,
									 int size, int digit) {
	int* src = new int[size];

	for (int i = 0; i < size; ++i) src[i] = dst[i];
	
	int c[10] = {0, };
	auto get_digit = [&digit](int num) {
		return static_cast<int>(num / std::pow(10, digit)) % 10;
	};

	for (int i = 0; i < size; ++i) c[get_digit(src[i])]++;
	
	for (int i = 1; i < 10; ++i) c[i] = c[i] + c[i - 1];
	
	for (int i = size - 1; i >= 0; --i) {
		dst[c[get_digit(src[i])] - 1] = src[i];
		c[get_digit(src[i])]--;
	}

	delete[] src;
}

void sian::sort::radix_sort(int* list, int size) {
	int max_value = std::numeric_limits<int>::min();
	for (int i = 0; i < size; ++i) {
		if (max_value < list[i]) max_value = list[i];
	}

	int digit = 1;
	while (max_value / 10 > 0) {
		digit++;
		max_value /= 10;
	}
	
	for (int i = 0; i < digit; ++i) {
		_stable_inner_radix(list, size, i);
	}
}

void sian::sort::bucket_sort(int* list, int size) {
	sian::data_structure::List<int>* buckets = new sian::data_structure::List<int>[10];
	int max_value = std::numeric_limits<int>::min();
	for (int i = 0; i < size; ++i) {
		if (max_value < list[i]) {
			max_value = list[i];
		}
	}

	int digit = 1;
	while (max_value / 10 > 0) {
		digit *= 10;
		max_value /= 10;
	}

	for (int i = 0; i < size; ++i) {
		buckets[list[i] / digit].insert_sorted(list[i]);
	}

	int idx = 0;
	for (int i = 0; i < 10; ++i) {
		sian::data_structure::Node<int>* ptr = buckets[i].front();
		
	    while(ptr) {
			list[idx] = ptr->value;
			ptr = ptr->next;
			idx++;
		}
	}

	delete[] buckets;
}

#endif // OS dependency

/*
#ifdef __cplusplus
}
#endif
*/
