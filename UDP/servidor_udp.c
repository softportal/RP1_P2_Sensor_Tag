/* FICHERO: servidor_udp.c
 * DESCRIPCION: codigo del servidor con sockets datagrama */

#include "common.h"

#define PUERTO_LOCAL PUERTO  /* puerto local en el servidor por el que se reciben los mensajes */

int main (int argc, char* argv[])
{
        int sockfd;
        struct sockaddr_in my_addr;     /* informacion de mi direccion */
        struct sockaddr_in their_addr;  /* informacion de la direccion del cliente */
        char buf[MAXDATASIZE];          /* buffer de recepcion */
        int numbytes;                   /* numero de bytes recibidos o enviados */
        struct idappdata *operation;    /* mensaje de operacion recibido */
        struct idappdata resultado;     /* mensaje de respuesta enviado */
        int error;                      /* indica la existencia de un error */
        int cont;
        size_t sin_size;

        /* crea el socket */
        if ((sockfd = socket (AF_INET, SOCK_DGRAM, 0)) == -1)
        {
                perror ("socket");
                exit (1);
        }

        my_addr.sin_family = AF_INET;  /* Familia: ordenacion de bytes de la maquina */
        my_addr.sin_port = htons (PUERTO_LOCAL);  /* Puerto: ordenacion de bytes de la red */
        my_addr.sin_addr.s_addr = INADDR_ANY;     /* IP: ordenacion de bytes de la red */
        memset (&(my_addr.sin_zero), '\0', 8);  /* Pone a cero el resto de la estructura */

        /* asigna el socket a un puerto local */
        if (bind (sockfd, (void*) &my_addr, sizeof (struct sockaddr_in)) == -1)
        {
                perror ("bind");
                exit (1);
        }

        /* recvfrom() loop... */
        while (1)
        {
                printf ("(servidor) esperando mensajes [puerto local %d]\n",
                        ntohs (my_addr.sin_port));

                /* recibe un mensaje de un cliente */
                memset (buf, '\0', MAXDATASIZE); /* Pone a cero el buffer inicialmente */
                sin_size = sizeof(struct sockaddr_in);
                if ((numbytes = recvfrom (sockfd, buf, MAXDATASIZE, 0,
                                          (void*)&their_addr, &sin_size))== -1)
                {
                        perror ("recvfrom");
                        continue;
                }
                printf("(servidor) mensaje recibido de IP %s puerto %d [longitud %d]\n",
                       inet_ntoa(their_addr.sin_addr), ntohs(their_addr.sin_port), numbytes);

                operation = (struct idappdata *) &buf;
                /* comprueba el n�mero de bytes recibidos */
                if ((numbytes < ID_HEADER_LEN) || (numbytes != operation->len + ID_HEADER_LEN))
                {
                        printf ("(servidor) unidad de datos recibida de manera incompleta \n");
                        continue;
                }
                else
                        printf ("(servidor) operacion recibida [op 0x%x id %d longitud %d]\n",
                                operation->op, operation->id, operation->len);

                /* realiza operacion solicitada por el cliente */
                error = 0;
                resultado.id = operation->id; /* id */
                switch (operation->op)
                {
                case OP_MINUSCULAS: /* minusculas */
                        resultado.op = OP_RESULTADO; /* op */
                        for(cont = 0; cont < operation->len; cont++){ /* data */
                                if (isupper(operation->data[cont]))
                                        resultado.data[cont] = tolower(operation->data[cont]);
                                else
                                        resultado.data[cont] = operation->data[cont];
                        }
                        resultado.len = cont; /* len */
                        break;
                case OP_MAYUSCULAS: /* mayusculas */
                        resultado.op = OP_RESULTADO; /* op */
                        for(cont = 0; cont < operation->len; cont++){ /* data */
                                if (islower(operation->data[cont]))
                                        resultado.data[cont] = toupper(operation->data[cont]);
                                else
                                        resultado.data[cont] = operation->data[cont];
                        }
                        resultado.len = cont; /* len */
                        break;
                case OP_SENSOR_READ:
                        printf("\n-------\n");
                        printf("%s", operation->data);
                        printf("\n-------\n");

                        break;
                default: /* operacion desconocida */
                        resultado.op = OP_ERROR; /* op */
                        strcpy(resultado.data, "Operacion desconocida");  /* data */
                        resultado.len = strlen (resultado.data);  /* len */
                        error = 1;
                        break;
                }

        }

        /* cierra socket (no se ejecuta nunca) */
        close (sockfd);

        return 0;
}
