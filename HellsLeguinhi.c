

#include <stdio.h>      // libreria estandar
#include <stdlib.h>     // para usar exit y funciones de la libreria standard
#include <string.h>
#include <pthread.h>    // para usar threads
#include <semaphore.h>  // para usar semaforos
#include <unistd.h>
#include <stdbool.h>

#define LIMITE 50

//creo estructura de semaforos 
struct semaforos {
    sem_t sem_mezclar;
    sem_t sem_salar;
    sem_t sem_armarMedallon;
    sem_t sem_cocinar;
    sem_t sem_armarHamburguesa;

	//poner demas semaforos aqui
};

//creo los pasos con los ingredientes
struct paso {
   char accion [LIMITE];
   char ingredientes[4][LIMITE];
   
};

//creo los parametros de los hilos 
struct parametro {
 int equipo_param;
 struct semaforos semaforos_param;
 struct paso pasos_param[8];
};

//funcion para imprimir las acciones y los ingredientes de la accion
void* imprimirAccion(void *data, char *accionIn) {
	FILE* salida=fopen("salida.txt","a");
	struct parametro *mydata = data;
	//calculo la longitud del array de pasos 
	int sizeArray = (int)( sizeof(mydata->pasos_param) / sizeof(mydata->pasos_param[0]));
	//indice para recorrer array de pasos 
	int i;
	for(i = 0; i < sizeArray; i ++){
		//pregunto si la accion del array es igual a la pasada por parametro (si es igual la funcion strcmp devuelve cero)
		if(strcmp(mydata->pasos_param[i].accion, accionIn) == 0){
		fprintf(salida, "\tEquipo %d - accion %s \n " , mydata->equipo_param, mydata->pasos_param[i].accion);
		//calculo la longitud del array de ingredientes
		int sizeArrayIngredientes = (int)( sizeof(mydata->pasos_param[i].ingredientes) / sizeof(mydata->pasos_param[i].ingredientes[0]) );
		//indice para recorrer array de ingredientes
		int h;
		fprintf(salida,"\tEquipo %d -----------ingredientes : ----------\n",mydata->equipo_param); 
			for(h = 0; h < sizeArrayIngredientes; h++) {
				//consulto si la posicion tiene valor porque no se cuantos ingredientes tengo por accion 
				if(strlen(mydata->pasos_param[i].ingredientes[h]) != 0) {
							fprintf(salida, "\tEquipo %d ingrediente  %d : %s \n",mydata->equipo_param,h,mydata->pasos_param[i].ingredientes[h]);
				}
			}
		}
	}
}

//funcion para tomar de ejemplo
void* cortar(void *data) {
	//creo el nombre de la accion de la funcion 
	char *accion = "cortar";
	//creo el puntero para pasarle la referencia de memoria (data) del struct pasado por parametro (la cual es un puntero). 
	struct parametro *mydata = data;
	//llamo a la funcion imprimir le paso el struct y la accion de la funcion
	imprimirAccion(mydata,accion);
	//uso sleep para simular que que pasa tiempo
	usleep( 20000 );
	//doy la señal a la siguiente accion (cortar me habilita mezclar)
    sem_post(&mydata->semaforos_param.sem_mezclar);
	
    pthread_exit(NULL);
}
void* mezclar(void *data){
   struct parametro *mydata = data;
   sem_wait(&mydata->semaforos_param.sem_mezclar);
	char *accion = "mezclar";
	imprimirAccion(mydata,accion);
	usleep(200000);
    sem_post(&mydata->semaforos_param.sem_salar);
    pthread_exit(NULL);

}



void* salar(void *data){
    struct parametro *mydata = data;
    sem_wait(&mydata->semaforos_param.sem_salar);
    pthread_mutex_lock(&salar);
    	char *accion = "salar";
    	imprimirAccion(mydata,accion);
    	usleep(200000);
    sem_post(&mydata->semaforos_param.sem_armarMedallon);
    pthread_mutex_unlock(&salar);
    pthread_exit(NULL);
} 

void* armarMedallon(void *data){
   struct parametro *mydata = data;
   sem_wait(&mydata->semaforos_param.sem_armarMedallon);
	 char *accion = "armar medallon";
        imprimirAccion(mydata,accion);
        usleep(100000);
    sem_post(&mydata->semaforos_param.sem_cocinar);
}
void* cocinar(void *data){
   struct parametro *mydata = data;
   sem_wait(&mydata->semaforos_param.sem_cocinar);
   pthread_mutex_lock(&cocinar);
   	char *accion = "cocinar";
        imprimirAccion(mydata,accion);
        usleep(500000);
   sem_post(&mydata->semaforos_param.sem_armarHamburguesa);
   pthread_mutex_unlock(&cocinar);
   pthread_exit(NULL);
}
void* cortarLyT(void *data){
	char *accion = "cortar extras";
	struct parametro *mydata = data;
        imprimirAccion(mydata,accion);
        usleep(100000);
	sem_post(&mydata->semaforos_param.sem_armarHamburguesa);
	pthread_exit(NULL);
}
void* hornear(void *data){
  pthread_mutex_lock(&hornear);
	 char *accion = "hornear";
        struct parametro *mydata = data;
        imprimirAccion(mydata,accion);
        usleep(1000000);
   sem_post(&mydata->semaforos_param.sem_armarHamburguesa);
   pthread_mutex_unlock(&hornear);
   pthread_exit(NULL);

}
void* armarHamburguesa(void *data){
   struct parametro *mydata = data;
  sem_wait(&mydata->semaforos_param.sem_armarHamburguesa);
  sem_wait(&mydata->semaforos_param.sem_armarHamburguesa);
  sem_wait(&mydata->semaforos_param.sem_armarHamburguesa);
	  char *accion = "armar hamburguesa";
        imprimirAccion(mydata,accion);
        usleep(100000);
   pthread_exit(NULL);

}

void* ejecutarReceta(void *i) {
	
	//variables semaforos
	sem_t sem_mezclar;
	sem_t sem_salar;
	sem_t sem_armarMedallon;
	sem_t sem_cocinar;
	sem_t sem_armarHamburguesa;
	//crear variables semaforos aqui
	//variables hilos
	pthread_t p1;
	pthread_t pMezclar;
	pthread_t pAMedallon;
	pthread_t pSalar;
	pthread_t pHornear;
	pthread_t pArmarHamburguesa;
	pthread_t pCocinar;
	pthread_t pCortarLechugayTomate;
	//crear variables hilos aqui
	
	//numero del equipo (casteo el puntero a un int)
	int p = *((int *) i);
	
	printf("Ejecutando equipo %d \n", p);

	//reservo memoria para el struct
	struct parametro *pthread_data = malloc(sizeof(struct parametro));

	//seteo los valores al struct
	
	//seteo numero de grupo
	pthread_data->equipo_param = p;

	//seteo semaforos
	pthread_data->semaforos_param.sem_mezclar = sem_mezclar;
	pthread_data->semaforos_param.sem_salar = sem_salar;
	pthread_data->semaforos_param.sem_armarMedallon = sem_armarMedallon;
	pthread_data->semaforos_param.sem_cocinar = sem_cocinar;
	pthread_data->semaforos_param.sem_armarHamburguesa = sem_armarHamburguesa;
	//setear demas semaforos al struct aqui
	

	//seteo las acciones y los ingredientes (Faltan acciones e ingredientes) ¿Se ve hardcodeado no? ¿Les parece bien?
	FILE* instructivo=fopen("pasosDePreparacion.txt","rb");
	char pipe[] = "|";
	char finDeLinea = '\n';
	char linea[100];
	int  cantInstrucciones = 0;
	int  iIngredientes= 0;
	int  iLinea = 0;
	bool   action = true;
        char *palabra;
	while (feof(instructivo)==0){
		char letra =fgetc(instructivo);
		if(letra !=finDeLinea){
			linea[iLinea]=letra;
			iLinea++;
		}
		else{
			palabra=strtok(linea,pipe);
			while (palabra!=NULL){
				if(action==true){
				strcpy(pthread_data->pasos_param[cantInstrucciones].accion, palabra);
				action=false;
				}
				else{
				 strcpy(pthread_data->pasos_param[cantInstrucciones].ingredientes[iIngredientes], palabra);
				iIngredientes++;
				}
		 		palabra=strtok(NULL, pipe);
			}
			memset(linea,0,100);
			iLinea=0;
			iIngredientes=0;
			cantInstrucciones++;
			action=true;
		}
	}
			
			
	//inicializo los semaforos

	sem_init(&(pthread_data->semaforos_param.sem_mezclar),0,0);
	sem_init(&(pthread_data->semaforos_param.sem_salar),0,0);
	sem_init(&(pthread_data->semaforos_param.sem_armarMedallon),0,0);
	sem_init(&(pthread_data->semaforos_param.sem_cocinar),0,0);
	sem_init(&(pthread_data->semaforos_param.sem_armarHamburguesa),0,0);
	//inicializar demas semaforos aqui


	//creo los hilos a todos les paso el struct creado (el mismo a todos los hilos) ya que todos comparten los semaforos 
    int rc;
    rc = pthread_create(&p1,                           //identificador unico
                            NULL,                          //atributos del thread
                                cortar,             //funcion a ejecutar
                                pthread_data);                     //parametros de la funcion a ejecutar, pasado por referencia
	//crear demas hilos aqui
    rc = pthread_create(&pMezclar,                           
                            NULL,                          
                                mezclar,             
                                pthread_data);
    rc = pthread_create(&pSalar,                           
                            NULL,                          
                                salar,             
                                pthread_data);
    rc = pthread_create(&pAMedallon,                           
                            NULL,                          
                                armarMedallon,             
                                pthread_data);   	
    rc = pthread_create(&pCocinar,                           
                            NULL,                          
                                cocinar,             
                                pthread_data); 
   rc = pthread_create(&pHornear,
                            NULL,
                                hornear,             
                                pthread_data); 
  rc = pthread_create(&pCortarLechugayTomate,
                            NULL,
                                cortarLyT,             
                                pthread_data); 
  rc = pthread_create(&pArmarHamburguesa,
                            NULL,
                                armarHamburguesa,             
                                pthread_data); 



	//join de todos los hilos
	pthread_join (p1,NULL);
	pthread_join (pMezclar,NULL);
	pthread_join (pSalar,NULL);
	pthread_join (pAMedallon,NULL);
	pthread_join (pCocinar,NULL);
	pthread_join (pHornear,NULL);
	pthread_join (pCortarLechugayTomate,NULL);
	pthread_join (pArmarHamburguesa,NULL);

	//crear join de demas hilos


	//valido que el hilo se alla creado bien 
    if (rc){
       printf("Error:unable to create thread, %d \n", rc);
       exit(-1);
     }

	 
	//destruccion de los semaforos 
	sem_destroy(&sem_mezclar);
	sem_destroy(&sem_salar);
	sem_destroy(&sem_armarMedallon);
	sem_destroy(&sem_cocinar);
	sem_destroy(&sem_armarHamburguesa);
	//destruir demas semaforos 
	
	//salida del hilo
	 pthread_exit(NULL);
}


int main ()
{
	//creo los nombres de los equipos
 
	int rc;
	int *equipoNombre1 =malloc(sizeof(*equipoNombre1));
	int *equipoNombre2 =malloc(sizeof(*equipoNombre2));
	int *equipoNombre3 =malloc(sizeof(*equipoNombre3));
	*equipoNombre1 = 1;
	*equipoNombre2 = 2;
	*equipoNombre3 = 3;
	
	//creo las variables los hilos de los equipos
	pthread_t equipo1; 
	pthread_t equipo2;
	pthread_t equipo3;
 	pthread_mutex_t salero;
	pthread_mutex_t cocina;
	pthread_mutex_t horno;
	pthread_mutex_t ganador;
	//inicializo los hilos de los equipos
    rc = pthread_create(&equipo1,                           //identificador unico
                            NULL,                          //atributos del thread
                                ejecutarReceta,             //funcion a ejecutar
                                equipoNombre1); 

    rc = pthread_create(&equipo2,                           //identificador unico
                            NULL,                          //atributos del thread
                                ejecutarReceta,             //funcion a ejecutar
                                equipoNombre2);

    rc = pthread_create(&equipo3,                           //identificador unico
                            NULL,                          //atributos del thread
                                ejecutarReceta,             //funcion a ejecutar
                                equipoNombre3);
	pthread_mutex_init(&salero, NULL);
	pthread_mutex_init(&cocina, NULL);
	pthread_mutex_init(&horno, NULL);
   if (rc){
       printf("Error:unable to create thread, %d \n", rc);
       exit(-1);
     } 

	//join de todos los hilos
	pthread_join (equipo1,NULL);
	pthread_join (equipo2,NULL);
	pthread_join (equipo3,NULL);


    pthread_exit(NULL);
    pthread_mutex_destroy(&salero);
    pthread_mutex_destroy(&cocina);
    pthread_mutex_destroy(&horno);
}

//Para compilar:   gcc HellsBurgers.c -o ejecutable -lpthread
//Para ejecutar:   ./ejecutable
