#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>


#define MAXROOM 100
#define BUFSIZE 80

int room_numbers[MAXROOM];
int north[MAXROOM];
int south[MAXROOM];
int west[MAXROOM];
int east[MAXROOM];
char* descriptions[MAXROOM];
int roomsize = 0;
int current_room = 0;
bool loadcomplete = false;

int get_room_index(int room_number)
{
	for (int i = 0; i <= roomsize; i++)
	{
		if (room_numbers[i] == room_number)
			return i;
	}
	return -1;
}

void free_descriptions()
{
	for(int i=0;i<roomsize;++i)
		free(descriptions[i]);
}


void loaddungeon(const char* path)
{

	FILE* fp=NULL;
	if (!path)
	{
		printf("Load file failed!\n");
		return;
	}
	fp = fopen(path, "r");
	if (!fp)
		printf("Load file failed!\n");
	else
	{
		free_descriptions();
		roomsize = 0;
		current_room = 0;
		bool failflag=false;
		while (!feof(fp))
		{
			char buffer[256];
			char* token;
			memset(buffer,0,sizeof(char)*256);
			fgets(buffer, 256, fp);
			if(!strcmp(buffer,"\r\n")|| !strcmp(buffer,"\n")){failflag=true;break;}
			token = strtok(buffer, " ");
			if(!token){failflag=true;break;}
			if(!(sscanf(token,"%d",&room_numbers[roomsize]) && room_numbers[roomsize]>0)){failflag=true;break;}
			token = strtok(NULL, "$");
			if(!token){failflag=true;break;}
			descriptions[roomsize] = (char*)malloc(sizeof(char) * 80);
			strcpy(descriptions[roomsize], token);
			token = strtok(NULL, " ");
			if(!token){failflag=true;break;}
			if(!(sscanf(token,"%d",&north[roomsize]) && (north[roomsize]>0 || north[roomsize]==-1))){failflag=true;break;}
			token = strtok(NULL, " ");
			if(!token){failflag=true;break;}
			if(!(sscanf(token,"%d",&south[roomsize]) && (south[roomsize]>0 || south[roomsize]==-1))){failflag=true;break;}
			token = strtok(NULL, " ");
			if(!token){failflag=true;break;}
			if(!(sscanf(token,"%d",&east[roomsize]) && (east[roomsize]>0 || east[roomsize]==-1))){failflag=true;break;}
			token = strtok(NULL, " ");
			if(!token){failflag=true;break;}
			if(!(sscanf(token,"%d",&west[roomsize]) && (west[roomsize]>0 || west[roomsize]==-1))){failflag=true;break;}
			roomsize++;
		}	
		if(!failflag)
			printf("%s\n", descriptions[current_room]);
		else
		{
			free_descriptions();
			printf("format error! everything will be cleared completely! please re-load with another file.\n");
			roomsize=0;
			loadcomplete=false;
		}
	}
}

void go_another_room(int new_room_number)
{
	int new_index = get_room_index(new_room_number);
	if (new_index != -1)
	{
		current_room = new_index;
		printf("%s\n",descriptions[current_room]);
	}
	else
		printf("You can't go there.\n");
}


void handle_command()
{
	for (;;)
	{
		printf("$ ");
		char cmd[128];
		scanf("%[^\n]", cmd);
		if (!strcmp(cmd, "quit"))break;
		if (strstr(cmd,"loaddungeon"))
		{
			char* temp = strtok(cmd, " ");
			temp = strtok(NULL, " ");
			loaddungeon(temp);
		}
		else
		{
			if (!roomsize)
				printf("No dungeon file loaded.\n");
			else if (!strcmp(cmd, "north"))
				go_another_room(north[current_room]);
			else if (!strcmp(cmd, "east"))
				go_another_room(east[current_room]);
			else if (!strcmp(cmd, "west"))
				go_another_room(west[current_room]);
			else if (!strcmp(cmd, "south"))
				go_another_room(south[current_room]);
			else
				printf("Wrong command, please re-enter.\n");
		}
		char c;
		while((c = getchar()) != '\n' && c != EOF);
	}

}



int main()
{
	handle_command();
	free_descriptions();
	return 0;
}
