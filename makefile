.PHONY: client

client:
	g++ UE.cpp -o client
	./client

.PHONY: server

server:
	g++ eNB.cpp -o server
	./server