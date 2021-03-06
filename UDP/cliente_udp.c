/* FICHERO: cliente_udp.c
 * DESCRIPCION: codigo del cliente con sockets datagrama */

#include "common.h"

#define PUERTO_REMOTO PUERTO /* puerto remoto en el servidor al que se envian los mensajes */

int main (int argc, char *argv[])
{
        int sockfd;
        struct sockaddr_in their_addr;  /* informacion de la direccion del servidor */
        struct sockaddr_in my_addr;  /* informacion de la direccion del servidor */
        char buf[MAXDATASIZE];          /* buffer de recepcion */
        struct idappdata operation;     /* mensaje de operacion enviado */
        int numbytes;                   /* numero de bytes recibidos o enviados */
        struct hndrel relations[2];
        size_t sin_size;
        char command[COMMAND_LENGTH];
        char command_test[] = "cat temperature";

        char std_out[RESPONSE_SIZE];
        memset (std_out, '\0', RESPONSE_SIZE);  /* Pone a cero el resto de la estructura */


        if (argc != 3)
        {
                fprintf (stderr, "uso: cliente hostname sensor\n");
                exit (1);
        }



        inithndrel(relations);
        if (activate(relations, argv[2]) == -1)
        {
            pp("sensors available: 0x24(temp) 0x2c(hum)");
            exit(-1);
        }

        sprintf(command, "gatttool -b %s -a %s --char-read", MAC, argv[2]);

        if (execute_command(command, std_out) !=0 )
        {
            pp("couldnt execute command");
            exit (1);
        }

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

        sprintf(operation.data,"read request\n\n  MAC: %s\n  sensor: %s\n  message: %s \n",MAC, argv[2], std_out);
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


        /* cierra el socket */
        close (sockfd);

        return 0;
}
