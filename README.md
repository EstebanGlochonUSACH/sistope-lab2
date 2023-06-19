# sistope-lab1
Laboratorio 1 de Sistemas Operativos

## Enunciado

En este laboratorio crearemos un "reconocedor", que en base a una expresión regular y a un archivo de texto, diga si cada expresión es una expresión regular o no .

La expresión regular a reconocer es:
```
(A|C|G)∗G+T+C(A|C|G|T)∗
```

El siguiente es una ejemplo de salida:

```txt
GATCTTATATAACTGTGAGATTAATCTCAGATAATGACACAAAATATAGTGAAGTTGGTA no
AGTTATTTAGTAAAGCTCATGAAAATTGTGCCCTCCATTCCCATATAATTTATTAATTGT no
CTAGGAACTTCCACATACATTGCCTCAATTTATCTTTCAACAACTTGTGTGTTATATTTT no
GGAATACAGATACAAAGTTATTATGCTTTCAAAATATTCTTTTGCTAATTCTTAGAACAA no
AGAAAGGCATAAATATATTAGTATTTGTGTACATCTGTTCCTTCCTGTGTGACCCTAAGT si
TTAGTAGAAGAAAGGAGAGAAAATATAGCCTAGCTTATAAATTTAAAAAAAAATTTATTT no
GGTCCATTTTGTGAAAAACATAAAAAAAGAACTGTCACATCTTAATTTAAAAAATATATG si
CTTAGTGGTAAGGAGATATATGTCAACTTTTAAGAGGTTGAAAAACAAACGCCTCCCATT si
ATAAGTTTATACTTCACCTCCCACCACTATAACAACCCAGAATCCATGAGGGCATTATCA no

Total de expresiones que Si son regulares:3
Total de expresiones que No son regulares:6
Total de lineas leídas:9
```

## Lógica de la sólucion

En este laboratorio crearemos un "reconocedor", que en base a una expresión regular y a un archivo de texto, diga si cada expresión es una expresión regular o no.

1. El proceso principal recibirá como argumentos por línea de comando el nombre del archivo de entrada, el nombre del archivo de salida, la cantidad de workers que serán generados y el número de chunks con el cuál se trabajara.
2. El proceso principal validará los datos entregados por pantalla y, una vez validados, ejecutará el proceso broker con `fork()` y algún miembro de la familia `exec()` entregándole los elementos ya validados.
3. El broker recibirá los argumentos del proceso padre y los utilizara para las tareas necesarias.
4. El broker creará la misma cantidad de workers que la ingresada por pantalla.
5. El broker ejecutara los procesos worker utilizando algún miembro de la familia `exec()` y se comunicará con ellos mediante el uso de pipes
6. Cuando no queden líneas por leer, el broker avisará a cada uno de los workers con la palabra "FIN", indicando que no debe esperar más líneas del broker.
7. Cada worker se encargará de obtener y procesar las líneas que entregue el broker.
8. Cuando un worker recibe una línea este se encargará de realizar cada calculo necesario para dicha línea los cuales deben ser almacenados en caso de que lo amerite (ej: si la línea es regular o no). La estructura que se use para almacenar estos resultados queda a elección del desarrollador.
9. Cuando un worker lea la palabra clave "FIN" este deberá dejar de esperar líneas del broker y enviar a este último la cantidad de líneas que procesó durante su ejecución. Luego, se finaliza su proceso.
10. Una vez que todos los workers hayan terminado sus cálculos, el broker retomará el control y escribirá en el archivo de salida los resultados siguiendo el formato entregado. Si se utiliza la bandera -b, estos resultados deberán además aparecer en la salida estándar (`stdout`) del terminal del Sistema Operativo incluyendo con ellos la cantidad de líneas que procesó cada worker (basta con mostrar el PID del worker o con una ID arbitraria asignada al mismo). Con esto, el padre finaliza su ejecución.
11. Tanto proceso padre, proceso broker y proceso worker debe encontrarse finalizado a la hora de terminar el programa.

## Ejecucion

El programa se ejecutará usando los siguientes argumentos (ejemplo):
```
$ ./lab1 -i datos_juegos.csv -o salida.txt -b
```
- `-i`: nombre del archivo de entrada.
- `-o`: nombre de archivo de salida.
- `-n`: numero de workers a generar.
- `-c`: tamaño del chunk.
- `-b`: bandera o flag que permite indicar si se quiere ver por consola la cantidad de expresiones regulares encontradas.

Como requerimientos no funcionales, se exige lo siguiente:
- Debe funcionar en sistemas operativos con kernel Linux.
- Debe ser implementado en lenguaje de programación C.
- Se debe utilizar un archivo Makefile para compilar los distintos targets.
- Realizar el programa utilizando buenas prácticas, dado que este laboratorio no contiene manual de usuario ni informe, es necesario que todo esté debidamente comentado.
- Los programas se encuentren desacoplados, es decir, que se desarrollen las funciones correspondientes en otro archivo .c para mayor entendimiento de la ejecución.
- La solución debe implementar `fork()`, `excec()`, `dup2()` y `pipe()`. De lo contrario se considerara
invalido.