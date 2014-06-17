#include <unp.h>

void strcli(FILE *fp , int sockfd)
{
	char sendline[MAXLINE] , recvline[MAXLINE];
	while(fgets(sendline , MAXLINE , fp) != NULL)
	{
		write(sockfd , sendline , strlen(sendline));
		if(read(sockfd , recvline , MAXLINE) == 0)
		{
			printf("strcli: server terminated prematurely\n");
			return;
		}
		fputs(recvline , stdout);
	}
}

int main(int argc, char const *argv[])
{
	int sockfd ;
	struct sockaddr_in  servaddr;
	if(argc != 2)
	{
		printf("usage : tcpcli <IPaddress>\n");
		return 0;
	}
	sockfd = socket(AF_INET , SOCK_STREAM , 0);
	bzero(&servaddr , sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(SERV_PORT);
	inet_pton(AF_INET , argv[1] , &servaddr.sin_addr);
	connect(sockfd , (SA*)&servaddr , sizeof(servaddr));
	strcli(stdin , sockfd);
	exit(0);
}