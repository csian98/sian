/**
 * @file		boost_test.cpp
 * @brief		
 * @author		Jeong Hoon (Sian) Choi
 * @version		1.0.0
 * @date		2023-12-13
 */

/* Copyright (C)
 * 2023 - Jeong Hoon (Sian) Choi
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

#include <iostream>
#include <boost/test/unit_test.hpp>
#include <boost/test/test_tools.hpp>

#if _TARGET_OS == OS_WINDOWS

#elif _TARGET_OS == OS_LINUX

using namespace boost::unit_test;

BOOST_AUTO_TEST_CASE(xxx) {
  BOOST_CHECK(1==1);

	BOOST_CHECK_EQUAL(1, 1);
}

BOOST_AUTO_TEST_SUITE(suite1)

BOOST_AUTO_TEST_CASE(xxx) {
	BOOST_CHECK(1==1);

	BOOST_CHECK_EQUAL(1, 1);
}

BOOST_AUTO_TEST_SUITE_END()

struct F{
	F(void): i(0) { BOOST_TEST_MESSAGE("setup_fixture"); }

	~F(void) { BOOST_TEST_MESSAGE("teardown fixture"); }

	int i;
};

BOOST_FIXTURE_TEST_CASE(test1, F) {
	BOOST_CHECK(i==0);
}

void test_function(void) {
	BOOST_CHECK(1==1);
}

#endif // OS dependency
