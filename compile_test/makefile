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

.PHONY: rder_encode

rder_encode:
	gcc rder_encode.c $(INCLUDE_DIR) $(SRC) -o rder_encode $(OPT)
	./rder_encode

.PHONY: rber_decode

rber_decode:
	gcc rber_decode.c $(INCLUDE_DIR) $(SRC) -o rber_decode $(OPT)
	./rber_decode
