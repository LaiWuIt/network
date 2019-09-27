#include "wrap.h"

void syserr(const char *str){
	perror(str);
	exit(1);	//用户进程结束
}

int syssocket(int family, int type, int protocol){
	int lfd;
	if((lfd = socket(family, type, protocol)) < 0)
		syserr("socket error");

	return lfd;
}

int sysbind(int fd, const struct sockaddr *sa, socklen_t salen){
	int r;
	if((r = bind(fd, sa, salen)) < 0)
		syserr("bind error");

	return r;
}

int syslisten(int fd, int num){
	int r;
	if((r = listen(fd, num)) < 0)
		syserr("listen error");
	
	return r;
}

int sysaccept(int fd,struct sockaddr *addr,socklen_t *addrlen){
	int r;
again:
	if((r = accept(fd,addr,addrlen)) < 0){
		if((errno == ECONNABORTED) || (errno == EINTR))
			goto again;
		else
			syserr("accept error");
	}

	return r;
}

ssize_t sysread(int fd, void *buf, size_t len){
	ssize_t r;
again:
	if((r = read(fd, buf, len)) < 0){
		if(errno == EINTR)
			goto again;
		else
			syserr("read error");
	}

	return r;
}

ssize_t syswrite(int fd, void *buf, size_t len){
	ssize_t r;
again:
	if((r = write(fd, buf, len)) < 0){
		if(errno == EINTR)
			goto again;
		else
			syserr("write error");
	}

	return r;
}

int sysconnect(int fd, const struct sockaddr *addr, socklen_t addrlen){
	int r;
	if((r = connect(fd, addr, addrlen)) < 0)
		syserr("connect error");
	
	return r;
}
