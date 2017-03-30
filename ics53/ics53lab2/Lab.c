#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <errno.h>
#include <unistd.h>
#define MAX_NUMBERS 10
#define MAX_BUFFER 256
int numbers[MAX_NUMBERS];
int size=0;
int target=0;
int root_pid=0;
int memid=0;
typedef struct IndexRecorder
{
	int size;
	int record[MAX_NUMBERS];
}IR;
IR* result=NULL;

void Find(int lo,int hi)
{
	if(lo==hi)
	{
		if(numbers[lo]==target)
		{
			result->record[result->size++]=lo;
		}
		return;
	}
	int mid=(lo+hi)/2;
	int pid1,pid2;
	pid1=fork();
	if(pid1==0)
		Find(lo,mid);
	else
	{
		pid2=fork();
		if(pid2==0)
			Find(mid+1,hi);
	}
	while(wait(NULL)!=-1);
}  




int main(int argc,char *argv[])
{
	if(argc!=3)
	{
		printf("Invaild number of arguments.\n");
		return -1;
	}
	if(!sscanf(argv[2],"%d",&target))
	{
		printf("Invaild number to search.\n");
		return -1;
	}
	FILE* fp=fopen(argv[1],"r");
	if(!fp)
	{
		printf("Open file failed.\n");
		return -1;
	}
	else
	{
		char buffer[MAX_BUFFER];
		char* fgets_result=fgets(buffer,MAX_BUFFER,fp);
		if(!strcmp(buffer,"\n") || fgets_result==NULL)
		{
			printf("The first line is empty.\n");
			return -1;
		}
		char* token=strtok(buffer," ");
		while(token && strcmp(token,"\n"))
		{
			int num;
			if(!sscanf(token,"%d",&num))
			{
				printf("Invaild Number.\n");
				return -1;
			}
			if(size==10)
			{
				printf("Amount of numbers exceeds the limit of 10!\n");
				return -1;
			}
			numbers[size++]=num;
			token=strtok(NULL," ");
		}
		fclose(fp);
		if(size==0)
		{
			printf("There is no number in the first line of the file.\n");
			return -1;
		}
		int lo=0,hi=size-1;
		pid_t pid;
		memid=shmget(0,sizeof(IR),IPC_CREAT|0660);
		void* temp=shmat(memid,NULL,0);
		if(temp==(void*)-1)
		{
			printf("shmat failed.\n");
			return -1;
		}
		result=(IR*)temp;
		result->size=0;
		root_pid=getpid();
		Find(lo,hi);
		if(getpid()==root_pid)
		{
			if(result->size)
			{
				for(int i=0;i<result->size;i++)
					printf("%d ",result->record[i]);
				printf("\n");
			}
			else
				printf("-1\n");
			int status=shmctl(memid,IPC_RMID,0);
			if(status==-1)
			{
				printf("shmctl failed\n");
			}
		}
	}
	return 0;
}






