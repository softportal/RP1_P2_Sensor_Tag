# RP1 Práctica 2: Bluetooth Low Energy
##  Tareas  


###  1
Habilita las notificaciones de temperatura para que se reciba un mensaje cada vez que ésta cambia. Intenta modificar también la frecuencia de refresco del sensor.

Vamos a activar el sensor de temperatura Desde la shell:
    
    $ gatttool -b B0:91:22:EA:81:04 -a 0x27 --char-write -n 01
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

Para poder usar gatttool sin el modo interactivo usamos la siguiente sintaxis:

    $ gatttool -b B0:91:22:EA:81:04 --characteristics


### 3
Repite el proceso anterior con algún otro sensor de entre los disponibles en el SensorTag. Puedes encontrar documentación sobre cómo tratar los datos y los UUID de las características de cada sensor en la guía de usuario del SensorTag (http://processors.wiki.ti.com/index.php/CC2650_SensorTag_User’s_Guide.). 

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
