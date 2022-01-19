all: server client test

server: server.o log.o networking.o connections.o server.h log.h networking.h connections.h
	gcc -o server server.o log.o connections.o networking.o

client: client.o log.o networking.o synth.o connections.o client.h log.h networking.h connections.h synth.h
	gcc -o client client.o log.o connections.o synth.o networking.o

server.o: server.c server.h
	gcc -c server.c

client.o: client.c client.h
	gcc -c client.c

connections.o: connections.c connections.h
	gcc -c connections.c

input.o: input.c input.h
	gcc -c input.c

log.o: log.c log.h
	gcc -c log.c

networking.o: networking.c networking.h
	gcc -c networking.c

synth.o: synth.c synth.h
	gcc -c synth.c

test: test.o input.o synth.o
	gcc -o test test.o log.o input.o synth.o

test.o: test.c
	gcc -c test.c

clean: 
	rm -f *.o
	rm -f *.exe
	rm -f server
	rm -f client
	rm -f test
	rm -f a.out