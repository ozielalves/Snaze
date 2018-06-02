/**
 * @file playerSnake.hpp
 * @version 1.0
 * @since May, 26.
 * @date May, 28.
 * @author Oziel Alves (ozielalves@ufrn.edu.br)
 * @author Max Willian (maxwilliam780@gmail.com)
 * @title The Player's snake
 */

#ifndef _PLAYERSNAKE_HPP_
#define _PLAYERSNAKE_HPP_
 
#include <deque> // More efficient insertion and deletion (container)
#include <cassert>
#include <stack>
#include "game.hpp"

/**
 *  Snake Class
 *  Functions and variables responsable for the player info (snake).
 */

class Snake {

	public:
	    int snakeSize;                               //!< Snake size.
        int currentDirection;                        //!< Current drection.
        std::deque<Game::Position> Directions;    	 //!< List of directions the should follow.
        std::deque<Game::Position> snakeBody;        //!< Snake body positions. 

	public:
        //! @brief Initializing an empty snake.
	    Snake() : snakeSize(0) {}

        /** @brief Trys to find a way to the apple.
            @return 1 if it's possible, 0 otherwise. */
        bool solveMaze( std::vector<std::string> currentBoard,
        				Game::Position initialPosition,
        				Game::Position sizeBoard,
        				Game::Position apple );

        /** @brief Returns the adjacent position accoring to the direction.
            @param pos Current position.
            @param dir Current position next place.
            @return Posição adjacente. */
		Game::Position adjacentPosition( Game::Position pos, short int dir );

        /** @brief verify if the last position is part of the snake body.
            @return true if it is a position occuped by the snake, false otherwise. */
        bool is_snakeBody(const Game::Position & pos) const;


        /** @brief Determines if the 'pos' is a valid position in the maze
            @return true if the 'pos' is valid, false otherwise. */
        bool is_validPosition( Game::Position pos, Game::Position size );
};

#include "playerSnake.inl"

#endif
