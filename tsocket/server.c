#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define  SERV_PORT	9527

void sys_err(const char *str){
	perror(str);
	exit(1);
}

int main(int argc, char *argv[]){
	int tfd, cfd, ret, i;
	char buf[BUFSIZ];

	//创建sockaddr_in结构体变量
	// struct sockaddr_in{
	//     sa_family_t     sin_family;   //地址族（Address Family），也就是地址类型 2字节
	//     uint16_t        sin_port;     //16位的端口号	 2字节
	//     struct in_addr  sin_addr;     //32位IP地址    4字节
	//     char            sin_zero[8];  //不使用，一般用0填充  8字节
	// };
	// struct in_addr{
	//     in_addr_t  s_addr;  //32位的IP地址
	// };
	struct sockaddr_in serv_addr, clit_addr;
	socklen_t clit_addr_len;

	serv_addr.sin_family = AF_INET;
	//htons是将整型变量从主机字节顺序转变成网络字节顺序,就是整数在地址空间存储方式变为高位字节存放在内存的低地址处
	serv_addr.sin_port = htons(SERV_PORT);   
	//htonl将本机字节顺序转化为网络字节顺序,所谓网络字节顺序（大尾顺序）就是指一个数在内存中存储的时候“高对低，低对高”（即一个数的高位字节存放于低地址单元，低位字节存放在高地址单元中）。但是计算机的内存存储数据时有可能是大尾顺序或者小尾顺序。
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);

	//创建套接字
	tfd = socket(AF_INET, SOCK_STREAM, 0);	//AF_INET:IPv4地址;SOCK_STREAM:流格式套接字/面向连接的套接字;protocol:传输协议
	if(tfd == -1){
		sys_err("socket error");
	}

	//int bind(int sock, struct sockaddr *addr, socklen_t addrlen);  //Linux
	bind(tfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));

	listen(tfd, 128);

	cfd = accept(tfd, (struct sockaddr *)&clit_addr, &clit_addr_len);
	if(cfd == -1){
		sys_err("accept error");
	}

	while(1){
		ret = read(cfd, buf, sizeof(buf));
		write(STDOUT_FILENO, buf, ret);
		for(i = 0; i < ret; i++){
			buf[i] = toupper(buf[i]);
		}
		write(cfd, buf, ret);
	}

	close(tfd);
	close(cfd);
	return 0;
}