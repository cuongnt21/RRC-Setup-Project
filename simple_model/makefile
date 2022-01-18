.PHONY: client

client:
	g++ UE.cpp -o client
	./client

.PHONY: server

server:
	g++ eNB.cpp -o server
	./server

all:
	g++ main.cpp -o main -pthread
	./main