/*************************************************************************
    > File Name: tcpEchoSrv.c
    > Author: Morain
    > Mail: morainchen135@gmail.com
    > Created Time: 2014年05月24日 星期六 15时54分58秒
 ************************************************************************/

#include <unp.h>

#define MaxLen 1024

int main(int argc , char * argv[])
{
	int listenfd , connfd ;
	int n;
	struct sockaddr_in srvaddr; 
	char buf[MaxLen];
	listenfd = socket(AF_INET , SOCK_STREAM , 0);
	bzero( &srvaddr ,sizeof(srvaddr));
	srvaddr.sin_family = AF_INET ;
	srvaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	srvaddr.sin_port = htons(9999);

	if (bind(listenfd , (SA*) &srvaddr ,sizeof(srvaddr)) < 0)
	{
		printf("bind error:%s\n", strerror(errno));
		return 0;
	}
	if (listen(listenfd , LISTENQ) < 0)
	{
		printf("listen error\n");
	}
	for( ; ; )
	{
		connfd = accept(listenfd , (SA*) NULL ,NULL);
		while( ( n = read(connfd , buf ,MaxLen) ) >0)
		{
			//buf [n] = 0;
		
			write(connfd , buf ,n);
		}
		close(connfd);
	}
}
