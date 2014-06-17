/*************************************************************************
    > File Name: tcpEchoCli.c
    > Author: Morain
    > Mail: morainchen135@gmail.com
    > Created Time: 2014年05月24日 星期六 15时09分21秒
 ************************************************************************/

#include <unp.h>

#define MaxLen 1024
int main(int argc ,char * argv[])
{
	if(argc != 2)
	{
		printf("usage: tcpEchoCli <IPaddress>");
		return 0;
	}

	char buf[MaxLen];
	//scanf("%s" ,buf);
	fgets(buf ,MaxLen , stdin);
	//printf("buf = %s \n",buf);
	//printf("strlen(buf) = %d\n" , strlen(buf));
	//printf("sizeof(buf) = %d\n" , sizeof(buf));
	int sockfd;
	struct sockaddr_in servaddr;
	char recvbuf[strlen(buf)+1];
	int n;

	if((sockfd = socket(AF_INET , SOCK_STREAM , 0)) <0)
	{
		printf("socket error !\n");
		return 0;
	}

	bzero(&servaddr , sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(9999);
	if(inet_pton(AF_INET , argv[1] , &servaddr.sin_addr) <= 0)
	{
		printf("inet_pton error for %s ",argv[1]);
		return 0;
	}
	if(connect(sockfd , (SA *)&servaddr , sizeof(servaddr)) <0 )
	{
		printf("connect error :%s\n",strerror(errno));
		return 0;
	}

	write(sockfd , buf , strlen(buf));
	
	while((n = read(sockfd , recvbuf , strlen(buf) ) ) >0)
	{
		recvbuf[n] = 0;
		if(fputs(recvbuf , stdout) == EOF)
		{
			printf("fputs error \n");
			return 0;
		}
	}
	if(n<0)
	{
		printf("read error \n");
		return 0;
	}
	return 0;
}
