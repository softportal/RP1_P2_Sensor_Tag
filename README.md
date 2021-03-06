# RP1 Práctica 2: Bluetooth Low Energy
##  Tareas  


###  1
Habilita las notificaciones de temperatura para que se reciba un mensaje cada vez que ésta cambia. Intenta modificar también la frecuencia de refresco del sensor.

Vamos a activar el sensor de temperatura Desde la shell.
Para poder usar gatttool sin el modo interactivo usamos la siguiente sintaxis:

    $ gatttool -b B0:91:22:EA:81:04 --characteristics
    
    $ gatttool -b B0:91:22:EA:81:04 -a 0x27 --char-write-req -n 01
    $ gatttool -b B0:91:22:EA:81:04 -a 0x24 --char-read

A partir de ahora podemos leer el handler 0x24 para saber la temperatura en hexadimal (ojo, los valores vienen cambiados).
  
Ahora vamos a activar las notificaciones usando el modo interactivo de gatttool.

Modo Interactivo:

    char-write-cmd 0x25 01:00

        Notification handle = 0x0024 value: d0 05 b8 0c 
        Notification handle = 0x0024 value: 38 05 b8 0c 
        Notification handle = 0x0024 value: b8 05 b8 0c 
        Notification handle = 0x0024 value: 80 05 b8 0c 
        Notification handle = 0x0024 value: 7c 05 b8 0c 
        Notification handle = 0x0024 value: 14 06 b8 0c 
        Notification handle = 0x0024 value: 88 06 b8 0c 
        Notification handle = 0x0024 value: b4 05 b4 0c 
        Notification handle = 0x0024 value: 58 06 b4 0c 
        Notification handle = 0x0024 value: 9c 06 b4 0c 
        Notification handle = 0x0024 value: bc 06 b4 0c 
        Notification handle = 0x0024 value: 94 07 b0 0c 
        Notification handle = 0x0024 value: 54 07 ac 0c 
        Notification handle = 0x0024 value: 64 07 a8 0c 
        Notification handle = 0x0024 value: ec 06 a8 0c 
        Notification handle = 0x0024 value: 4c 07 a4 0c 
        Notification handle = 0x0024 value: 28 06 a4 0c 


### 2
Crea un pequeño programa C que muestre la temperatura ambiente y del objeto a partir de los cuatro bytes recibidos desde el sensor. El programa recibirá como argumento los cuatro bytes devueltos por una petición al SensorTag, y mostrará por pantalla la temperatura ambiente y del objeto en grados centígrados. 




### 3
Repite el proceso anterior con algún otro sensor de entre los disponibles en el SensorTag. Puedes encontrar documentación sobre cómo tratar los datos y los UUID de las características de cada sensor en la guía de usuario del SensorTag (http://processors.wiki.ti.com/index.php/CC2650_SensorTag_User’s_Guide.). 

Para esta parte primero vamos a descubrir cuales son los handlers que hay que manejar, para ello primero acudimos a la wiki o al fichero de configuración del sensor de humedad

info          | value
--------------|-------------------
Data          | AA21* 	R/N 	4 	
Notification  |	2902 	R/W 	
Configuration | AA22* 	R/W 	
Period 	AA23* | R/W 	1

ya sabemos los UUID que nos dirán los handlers, ahora mediante BLE y nuestra ci40:

    $ mkdir sensortag
    $ gatttool -b B0:91:22:EA:81:04 --char-desc > chardesc
    $ cat chardesc | grep aa22
    handle = 0x002f, uuid = f000aa22-0451-4000-b000-000000000000
    $ cat chardesc | grep aa21
    handle = 0x002c, uuid = f000aa21-0451-4000-b000-000000000000

Ya sabemos la confiruación la escribimos en 0x002f y la lectura en 0x002c!


Vamos a activar el sensor de humedad (todo desde el modo interactivo:

    [B0:91:22:EA:81:04][LE]> char-write-cmd 0x2f 01
    [B0:91:22:EA:81:04][LE]> char-read-hnd 0x2c
    Characteristic value/descriptor: 3c 6f c8 2d 


### 4
Diseña y escribe un sistema cliente/servidor en el que el cliente se ejecute en la Ci40 y el servidor en la máquina virtual. El cliente realizará consultas para el valor de un sensor determinado (proporcionado a través de línea de comandos por el usuario) a través de BLE, y lo enviará a través de UDP al servidor junto con información sobre qué sensor se está monitorizando y la dirección hardware del dispositivo sensor. Aunque existe una API para desarrollo de aplicaciones BLE en Linux (Bluez), simplificaremos el desarrollo mediante el uso directo de la herramienta gatttool desde el propio programa en C. Para ello, utiliza la llamada al sistema popen (por ejemplo),que permite ejecutar directamente los comandos pasados como parámetro. Un posible modo de funcionamiento del programa cliente sería el siguiente:

    ./cliente sensor IP_destino PUERTO_destino con: 

    sensor: una clave única para consultar un sensor específico de entre los disponibles en el SensorTag.
    IPdestino: dirección lógica de escucha del servidor UDP.
    PUERTOdestino: número de puerto de escucha del servidor UDP.

Internamente, el programa invocará a la aplicación gatttool con los parámetros deseados. Ten en cuenta que esta invocación no debe ser interactiva, por lo que tendrás que estudiar cómo leer los valores de los sensores con llamadas individuales a la herramienta. El servidor, por su parte, simplemente permanecerá a la escucha de posibles peticiones,y mostrará por pantalla la información recibida (por ejemplo, dirección física del SensorTag, tipo de sensor y valor recibido. 
###  5
Realiza un proceso de compilación y descarga del firmware básico a partir de los
proyectos que se te proporcionan. Para asegurar que el firmware que descargas es el
que acabas de generar, busca en los proyectos el lugar en el que se define la versión
del mismo (fichero sensortag_revision.h), y modifica la cadena para crear una nueva
versión. Por ejemplo, si ahora mismo estás ejecutando la versión 1.30, conviértela en
la versión 2.00. Una vez descargado, comprueba que todo funciona correctamente
desde la aplicación móvil o utilizando gatttool y que, efectivamente, la versión
del firmware visible desde la aplicación móvil es la correcta.

Para esta tarea lo único que haremos será abrir la maquina virtual para acceder a los proyectos.
Ctrl-alt-T

    $ vim $(find ~/ti | grep sensortag_revision)
 
 Buscamos la parte de la versión y la cambiamos por 2.00
 
        #if defined (CC1350_LAUNCHXL) | defined (CC2650_LAUNCHXL)
        #define FW_VERSION      1.20
        #elif defined (CC1350STK) | defined (CC2650STK)
        #define FW_VERSION      2.00
        #endi
        
A continuación hemos decidido usar el code composer sobre workspace para compilar los proyectos necesitados (app y stack).
volvemos a la consola:

        $ cd ~/workspace
        $ mkdir build && cp $(find . | egrep *.hex) build)
        $ cd build
        $ python /home/user-iot/.local/bin/hexmerge.py -o SENSORTAG_CUSTOM.hex \
                                                            -r 0000:1FFFF \
          sensortag_cc2650stk_app.hex:0000:1EFFF sensortag_cc2650stk_stack.hex \
          bim_extflash.hex:0000:1FFFF --overlap=error

Ya tenemos nuestro binario preparado en SENSORTAG_CUSTOM.hex, solo tenemos que abrir uniflash y flashear nuestro sensortag. Una vez reiniciado (el sensortag) se puede comprobar satisfactoriamente desde el movil que la versión apunta a 2.00.

### 6
Estudia el proceso completo de configuración y publicación del sensor de temperatura,
incluyendo sus características, codificación de los datos, configuración, período
de muestreo y codificación.
A continuación, se pide, como tarea principal asociada a esta práctica, la adaptación
del servicio de monitorización de humedad relativa para añadir un nuevo dato a
los (dos) que ya se publicitan vía BLE –temperatura y humedad relativa–: la sensación
térmica.
La sensación térmica se obtiene combinando los datos de temperatura y humedad
según la Tabla 8. Debido a que la tabla únicamente incluye conversiones para valores
de temperatura y humedad enteros y dentro de un rango determinado, se deja
libertad al alumno para realizar la conversión que se crea conveniente en caso de
valores con decimales o fuera de rango.
Esta funcionalidad deberá ser integrada y consultada en el el sistema cliente/servidor
que se solicita como primer entregable de la práctica.
