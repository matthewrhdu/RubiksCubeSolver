/**
 * @file SocketTools.cpp
 * @author Matthew Du (matthewrhdu2@gmail.com)
 * @brief The implementation file for the code to set up a TCP socket
 * @version 0.1
 * @date 2022-09-02
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "SocketTools.hpp"

int Socket(){
    int soc = socket(AF_INET, SOCK_STREAM, 0);
    if (soc == -1){
        perror("socket");
        exit(1);
    }
    return soc;
}

int Bind(int __fd, int port){
    // initialize server address    
    struct sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_port = htons(port);
    memset(&server.sin_zero, 0, 8);
    server.sin_addr.s_addr = INADDR_ANY;
    
    int bind_ret = bind(__fd, (struct sockaddr *) &server, sizeof(struct sockaddr_in));
    if (bind_ret == -1) {
        perror("server: bind");
        Close(__fd);
        exit(1);
    }
    return bind_ret;
}

int Listen(int __fd, int __n){
    int listen_ret = listen(__fd, __n);
    if (listen_ret < 0) {
        perror("listen");
        exit(1);
    }

    return listen_ret;
}

int Select(int __nfds, fd_set *__readfds, timeval * __timeout){
    int select_ret = select(__nfds, __readfds, NULL, NULL, __timeout);
    if (select_ret == -1){
        perror("select");
        exit(1);
    }
    return select_ret;
}

int Accept(int __fd){
    struct sockaddr_in client_addr;
    socklen_t client_len = sizeof(struct sockaddr_in);
    client_addr.sin_family = AF_INET;
    
    int player_fd = accept(__fd, (struct sockaddr *)&client_addr, &client_len);
    if (player_fd == -1){
        perror("accept");
        exit(1);
    }
    return player_fd;
}

int Connect(int __fd, int port){
    // initialize server address    
	struct sockaddr_in server;
	server.sin_family = AF_INET; // Sets the family of socket
	server.sin_port = htons(port); // Port number in network order
	memset(&server.sin_zero, 0, 8); // Extra Padding; makes sockaddr_in same size as sockaddr struct.
	
	struct addrinfo *ai;
	char hostname[] = "localhost";
	
	/* this call declares memory and populates ailist */
	getaddrinfo(hostname, NULL, NULL, &ai);
	/* we only make use of the first element in the list */
	server.sin_addr = ((struct sockaddr_in *) ai->ai_addr)->sin_addr;
	
	// free the memory that was allocated by getaddrinfo for this list
	freeaddrinfo(ai);
	
    int conn_port = connect(__fd, (struct sockaddr *)&server, sizeof(struct sockaddr_in));
    if (conn_port == -1){
        perror("connect");
        exit(1);
    }

	return conn_port;
}

int Read(int fd, void *buf, size_t count){
    return (int) read(fd, buf, count);
}

int Write(int fd, void *buf, size_t count){
    return (int) write(fd, buf, count);
}

int Close(int fd){
    return close(fd);
}
