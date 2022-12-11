CC_x64 		= x86_64-w64-mingw32-g++
OUTPUTFILE 	= build/screenshot_ex1
OPTIONS		= -Wall -s -O2 -lgdiplus -static-libstdc++ -static-libgcc -mwindows 
SOURCE 		= main.cpp

make: clean
	@mkdir -p build
	@$(CC_x64) $(SOURCE) $(OPTIONS)  -o $(OUTPUTFILE)_x64.exe 
	@echo "Compiled Successfully"

clean:
	@rm -rf build/*.exe


