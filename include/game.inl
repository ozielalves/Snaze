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

/** @brief Checks if the last character is the start point.
    @return 1 if it is, 0 otherwise. */
bool Game::isInitialPosition( char ch ){
    return ( ch == '*' );
}

/** @brief Checks if the last character is an wall.
    @return 1 if it is, 0 otherwise. */
bool Game::isWall( char ch ){
    return ( ch == '#' );
}

/** @brief Checks if the last character is an free space.
    @return 1 if it is, 0 otherwise. */
bool Game::isFree( char ch ){
    return ( ch == ' ' );
}

/** @brief Checks if the last character is a mark.
    @return 1 if it is, 0 otherwise. */
bool Game::isInvisibleWall( char ch ){
    return ( ch == '.' );
}

/** @brief Checks if the snake ate the apple.
    @return 1 if it did, 0 otherwise. */
bool Game::ateApple( ){ TODO }

/*------------------------------ Actions ------------------------------*/

/** @brief Identify the snack start point on the maze. 
*   @return Snack start point. */
Position Game::startPosition(){

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

/** @brief Throws an apple on the game maze.
*   @return The apple spawn position. */
Position Game::throwApple(){ TODO }

/** @brief Moves the snake on position.
*   @return 1 if the snake ate the apple/crashed somewhere and 0 otherwise. */
bool Game::moveSnake(){ TODO }

/*------------------------ Setters and getters ------------------------*/

/** @brief Determines how many phases the game have.
*  @param lvs The Phases.
*  @return True if the number of phases > zero, False otherwise. 
*/
bool Game::setLevels( int lvs ){
    if( lvs > 0 ){
        levels = lvs;
        return true;
    } else {
        return false;
    }
}

/** @brief Recover the game number of phases.
 *  @return The Phases. */
int Game::getLevels( ) const{
    return levels;
}

/** @brief Define a vetor with the game boards.
 *  @param bdrs The boards.
 *  @return True if the number of boards > zero; False otherwise. 
 */
bool Game::setBoards( std::vector<std::vector<std::string>> bdrs ){
    int qtd = bdrs.size();
    if( qtd > 0 ){
        boards = bdrs;
        return true;
    } else {
        return false;
    }
}

/** @brief Recover the game boards.
 *  @return The boards. */
std::vector<std::vector<std::string>> Game::getBoards( ) const{
    return boards;
}

/** @brief Takes one life from the player.
 *  @return True if the player has lifes to be taken; False otherwise. */
bool Game::setLifes( ){
    if( lifes > 0 ){
        lifes--;
        return true;
    } else {
        return false;
    }
}

/** @brief Recover the player's number of lifes.
 *  @return The lifes */
int Game::getLifes( ) const{
    return lifes;
}

/** @brief Update the player's status
 *  @param stts Status */
void Game::setStatus( int stts ){
    status = stts;
}

/** @brief Recover the players's status.
 *  @return True se jogador ganhou; False se perdeu */
bool Game::getStatus( ) const{
    if( status == 1 ){
        return true;
    }else if( status == 0 ){
        return false;
    }
}

/** @brief Update the game board sizes.
 *  @param szBoards Vecctor with the sizes. */
void Game::setSizeBoards( std::vector<Position> szBoards ){
    sizesBoards = szBoards;
}

/** @brief Recover the vector with the sizes. */
std::vector<Position> Game::getSizeBoards( void ) const{
    return sizesBoards;
}


