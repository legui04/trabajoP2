# trabajoP2
trabajo practico
Por el medio del presente texto se pasara a explicar la resolucion que se realizo en este trabajo.
en primera instancia que pasos se realizaron primero y metodos que se planeaban realizar para resolver la misma.
en primera como bien se mostro en la clase. 
procedi a hacer pseudocodigo en mi caso:
cortar(): Ya venian definidos en el trabajo practico.

mezclar(): El semaforo de mezclar espera una señal que sale de cortar y mezcla los ingredientes 
anterior cortado con la carne picada. Despues lanza una señal a salar.

salar():El semaforo de salar espera la señal que sale de mezclar.Ademas de revisar y cambiar el 
estado del mutex salero, de esta manera emula la presencia de un solo salero. Su funcion es 
poner sal a la mezcla del medallon. Cuando termina manda una señal al semaforo de armar Medallon.

armarMedallon(): El semaforo de armarMedallon espera la señal que sale de salar.Su funcion es 
dar forma a la mezcla de medallon y prapararlas para cocinar. Cuado termina manda una señal al semaforo de
cocinar.


cocinar(): El semaforo de cocinar espera la señal que sale de armar medallon.Ademas de revisar y cambial el
estado del mutex cocina, de esta manera emula la presencia de una sola plancha. Su funcion es la de cocinar
los medallones armados. Cuando termina se manda una señal a armar hamburguesa.

cortarExtras(): Esta funcion no depende de ningun mutex o semaforo  y se realiza cuando esta disponible. Su funcion es
la de cortar la lechuga y el tomate. Cuando termina manda una señal al semaforo de armar hamburguesa.

hornear():Esta funcion no depente de un semaforo pero si de un mutex. El mutex trata de emular la presencia
de un solo horno .Su funcion es la de cocinar los panes. cuando termina manda una señal al semaforo de armar 
hamburguesa.

ArmarHamburguesa():Esta funcion espera la señal de 3 funciones que son cocinar,cortar extras y hornear.Su funcion es
la de preparar la hamburguesa.



Ahora pasare a explicar los conflictos y las diferentes maneras de afrontar el tp que tuve a lo largo de estos dias.
En primera cuenta uno de los conflictos que tuve fue la manera de escanear la receta.
Lo primero que trate de utilizar fue la funcion scanf y solo tomaba el nombre y procedia a hacer las actividades.
Pero al momento de ver las cosas que teniamos que hacer y la manera que se planteo para realizarlo me di cuenta que
era una funcion muy floja para lo que se pedia y se procedio a cambiarlo.
otra fue la de realizar un ciclo while para leerlo y otros ciclo while que se encargaba de pasarlo a parametros
pero al hacerlo me di cuenta que se estaba achicando cada vez mas el string original y entonces.
Procedi a realizarlo de la siguiente manera. 
La manera es la siguiente, Cuando termina termino de traspasar la primera linea a un string.
Acciono sobre ella y la manera es ingresarlo en un split que los va a ir dividiendo por el pipe.
Como lo primero siempre es la accion se creo una variable bool para que entre solo una vez a setear la accion despues
la cambio a false de esta manera me aseguro de asignar la accion y despues de que las siguientes cosas son los ingredientes.
Esta tarea se realiza hasta que termina de haber lineas en el archivo de texto.
otro problema fue a la hora de escribirlos en un fichero de salida, pero a la hora de revisar un poco 
los manuales no hubo tantos conflictos.
de resto fue un tp bastante accesible el cual a primera instancia me intimido pero con la ayuda del template lo pude realizar
