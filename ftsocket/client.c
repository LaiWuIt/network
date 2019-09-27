#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <ctype.h>
#include <sys/socket.h>

#include "wrap.h"

#define SERV_PORT 9525

int main(){
	int fd,ret;
	int len = 10;
	char buf[BUFSIZ];
	struct sockaddr_in  serv_addr;			//服务器端地址结构

	//创建套接字syssocket
	fd = syssocket(AF_INET, SOCK_STREAM, 0);

	//连接 sysconnect
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(SERV_PORT);
	inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr.s_addr);
	sysconnect(fd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));

	//写数据
	while(--len){
		write(fd, "hello\n",6);
		ret = read(fd, buf, sizeof(buf));
		write(STDOUT_FILENO, buf, ret);
	}
	
	//关闭连接
	close(fd);
	return 0;
}