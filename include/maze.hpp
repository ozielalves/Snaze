/**
 * @file maze.hpp
 * @version 1.0
 * @since May, 26.
 * @date May, 28.
 * @author Oziel Alves (ozielalves@ufrn.edu.br)
 * @author Max Willian ()
 * @title The Maze
 */

#ifndef _PARSER_H_
#define _PARSER_H_

#include <iostream>
#include <vector>
#include <utility>
#include <cstdlib>
#include <time.h>

class Maze{

	using size size_t;
	using maze_type = char;

private:
	Maze(){}

	Maze(size lin, size col, maze_type **maze);

	~Maze(){}

	size getLin();

	void setLin(size lin);

	size getCol(size col);

	void setMaze();

	maze_type ** getMaze();

	maze_type getMazeValue(size lin, size cos);

	void printMaze();
};

#include "maze.inl"

#endif