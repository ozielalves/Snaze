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

#include "level.hpp"
#include "playerSnake.hpp"

/**
 * Game class:
 * With functions to help with the game procedure
 */  

class Game{

public:

	int currentStatus; //!< Current status of the game

	//! @brief Initializing an empty game. 
	Game(): lifes(5), currentStatus(GROW) {}

/*-------------------------------- Status -----------------------------------*/
	enum Status	{
		RUN = 0, 	//!< The snake start the apple chase.
		GROW, 		//!< The snake keep walking and grows one snake_size_unity.
		NEXT_LEVEL, //!< The snake ate all the apples on that level and goes to the next level.
		CRASH, 		//!< The snake crashed on the wall or on its own tail.
		DEAD, 		//!< The snake have no more lifes remaining.

	};

	/** @brief The snake starts the apple chase. */
    void runSnake( );

	/** @brief Makes the snake grow one snake_size_unity. */
    void growSnake( );


    /** @brief Calls the next level. */
    void nextLevel( );


    /** @brief Checks if the snake crashed somewhere. */
    bool crashSnake( );


    /** @brief Simulates the snaked death. */
    void deadSnake( );

    
/*------------------------------ Directions ---------------------------------*/

	enum Direction{
		NORTH = 0, 
		SOUTH = 1, 
		WEST = 2,  
		EAST = 3   
	};

/*------------------------------- Position ----------------------------------*/

public:	
	struct Position{

		int x;   //<! Position col
		int y;   //<! Position Lin

		/*! Initializer */
		Position( int x_=0, int y_=0 ): x(x_), y(y_) {}

		/*! Configurator: Changes the position according to the direction.*/
		void set( const short int& dir ){
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
					std::cout << "Invalid Direction!";
			}
		}

		// To check if the snack keeps followin the same direction
		bool operator==( const Position& rhs ) const{
			return (y == rhs.y and x == rhs.x );
		}


	};

/*------------------------------- The Maze ----------------------------------*/
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

/*------------------------------- Actions -----------------------------------*/

	/** @brief Identify the snack start point on the maze. 
	 * 	@return Snack start point
	 */
	Position startPoint();

	/** @brief Throws an apple on the game maze.
	 *	@return The apple spawn position. */
	Position throwApple();

	/** @brief Moves the snake on position.
	 * 	@return 1 if the snake ate the apple/crashed somewhere and 0 otherwise. */
	bool moveSnake();
	

/*-------------------------- Setters and getters ----------------------------*/

	/** @brief Determines how many phases the game have.
     *	@param lvs The Phases.
     *	@return True if the number of phases > zero, False otherwise. 
     */
	bool setLevels( int lvs );


	/** @brief Recover the game number of phases.
	 *	@return The Phases. */
    int getLevels( ) const;


	/** @brief Define a vetor with the game boards.
 	 *	@param bdrs The boards.
	 *	@return True if the number of boards > zero; False otherwise. 
	 */
	bool setBoards( std::vector<std::vector<std::string>> bdrs );

	/** @brief Recoer the game boards.
	 * 	@return The boards. */
	std::vector<std::vector<std::string>> getBoards( ) const;

	/** @brief Takes one life from the player.
	 *	@return True if the player has lifes to be taken; False otherwise. */
	bool setLifes( );


	/** @brief Recover the player's number of lifes.
	 * 	@return The lifes */
	int getLifes( ) const;


	/** @brief Update the player's status
	 *	@param stts Status */
	void setStatus( int stts );


	/** @brief Recover the players's status.
	 *	@return True se jogador ganhou; False se perdeu */
	bool getStatus( ) const;


	/** @brief Update the game board sizes.
	 *	@param szBoards Vecctor with the sizes. */
	void setSizeBoards( std::vector<Position> szBoards );


	/** @brief Recover the vector with the sizes. */
	std::vector<Position> getSizeBoards( ) const;		

	/*/-/-/-/-/-/ Level Setters and Getters /-/-/-/-/-/-*/

	/** @brief Determines the current game phase.
	 * 	@param lvl The phase.
 	 * 	@return True se tiver um numero de fases maior que zero; False otherwise. */
	bool setCurrentLevel( int lvl );

	/** @brief Recover the current game phase.
     *	@return The phase. */
	int getCurrentLevel( ) const;

	/** @brief Determines the current game board.
	 * 	@param brd The board
	 * 	@return True if there is an board, False otherwise. */
	bool setCurrentBoard( std::vector<std::string> brd );

	/** @brief Recover the current game board.
	 * 	@return The board. */
	std::vector<std::string> getCurrentBoard( ) const;

	/** @brief Recover the eaten apples in the maze.
	 * 	@return The total number of eaten apples. */
	int getEatenApples( );

	/** @brief Set the snake's head position in the maze with the right character to represent it. */
	void putSnake();

	/** @brief Set the snake's body position in the maze with the blank space character to represent it.*/
    void clearSnake();

private:
	
	int levels; 					                 //<! Total os game phases.
	std::vector<std::vector<std::string>> boards;    //<! Mazes to be processed
	int lifes;   			                         //<! Snake lifes
	int status;					                     //<! 0 if the player loses, 1 otherwise.
	std::vector<Position> sizesBoards; 	             //!< Maze sizes.

	Position apple; 								//!< Apple position in the game.

};

#include "game.inl"

#endif 
