clean:
	del *.o
	@echo ! Succesfull deleted all *.o files !

debug:
	@xcopy /Q /Y /E res build\debug\res

	@echo ! Start Compiling!
	g++ -pthread -c src\main.cpp -g -Wall -m64 
	g++ -pthread *.o -o build\debug\main -s -L -lmingw32 -lwinmm 
	@echo ! Ready !

release:
	@xcopy /Q /Y /E res build/release/res

	@echo ! Start Compiling!
	g++ -c src/main.cpp -std=c++14 -g -Wall -m64
	g++ *.o -o build/release/main 
	@echo ! Ready !

releaserun:
	@xcopy /Q /Y /E res build\release\res

	@echo ! Start Compiling!
	g++ -c src\main.cpp -std=c++14 -g -Wall -m64
	g++ *.o -o build\release\main && start build\release\main 
	@echo ! Ready !

debugrun:
	@xcopy /Q /Y /E res build\debug\res

	@echo ! Start Compiling!
	g++ -c src\main.cpp -std=c++14 -g -Wall -m64
	g++ *.o -o build\debug\main  && start build\debug\main
	@echo ! Ready !