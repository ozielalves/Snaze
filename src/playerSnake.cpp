/**
 * @file playerSnake.inl
 * @version 1.0
 * @since May, 26. 
 * @date May, 30.
 * @author Oziel Alves (ozielalves@ufrn.edu.br)
 * @author Max Willian (maxwilliam780@gmail.com)
 * @title The Player's snake src code
 */

#include "playerSnake.hpp"

#include <queue>
#include <deque>
Game gm; // To access the functions.

struct Pos{
	std::deque<Position> path;
	Position current;
	
	Pos(Position a,std::deque<Position> l = std::deque<Position>() ): path(l),current(a) {}
};
/** @brief Trys to find a way to the apple.
   	@return 1 if it's possible, 0 otherwise. */

bool Snake::solveMaze( 	std::vector<std::string> currentBoard, 
						Position initialPosition, 
						Position sizeBoard, 
						Position apple ){

	int maze[sizeBoard.y][sizeBoard.x];

	for( int i(0) ; i < sizeBoard.y ; i++ ){
		for( int j(0) ; j < sizeBoard.x; j++ ){
			if( gm.isWall( currentBoard[i][j] ) ){ // If the current position is an wall, it's not free.
				maze[i][j] = 1;
			} else if( gm.isInvisibleWall( currentBoard[i][j] ) ){  // If the current position is an invisible wall, it's not free.
				maze[i][j] = 1;
			} else { // If it is free.
				maze[i][j] = 0; // Initializes everything with zero.
			}

		}
	}
	std::queue<Pos> Q;
	Q.push(Pos(initialPosition));
	std::string toHash;
	
	int i = 0;
	while(!Q.empty()){
		++i;
//		std:: cout << "counter: " << i << std::endl;
		auto V = Q.front();
		toHash.clear();
		toHash += V.current.x + '0'; 
		toHash += V.current.y + '0'; 
		
		if(V.current == apple){
			V.path.push_back(V.current);	
			Directions = V.path;
			std::cout << "ended true" << std::endl;
//			std::cout << "what was hashed just now " << V.current.x << " " <<  V.current.y << std::endl;
			for (auto i = V.path.begin(); i != V.path.end(); ++i) {
				std::cout << "Solution Coordenates " << (*i).y << " " << (*i).x  << std::endl;
			}
				std::cout << "Apple loc " << apple.y << " " << apple.x << std::endl;

			hash.clear();
			toHash.clear();
			auto block = *(V.path.end()-2);
			toHash += block.x + '0'; 
			toHash += block.y + '0'; 
			hash.insert(toHash,0);
			return true;
		}

		if(!hash.insert(toHash,0)) {
//		std::cout << "string that was already in hash: " << toHash << std::endl;
		Q.pop();
		continue;
		}

		else if(maze[V.current.y][V.current.x] == 1){
			Q.pop();
			continue;
		}
		V.path.push_back(V.current);
        Q.push(Pos(adjacentPosition(V.current, NORTH),V.path));//[0]
		
		Q.push(Pos(adjacentPosition(V.current, SOUTH),V.path ));//[1]
		
		Q.push(Pos(adjacentPosition(V.current, EAST),V.path)); //[3]
        
		Q.push(Pos(adjacentPosition(V.current, WEST),V.path)); //[2]

		Q.pop();
		}

	std::cout << "ended false" << std::endl;
	hash.clear();
	return false;

	}


					
/** @brief Returns the adjacent position accoring to the direction.
	@param pos Current position.
	@param dir Current position next place.
	@return Posição adjacente. */
Position Snake::adjacentPosition( Position pos, short int dir ){

    switch( dir ){
        case NORTH:
            pos.set( NORTH );
            break;

        case SOUTH:
            pos.set( SOUTH );
            break;

        case WEST:
            pos.set( WEST );
            break;

        case EAST:
            pos.set( EAST );
            break;
    }

    return pos;
}

/** @brief verify if the last position is part of the snake body.
	@return true if it is a position occuped by the snake, false otherwise. */
bool Snake::is_snakeBody(const Position & pos) const{

    std::cout << "Trying to know if it is body, " << pos.y <<" "<< pos.x << " é body? " << "\n";
    std::cout << "Snake size = " << snakeBody.size() << "\n";
    std::cin.ignore(); //esperar enter
    int i(snakeBody.size()-1); //nao precisa comparar o rabo
    
    while( i >= 0 ){
        if( snakeBody[i] == pos )
            return true;
        i--;
    }
    return false;
}

/** @brief Determines if the 'pos' is a valid position in the maze
	@return true if the 'pos' is valid, false otherwise. */
bool Snake::is_validPosition( Position pos, Position size ){

    return (pos.x >= 0 and pos.x < size.x and pos.y >= 0 and pos.y < size.y );
}
