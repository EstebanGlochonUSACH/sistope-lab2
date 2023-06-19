# sistope-lab1
Laboratorio 1 de Sistemas Operativos

## Enunciado

En este laboratorio crearemos un "reconocedor", que en base a una expresión regular y a un archivo de texto, diga si cada expresión es una expresión regular o no .

La expresión regular a reconocer es:
```
(A|C|G|T)∗GT+C(A|C|G|T)∗
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

El programa se ejecutará usando los siguientes argumentos (ejemplo):
```
$ ./lab1 -i datos_juegos.csv -o salida.txt -b
```
- `-i`: nombre del archivo de entrada.
- `-o`: nombre de archivo de salida.
- `-b`: bandera o flag que permite indicar si se quiere ver por consola la cantidad de expresiones regulares encontradas.

Como requerimientos no funcionales, se exige lo siguiente:
- Debe funcionar en sistemas operativos con kernel Linux.
- Debe ser implementado en lenguaje de programación C.
- Se debe utilizar un archivo Makefile para compilar los distintos targets.
- Realizar el programa utilizando buenas prácticas, dado que este laboratorio no contiene manual de usuario ni informe, es necesario que todo esté debidamente comentado.
- Los programas se encuentren desacoplados, es decir, que se desarrollen las funciones correspondientes en otro archivo .c para mayor entendimiento de la ejecución.