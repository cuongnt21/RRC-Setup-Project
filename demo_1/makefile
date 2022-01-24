INCLUDE_DIR += -I./lib

SRC += ./lib/*.cpp

OPT = -pthread -w

APPNAME = main


.PHONY: build run all

build:
	g++ main.cpp $(INCLUDE_DIR) $(SRC) -o $(APPNAME) $(OPT)

run:
	./$(APPNAME)

all:
	g++ main.cpp $(INCLUDE_DIR) $(SRC) -o $(APPNAME) $(OPT)
	./$(APPNAME)

# all2:
# 	g++ main2.cpp $(INCLUDE_DIR) $(SRC) -o main2 $(OPT)
# 	./main2