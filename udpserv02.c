#include <unp.h>
#include <time.h>

int main(int argc, char *argv[])
{
	int sockfd ;
	char buff[MAXLINE];
	struct sockaddr_in servaddr , cliaddr;
	socklen_t len = sizeof(cliaddr);
	//socklen_t len = 1;
	time_t ticks;
	sockfd = socket(AF_INET , SOCK_DGRAM , 0);
	bzero(&servaddr , sizeof(servaddr));
	bzero(&cliaddr , sizeof(cliaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(9999);
	
	bind(sockfd , (SA*) &servaddr , sizeof(servaddr));

	recvfrom(sockfd , buff , MAXLINE , 0 , (SA *)&cliaddr , &len);
	printf("%s\n",buff);
	printf("%s\n",inet_ntoa(cliaddr.sin_addr));
	int n;
	while(1)
	{
		ticks = time(NULL);
		snprintf(buff ,  sizeof(buff) , "%.24s\n" , ctime(&ticks));
		n = sendto(sockfd , buff , strlen(buff) , 0 , (SA*)&cliaddr , len);
		//printf("n = %d\n",n);
		//printf("%s\n",strerror(errno));
		//printf("sending...\n");
		sleep(1);
	}
}
