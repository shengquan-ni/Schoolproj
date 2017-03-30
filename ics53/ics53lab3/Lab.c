#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define HEAP_SIZE 128
#define MAX_BLOCK_SIZE 128
#define MAX_BLOCK 256
unsigned char* heap;
bool exitflag=false;
int allocated=0;


void InitHeap()
{
	heap=malloc(HEAP_SIZE);
	heap[0]=0;
	heap[1]=254;
}


void Allocate(int size)
{
	if(size<=0){printf("allocation size should greater than 0!\n");return;}
	int actual_size=size+2;
	if(allocated>MAX_BLOCK || actual_size>MAX_BLOCK_SIZE)
	{
		printf("Allocation failed\n");
		return;
	}
	int start=0;
	while(start<HEAP_SIZE-1)
	{
		int block_header2=heap[start+1];
		int block_size=(block_header2>>1)+1;
		int blocknum=heap[start];
		if(!(block_header2 & 0x1) && block_size >=actual_size)
		{
			if(block_size-actual_size<=2)
				actual_size=block_size;
			heap[start]=++allocated;
			heap[start+1]=((actual_size-1)<<1)+1;
			if(block_size>actual_size)
			{
				heap[start+actual_size]=blocknum;
				heap[start+actual_size+1]=(block_size-actual_size-1)<<1;
			}
			printf("%d\n",allocated);
			return;
		}
		start+=block_size;
	}
	printf("No block available\n");
}

void Free(int blocknum)
{
	if(blocknum<=0){printf("block number must be a positive integer!\n");return;}
	int start=0;
	while(start<HEAP_SIZE-1)
	{
		if(heap[start]==blocknum && (heap[start+1]&0x1))
		{
			--heap[start+1];
			return;
		}
		start+=1+(heap[start+1]>>1);
	}
	printf("Block not found.\n");
	return;
}

void ShowBlockList()
{
	int start=0;
	printf("Size Allocated Start           End           \n");
	while(start<HEAP_SIZE-1)
	{
		printf("%-5d%-10s%-16p%-16p\n",1+(heap[start+1]>>1),((heap[start+1]& 0x1)?"yes":"no"),heap+start,heap+start+(heap[start+1]>>1));
		start+=1+(heap[start+1]>>1);
	}
}


void WriteHeap(int blocknum,char data,int times)
{
	if(blocknum<=0){printf("block number must be a positive integer!\n");return;}
	if(times<0){printf("the number of copies of the character must >= 0!\n");return;}
	int start=0;
	while(start<HEAP_SIZE-1)
	{
		if(heap[start]==blocknum && (heap[start+1] & 0x1))
		{
			if(times>(heap[start+1]>>1)-1)
			{
				printf("Write too big.\n");
				return;
			}
			for(int i=0;i<times;i++)
				heap[start+2+i]=data;
			return;
		}
		start+=1+(heap[start+1]>>1);
	}
	printf("Block not found.\n");
}


void PrintHeap(int blocknum,int size)
{
	if(blocknum<=0){printf("block number must be a positive integer!\n");return;}
	if(size<0){printf("the number of bytes to print must >= 0!\n");return;}
	int start=0;
	while(start<HEAP_SIZE-1)
	{
		if(heap[start]==blocknum && (heap[start+1] & 0x1))
		{
			if(start+size+1>=128){printf("index will be greater than 127!\n");return;}
			for(int i=0;i<size;i++)
				printf("%c",heap[start+2+i]);
			printf("\n");
			return;
		}
		start+=1+(heap[start+1]>>1);
	}
	printf("Block not found.\n");
}

void PrintHeader(int blocknum)
{
	if(blocknum<=0){printf("block number must be a positive integer!\n");return;}
	int start=0;
	while(start<HEAP_SIZE-1)
	{
		if(heap[start]==blocknum && (heap[start+1] & 0x1))
		{
			printf("%02x%02x\n",heap[start],heap[start+1]);
			return;
		}
		start+=1+(heap[start+1]>>1);
	}
	printf("Block not found.\n");
}


bool standardize_input(char* input,char* cmd,int* args,int max_args,int* num)
{
	char* token=strtok(input," ");
	strcpy(cmd,token);
	int index=0;
	while(token=strtok(NULL," "))
	{
		if(index==max_args)
		{
			printf("Command format error\n");
			return false;
		}
		if(index==1 && !strcmp(cmd,"writeheap"))
		{
			if(strlen(token)!=1 || !sscanf(token,"%c",&args[index++]))
			{
				printf("Command format error\n");
				return false;
			}	
		}
		else if(!sscanf(token,"%d",&args[index++]))
		{
			printf("Command format error\n");
			return false;
		}
	}
	*num=index;
	return true;
}

void process_command(const char* cmd,int* args,int num)
{
	if(!strcmp(cmd,"allocate") && num==1)
		Allocate(args[0]);
	else if(!strcmp(cmd,"free") && num==1)
		Free(args[0]);
	else if(!strcmp(cmd,"blocklist") && num==0)
		ShowBlockList();
	else if(!strcmp(cmd,"writeheap") && num==3)
		WriteHeap(args[0],(char)args[1],args[2]);
	else if(!strcmp(cmd,"printheap") && num==2)
		PrintHeap(args[0],args[1]);
	else if(!strcmp(cmd,"printheader") && num==1)
		PrintHeader(args[0]);
	else if(!strcmp(cmd,"quit") && num==0)
		exitflag=true;
	else
		printf("Wrong command, please re-enter.\n");
}

bool all_blank(const char* str)
{
	for(int i=0;i<strlen(str);++i)
		if(str[i]!=' ')return false;
	return true;
}

int main()
{
	InitHeap();
	for(;;)
	{
		printf(">");
		char line[256];
		fgets(line,256,stdin);
		if(strlen(line)==0 || !strcmp(line,"\n")){printf("Wrong command, please re-enter.\n");continue;}
		line[strlen(line)-1]='\0';
		if(all_blank(line)){printf("Wrong command, please re-enter.\n");continue;}
		char cmd[32];
		int args[3];
		int numofargs=0;
		if(standardize_input(line,cmd,args,3,&numofargs))
			process_command(cmd,args,numofargs);
		if(exitflag)break;
	}
	free(heap);
	return 0;
}


