#include "common.h"


int execute_command(char *command,char *output){
	int errn,stat;
	FILE *fp;
	char path[RESPONSE_SIZE];
	fp=popen(command,"r");
	if(fp==NULL){
		errn=errno;
		printf("popen\t:%s",strerror(errn));
		exit(EXIT_FAILURE);
	}
	while (fgets(path, RESPONSE_SIZE, fp) != NULL){
	  //  sprintf(output,"%s", path);
		strcat(output,path);
	}
	stat=pclose(fp);
	if(stat==-1){
		errn=errno;
		printf("pclose\t:%s",strerror(errn));
		exit(EXIT_FAILURE);
	}
	return 0;

}

