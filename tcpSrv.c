/*
 * =====================================================================================
 *
 *       Filename:  tcpSrv.c
 *
 *    Description:  TCP的服务器端程序示例
 *
 *        Version:  1.0
 *        Created:  2015年04月27日 10时46分40秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <arpa/inet.h>

int main(int argc ,char *argv[])
{
	int skfd , cnfd , addr_len;
	struct sockaddr_in  srv_addr , clt_addr;
	int portNumber;
	char hello[] = "Hello \n";
	if(argc != 2 || (portNumber = atoi(argv[1])) < 0){
		printf("usage : %s port \n",argv[0]);
		exit(1);
	}

	if( (skfd = socket(AF_INET , SOCK_STREAM , 0)) < 0){
		perror("Socket error");
		exit(1);
	}

	bzero(&srv_addr , sizeof(struct sockaddr_in));
	srv_addr.sin_family = AF_INET;
	srv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	srv_addr.sin_port = htons(portNumber);

	if(bind(skfd , (struct sockaddr *)(&srv_addr) , sizeof(struct sockaddr)) < 0){
		perror("Bind error");
		exit(1);
	}

	if(listen(skfd , 4) < 0){
		perror("Listen error");
		exit(1);
	}

	while(1){
		addr_len = sizeof(struct sockaddr_in);
		if( (cnfd = accept(skfd , (struct sockaddr *)(&clt_addr) , &addr_len)) < 0){
			perror("Accept error");
			exit(1);
		}

		printf("Connect from %s:%u\n",inet_ntoa(clt_addr.sin_addr) , ntohs(clt_addr.sin_port));

		if(write(cnfd , hello , strlen(hello)) < 0){
			perror("send error");
			exit(1);
		}
		close(cnfd);
	}
	close(skfd);
	exit(0);
}

