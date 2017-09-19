#include <unistd.h>
#include <stdio.h>

int main(){

	long int conf;

	//longitud maxima de los argumentos de las funciones exec()
	conf = sysconf(_SC_ARG_MAX);
	printf("Num max arg: %i\n", conf);

	//numero maximo de procesos simultaneos por usuarios
	conf = sysconf(_SC_CHILD_MAX);
	printf("Hijos máximos: %i\n", conf);

	//numero maximo de procesos que puede abrir el proceso
	conf = sysconf(_SC_OPEN_MAX);
	printf("Ficheros max: %i\n", conf);
	
	return 0;
}
