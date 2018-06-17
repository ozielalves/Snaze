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
	toHash += initialPosition.x + '0'; 
	toHash += initialPosition.y + '0'; 
//	std::cout << toHash << std::endl;
	int i = 0;
	while(!Q.empty()){
		++i;
		std:: cout << "counter: " << i << std::endl;
		auto V = Q.front();
		toHash.clear();
		toHash += V.current.x + '0'; 
		toHash += V.current.y + '0'; 
		
		if(V.current == apple){
			//V.path.pop_front();	
			Directions = V.path;
			std::cout << "ended true" << std::endl;
			std::cout << "what was hashed just now " << V.current.x << " " <<  V.current.y << std::endl;
			for (auto i = V.path.begin(); i != V.path.end(); ++i) {
				std::cout << "Coordenates " << (*i).y << (*i).x  << std::endl;
			}

		//	hash.clear();
			return true;
		}

		if(!hash.insert(toHash,0)) {
		std::cout << "string that was already in hash: " << toHash << std::endl;
		Q.pop();
		continue;
		}

		else if(maze[V.current.y][V.current.x] == 1){
			Q.pop();
			continue;
		}
		V.path.push_back(V.current);
        Q.push(Pos(adjacentPosition(V.current, NORTH),V.path));//[0]
		
//		V.path.pop_back();
//		V.path.push_back(adjacentPosition(V.current, SOUTH));
        
		Q.push(Pos(adjacentPosition(V.current, SOUTH),V.path ));//[1]
		
//		V.path.pop_back();
//		V.path.push_back(adjacentPosition(V.current,WEST ));
        
		Q.push(Pos(adjacentPosition(V.current, EAST),V.path)); //[3]
		
//		V.path.pop_back();
//		V.path.push_back(adjacentPosition(V.current, EAST));
        
		Q.push(Pos(adjacentPosition(V.current, WEST),V.path)); //[2]

		Q.pop();
		}

	std::cout << "ended false" << std::endl;
	hash.clear();
	return false;

	}


					
/** @brief Trys to find a way to the apple.
   	@return 1 if it's possible, 0 otherwise. */
/*bool Snake::solveMaze( 	std::vector<std::string> currentBoard, 
						Position initialPosition, 
						Position sizeBoard, 
						Position apple ){

    int freeSpaces = 0; // Free spaces on the board.
    std::stack< Position > marked; // Stack.
    Position currentPosition; // To control the backtracking current position.

    // Creating an position board -> (1) Not free ; (0) Free.
    // Making easy the way search to the apple.
    int maze[sizeBoard.y][sizeBoard.x];

    for( int i(0) ; i < sizeBoard.y ; i++ ){
        for( int j(0) ; j < sizeBoard.x; j++ ){
            if( gm.isWall( currentBoard[i][j] ) ){ // If the current position is an wall, it's not free.
                maze[i][j] = 1;
            } else if( gm.isInvisibleWall( currentBoard[i][j] ) ){  // If the current position is an invisible wall, it's not free.
                maze[i][j] = 1;
            } else { // If it is free.
                maze[i][j] = 0; // Initializes everything with zero.
                freeSpaces+=1; // Saves the number of free spaces.
            }

        }
    }
*/
/*------------------------- Backtracking ---------------------------*/

    // I ) Makes initialPosition the current cell and mark as visited
 /*   currentPosition = initialPosition;
    maze[initialPosition.y][initialPosition.x] = 1; // Makes an Not free space.
    freeSpaces -= 1; // decreases one free space

    // II ) Search for cells not visited yet.
    while( freeSpaces > 0 ){ // While there's free spaces in the maze

        std::vector< Position > neighborhood; //<! The neighborhood
        neighborhood.push_back(adjacentPosition(currentPosition, NORTH));//[0]
        neighborhood.push_back(adjacentPosition(currentPosition, SOUTH));//[1]
        neighborhood.push_back(adjacentPosition(currentPosition, EAST)); //[3]
        neighborhood.push_back(adjacentPosition(currentPosition, WEST)); //[2]


    */    /* 	Avoiding a segmentation fault, if the position is invalid,
        	it will be changed to the initial position (which is occupied). */
     /*   for (auto i = 0u; i < neighborhood.size(); i++)
            if( not is_validPosition( neighborhood[i], sizeBoard ) ) // se a posicao do visinho for invalida
                neighborhood[i] = initialPosition;

        if( currentPosition == apple ){ // If the current pos is the apple.

            // The apple position is pushed to the stack
            marked.push( currentPosition );

            while( !(marked.empty()) ){

                // See who is the next
                Position dir = marked.top();

                // Adds to the list
                Directions.push_front( dir );
                
                // Takes it off
                marked.pop();
            }

            return true;
		}
        // III ) If the neighbors are free, valid or have apple.
        else if( maze[neighborhood[0].y][neighborhood[0].x] == 0
            or maze[neighborhood[1].y][neighborhood[1].x] == 0
            or maze[neighborhood[2].y][neighborhood[2].x] == 0
            or maze[neighborhood[3].y][neighborhood[3].x] == 0 ){ // Free nghbrs, are not wall and weren't visited yet

            // IV ) Choses one of the neighbors, one of them will enter.
            Position vizinho;
            for (auto i = 0u; i < neighborhood.size(); i++){

            	// If the neighbor pos is free and is not the snake body.
                if( maze[neighborhood[i].y][neighborhood[i].x] == 0 ){
                    vizinho = neighborhood[i];   // Determines the neighbors.
                    freeSpaces -= 1; // Decreses one free space.
                    maze[neighborhood[i].y][neighborhood[i].x] = 1; // Mark on the maze wich pos is not free.
                    break;
                }
            }

             // Push the current pos to the stack
             marked.push( currentPosition );

             // The current pos now is the chosen neighbor
             currentPosition = vizinho;

        }
        // V ) If none of the neighbor is free but the stack still not empty 
        else if( !(marked.empty()) ){ 
           
            // Pops the last stack element
            marked.pop();

            // Saves the top
            Position newPosition = marked.top();

            // Makes the new cell the current cell
            currentPosition = newPosition;
        }

    }

    return false;
}
*/
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
