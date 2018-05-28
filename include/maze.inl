/**
 * @file maze.inl
 * @version 1.0
 * @date May, 26.
 * @author Max Willian and Oziel Alves
 * @title The Maze source code 
 */

#include "maze.hpp"

Maze(size lin, size col, maze_type **maze){
	m_lin = lin;
	m_col = col;
	m_maze = maze;
}

size getLIn(){ 
	return m_lin; 
}

void setLin(size lin){ 
	m_lin = lin; 
}

size getCol(){ 
	return m_col; 
}

void setCOl(size col){ 
	m_col = col; 
}

void setMaze(){} // TODO

maze_type ** getMaze(){ 
	return m_maze; 
}

maze_type getMazeValue(size lin, size cos){ 
	return m_maze[lin][cos]; 
}

void printMaze(){
	for(auto i(0u); i < m_lin; i++){
		for(auto j(0u); j < m_col; j++){
			std::cout << m_maze[i][j];
		}
		std:: cout << "\n";
	}
}