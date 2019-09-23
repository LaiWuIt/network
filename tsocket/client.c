#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define SERV_PORT 9527
void sys_err(const char *str){
	perror(str);
	exit(1);
}

int main(){
	int cfd;
	int len = 10;
	char buf[BUFSIZ];

	struct sockaddr_in  serv_addr;		//服务器端地址结构

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(SERV_PORT);
	inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr.s_addr);

	//socket()
	cfd = socket(AF_INET, SOCK_STREAM, 0);
	if(cfd == -1){
		sys_err("socket error");
	}

	//connect()
	int ret = connect(cfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
	if(ret != 0){
		sys_err("connect error");
	}

	while(--len){
		write(cfd, "hello\n", 6);
		ret = read(cfd, buf, sizeof(buf));
		write(STDOUT_FILENO, buf, ret);
		sleep(1);
	}
	
	close(cfd);
	return 0;
}