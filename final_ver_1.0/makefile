INCLUDE_DIR += -I./lib

CPP_SRC += ./lib/*.cpp

C_SRC += ./lib/*.c

OPT = -pthread -w

APPNAME = main


.PHONY: build run all rm

build:
	gcc -c $(INCLUDE_DIR) $(C_SRC) $(OPT)
	g++ -c main.cpp $(INCLUDE_DIR) $(CPP_SRC) $(OPT)
	g++ *.o -o $(APPNAME) $(OPT)

run:
	./$(APPNAME)

all:
	gcc -c $(INCLUDE_DIR) $(C_SRC) $(OPT)
	g++ -c main.cpp $(INCLUDE_DIR) $(CPP_SRC) $(OPT)
	g++ *.o -o $(APPNAME) $(OPT)
	rm *.o
	./$(APPNAME)

rm:
	rm *.o
