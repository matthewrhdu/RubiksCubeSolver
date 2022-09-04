#define PORT 54321 // Port number

#include <iostream>

#include "Player.hpp"

Player::Player(){
    sock = Socket();
    
    std::cout << "Connecting..." << std::endl;
    Connect(sock, PORT);

    FD_ZERO(&all_fds);
    FD_SET(fileno(stdin), &all_fds);
    FD_SET(sock, &all_fds);
    
    max_fds = sock;
}

void Player::setup(){
    read(sock, &state, sizeof(char));
}

void Player::run(){
    setup();

    std::cout << "Connected. Waiting for Opponent." << std::endl;
    
    fd_set working_fds = all_fds;

    Select(max_fds + 1, &working_fds, NULL);

    if (FD_ISSET(sock, &working_fds)){
        read(sock, &state, sizeof(char));
    }
    
    close_everything();
}

void Player::close_everything(){
    close(sock);
}
