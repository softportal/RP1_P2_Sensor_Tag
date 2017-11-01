#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <pthread.h>
#include <arpa/inet.h>
#include <ctype.h>

#define PUERTO 3490     /* puerto en el servidor */
#define BACKLOG 10      /* numero maximo de conexiones pendientes en cola */
#define FORMAT 128
#define MAXDATASIZE (FORMAT*4) /* maximo numero de bytes que podemos recibir */


#define ID_HEADER_LEN (sizeof (unsigned short) * 3)
#define RESPONSE_SIZE (MAXDATASIZE - ID_HEADER_LEN - FORMAT)

/* formato de la unidad de datos de aplicacion para Datagramas*/
struct idappdata
{
        unsigned short op;                        /* codigo de operacion */
        unsigned short id;                        /* identificador */
        unsigned short len;                       /* longitud de datos */
        char data[MAXDATASIZE - ID_HEADER_LEN];   /* datos */
};


/* codigos de operacion (appdata.op) */
#define OP_SENSOR_READ          0x0003  /* sensor read */
#define OP_ERROR                0xFFFF  /* error */

int execute_command(char *command, char *output);
