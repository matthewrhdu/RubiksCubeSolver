#ifndef SOCKETTOOLS_HPP
#define SOCKETTOOLS_HPP

#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>    /* Internet domain header */
#include <arpa/inet.h>     /* only needed on my mac */

int Socket();

int Bind(int __fd, int port);

int Listen(int __fd, int __n);

int Select(int __nfds, fd_set *__readfds, timeval *__timeout);

int Accept(int __fd);

int Connect(int __fd, int port);

int Read(int fd, void *buf, size_t count);

int Write(int fd, void *buf, size_t count);

int Close(int fd);

#endif // SOCKETTOOLS_HPP