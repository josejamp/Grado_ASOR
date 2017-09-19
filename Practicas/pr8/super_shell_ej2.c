#include <sched.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char** args){
	
	//cramos la estructura del planificador
	const struct sched_param p;
	
	//fijamos el planificador con Round Robin
	int prioty = sched_setscheduler(0, SCHED_RR, &p);

	//si hay mas de un argumento en el main
	if(argc > 1){ //fijamos la prioridad a args[1] para el proceso
		setpriority(PRIO_PROCESS, 0, ((int)args[1]));
	}
	else{ //si no fijamos la prioridad maxima
		int max = sched_get_priority_max(SCHED_RR);
		setpriority(PRIO_PROCESS, 0, max);
	}	
	
	//lo ejecutamos
	int salida = system("/bin/bash");
	
	return 0;
}
