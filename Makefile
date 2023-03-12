CC=g++

all: server client

server:
	$(CC)  server.cpp -o server

client:
	$(CC)  client.cpp -o client

clean:
	rm -rf *.o server client