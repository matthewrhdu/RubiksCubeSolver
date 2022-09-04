GCC=g++ -Wall -g

all : controller_main player_main

controller_main : controller_main.cpp Interfaces/*.o
	${GCC} -o $@ $^

player_main : player_main.cpp Interfaces/*.o
	${GCC} -o $@ $^

clear :
	rm controller_main player_main