#include "game.hpp"

Level lv;

/*---------------------------- Status -------------------------------*/

/** @brief The snake start_s the apple chase. */
void Game::runSnake(){ TODO }

/** @brief Makes the snake grow one snake_size_unity. */
void Game::growSnake(){ TODO }

/** @brief Calls the next level. */
void Game::nextLevel(){ TODO }

/** @brief Checks if the snake crashed somewhere. */
bool Game::crashSnake(){

    std::cout << "You're crash! :c \n";
    currentStatus = DEAD;
}

/** @brief Simulates the snaked death. */
void Game::deadSnake(){

    lives -= 1;

    std::cout << ">>> Press <ENTER> when you are ready to continue.";
    std::string tcl;
    std::getline( std::cin, tcl );

    currentState = RUN;

}

/*------------------------------ The Maze -----------------------------*/

bool Game::isInitialPosition( char ch ){
    return ( ch == '*' );
}

bool Game::isWall( char ch ){
    return ( ch == '#' );
}

bool Game::isFree( char ch ){
    return ( ch == ' ' );
}

bool Game::isInvisibleWall( char ch ){
    return ( ch == '.' );
}

bool Game::ateApple( ){ TODO }

/*------------------------------ Actions ------------------------------*/

Position Game::initialPosition(){

    // Goes through the maze trying to find the start_ point.
    for( int i = 0 ; i < lv.currentBoard.size() ; i++ ){        // Goes through each pos of the vector
        for( int j=0 ; j < lv.currentBoard[i].length() ; j++ ){ // Goes through the whole string
            if( lv.currentBoard[i][j] == '*' ){
                Position start_;
                start_.x = j; // col
                start_.y = i; // lin 
                lv.start = start_;
                return start_;
            }
        }
    }
}

Position Game::throwApple(){ TODO }

bool Game::moveSnake(){ TODO }