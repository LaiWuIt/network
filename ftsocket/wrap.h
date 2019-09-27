#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <ctype.h>
#include <errno.h>
#ifndef __WRAP_H_
#define __WRAP_H_

void syserr(const char *str);
int syssocket(int family, int type, int protocol);
int sysbind(int fd, const struct sockaddr *sa, socklen_t salen);
int sysaccept(int sockfd,struct sockaddr *addr,socklen_t *addrlen);
ssize_t sysread(int fd, void *buf, size_t len);
ssize_t syswrite(int fd, void *ptr, size_t nbt);
int sysconnect(int fd, const struct sockaddr *addr, socklen_t addrlen);

#endif