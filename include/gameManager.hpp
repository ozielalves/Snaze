/**
 * @file gameManager.hpp
 * @version 1.0
 * @since May, 26.
 * @date Jun, 01.
 * @author Oziel Alves (ozielalves@ufrn.edu.br)
 * @author Max Willian (maxwilliam780@gmail.com)
 * @title Game Manager
 */

#ifndef _GAMEMANAGER_HPP_
#define _GAMEMANAGER_HPP_

#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <unistd.h> // usleep() -> sleep for microseconds
#include <stdlib.h> //system()

#include "game.hpp"

/*! Manager Class */
class Manager{ 

public:

	enum Error{
			
		BOARD_OK = 0,      		// File is succefuly read.
		MISSING_START_POSITION,	// The start point is missing (*)
		EXTRANEOUS_SYMBOL,	 	// If there is any symbol in the maze != ('#', ' ', '*', '.')
		ARCHIVE_NOT_FINDED     	// File not finded
	};


   	/** @brief Verifies if there is any error in the board.
       @return The finded error, if exists. */
	Error parsing( );

	/** @brief Reads the client file.
	    @return File was succefuly read or the finded error. */
	Error initialize( char * file );

	//! @brief Calls the next Game phase.
	void process( );

	//! @brief Shows the start conditions of the game.
	void welcome( );

	/** @brief Determines if the game should keep going or not.
	    @return True if the game if over, 0 otherwise. */
	bool gameover( );

	//! @brief Show the phase's result.
	void render( );

	//! @brief Shows the final results.
	void render_final( );

	//! @brief Updates the game status.
	void update( );

};

//#include "gameManager.inl"

#endif