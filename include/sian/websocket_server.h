/**
 * @file		kyra-server.h
 * @author		Jeong Hoon (Sian) Choi
 */
	 
//#pragma once
//#pragma GCC diagnostic ignored "-Wstringop-truncation"
//#pragma comment(lib, "libpthread.so")

#ifndef _HEADER_KYRA_SERVER_H_
#define _HEADER_KYRA_SERVER_H_

/* Include */

#include <thread>
#include <string>
#include <set>

#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>
#include <boost/beast.hpp>
#include <boost/beast/ssl.hpp>

#include <nlohmann/json.hpp>

#include "kyra-exception.h"

/* C & CPP */
/*
#ifdef __cplusplus
extern "C" {
#endif
*/

/* defines typedef & constant */

/* MACRO functions */

/* Inline define */

/* Attributes */
/*
[[noreturn]]
[[deprecated]]
[[fallthrough]]
[[nodiscard]]
[[maybe_unused]]
*/

/* Declaration */

/* ASM codes */
// extern "C" int func(int x, int y);

/* Data structures declaration - struct & class */

namespace kyra {
	namespace asio = boost::asio;
	namespace ssl = asio::ssl;
	namespace beast = boost::beast;
	namespace http = beast::http;
	namespace websocket = beast::websocket;

	using tcp = asio::ip::tcp;

	extern std::set<websocket::stream<beast::ssl_stream<tcp::socket>>*> clients;

	extern std::mutex mtx_clients;
	
	class WebSocketSession {
	public:
		explicit WebSocketSession(beast::ssl_stream<tcp::socket>);

		void run(http::request<http::string_body>);
		
	private:
		void broadcast(const std::string&);

		websocket::stream<beast::ssl_stream<tcp::socket>> ws;
	};

	
	class WebSocketServer {
	public:
		explicit WebSocketServer(void);
		
		virtual ~WebSocketServer(void) noexcept = default;

		void start(void);
		
	private:
		void handle_client(tcp::socket);

		asio::io_context ioc;
		
		ssl::context ctx;
		
		tcp::acceptor acceptor;
	};
}

/* Functions declaration */

// void swap(Sample&, Sample&) noexcept;

/*
#ifdef __cplusplus
}
#endif
*/

/* Inline & Template Define Header */
//#include "sample.hpp"

#endif // Header duplicate
