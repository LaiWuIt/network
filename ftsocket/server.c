#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <ctype.h>
#include <errno.h>
#include "wrap.h"

#define SERV_PORT 9525

int main(){
	int lfd,r,cfd,ret,i;
	char buf[BUFSIZ];
	socklen_t clit_addr_len;
	struct sockaddr_in serv_addr, clit_addr;

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(SERV_PORT);
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);

	lfd = syssocket(AF_INET, SOCK_STREAM, 0);

	sysbind(lfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
	syslisten(lfd, 128);
	cfd = sysaccept(lfd,(struct sockaddr *)&clit_addr,&clit_addr_len);	//接收客户端请求

	while(1){
		ret = sysread(cfd, buf, sizeof(buf));
		syswrite(STDOUT_FILENO, buf, ret);
		for(i = 0; i < ret; i++){
			buf[i] = toupper(buf[i]);
		}
		syswrite(cfd, buf, ret);
	}
	return 0;
}