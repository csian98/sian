
/**
 * @file		bfs.cpp
 * @brief		BFS
 * @author		Jeong Hoon (Sian) Choi
 * @version 	1.0.0
 * @date		2024-07-23
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

#include <iostream>
#include <limits>

#include "sian/timer.h"
#include "sian/graph.h"
#include "sian/graph_algorithm.h"

#include "sian/b_tree.h"

#define OS_WINDOWS	0
#define OS_LINUX	1

#ifdef _WIN32
#define _TARGET_OS	OS_WINDOWS
#else
	#define _TARGET_OS	OS_LINUX
#endif

#if _TARGET_OS == OS_WINDOWS

#elif _TARGET_OS == OS_LINUX

// void custom_terminate_fnct(void) {
//	exit(1);
// }

using namespace sian::graph;

int main(int argc, char* argv[]) {
// 	std::terminate_handler default_terminate =
//	std::set_terminate(&custom_terminate_fnct);
	size_t vertex_size = 8;
	
	BFS bfs(vertex_size);
	bfs.connect(0, 1);
	bfs.connect(0, 4);
	bfs.connect(1, 5);
	bfs.connect(2, 3);
	bfs.connect(2, 5);
	bfs.connect(2, 6);
	bfs.connect(3, 6);
	bfs.connect(3, 7);
	bfs.connect(5, 6);
	bfs.connect(6, 7);
	
	bfs.run(1);

	for (int i = 0; i < vertex_size; ++i) {
		int distance = bfs.get_distance(i);
		std::cout << "distance [" << i << "] : " << distance << std::endl;
	}
    
	return 0;
}

#endif // OS dependency
