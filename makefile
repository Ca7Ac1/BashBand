all: server client client_test

server: server.o log.o networking.o connections.o server.h log.h networking.h connections.h
	gcc -o server server.o log.o connections.o networking.o

client: client.o log.o networking.o synth.o connections.o input.o gui.o client.h log.h networking.h connections.h synth.h input.h gui.h
	gcc -o client client.o log.o connections.o synth.o networking.o input.o gui.o `sdl2-config --cflags --libs` -Wall -lSDL2_ttf

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
	gcc -o test test.o log.o input.o synth.o gui.o -lncurses `sdl2-config --cflags --libs` -Wall -lSDL2_ttf

test.o: test.c
	gcc -c test.c `sdl2-config --cflags --libs` -Wall -lSDL2_ttf

client_test: client_test.o log.o networking.o synth.o gui.o client_test.h log.h networking.h connections.h synth.h gui.h
	gcc -o client_test client_test.o log.o connections.o synth.o networking.o gui.o `sdl2-config --cflags --libs` -Wall -lSDL2_ttf

client_test.o: client_test.c client_test.h
	gcc -c client_test.c

clean:
	rm -f *.o
	rm -f *.exe
	rm -f *.txt
	rm -f server
	rm -f client
	rm -f client_test
	rm -f test
	rm -f a.out
