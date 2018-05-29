/**
 * @file level.hpp
 * @version 1.0
 * @since May, 27.
 * @date May, 29. 
 * @author Oziel Alves (ozielalves@ufrn.edu.br)
 * @author Max Willian (maxwilliam780@gmail.com)
 * @brief File containing the game phase data.
 */

#ifndef _LEVEL_HPP_
#define _LEVEL_HPP_

#include "game.hpp"

/** Level class with whole the informations about the game phases.*/
class Level {

	public:

	   //! @brief Creating an empty game.
	   Level() : currentLevel(0), totalApples(10), eatenApples(0) {}


    	std::vector<std::string> currentBoard;   //!< Current maze being proccessed.
    	int currentLevel;			  			 //!< Current level of the game.
        int totalApples;                         //!< Total of apples in the maze.
        int eatenApples;			   			 //!< Total of eaten apples.

		Position start;							//!< Start position on the maze.

};

#endif