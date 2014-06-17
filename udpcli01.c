#include <unp.h>

void dg_cli(FILE * fp , int sockfd , const SA *pservaddr , socklen_t servlen)
{
	int n;
	char sendline[MAXLINE] , recv[MAXLINE + 1];
	while(fgets(sendline , MAXLINE , fp) != NULL)
	{
		sendto(sockfd , sendline , strlen(sendline) , 0 , pservaddr , servlen);
		n = recvfrom(sockfd , recv , MAXLINE , 0 ,NULL , NULL);
		recv[n] = 0;
		fputs(recv , stdout);
	}
}
int main(int argc, char *argv[])
{
	int sockfd ;
	struct sockaddr_in servaddr , cliaddr;

	if(argc != 2)
	{
		printf("usage : udpcli <IPAddress>\n");
		return 0;
	}
	bzero(&servaddr , sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(SERV_PORT);
	inet_pton(AF_INET , argv[1] , &servaddr.sin_addr);
	sockfd = socket(AF_INET , SOCK_DGRAM , 0);
	dg_cli(stdin , sockfd , (SA *) &servaddr , sizeof(servaddr));

	exit(0);
}