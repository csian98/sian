
/**
 * @file		logger.cpp
 * @brief       multi thread logger
 * @author  	Jeong Hoon (Sian) Choi
 * @version 	1.0.0
 * @date		2024-05-13
 */

#include "sian/logger.h"

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

sian::Logger::Logger(std::string_view path)
	: m_path(path.data()) {
	m_thread = std::thread{&Logger::thread_process, this};
}

sian::Logger::~Logger(void) {
	{
		std::unique_lock lock(this->m_mutex);
		this->m_exit = true;
		this->m_cond_var.notify_all();
		lock.unlock();
	}

	this->m_thread.join();
}

void sian::Logger::log(std::string_view entry) {
	std::unique_lock lock(this->m_mutex);

	this->m_queue.push(entry.data());
	m_cond_var.notify_all();

	lock.unlock();
}

void sian::Logger::thread_process(void) {
	std::ofstream fp(this->m_path);

	if (fp.fail()) {
		std::cerr << "Failed to open file" << std::endl;
		return;
	}

	std::unique_lock lock(this->m_mutex);
	while (true) {
		if (!this->m_exit) {
			this->m_cond_var.wait(lock);
		}

		lock.unlock();
		while (true) {
			lock.lock();
			if (this->m_queue.empty()) {
				break;
			} else {
				fp << this->m_queue.front() << std::endl;
				this->m_queue.pop();
			}
			lock.unlock();
		}

		if (this->m_exit) {
			break;
		}
	}
}

/* Functions declare */

/*

void swap(Sample& lhs, Sample& rhs) noexcept {
	// shallow copy
    // using std::swap;
}

*/

#endif // OS dependency

/*
#ifdef __cplusplus
}
#endif
*/
