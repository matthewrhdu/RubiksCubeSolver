#include "SocketTools.hpp"

#ifndef STATES // A set of states of the Controller
#define STATES // Boilerplate
#define WAIT_STATE 0 // The wait state
#define START_STATE 1 // Start the game
#endif // STATES

class Player {
	private: int sock;
	private: fd_set all_fds;
	private: int max_fds;
    private: char state;

	public: Player();

	private: void setup();

	public: void run();
	
	private: void close_everything();
};