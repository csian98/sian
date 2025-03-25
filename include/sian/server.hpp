/**
 * @file		server.hpp
 * @brief		SERVER
 * @author		Jeong Hoon (Sian) Choi
 * @version		1.0.0
 * @date		2024-04-30
 */
	 
//#pragma once
//#pragma GCC diagnostic ignored "-Wstringop-truncation"

#ifndef _HEADER_SERVERHPP_
#define _HEADER_SERVERHPP_

#include "sian/server.h"

#if _TARGET_OS == OS_WINDOWS

#elif _TARGET_OS == OS_LINUX

/* Inline & Template Define */

template <typename T, typename U>
sian::Server<T, U>::Server(const IPv4& ipv4,
						   std::ostream& ostrm, std::istream& istrm)
	: tcpssl(ipv4), ostrm(ostrm), istrm(istrm) {
	this->status = true;

	this->tcpssl.socket();

	this->tcpssl.bind();

	this->tcpssl.listen(MAX_CLIENTS);
}

template <typename T, typename U>
sian::Server<T, U>::~Server(void) noexcept {
	this->status = false;

	for(U* clnt: this->clients) {
		this->tcpssl.close(*clnt);
		delete clnt;
	}
}

template <typename T, typename U>
void sian::Server<T, U>::run(void) {
	std::thread thrd_accpt = std::thread(sian::Server<T, U>::thread_accept, this);
	std::thread thrd_rd = std::thread(sian::Server<T, U>::thread_read, this);

	thrd_accpt.join();
	thrd_rd.join();
}

template <typename T, typename U>
void sian::Server<T, U>::thread_accept(Server* server) {
	U* client;
	while (server->status) {
		client = new U;
		server->tcpssl.accept(*client);

		server->mtx.lock();
		server->clients.push_back(client);
		server->mtx.unlock();
	}
}

template <typename T, typename U>
void sian::Server<T, U>::thread_read(Server* server) {
	int rcv = 0;
	
	while (server->status) {
		int nclient = server->clients.size();

		for (int index = 0; index < nclient;) {
			std::string msg;
			rcv = server->tcpssl.recv(msg, server->clients[index]);

			if (rcv == 1) {
				server->ostrm << msg;
				server->ostrm.flush();
			}

			if (rcv == 0) {
				server->tcpssl.close(*(server->clients[index]));
				delete server->clients[index];
				
				server->mtx.lock();
				server->clients.erase(server->clients.begin() + index);
				server->mtx.unlock();
			} else {
				++index;
			}
		}
	}
}

#endif // OS dependency

#endif // Header duplicate
