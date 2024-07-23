/**
 * @file		mariadb.cpp
 * @brief		mariadb connector wrapper
 * @author		Jeong Hoon (Sian) Choi
 * @version		1.0.0
 * @date		2024-06-08
 */

#include "sian/mariadb.h"

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

sian::MariaDB::MariaDB(const std::string user,
					   const std::string password,
					   const std::string database,
					   int port) {
	try {
		sql::Driver* driver = sql::mariadb::get_driver_instance();
		sql::SQLString url("jdbc::mariadb://localhost:" +
						   std::to_string(port) + "/" + database);
		sql::Properties properties({
				{"user", user},
				{"password", password},
			});
		
		std::unique_ptr<sql::Connection> conn(driver->connect(url, properties));
		this->conn = std::move(conn);
		this->statement = std::make_shared<sql::Statement>(this->conn->createStatement());
		
	} catch (sql::SQLException& e) {
		throw e;
	}
}

sian::MariaDB::~MariaDB(void) noexcept {
	this->conn->close();
}

void sian::MariaDB::sql(std::string_view query) {
	try {
		this->statement->executeUpdate(query.data());
	} catch (sql::SQLException& e) {
		throw e;
	}
}

/* Functions definition */

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
