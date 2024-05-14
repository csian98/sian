/**
 * @file		client.hpp
 * @brief		CLIENT
 * @author  	Jeong Hoon (Sian) Choi
 * @version 	1.0.0
 * @date		2024-04-30
 */
	 
//#pragma once
//#pragma GCC diagnostic ignored "-Wstringop-truncation"

#ifndef _HEADER_SAMPLEHPP_
#define _HEADER_SAMPLEHPP_

#include "sian/client.h"

#if _TARGET_OS == OS_WINDOWS

#elif _TARGET_OS == OS_LINUX

/* Inline & Template Define */

template <typename T, typename U>
sian::Client<T, U>::Client(const IPv4& ipv4) : tcpssl(ipv4) {
	this->status = true;

	this->tcpssl.socket();

	this->tcpssl.connect();
}

template <typename T, typename U>
sian::Client<T, U>::~Client(void) noexcept {
	this->status = false;

	this->tcpssl.close();
}

template <typename T, typename U>
void sian::Client<T, U>::send(const std::string& msg) {
	this->tcpssl.send(msg, nullptr);
}



#endif // OS dependency

#endif // Header duplicate
