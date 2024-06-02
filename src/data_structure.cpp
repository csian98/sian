/**
 * @file		data_structure.cpp
 * @brief		basic data structures (learning purpose source codes)
 * @author		Jeong Hoon (Sian) Choi
 * @version		1.0.0
 * @date		2024-05-29
 */

#include "sian/data_structure.h"

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



/* Functions definition */

int sian::data_structure::hash_functions::multiply_hash_function(int key) {
	static const float A = (std::sqrt(5) -1) / 2;
	static const int using_last_bits_num = 8;
	static const int int_bit_size = sizeof(unsigned int) * 8;
	auto digit_count = [](int number) {
		int digit = 0;
		while (number) {
			digit++;
			number /= 10;
		}
		return digit;
	};
	
	static const int maximum_digit =
		std::pow(10.0, digit_count(std::numeric_limits<int>::max()) - 1);
	
	float decimal = static_cast<float>(key) * A;
    decimal = decimal - static_cast<int>(decimal);
	decimal *= maximum_digit;

	int shift_num = int_bit_size - using_last_bits_num;
	int last_bits = (static_cast<unsigned int>(decimal) << shift_num) >> shift_num;

	return last_bits;
}

#endif // OS dependency

/*
#ifdef __cplusplus
}
#endif
*/
