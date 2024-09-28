/**
 * @file		unit_test.cpp
 * @brief		
 * @author		Jeong Hoon (Sian) Choi
 * @version 	1.0.0
 * @date		2024-09-23
 */

/* Copyright (C)
 * 2024 - Jeong Hoon (Sian) Choi
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 */

#define BOOST_TEST_MODULE "Boost Unit Test"
#include <boost/test/unit_test.hpp>
#include <boost/test/included/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(TEST_SUITE1)

BOOST_AUTO_TEST_CASE(TEST_CASE1) { BOOST_TEST(true); }

BOOST_AUTO_TEST_CASE(TEST_CASE2) { BOOST_TEST(false); }

BOOST_AUTO_TEST_CASE(TEST_CASE3, *boost::unit_test::timeout(2)) {
#ifdef BOOST_SIGACTION_BASED_SIGNAL_HANDLING
	do {} while (true);
	BOOST_TEST(true);
#else
	BOOST_TEST(false);
#endif
}

BOOST_AUTO_TEST_SUITE_END()
