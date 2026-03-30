/**
 * @file		kyra-client.cpp
 * @author		Jeong Hoon (Sian) Choi
 */

#include "kyra-client.h"

/* C & CPP */
/*
#ifdef __cplusplus
extern "C" {
#endif
*/

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

#include <iostream>

namespace kyra {
	WebSocketClient::WebSocketClient(void)
		: ctx(ssl::context::tlsv12_client), ws(ioc, ctx) {
		this->ctx.set_verify_mode(ssl::verify_none);

		this->ws.set_option(
			websocket::stream_base::decorator(
				[this](websocket::request_type& req) {
					req.set(beast::http::field::authorization,
							"Bearer Ugu5wZadmJYQ1pxE0bzmFCawrzHFyYMR");
				}));
	}

	void WebSocketClient::connect(void) {
		tcp::resolver resolver{this->ioc};
		auto results = resolver.resolve("127.0.0.1", "6334");
		asio::connect(this->ws.next_layer().next_layer(), results);

		this->ws.next_layer().handshake(ssl::stream_base::client);
		this->ws.handshake("127.0.0.1", "/");

		std::cout << "Connected (wss):\n";

		this->worker = std::thread([this]() { this->read_work(); });
	}

	void WebSocketClient::disconnect(void) {
		this->ws.close(websocket::close_code::normal);
		if (this->worker.joinable())
			this->worker.join();
	}

	void WebSocketClient::send(const std::string& message) {
		this->ws.write(asio::buffer(message));
	}

	void WebSocketClient::read_work(void) {
		try {
            for (;;) {
                beast::flat_buffer buffer;
                this->ws.read(buffer);
                std::cout << "\n[chat] "
                          << beast::buffers_to_string(buffer.data())
                          << "\n> ";
            }
        } catch (const std::exception& e) {
            std::cerr << "[Reader] " << e.what() << "\n";
        }
	}
}


/* Functions definition */

/*

void swap(Sample& lhs, Sample& rhs) noexcept {
	// shallow copy
    // using std::swap;
}

*/

/*
#ifdef __cplusplus
}
#endif
*/
