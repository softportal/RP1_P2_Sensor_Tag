# RP1 Práctica 2: Bluetooth Low Energy
##  Cuestiones
### Investiga en qué consiste la técnica de modulación por desplazamiento de frecuencia gaussiana (GFSK) y la de espectro ensanchado por salto de frecuencia (FHSS).  
### Comprueba que, tras el emparejamiento con el SensorTag, el proceso de publicación de anuncios GAP finaliza. 
### Analiza el resto de perfiles y servicios ofrecidos por Bluetooth SIG como estándares. ¿Existe alguno que hayas utilizado (aun sin saberlo) en algún dispositivo Bluetooth que poseas? 
### Busca otros servicios que te resulten de interés y descríbelos (fíjate en sus características soportadas y requeridas). 
### En el proceso de arranque, ¿cuántos servicios y características reporta la aplicación al analizar el dispositivo SensorTag? Interactúa y experimenta con la información reportada por la aplicación. Comprueba que todos los sensores y botones funcionan correctamente y que la información reportada es correcta. 
### Estudia la ayuda de la herramienta hcitool para determinar sus opciones principales.  
### Desde la shell interactiva, muestra los comandos disponibles en gatttool usando la orden help.  
##  Tareas  
###  1
Habilita las notificaciones de temperatura para que se reciba un mensaje cada vez que ésta cambia. Intenta modificar también la frecuencia de refresco del sensor. Crea un pequeño programa C que muestre la temperatura ambiente y del objeto a partir de los cuatro bytes recibidos desde el sensor. El programa recibirá como argumento los cuatro bytes devueltos por una petición al SensorTag, y mostrará por pantalla la temperatura ambiente y del objeto en grados centígrados. Repite el proceso anterior con algún otro sensor de entre los disponibles en el SensorTag. Puedes encontrar documentación sobre cómo tratar los datos y los UUID de las características de cada sensor en la guía de usuario del SensorTag (http://processors.wiki.ti.com/index.php/CC2650_SensorTag_User’s_Guide.). Diseña y escribe un sistema cliente/servidor en el que el cliente se ejecute en la Ci40 y el servidor en la máquina virtual. El cliente realizará consultas para el valor de un sensor determinado (proporcionado a través de línea de comandos por el usuario) a través de BLE, y lo enviará a través de UDP al servidor junto con información sobre qué sensor se está monitorizando y la dirección hardware del dispositivo sensor. Aunque existe una API para desarrollo de aplicaciones BLE en Linux (Bluez), simplificaremos el desarrollo mediante el uso directo de la herramienta gatttool desde el propio programa en C. Para ello, utiliza la llamada al sistema popen (por ejemplo),que permite ejecutar directamente los comandos pasados como parámetro. Un posible modo de funcionamiento del programa cliente sería el siguiente:

    ./cliente sensor IP_destino PUERTO_destino con: 

    sensor: una clave única para consultar un sensor específico de entre los disponibles en el SensorTag.
    IPdestino: dirección lógica de escucha del servidor UDP.
    PUERTOdestino: número de puerto de escucha del servidor UDP.

Internamente, el programa invocará a la aplicación gatttool con los parámetros deseados. Ten en cuenta que esta invocación no debe ser interactiva, por lo que tendrás que estudiar cómo leer los valores de los sensores con llamadas individuales a la herramienta. El servidor, por su parte, simplemente permanecerá a la escucha de posibles peticiones,y mostrará por pantalla la información recibida (por ejemplo, dirección física del SensorTag, tipo de sensor y valor recibido. 
###  2
Realiza un proceso de compilación y descarga del firmware básico a partir de los
proyectos que se te proporcionan. Para asegurar que el firmware que descargas es el
que acabas de generar, busca en los proyectos el lugar en el que se define la versión
del mismo (fichero sensortag_revision.h), y modifica la cadena para crear una nueva
versión. Por ejemplo, si ahora mismo estás ejecutando la versión 1.30, conviértela en
la versión 2.00. Una vez descargado, comprueba que todo funciona correctamente
desde la aplicación móvil o utilizando gatttool y que, efectivamente, la versión
del firmware visible desde la aplicación móvil es la correcta.

### 3
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
