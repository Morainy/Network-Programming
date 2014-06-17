#include <unp.h>

int main(int argc, char *argv[])
{
	int sockfd ;
	struct sockaddr_in servaddr , cliaddr;
	char recv[MAXLINE] , send[MAXLINE];
	socklen_t len;

	if(argc != 2)
	{
		printf("usage : udpcli <IPAddress>\n");
		return 0;
	}
	bzero(&servaddr , sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(9999);
	inet_pton(AF_INET , argv[1] , &servaddr.sin_addr);
	sockfd = socket(AF_INET , SOCK_DGRAM , 0);
	//dg_cli(stdin , sockfd , (SA *) &servaddr , sizeof(servaddr));
	fgets(send , MAXLINE , stdin);
	int n = sendto(sockfd , send , strlen(send) , 0 , (SA *)&servaddr , sizeof(servaddr));
	//printf("n = %d\n",n);
	//printf("%s\n",strerror(errno));
	int i;
	for( i =0 ; i<100 ; i++)
	{
		recvfrom(sockfd ,recv , MAXLINE , 0 ,NULL , NULL);
		fputs(recv , stdout);
	}
	exit(0);
}
