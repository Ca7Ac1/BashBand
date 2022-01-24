all: server client main

main: main.o server client
	gcc -o main main.o server.o client.o input.o settings.o log.o networking.o connections.o synth.o gui.o `sdl2-config --cflags --libs` -Wall -lSDL2_ttf

main.o: main.c
	gcc -c main.c

server: server.o log.o networking.o connections.o server.h log.h networking.h connections.h
	# gcc -o server server.o log.o connections.o networking.o `sdl2-config --cflags --libs`

server.o: server.c server.h
	gcc -c server.c

client: client.o input.o settings.o log.o networking.o synth.o gui.o client.h input.h settings.h log.h networking.h connections.h synth.h gui.h
	# gcc -o client client.o input.o settings.o log.o connections.o synth.o networking.o gui.o `sdl2-config --cflags --libs` -Wall -lSDL2_ttf

client.o: client.c client.h
	gcc -c client.c

input.o: input.c input.h
	gcc -c input.c

settings.o: settings.c settings.h
	gcc -c settings.c

connections.o: connections.c connections.h
	gcc -c connections.c

gui.o: gui.c gui.h
	gcc -c gui.c `sdl2-config --cflags --libs`

log.o: log.c log.h
	gcc -c log.c
	
networking.o: networking.c networking.h
	gcc -c networking.c

synth.o: synth.c synth.h
	gcc -c synth.c

clean:
	rm -f *.o
	rm -f *.exe
	rm -f *.txt
	rm -f main
	rm -f server
	rm -f client
	rm -f bad_client
	rm -f test
	rm -f a.out
