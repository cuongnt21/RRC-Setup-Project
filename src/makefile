INCLUDE_DIR += -I../asn1c\
			   -I./network

CPP_SRC += ./network/*.cpp

C_SRC += ../asn1c/*.c

OPT = -pthread -w

APPNAME = main


.PHONY: build run all rm

build:
	gcc -c $(INCLUDE_DIR) $(C_SRC) $(OPT)
	g++ -c main.cpp $(INCLUDE_DIR) $(CPP_SRC) $(OPT)
	g++ *.o -o $(APPNAME) $(OPT)
	rm *.o

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
	rm *.bin
