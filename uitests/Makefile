clean:
	rm *.o
	rm build/debug/main

run:
	build/debug/./main

copyAssets:
	cp res/ build/debug/res -r
	@echo ! Ready !

debug:
	@echo ! Start Compiling!
	g++ -c src/main.cpp -Wall -Wextra -Wfloat-equal -Wundef -Wcast-align -Wwrite-strings -Wlogical-op -Wmissing-declarations -Wredundant-decls -Wshadow -Woverloaded-virtual
	g++ *.o -o build/debug/main -s -lSDL2 -lSDL2_image
	@echo ! Ready !