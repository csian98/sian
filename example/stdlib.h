/**
 * @file		stdlib.h
 * @brief		
 * @author		Jeong Hoon (Sian) Choi
 * @version		1.0.0
 * @date		2023-11-30
 */
	 
//#pragma once
//#pragma GCC diagnostic ignored "-Wstringop-truncation"

#ifndef _HEADER_STDLIBH_
#define _HEADER_STDLIBH_

/* Include */

// C++
#include <new>
#include <memory>
#include <memory_resource>
#include <iterator>
#include <cstddef>

#include <exception>
#include <stdexcept>
#include <system_error>

#include <iostream>
#include <iomanip>
#include <ios>
#include <iosfwd>
#include <istream>
#include <ostream>
#include <sstream>
#include <streambuf>
#include <fstream>
#include <strstream>

#include <regex>
#include <string>
#include <string_view>
#include <charconv>
#include <codecvt>
#include <locale>

#include <cmath>
#include <complex>
#include <valarray>

#include <chrono>
#include <random>
#include <filesystem>
#include <ratio>

#include <utility>
#include <algorithm>
#include <numeric>
#include <limits>
#include <cstdint>
#include <type_traits>
#include <typeinfo>

#include <initializer_list>
#include <optional>
#include <variant>
#include <any>
#include <functional>

#include <tuple>
#include <vector>
#include <list>
#include <forward_list>
#include <deque>
#include <queue>
#include <stack>
#include <array>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <bitset>

#include <thread>
#include <mutex>
#include <shared_mutex>
#include <atomic>
#include <condition_variable>
#include <future>
#include <execution>

#include <coroutine>

#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/signal.h>
#include <sys/msg.h>
#include <sys/sem.h>
#include <errno.h>



using namespace std::string_literals;
using namespace std::string_view_literals;

template <typename T,
          template <typename E, typename Allocator = std::allocator<E>>
          class Container = std::vector>
class Sample {
public:
	Sample(void)=default;

	virtual ~Sample(void)=default;

	Sample(const Sample&);

	Sample(Sample&&) noexcept;

	Sample& operator=(const Sample&);

	Sample& operator=(Sample&&) noexcept;
};

#endif

