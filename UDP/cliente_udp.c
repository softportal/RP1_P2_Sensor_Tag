/* FICHERO: cliente_udp.c
 * DESCRIPCION: codigo del cliente con sockets datagrama */

#include "common.h"

#define COMMAND_LENGTH 64
#define PUERTO_REMOTO PUERTO /* puerto remoto en el servidor al que se envian los mensajes */
#define MAC "B0:91:22:EA:81:04"

int main (int argc, char *argv[])
{
        int sockfd;
        struct sockaddr_in their_addr;  /* informacion de la direccion del servidor */
        struct sockaddr_in my_addr;  /* informacion de la direccion del servidor */
        char buf[MAXDATASIZE];          /* buffer de recepcion */
        struct idappdata operation;     /* mensaje de operacion enviado */
        struct idappdata *resultado;    /* mensaje de respuesta recibido */
        int numbytes;                   /* numero de bytes recibidos o enviados */
        size_t sin_size;
        char command[COMMAND_LENGTH];
        char command_test[] = "cat temperature";
        char out_buff[] = "aqui va a venir el resultado biiiitch";
        char std_out[MAXDATASIZE - HEADER_LEN];

        if (argc != 3)
        {
                fprintf (stderr, "uso: cliente hostname sensor\n");
                exit (1);
        }

        sprintf(command, "gatttool -b %s -a %s --char-read", MAC, argv[2]);
        printf("la orden parseada es: %s\n", command_test);

        /* crea el socket */
        if ((sockfd = socket (AF_INET, SOCK_DGRAM, 0)) == -1)
        {
                perror ("socket");
                exit (1);
        }

        their_addr.sin_family = AF_INET;  /* Familia: ordenacion de bytes de la maquina */
        their_addr.sin_port = htons (PUERTO_REMOTO);    /* Puerto: ordenacion de bytes de la red */
        their_addr.sin_addr.s_addr =             /* IP: ordenacion de bytes de la red */
            inet_addr (argv[1]);
        memset (&(their_addr.sin_zero), 0, 8);  /* Pone a cero el resto de la estructura */

        my_addr.sin_family = AF_INET;  /* Familia: ordenacion de bytes de la maquina */
        my_addr.sin_port = htons (33333);    /* Puerto: ordenacion de bytes de la red */
        my_addr.sin_addr.s_addr = INADDR_ANY;            /* IP: ordenacion de bytes de la red */

	    bind( sockfd, (void*) &my_addr, sizeof( struct sockaddr_in) );

        memset (buf, '\0', MAXDATASIZE); /* Pone a cero el buffer inicialmente */

        /* envia mensaje de operacion al servidor */
        operation.op = OP_SENSOR_READ;   /* op */
        operation.id = 1; /* id */

        sprintf(operation.data,"read request\n\n  MAC: %s\n  sensor: %s\n  message: %s \n",MAC, argv[2], out_buff);
        //strcpy(operation.data, "Esta es Una PRUEBA");  /* data */
        operation.len = strlen (operation.data);  /* len */
        if ((numbytes = sendto (sockfd, (char *) &operation,
                                operation.len + ID_HEADER_LEN, 0,
                                (void*)&their_addr,
                                sizeof(struct sockaddr_in))) == -1)
        {
                perror ("send");
                exit (1);
        }
        else
                printf ("(cliente) mensaje enviado al servidor [longitud %d]\n", numbytes);

        printf ("(cliente) operacion enviada [op 0x%x id %d longitud %d]\n",
                operation.op, operation.id, operation.len);

        /* espera resultado de la operacion */

        /* cierra el socket */
        close (sockfd);

        return 0;
}
