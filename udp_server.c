#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<stdlib.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<string.h>
int main()
{
	int sock=socket(AF_INET,SOCK_DGRAM,0);
	if(sock<0)
	{
		perror("socket");
		exit(1);
	}

	struct sockaddr_in server;
	server.sin_family=AF_INET;
	server.sin_port=htons(8088);
	server.sin_addr.s_addr=htonl(INADDR_ANY);
	bind(sock,(struct sockaddr*)&server,sizeof(server));

	struct sockaddr_in remote;
	char buf[1024];
	socklen_t len=0;
	while(1)
	{
		memset(buf,'\0',sizeof(buf));
		ssize_t len=recvfrom(sock,buf,sizeof(buf)-1,0,(struct sockaddr*)&remote,&len);
		printf("len=%d\n",len);
		if(len<0){
			perror("recvfrom\n");
			exit(1);
		}
		printf("client->%s\n",buf);
		len=sendto(sock,buf,strlen(buf),0,(struct sockaddr*)&remote,sizeof(remote));
		if(len<0){
			perror("sendto");
			exit(1);
		}
	}
	close(sock);
	return 0;
}
