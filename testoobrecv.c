/*
 * =====================================================================================
 *
 *       Filename:  testoobrecv.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2015年08月22日 15时31分46秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <assert.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>

#define BUF_SIZE 1024

int main(int argc , char* argv[])
{
	if(argc <= 2){
		printf("usage: %s ip_address port_number\n" , basename(argv[0]));
		return -1;
	}

	const char * ip = argv[1];
	int port = atoi(argv[2]);

	struct sockaddr_in address;
	bzero(&address , sizeof(address));
	address.sin_family = AF_INET;
	inet_pton(AF_INET ,	ip , &address.sin_addr);
	address.sin_port = htons(port);
	
	int sock = socket(PF_INET , SOCK_STREAM , 0);
	assert(sock >= 0);

	int ret = bind(sock , (struct sockaddr*)&address , sizeof(address));
	assert(ret >= 0);

	ret = listen(sock , 5);
	assert(ret >= 0);

	int recvbuf;
	int len = sizeof(recvbuf);
	getsockopt(sock , SOL_SOCKET , SO_RCVBUF , &recvbuf , (socklen_t*)&len);
	printf("The TCP recv buffer size is %d\n" , recvbuf);

	struct sockaddr_in client;
	socklen_t client_len = sizeof(client);
	int connfd = accept(sock , (struct sockaddr*)&address , &client_len);
	if(connfd < 0){
		printf("errno is: %d\n" , errno);
	}else{
		char buff[BUF_SIZE];

		bzero(buff , BUF_SIZE);
		ret = recv(connfd , buff , BUF_SIZE-1 , 0);
		printf("got %d bytes of normal data '%s'\n" , ret , buff);
		
		bzero(buff , BUF_SIZE);
		ret = recv(connfd , buff , BUF_SIZE-1 , MSG_OOB);
		printf("got %d bytes of normal data '%s'\n" , ret , buff);
		
		bzero(buff , BUF_SIZE);
		ret = recv(connfd , buff , BUF_SIZE-1 , 0);
		printf("got %d bytes of normal data '%s'\n" , ret , buff);
	
		close(connfd);
	}
	close(sock);
	return 0;
}
