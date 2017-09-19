#include <stdio.h>
#include <signal.h>


int main(){
	
	//creamos los grupos
	sigset_t blk_grupo, pend, des;

	//metemos las seniales deseadas en los grupos
	//mandar SIGINT es como hacer Ctrl+C
	sigaddset(&blk_grupo, SIGINT);
	sigaddset(&blk_grupo, SIGTSTP);

	//bloqueamos las seniales que hay en el grupo
	sigprocmask(SIG_BLOCK, &blk_grupo, NULL);

	//accedemos a la variable del sistema para ver cuantos
	//segundos hemos de dormir
	char* buff = getenv("SLEEP_SECs");
	printf("secs: %s\n", buff);
	int secs = atoi(buff); //parser
	sleep(secs); //dormimos

	//nos despertamos y vemos cuantas seniales hay pendientes
	sigpending(&pend);

	//si es SIGINT lo mostramos
	if(sigismember(&pend, SIGINT)){
		printf("SIGINT\n");
	}
	
	//si es SIGTSTP  desbloqueamos la senial y el programa se bloquea,
	//se puede desbloquear desde la Shell
	if(sigismember(&pend, SIGTSTP)){
		printf("SIGTSTP\n");
		sigaddset(&des, SIGTSTP);
		sigprocmask(SIG_UNBLOCK, &blk_grupo, NULL);
	}
	
	return 0;
}
