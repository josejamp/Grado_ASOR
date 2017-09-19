#include <stdio.h>
#include <signal.h>

/**
 Estructura con el total de seniales recibidas
 y el total de cada senial
**/
struct senal{
	int sigint;
	int sigtstp;
	int total;
};

/**
 La variable debe ser volatil,
 NO ESTOY SEGURO de que definida asi
 FUNCIONE
**/
volatile senal total; 

/**
 Manejador, dependiendo de que senial sumamos a la variable correspondiente
**/
void sig_handler(int signo){
	
	if(signo == SIGINT){
		total.sigint++;
		total.total++;
	}
	else if(signo == SIGTSTP){
		total.sigtstp++;
		total.total++;
	}
}

int main(){
	//creamos el grupo
	sigset_t grupo;
	
	//metemos las seniales en el grupo
	sigaddset(&grupo, SIGINT);
	sigaddset(&grupo, SIGTSTP);
	
	//creamos una estructura para manejar las seniales del grupo
	struct sigaction act;
	act.sa_handler = sig_handler;
	act.sa_mask = grupo;
	act.sa_flags = 0;

	//agregamos las seniales al grupo
	sigaction(SIGINT, &act, NULL);
	sigaction(SIGTSTP, &act, NULL);

	//esperamos mientras sea menor que 10
	while(total.total < 10){/* */}

	//mostramos
	printf("SIGINT: %i\n", total.sigint);
	printf("SIGTSTP: %i\n", total.sigtstp);
	
	return 0;
}
