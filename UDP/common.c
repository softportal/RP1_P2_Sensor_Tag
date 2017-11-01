#include "common.h"

int execute_command(char *command, char *output)
{
    printf("\nexec %s\n", command);
    strcpy(output, "aqui va el resultado");  /* data */
    return 0;

}
