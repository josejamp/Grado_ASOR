#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char** argv){
	
	// creamos los pipes
	int p_h[2], h_p[2];
	pipe(p_h);
	pipe(h_p);
	
	pid_t pid = fork();

	switch(pid){
		case -1: perror("Error en fork()"); break;
		case 0:{ // hijo
			
			int i;
			
			for(i = 0; i < 9; i++){
				// leemos
				char msg[80];
				read(p_h[0], msg, 80);
				
				// mostramos y esperamos
				printf("mensaje: %s\n", msg);
				wait(1);
			
				// mandamos mensaje
				write(h_p[1], "l", strlen("l"));
				printf("i: %d\n", i);
			}
			write(h_p[1], "q", 2);
			
		} break;
		default:{ //padre
			
			char *confirm = "a";
			
			while(strcmp(confirm, "q") != 0){
				// leemos de pantalla			
				char input[80];
				scanf("%s", input);
			
				// escribimos en la tuberia
				write(p_h[1], input, 80);
		
				// esperamos confirmacion
				read(h_p[0], confirm, strlen(confirm));

				printf("confirmacion: %s\n", confirm);
			}	

		} break;

	}
	return 0;
}
