#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <error.h>
#include <errno.h>

typedef int SOCKET;  
#ifndef INVALID_SOCKET  
#define INVALID_SOCKET  (SOCKET)(~0)  
#endif  
#ifndef SOCKET_ERROR  
#define SOCKET_ERROR    (-1)  
#endif  

bool check_num(char* str)
{
	for(char* temp=str;*temp!='\0';++temp)
	{
		if(*temp<'0' || *temp>'9')
			return false;
	}
	return true;
}


int main(int argc,char *argv[]){

	if(argc!=3)
	{
		printf("Invaild number of arguments.\n");
		return -1;
	}
	if(!check_num(argv[2]))
	{
		printf("Invaild port number.\n");
		return -1;
	}
	int portnum=atoi(argv[2]);
	struct hostent *hptr;
	if((hptr=gethostbyname(argv[1]))==NULL)
	{
		printf("Invaild host name.\n");
		return -1;
	}
	char IP[INET_ADDRSTRLEN] = {0};
	inet_ntop(hptr->h_addrtype, *hptr->h_addr_list, IP, INET_ADDRSTRLEN);
	while(1)
	{
		int sock = socket(AF_INET, SOCK_STREAM, 0);
		struct sockaddr_in clientaddr;
		bzero((char*)&clientaddr,sizeof(clientaddr));
		clientaddr.sin_family=AF_INET;
		clientaddr.sin_port=htons((unsigned short)portnum);
		inet_pton(AF_INET, IP, &clientaddr.sin_addr);
		if(connect(sock, (struct sockaddr*)&clientaddr, sizeof(clientaddr))==-1)
		{
			printf("Connect failed.\n");
			return -1;
		}
		printf(">");
		char message[257];
		fgets(message,256,stdin);
		message[strlen(message)-1]='\0';
		if(!strcmp("+++",message)){close(sock);break;}
		int len=strlen(message);
		memmove(message+1,message,len+1);
		message[0]=(char)len+1;
		send(sock,message,strlen(message),0);
		char len2[1];
		recv(sock,len2,1,0);
		char* response=(char*)malloc((int)*len2);
		recv(sock,response,*len2,0);
		printf("%s\n",response);
		close(sock);
	}
	return 0;

}