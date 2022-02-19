INCLUDE_DIR += -I./lib

SRC += ./lib/*.c

OPT = -w

APPNAME = main

.PHONY: complile run all rm

compile:
	gcc -c $(INCLUDE_DIR) $(SRC) $(OPT)
	g++ -c main.cpp $(INCLUDE_DIR)
	g++ *.o -o $(APPNAME)

run:
	./$(APPNAME)

all:
	gcc -c $(INCLUDE_DIR) $(SRC) $(OPT)
	g++ -c main.cpp $(INCLUDE_DIR)
	g++ *.o -o $(APPNAME)
	rm *.o
	./$(APPNAME)

rm:
	rm *.o