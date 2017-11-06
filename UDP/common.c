#include "common.h"

void pp(char * input){
    char *output[strlen(input) + 3];

    sprintf(output,"\n%s\n",input);
    printf("%s", output);
}

int execute_command(char *command,char *output){
	int errn,stat;
	FILE *fp;
	char path[RESPONSE_SIZE];
	fp=popen(command,"r");
	if(fp==NULL){
		errn=errno;
		printf("popen\t:%s",strerror(errn));
        return -1;
	}
	while (fgets(path, RESPONSE_SIZE, fp) != NULL){
	  //  sprintf(output,"%s", path);
		strcat(output,path);
	}
	stat=pclose(fp);
	if(stat==-1){
		errn=errno;
		printf("pclose\t:%s",strerror(errn));
        return -1;
	}
	return 0;

}


void inithndrel(struct hndrel *relations)
{
    //temp
    strcpy(relations[0].write, "0x27");
    strcpy(relations[0].read,  "0x24");

    //hum
    strcpy(relations[1].write, "0x2f");
    strcpy(relations[1].read,  "0x2c");
}


int activate(struct hndrel *relations, char *sensor)
{
    char output[RESPONSE_SIZE];
    char command[COMMAND_LENGTH];
    for (int i = 0; i < RELATIONS; i++)

    {
        if (strncmp(relations[i].read, sensor, 4) == 0)
        {
            sprintf(command,"gatttool -b %s -a %s --char-write-req -n 01",MAC, relations[i].write);
            return execute_command(command, output);
        }
    }
    return -1;
}
