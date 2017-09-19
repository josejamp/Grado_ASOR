#include <time.h>
#include <sys/time.h>
#include <stdio.h>

int main(){

	//conseguimos el tiempo del sistema
	time_t t;
	time(&t);
	printf("Tiempo es: %s\n", ctime(&t));

	//el tiempo del dia con microsegundos antes del buce
	struct timeval *antes;

	gettimeofday(antes, NULL);
		
	//ejecutamos un bucle para ver cuanto tarda
	int i;
	for(i=0;i<10000;i++) ;

	//el tiempo del dia con microsegundos despues del buce
	struct timeval *despues;	
	
	gettimeofday(despues, NULL);
	
	//mostramos lo que ha tardado
	printf("Ha tardado: %i\n", (despues->tv_usec - antes->tv_usec));
	
	//mostramos el año con localtime()
	struct tm *tml;

	tml = localtime(&t);

	printf("Año: %i\n", (1900 + tml->tm_year));

	char buffer[80];

	//mostramos el dia y la hora con strftime()
	strftime(buffer, 80, "%A, %H:%M", tml);

	printf("Es: %s\n", buffer);

	return 0;
}
