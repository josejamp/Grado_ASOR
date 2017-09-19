#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define PW 1
#define PR 0

int main(int argc, char** argv){
	
	// creamos el pipe
	int tuberias[2];
	pipe(tuberias);

	pid_t pid = fork();

	switch(pid){
		case -1: perror("Error en fork()"); break;
		case 0:{ // hijo

			printf("En el hijo\n");			
	
			// cerramos el flujo que no vamos a utilizar
			close(tuberias[PW]);

			// leemos de la tuberia
			char result[80];
			dup2(tuberias[PR],0);
			close(tuberias[PR]);

			// ejecutamos
			execlp(argv[3],argv[3],argv[4],0);
			
		} break;
		default:{ // padre
			
			printf("En el padre\n");

			// cerramos lo no necesario
			close(tuberias[PR]);
			
			// redireccionamos la salida estandar a la tuberia	
			int save_out = dup(fileno(stdout));
			dup2(tuberias[PW], 1);
			
			// cerramos lo innecesario
			close(tuberias[PW]);

			// ejecutamos la orden
			execlp(argv[1],argv[1],argv[2],0);			


		} break;
	}
	
	
	
	
	
	return 0;
}
