/**
 * @file game.hpp
 * @version 1.0
 * @since May, 26.
 * @date May, 28.
 * @author Oziel Alves (ozielalves@ufrn.edu.br)
 * @author Max Willian (maxwilliam780@gmail.com)
 * @title The Maze
 */

#ifndef _GAME_HPP_
#define _GAME_HPP_

#include <iostream>
#include <string>
#include <vector>
#include <ctime>

/**
 * Game class:
 * With functions to help with the game procedure
 */  
class Game{

public:

	//! @brief Initializing an empty game. 
	Game(): lives(5), currentStatus(EXPAND) {}
/*---------------------------- Status -------------------------------*/
	enum Status	{
		RUN = 0, 	//!< The snake start the apple chase.
		GROW, 		//!< The snake keep walking and grows one snake_size_unity.
		NEXT_LEVEL, //!< The snake ate all the apples on that level and goes to the next level.
		CRASH, 		//!< The snake crashed on the wall or on its own tail.
		DEAD, 		//!< The snake have no more lifes remaining.

	};

	/** @brief The snake starts the apple chase. */
    void runSnake();

	/** @brief Makes the snake grow one snake_size_unity. */
    void growSnake();


    /** @brief Calls the next level. */
    void nextLevel();


    /** @brief Checks if the snake crashed somewhere. */
    bool crashSnake();


    /** @brief Simulates the snaked death. */
    void deadSnake();

    
/*--------------------------- Directions ----------------------------*/

	enum Direction{
		NORTH = 0, 
		SOUTH = 1, 
		WEST = 2,  
		EAST = 3   
	};

/*---------------------------- Position -----------------------------*/

	struct Position{

		int x;   //<! Position col
		int y;   //<! Position Lin

		/*! Initializer */
		Position( int x_=0, int y_=0 ): x(x_), y(y_) {}

		/*! Configurator: Changes the position according to the direction.*/
		void set( const direction_t& dir ){
			switch( dir ){
				case NORTH:
					y -= 1;
					break;

				case SOUTH:
					y += 1;
					break;

				case WEST:
					x -= 1;
					break;

		  		case EAST:
					x += 1;
					break;
				default:
					cout << "Invalid Direction!";
			}
		}

		// To check if the snack keeps followin the same direction
		bool operator==( const Position& rhs ) const{
			return (y == rhs.y and x == rhs.x );
		}


	};

/*------------------------------ The Maze -----------------------------*/
	/*! Structure to define what means each character on the Maze */
	struct Maze{
		char init    = 'i'; /*<! Character that defines the snake's start point. */
		char wall    = '#'; /*<! Character that defines a wall. */
		char way     = ' '; /*<! Character that defines an open way. */
		char spawn   = '*'; /*<! Character that defines the apple spawn point. */
		char marker  = '.'; /*<! Character taht defines a marker(fake wall). */
	};

	/** @brief Checks if the last character is the start point.
        @return 1 if it is, 0 otherwise. */
	bool isInitialPosition( char ch );

	/** @brief Checks if the last character is an wall.
		@return 1 if it is, 0 otherwise. */
    bool isWall( char ch );

    /** @brief Checks if the last character is an free space.
		@return 1 if it is, 0 otherwise. */
	bool isFree( char ch );

	/** @brief Checks if the last character is a mark.
		@return 1 if it is, 0 otherwise. */
	bool isInvisibleWall( char ch );

 	/** @brief Checks if the snake ate the apple.
		@return 1 if it did, 0 otherwise. */
	bool ateApple( );

/*------------------------------ Actions ------------------------------*/
	/** @brief Identify the snack start point on the maze. 
	 * 	@return Snack start point
	 */
	Position startPoint();

	/** @brief Throws an apple on the game maze.
	 * 	@return The apple spawn position. */
	Position throwApple();

	/** @brief Moves the snake on position.
	 * 	@return 1 if the snake ate the apple/crashed somewhere and 0 otherwise. */
	bool moveSnake();


};	

/*------------------------ Setters and getters ------------------------*/

