#include<stdio.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<stdlib.h>
#include<unistd.h>
#include<netinet/in.h>
#include<arpa/inet.h>
int main()
{
	int sock=socket(AF_INET,SOCK_DGRAM,0);
	struct sockaddr_in remote;
	remote.sin_family=AF_INET;
	remote.sin_port=htons(8088);
	inet_aton("127.0.0.1",&remote.sin_addr);
	socklen_t len=0;
	char buf[1024];
	while(1)
	{
		memset(buf,'\0',sizeof(buf));
		gets(buf);
		ssize_t len=sendto(sock,buf,strlen(buf),0,(struct sockaddr*)&remote,sizeof(remote));
		memset(buf,'\0',sizeof(buf));

		recvfrom(sock,buf,sizeof(buf)-1,0,(struct sockaddr*)&remote,&len);
		printf("server echo:%s\n",buf);
	}
	
	return 0;
}
