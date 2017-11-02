#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#define RESPONSE_SIZE 80 // no copiar a common


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


int main(int args,char *argv[]){
	char cmd,out;
	sprintf(&cmd,"%s %s",argv[1],argv[2]);
/*	printf("%s\n",&out); 
	exit(EXIT_SUCCESS);*/
	execute_command(&cmd,&out);
	printf("%s\n",&out);
	exit(EXIT_SUCCESS);
}
