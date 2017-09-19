#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <sys/time.h>

/**
	Se ejecuta cuando llega la senial
**/
void sig_handler(int signo){
	
	//borramos el archivo
	unlink("/home/usuarioso/Documentos/ASOR/Pr8/signal_ej5");
	//mostramos si hay errores
	perror("Error");
	
}

int main(int argc, char** args){
	
	sigset_t grupo;
	
	//llenamos el grupo con todas las seniales
	sigfillset(&grupo);
	
	//le quitamos la SIGALARM al grupo
	sigdelset(&grupo, SIGALARM);
	
	// manejador de SIGALARM
	signal(SIGALRM, sig_handler);
	
	//leemos el num de seg de args
	int secs = atoi(args[1]);
	
	//creamos la alarma
	alarm(secs);
	
	//esperamos hasta que se produzca
	sigsuspend(&grupo);

	return 0;
}
