## Instituto Tecnológico de Costa Rica
## Área de Ingeniería en Computadores
## Algoritmos y Estructuras de Datos II
## Primer Semestre 2020
## Proyecto 3 - Manejador de Versiones GOT
### Estudiantes:
### Simón Fallas Villalobos (2019324313)
### David Quesada Calderón (2016246935)

## Descripción:

Got es un manejador de versiones que registra los cambios efectuados en archivos de computadoras permitiendo la colaboración entre personas. 
Utiliza un modelo basado en Subversion para administrar los proyectos. El cliente esta desarrollado en C++ y se puede utilizar mediante comandos de consola. Los commits se envian a un servidor desarrollado con Node.js, quien se encarga de almacenarlos en una base de datos implementada con MySQL.

## Planificación y administración del proyecto:

La administración del proyecto se relizó utilizando Jira Software, la cual puede accederse mediante este [link](https://simonfv.atlassian.net/jira/software/projects/GS/boards/6)

### Historias de Usuario:
* Como usuario, quiero que el cliente Got se conecte a un API para almacenar los cambios en una base de datos con MySQL.
* Como usuario, quiero que el controlador de versiones utilice un sistema SVN.
* Como usuario, quiero que se mantenga la integridad y seguridad de los archivos al guardarse en el servidor.
* Como usuario, quiero que se verifiquen los datos que se envían entre el cliente y el servidor para encontrar posibles errores.
* Como usuario, quiero utilizar el control de versiones Got mediante comandos ingresados por la terminal.

## Diagramas:
### Diagrama de Clases:
![GOT-diagrama-clases](https://user-images.githubusercontent.com/47420204/90317417-a0369f00-dee6-11ea-8d08-a0e3db6bd5ee.png)

### Diagrama de Arquitectura:
![Got-arquitectura](https://user-images.githubusercontent.com/47420204/90317422-adec2480-dee6-11ea-8dbe-dab629023e41.png)

## Estructuras y algoritmos implementados:
### Codificación Huffman:
Para la compresión del contenido de los archivos se utilizó el algoritmo Huffman. Este es un algoritmo de codificación utilizado para la compresión de datos del tipo *loseless*, es decir, se mantiene la integridad de los datos al ser comprimidos y descomprimidos.
La forma en que trabaja el algoritmo para comprimir se resume en tres pasos:
* Primero se saca una tabla de frecuencias donde se listan el número de veces que aparece un caracter dentro del conjunto.
* Luego se genera un árbol binario a partir de esta tabla de frecuencias de forma que los caracteres con mayores frecuencias se situan más cerca de la raiz. La siguiente imagen muestra un ejemplo de como se vería un árbol de Huffman:
![Arbol Huffman](https://upload.wikimedia.org/wikipedia/commons/thumb/2/2a/Arbol_de_Huffman.svg/1920px-Arbol_de_Huffman.svg.png)
* Por último, se generan códigos con valores binarios para cada caracter en el árbol. Esto se hace recorriendo el árbol hasta llegar a un nodo sin hijos y agregando los valores de 0 si se avanza a la izquierda o 1 si se avanza hacia la derecha. Entonces, del ejemplo anterior el código para el caracter E sería 100. Para comprimir el conjunto, se debe solamente reemplazar cada caracter por su respectivo código, generando una cadena de unos y ceros. Para descomprimir solo se debe realizar este último paso de forma inversa.

### MD5:
MD5 es un algoritmo de reducción criptográfico de 128 bits. Se suele utilizar para comprobar la integridad de los archivos cuando se envían o copian. Para este proyecto se utilizó MD5 para comprobar la integridad de los commits, utilizado como un *checksum*. El algoritmo funciona generando un código similar al siguiente: 5df9f63916ebf8528697b629022993e8. Este mismo código se genera siempre que se ejecute el mismo algoritmo sobre el mismo grupo de datos, por lo que se puede comprobar fácilmente si se corrompió la información, ya que se generaría un código totalmente diferente.

### ASCII:
Código ASCII es una representación numérica de siete bits de un carácter. Durante este proyeto se utilizó esta codificación para enviar de forma segura los códigos utilizados por el algoritmo Huffman, ya que se notó que se generaban algunas pérdidas con algunos caracteres especiales al ser enviados desde el cliente al servidor y viceversa.

### Árbol Binario:
Se inmplemento un árbol binario de búsqueda para utilizarlo con el algoritmo Huffman. Es árbol tiene una estructura como la mostrada anteriormente. Cada nodo es una instancia en el código, y estos se enlazan entre sí mediante punteros. Cada nodo tiene entonces, tres punteros, dos para sus dos nodos hijos, y uno para el nodo padre.

### Singleton:
Para controlar la instanciación de la clase Cliente y también para facilitar el acceso a sus atributos y métodos, esta se implementó con el patró de diseño Singleton. Este patrón permite restringir una clase para que solo se pueda generar una instancia de esta. Además, facilita el acceso a dicha instancia desde cualquier sitio dentro del código.
