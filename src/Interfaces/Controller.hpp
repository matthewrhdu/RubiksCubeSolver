/**
 * @file Controller.hpp
 * @author Matthew Du (matthewrhdu2@gmail.com)
 * @brief A controller class for handling the game
 * @version 0.1
 * @date 2022-09-02
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "SocketTools.hpp"

#ifndef STATES // A set of states of the Controller
#define STATES // Boilerplate
#define WAIT_STATE 0 // The wait state
#define START_STATE 1 // Start the game
#endif // STATES


class Controller {
    private: int sock_fd;
    private: fd_set all_fds;
    private: int max_fds;
    private: char state;
    private: int player_fds[2];

    public: Controller();

    public: void run();

    private: void setup_clients();

    private: void close_everything();
};
