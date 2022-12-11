CC_x64 		= x86_64-w64-mingw32-g++
CC_x86 		= i686-w64-mingw32-gcc
OUTPUTFILE 	= build/convertBMP2JPEG
OPTIONS		= -Wall -lgdiplus -static -mwindows 
SOURCE 		= main.cpp

make: clean
	@mkdir -p build
	@$(CC_x64) $(SOURCE) $(OPTIONS)  -o $(OUTPUTFILE)_x64.exe 
	@echo "Compiled Successfully"

clean:
	@rm -rf build/*.exe


