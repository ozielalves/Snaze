#include "game.hpp"
#include "playerSnake.hpp"

Level lv;
Snake sk;

/*---------------------------- Status -------------------------------*/

/** @brief The snake start_s the apple chase. */
void Game::runSnake( ){

    bool stop = moveSnake( );

    if( stop == false ){
        currentStatus = RUN;
    }

}

void Game::random_move()
{

	std::mt19937 random (std::chrono::system_clock::now().time_since_epoch().count());


    Position dir = adjacentPosition(sk.snakeBody.front(), random ()  % 4);
    
	if(lv.currentBoard[dir.y][dir.x] == '0') // if it tries to touch itself
	{
		currentStatus = DEAD;
    
		putSnake( ); // Puts the snake back in the board.
		return;

	}
    clearSnake( ); // Deletes the past snake in the board.
	if(isWall(lv.currentBoard[dir.y][dir.x])){
		currentStatus = DEAD;
    
		putSnake( ); // Puts the snake back in the board.
		return;
	}
    sk.snakeBody.push_front( dir );
    sk.snakeBody.pop_back();

    
    putSnake( ); // Puts the snake back in the board.

    if( ateApple() ){ // If the snake ate the apple
        currentStatus = GROW;
        lv.eatenApples += 1;
    }

}

/** @brief Makes the snake grow one snake_size_unity. */
void Game::growSnake( ){

    Position pos = startPoint();
	
    throwApple();

    if( sk.snakeSize == 0 ){ // If the snake size is 1 it is transformed to snake
        lv.currentBoard[pos.y][pos.x] = 'D';
        sk.snakeBody.push_front( pos );

        sk.snakeSize += 1; // Snake growing
    }

    if( sk.snakeSize >= 1 ){ // If the snake size is bigger or iqual to 1 it grows
        sk.Directions.clear();
        sk.currentDirection = 0;
        lv.start = sk.snakeBody.front();

        sk.snakeBody.push_front( sk.snakeBody.front() ); // New pos to the new bod part (Valid)

        sk.snakeSize += 1; // Snake grows
    }
    
	bool solve = sk.solveMaze( lv.currentBoard, lv.start, sizesBoards[ lv.currentLevel - 1 ], apple );

	if (solve == false) currentStatus = RANDOM;
	
	else currentStatus = RUN;

    if( lv.eatenApples >= lv.totalApples ){ 
        currentStatus = NEXT_LEVEL;
    }

/*    if( lv.eatenApples < lv.totalApples ){
        currentStatus = RUN;
    }*/


}

/** @brief Calls the next level. */
void Game::nextLevel( ){ 

    lv.currentLevel += 1;

    if( lv.currentLevel <= levels ){
        lv.currentBoard = boards[lv.currentLevel-1]; // Recovers the level board
    }

    // Restarting the whole game
    lv.eatenApples = 0;
    sk.snakeBody.clear();
    sk.snakeSize = 0;

    currentStatus = GROW;

}

/** @brief Simulates the snaked death. */
void Game::deadSnake(){

    lifes -= 1;

    std::cout << "You've crashed! :c \n";
    std::cout << ">>> Press <ENTER> when you are ready to continue.";
    std::string tcl;
    std::getline( std::cin, tcl );
	
	clearSnake();
	
	/* Resizes the snake's body*/
	while(sk.snakeBody.size() > 2) sk.snakeBody.pop_back();

    bool solve = sk.solveMaze( lv.currentBoard, lv.start, sizesBoards[ lv.currentLevel - 1 ], apple );

	if ( solve = false) currentStatus = RANDOM;

	else currentStatus = RUN;

}

/*------------------------------ The Maze -----------------------------*/

/** @brief Checks if the last character is the start point.
    @return 1 if it is, 0 otherwise. */
bool Game::isStartPoint( char ch ){
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
bool Game::ateApple( ){ 

    Position pos = sk.snakeBody.front();

    if( pos == apple ){
        return true;
    } else {
        return false;
    }

} 

/*------------------------------ Actions ------------------------------*/

/** @brief Identify the snack start point on the maze. 
*   @return Snack start point. */
Position Game::startPoint( ){

    // Goes through the maze trying to find the start_ point.
    for( unsigned int i = 0 ; i < lv.currentBoard.size() ; i++ ){        // Goes through each pos of the vector
        for( unsigned int j=0 ; j < lv.currentBoard[i].length() ; j++ ){ // Goes through the whole string
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
Position Game::throwApple( ){

    bool invalid = true;

    std::srand(std::time(0)); // seed to the rand (random numbers)
    Position tamanho = sizesBoards[lv.currentLevel-1]; // Gets the current level

    // Draw the apple until it falls into free space
    while( invalid ){

        int menor = 1;
        int maiorLinha  = tamanho.y -1;
        int maiorColuna = tamanho.x -1;

        Position pos; 

        pos.y = rand()%(maiorLinha-menor+1) + menor;  // Draw an random number to the line
        pos.x = rand()%(maiorColuna-menor+1) + menor; // Draw an random number to the column
        if( isFree(lv.currentBoard[pos.y][pos.x]) ){
            invalid = false;
            lv.currentBoard[pos.y][pos.x] = 'a';
            apple = pos;
        }
    }
}

/** @brief Moves the snake on position.
*   @return 1 if the snake ate the apple/crashed somewhere and 0 otherwise. */
bool Game::moveSnake( ){ 

    clearSnake( ); // Deletes the past snake in the board.

    Position dir = sk.Directions[sk.currentDirection];
    sk.snakeBody.push_front( dir );
    sk.snakeBody.pop_back();

    
    putSnake( ); // Puts the snake back in the board.

    if( ateApple() ){ // If the snake ate the apple
        currentStatus = GROW;
        lv.eatenApples += 1;
        return true; 
    }

    if( sk.Directions.size() == sk.currentDirection ){
        return true; // Stop is changed 
    }

    sk.currentDirection += 1;

    return false; // Else, stop is changed to false, the game keeps running.
}

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
void Game::setSizeBoards( std::vector< Position > szBoards ){
    sizesBoards = szBoards;
}

/** @brief Recover the vector with the sizes. */
std::vector<Position> Game::getSizeBoards( ) const{
    return sizesBoards;
}


    /*/-/-/-/-/-/ Level Setters and Getters /-/-/-/-/-/-*/


/** @brief Define a fase atual que o jogador se encontra.
    @param lvl A fase
    @return True se tiver um numero de fases maior que zero; False otherwise. */
bool Game::setCurrentLevel( int lvl ){
    if( lvl > 0 ){
        lv.currentLevel = lvl;
        return true;
    } else {
        return false;
    }
}


/** @brief Recupera a fase atual do jogo.
    @return A fase. */
int Game::getCurrentLevel( ) const{
    return lv.currentLevel;
}

/** @brief Recupera o tabuleiro atual do jogo.
    @return O tabuleiro. */
std::vector<std::string> Game::getCurrentBoard( ) const{
    return lv.currentBoard;
}

/** @brief Define o tabuleiro atual do jogo.
    @param lvl O tabuleiro
    @return True se tiver um tabuleiro; False otherwise. */
bool setCurrentBoard( std::vector<std::string> brd ){
    lv.currentBoard = brd;
}

/** @brief Recupera as macas comidas do jogo.
     @return A quandiade de macas. */
int Game::getEatenApples( ) {
    return lv.eatenApples;
}

/** @brief Set the snake's head position in the maze with the right character to represent it.*/
void Game::putSnake()
{
    lv.currentBoard[sk.snakeBody[0].y][sk.snakeBody[0].x] = 'D'; //desenha a cabeça
    for(auto i = 1u; i < sk.snakeBody.size(); i++)
        lv.currentBoard[sk.snakeBody[i].y][sk.snakeBody[i].x] = '0';
}

/** @brief Set the snake's body position in the maze with the blank space character to represent it.*/
void Game::clearSnake()
{
    for(auto i = 0u; i < sk.snakeBody.size(); i++)
        lv.currentBoard[sk.snakeBody[i].y][sk.snakeBody[i].x] = ' ';
}
