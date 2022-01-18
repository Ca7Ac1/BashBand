all: server client test

server: server.o log.o networking.o connections.o
	gcc -o server server.o log.o connections.o networking.o

client: client.o log.o networking.o synth.o connections.o
	gcc -o client client.o log.o connections.o synth.o networking.o

server.o: server.c
	gcc -c server.c 

client.o: client.c
	gcc -c client.c

connections.o: connections.c
	gcc -c connections.c

input.o: input.c
	gcc -c input.c

log.o: log.c
	gcc -c log.c

networking.o: networking.c
	gcc -c networking.c

synth.o: synth.c
	gcc -c synth.c

test: test.o input.o synth.o
	gcc -o test test.o log.o input.o synth.o

test.o: test.c
	gcc -c test.c