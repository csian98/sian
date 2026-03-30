/**
 * @file		kyra-server.cpp
 * @author		Jeong Hoon (Sian) Choi
 */

#include "kyra-server.h"

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
	std::set<websocket::stream<beast::ssl_stream<tcp::socket>>*> clients;

	std::mutex mtx_clients;

	WebSocketSession::WebSocketSession(beast::ssl_stream<tcp::socket> stream)
		: ws(std::move(stream)) {}

	void WebSocketSession::run(http::request<http::string_body> req) {
		this->ws.accept(req);

		{
			std::lock_guard<std::mutex> lock(mtx_clients);
			clients.insert(&this->ws);
		}

		try {
			for (;;) {
                beast::flat_buffer buffer;
                ws.read(buffer);

                std::string msg = beast::buffers_to_string(buffer.data());
                std::cout << "[recv] " << msg << std::endl;

                broadcast(msg);
            }
			
		} catch (...) {
			
		}

		{
			std::lock_guard<std::mutex> lock(mtx_clients);
			clients.erase(&this->ws);
		}
	}

	void WebSocketSession::broadcast(const std::string& message) {
		std::lock_guard<std::mutex> lock(mtx_clients);
		for (auto* client: clients) {
			client->text(true);
			client->write(asio::buffer(message));
		}
	}
	
	WebSocketServer::WebSocketServer(void)
		: ctx(ssl::context::tlsv12_server),
		  acceptor(ioc, tcp::endpoint(tcp::v4(), 6334)) {
		this->ctx.use_certificate_chain_file("etc/server/cert.pem");
		this->ctx.use_private_key_file("etc/server/key.pem", ssl::context::pem);
	}

	void WebSocketServer::start(void) {
		for (;;) {
            tcp::socket socket{ioc};
            acceptor.accept(socket);

            std::thread(&WebSocketServer::handle_client, this,
						std::move(socket)).detach();
        }
	}

	void WebSocketServer::handle_client(tcp::socket socket) {
		try {
            beast::ssl_stream<tcp::socket> stream(std::move(socket), ctx);
            stream.handshake(ssl::stream_base::server);

            beast::flat_buffer buffer;
            http::request<http::string_body> req;
            http::read(stream, buffer, req);

            auto it = req.find(http::field::authorization);
            if (it == req.end() || it->value() != "Bearer Ugu5wZadmJYQ1pxE0bzmFCawrzHFyYMR") {
                http::response<http::string_body> res{
                    http::status::unauthorized, req.version()
                };
                res.set(http::field::content_type, "text/plain");
                res.body() = "Unauthorized";
                res.prepare_payload();
                http::write(stream, res);
                return;
            }

            WebSocketSession session(std::move(stream));
            session.run(std::move(req));

        } catch (std::exception& e) {
            std::cout << "client error: " << e.what() << "\n";
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
