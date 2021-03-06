/**
 * @file gameManager.inl
 * @version 1.0
 * @since May, 26.
 * @date Jun, 01. Map
 * @author Oziel Alves (ozielalves@ufrn.edu.br)
 * @author Max Willian (maxwilliam780@gmail.com)
 * @title Game Manager source code
 */

#include "gameManager.hpp"

Game game;

/** @brief Verifies if there is any error in the board.
    @return The finded error, if exists. */
Manager::Error Manager::parsing( ){

	// Getting the game board.
    std::vector<std::vector<std::string>> boards_ = game.getBoards();

    // Searching for erros in the maze.
    for( unsigned int i(0) ; i < boards_.size() ;  i++ ){ // For each board

        int starting_point = 0;

        for( unsigned int j (0) ; j < boards_[i].size() ; j++ ){ // For each board's line

            for( unsigned int k(0) ; k < boards_[i][j].size() ; k++ ){ // For each board's column

                char symb = boards_[i][j][k];

                // If there is any extraneous symbol.
                if( !(game.isStartPoint( symb )) and !( game.isWall( symb )) and !(game.isFree( symb )) and !(game.isInvisibleWall( symb )) ){
                    return EXTRANEOUS_SYMBOL;
                }

                // Verifies if it is an start point.
                if( game.isStartPoint( symb ) ){
                    starting_point += 1;
                }
        	} 
    	}

        if( starting_point != 1 ){ // If there is more than one start points.
            return MISSING_START_POSITION;
        }
    }

    return BOARD_OK;
}

/** @brief Reads the client file.
	@return File was succefuly read or the finded error. */
Manager::Error Manager::initialize( char * file ){

    // An input stream file.
    std::ifstream fl;

    // File opening.
    fl.open( file, std::ios::in );

    // Looking for errors on the file opening.
    if (!fl.is_open()){
        return Error::ARCHIVE_NOT_FINDED;
    }

    std::vector<std::vector<std::string>> _boards;
    std::vector<Position> boards_size;
    int _levels = 0;

    Position size;
    std::string Board_line;
    std::string build;

    // While there is something on the file
    while( fl.good() ){

        std::vector<std::string> lin_board;

        fl >> size.y; // How many lins
        fl >> size.x; // How many cols

        boards_size.push_back( size );

        getline( fl, build ); //
        
        for( int j(0u) ; j<size.y ; j++ ){

            getline( fl, Board_line );
            
            lin_board.push_back(Board_line);

        }

        _boards.push_back( lin_board );

        _levels += 1;
        
        getline( fl, build ); //

    } 

    game.setLevels( _levels );           
    game.setSizeBoards( boards_size ); 
    game.setBoards( _boards );         
	
	// Starts the game
	game.nextLevel(); 

    auto result = parsing();

    return result;
}

//! @brief Calls the next Game phase.
void Manager::process( ){
    
    usleep(100000); // Game pauses for some microseconds
}

//! @brief Shows the start conditions of the game.
void Manager::welcome( ){
    int n_levels = game.getLevels();
    int n_lives  = game.getLifes();

    system("clear");                                                                                          
    std::cout << "                              Welcome, This is the Snaze game                           \n";    
    std::cout << "                  The game has " << n_levels << " phases and you have " << n_lives << " lifes! Get ready!\n";
    std::cout << "                                 Press <ENTER> To start!                                   \n";
    std::cout << "\n";
    std::cout << "//////////////////////////////////////////////////////////////////////////////////////////////////\n";

    std::string build;
    std::getline( std::cin, build );

}

/** @brief Determines if the game should keep going or not.
	@return True if the game if over, 0 otherwise. */
bool Manager::gameover( ){

    int currentLevel_ = game.getCurrentLevel();
    int _levels = game.getLevels();
    int life = game.getLifes();


    // If the snake ate all the apples.
    if( currentLevel_ > _levels ){
        game.setStatus( 1 ); // WON
        return true;
    }
    // If there is no more lifes left.
    else if ( life == 0 ){
        game.setStatus( 0 ); // LOSE
        return true;
    }
    else { // The game continues...
        return false;
    }
}

//! @brief Show the phase's result.
void Manager::render( ){
    system("clear");
    std::vector<std::string> currentBoard_ = game.getCurrentBoard();
    Position initial = game.startPoint();
    std::cout << "                                              LEVEL "<< game.getCurrentLevel() <<"                                             \n";
    std::cout << "                                                                                                  \n";
    std::cout << "                                Lifes: " << game.getLifes() << "    ||   Eaten food:  " << game.getEatenApples() << " of 10                             \n";
    std::cout << "\n";
    std::cout << "//////////////////////////////////////////////////////////////////////////////////////////////////\n";

    // Adjusting the game (centralizando)
    int numero_espacos = (int) ( 92 - currentBoard_.front().size() ) / 2;
    
    for( unsigned int i(0u); i < currentBoard_.size() ; i++ ){
        std::cout << "/// ";
        
        for (int j(0u); j < numero_espacos; ++j) // Printing spaces
            std::cout << " ";

        std::cout << currentBoard_[i]; // Printing TAB character

        for (int j(0u); j < numero_espacos; ++j) // Printing spaces
            std::cout << " ";
        
        std::cout << "///\n";
    }

    std::cout << "//////////////////////////////////////////////////////////////////////////////////////////////////\n";
}

//! @brief Shows the final results.
void Manager::render_final( ){

    // Recovers the Player status
    bool result = game.getStatus();
    std::cout << "\n";
    std::cout << "                                            Game Over                                             \n";
    std::cout << "\n";

    // If the player won
    if( result == true ){
        std::cout << "                                    Congratulations, YOU WON!!!                                    \n";
    }

    if( result == false ){
        std::cout << "                                  What a shame, fantastic loser!                                    \n";
    }
    std::cout << "//////////////////////////////////////////////////////////////////////////////////////////////////\n";
}

//! @brief Updates the game status.
void Manager::update( ){

    switch (game.currentStatus){
        case Game::Status::RUN:
            game.moveSnake(); 
            break;
        case Game::Status::RANDOM:
            game.random_move();
            break;
        case Game::Status::GROW:
            game.growSnake();
            break;
        case Game::Status::NEXT_LEVEL:
            game.nextLevel();
                std::cout << "\n";
                std::cout << "                               Press <ENTER> When you're ready.                      \n";
                std::cout << "\n";
                std::cout << "//////////////////////////////////////////////////////////////////////////////////////////////////\n";
            break;
        case Game::Status::DEAD:
            game.deadSnake();
            break;
    }

}



