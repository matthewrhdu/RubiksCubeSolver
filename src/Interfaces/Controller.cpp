#define PORT 54321 // Port number

#include "Controller.hpp"

#include <iostream>
#include <cstdlib>

Controller::Controller(){
    sock_fd = Socket();  
    Bind(sock_fd, PORT);

    Listen(sock_fd, 5);

    FD_ZERO(&all_fds);
    max_fds = sock_fd;
}

void Controller::setup_clients(){
    for (int num_players = 0; num_players != 2; num_players++){
        int response = Accept(sock_fd);

        std::cout << "Connection Received" << std::endl;
        
        char wait_cmd = WAIT_STATE;
        Write(response, &wait_cmd, sizeof(char));
        
        player_fds[num_players] = response;
        FD_SET(response, &all_fds);
    }
}

void Controller::close_everything(){	
    for (int n = 0; n < 2; n++){
        Close(player_fds[n]);
    }
    Close(sock_fd);
}

void Controller::run(){
    setup_clients();

    for (int n = 0; n < 2; n++){
        char start_cmd = START_STATE;
        Write(player_fds[n], &start_cmd, sizeof(char));
    }
    
    std::cout << "Setup complete" << std::endl;

    close_everything();
}
