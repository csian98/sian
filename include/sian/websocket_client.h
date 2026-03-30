/**
 * @file		kyra-client.h
 * @author		Jeong Hoon (Sian) Choi
 */
	 
//#pragma once
//#pragma GCC diagnostic ignored "-Wstringop-truncation"
//#pragma comment(lib, "libpthread.so")

#ifndef _HEADER_KYRA_CLIENT_H_
#define _HEADER_KYRA_CLIENT_H_

/* Include */

#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>
#include <boost/beast.hpp>
#include <boost/beast/ssl.hpp>

#include <nlohmann/json.hpp>

#include <thread>

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
	
	class WebSocketClient {
	public:
		explicit WebSocketClient(void);
		
		virtual ~WebSocketClient(void) noexcept = default;

		void connect(void);

		void disconnect(void);

		void send(const std::string&);
		
	private:
		void read_work(void);
		
		asio::io_context ioc;

		ssl::context ctx;

		websocket::stream<beast::ssl_stream<tcp::socket>> ws;

		std::thread worker;
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
