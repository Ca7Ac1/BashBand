all: server client test

server: server.o log.o networking.o connections.o server.h log.h networking.h connections.h
	gcc -o server server.o log.o connections.o networking.o

client: client.o log.o networking.o synth.o connections.o input.o client.h log.h networking.h connections.h synth.h input.h
	gcc -o client client.o log.o connections.o synth.o networking.o input.o `sdl2-config --cflags --libs` -Wall

server.o: server.c server.h
	gcc -c server.c

client.o: client.c client.h
	gcc -c client.c

connections.o: connections.c connections.h
	gcc -c connections.c

gui.o: gui.c gui.h
	gcc -c gui.c `sdl2-config --cflags --libs`

input.o: input.c input.h
	gcc -c input.c

log.o: log.c log.h
	gcc -c log.c

networking.o: networking.c networking.h
	gcc -c networking.c

synth.o: synth.c synth.h
	gcc -c synth.c

test: test.o input.o synth.o gui.o
	gcc -o test test.o log.o input.o synth.o gui.o -lncurses `sdl2-config --cflags --libs` -Wall

test.o: test.c
	gcc -c test.c `sdl2-config --cflags --libs` -Wall

clean:
	rm -f *.o
	rm -f *.exe
	rm -f server
	rm -f client
	rm -f test
	rm -f a.out
