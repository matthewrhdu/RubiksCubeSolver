GCC=g++ -Wall -g

all : controller player socket_tools

controller : Controller.cpp Controller.hpp
	${GCC} -c $<

player : Player.cpp Player.hpp
	${GCC} -c $<

socket_tools : SocketTools.cpp SocketTools.hpp
	${GCC} -c $<

clear :
	rm *.o