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

typedef int SOCKET;  
#ifndef INVALID_SOCKET  
#define INVALID_SOCKET  (SOCKET)(~0)  
#endif  
#ifndef SOCKET_ERROR  
#define SOCKET_ERROR    (-1)  
#endif  
#define LISTENQ 5

const char* emails[3];
const char* names[3];

typedef struct sockaddr SA;

void InitDB()
{
	emails[0]="harris@ics.uci.edu";
	emails[1]="joe@cnn.com";
	emails[2]="jane@slashdot.org";
	names[0]="Ian G. Harris";
	names[1]="Joe Smith";
	names[2]="Jane Smith";
}

const char* find(const char* email)
{
	for(int i=0;i<3;++i)
	{
		if(!strcmp(emails[i],email))
			return names[i];
	}
	return "unknown";
}


bool check_num(char* str)
{
	for(char* temp=str;*temp!='\0';++temp)
	{
		if(*temp<'0' || *temp>'9')
			return false;
	}
	return true;
}

int main(int argc,char* argv[])
{
	if(argc!=2)
	{
		printf("Invaild number of arguments.\n");
		return -1;
	}
	if(!check_num(argv[1]))
	{
		printf("Invaild port number.\n");
		return -1;
	}
	int portnum=atoi(argv[1]);
	int listenfd;
	if((listenfd=socket(AF_INET,SOCK_STREAM,0))<0)
	{
		printf("Socket initialization failed.\n");
		return -1;
	}
	bool optval=true;
	if(setsockopt(listenfd,SOL_SOCKET,SO_REUSEADDR,(const void*)&optval,sizeof(int))<0)
	{
		printf("Setsockopt failed.\n");
		return -1;
	}
	struct sockaddr_in serveraddr;
	bzero((char*)&serveraddr,sizeof(serveraddr));
	serveraddr.sin_family=AF_INET;
	serveraddr.sin_port=htons((unsigned short)portnum);
	serveraddr.sin_addr.s_addr=htonl(INADDR_ANY);
	if(bind(listenfd,(SA*)&serveraddr,sizeof(serveraddr))<0)
	{
		printf("Bind failed.\n");
		return -1;
	}
	if(listen(listenfd,LISTENQ)<0)
	{
		printf("Listen failed.\n");
		return -1;
	}
	printf("Address server started.\n");
	InitDB();
	while(1)
	{
		int connfd;
		struct sockaddr_in clientaddr;
		int clientlen;
		clientlen=sizeof(clientaddr);
		connfd=accept(listenfd,(SA*)&clientaddr,&clientlen);
		if(connfd!=INVALID_SOCKET)
		{
			char len[1];
			int result1=recv(connfd,len,1,0);
			if(result1!=SOCKET_ERROR)
			{
				if((int)*len==1){printf("\n");send(connfd,"\tunknown",strlen("unknown")+2,0);continue;}
				char* email=(char*)malloc((int)*len);
				int result2=recv(connfd,email,*len,0);
				if(result2!=SOCKET_ERROR)
				{
					printf("%s\n",email);
					const char* find_res=find(email);
					char* response=malloc(strlen(find_res)+2);
					response[0]=(char)(strlen(find_res)+1);
					strcpy(response+1,find_res);
					response[strlen(find_res)+1]='\0';
					send(connfd,response,strlen(find_res)+2,0);
				}
				else
					printf("Recv failed.\n");
			}
			else
				printf("Recv failed.\n");
		}
		else
			printf("Accept failed.\n");
	}
	return 0;
}
 
	