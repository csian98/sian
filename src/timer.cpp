/**
 * @file		timer.cpp
 * @brief		chrono timer
 * @author		Jeong Hoon (Sian) Choi
 * @version		1.0.0
 * @date		2024-05-16
 */

#include "sian/timer.h"

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

sian::Time::Time(void) {
	this->time.zero();
}

void sian::Time::set_name(std::string_view name) {
	this->name = name.data();
}

void sian::Time::reset(void) {
	this->is_start = false;
	this->time.zero();
	this->name.clear();
}

void sian::Time::start(void) {
	this->is_start = true;
	this->begin = std::chrono::high_resolution_clock::now();
}

void sian::Time::stop(void) {
	this->is_start = false;
	this->end = std::chrono::high_resolution_clock::now();
}

sian::Timer::Timer(int size) : size(size), times(size)  {}

sian::Time& sian::Timer::operator[](int index) {
	if (index >= this->size) {
		throw std::invalid_argument("Timer index is invalid argument");
	}
	return this->times[index];
}

void sian::Timer::initialize(void) {
	for (auto& time : this->times) {
		time.reset();
	}
}

/* Functions definition */

std::ostream& sian::operator<<(std::ostream& out, const sian::Time& time) {
	if (!time.name.empty()) {
		out << time.name << " : ";
	} else {
		out << "Anonymous: ";
	}

	out << std::setprecision(6) << time.total_time<std::milli>()
		<< " milli seoncds" << std::endl;
	return out;
}

std::ostream& sian::operator<<(std::ostream& out, const sian::Timer& timer) {
	out << std::setiosflags(std::ios::left);
	out << std::setw(15) << "#" << "Timer Report";
	out << std::setiosflags(std::ios::right);	
	out	<< std::setw(16) << "#\n";
	out << "#  The number of timer = " << timer.size << '\n';
	out << "####" << std::endl;
	
	for (const auto& time : timer.times) {
		out << time;
	}
	return out;
}

#endif // OS dependency

/*
#ifdef __cplusplus
}
#endif
*/
