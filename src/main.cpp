/**
 * @file main.cpp
 * @version 1.0
 * @since May, 26.
 * @date Jun, 04.
 * @author Oziel Alves (ozielalves@ufrn.edu.br)
 * @author Max Willian (maxwilliam780@gmail.com)
 * @title Game Loop
 */

#include "gameManager.hpp"
#include "game.hpp"
#include "level.hpp"
#include "playerSnake.hpp"

int main( int argc, char * argv[] ){

	Manager Manager;
	
	auto result = Manager.initialize( argv[1] );
std::cout << "ooi 1\n";
	if(result != Manager::Error::BOARD_OK ){ 
		if( result == Manager::Error::ARCHIVE_NOT_FINDED){
			std::cout << "Could not find the file with the game info.\n";
		} else if( result == Manager::Error::MISSING_START_POSITION){
			std::cout << "Some Mazes have missing start positions\n";
		} else if( result == Manager::Error::EXTRANEOUS_SYMBOL){
			std::cout << "Extraneous symbols were finded on the mazes.\n";
			std::cout << "You can only use: '#', ' ', '*', '.'";
		} else {
			std::cout << "A process error happend, unexpectedly.";
		}
		return 0;
	}
std::cout << "ooi 2 \n";


	// Initial message
    Manager.welcome();
std::cout << "ooi 3\n";

	// The game loop
	while( not Manager.gameover() ){
		Manager.process();
		Manager.update();
		Manager.render();
	}
std::cout << "ooi 4\n";
	Manager.render_final();
std::cout << "ooi 5 \n";
	return 0;
}
