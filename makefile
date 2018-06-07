All:
	@echo "Compiling Snaze..."
	@g++ -w -std=c++11 src/* -I include -o bin/snaze
	@echo "For running Snaze"
	@echo "Use: ./bin/snaze data/boards"
clean:
	@echo "Cleaning..."
	@rm bin/*