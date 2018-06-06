All:
	@echo "Compiling Snaze..."
	@g++ -W -std=c++11 include/gameManager.hpp src/main.cpp include/game.hpp include/playerSnake.hpp -I include -o bin/snaze
	@echo "For running Snaze"
	@echo "Use: /bin/snaze data/tab1"
clean:
	@echo "Cleaning..."
	@rm bin/*