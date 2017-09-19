#include <sched.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

int main(){
	
	pid_t  mi_pid, pid;

	pid = fork(); //hacemos un hijo

	switch(pid){
		case -1:{ //si fala, error
			perror("fork");
			return -1;
		} break;
		case 0:{ // si es el hijo

			pid_t hijo, grupo, sesion;

			//para acceder al uso de recursos del sistema
			struct rlimit rlim;
			
			//cogemos los id de proceso, grupo y sesion
			hijo = getpid();
			grupo = getpgid(0);
			sesion = getsid(0);

			//numero maximo de descriptores de archivo
			int archivos = getrlimit(RLIMIT_NOFILE, &rlim);
	
			//preparacion de strings para el PATH absluto
			char* buff, buff4;
			char buff2[80], buff3[90];
			
			//guardamos el path absoluto
			buff = getcwd(buff2, 80
			
			//le metemos /tmp al final
			strcpy(buff3, buff2);
			strcat(buff3, "/tmp");
			
			//cambamos el directorio de trabajo
			if(	chdir(buff3) != 0) perror("Error con chdir");
			buff = getcwd(buff2, 80);
			
			//mostramos todo
			printf("pid: %i\n", hijo);
			printf("pgid: %i\n", grupo);
			printf("sesion: %i\n", sesion);
			printf("archivos: %i\n", rlim.rlim_max);
			printf("path: %s\n", buff);

		} break;
		default:{ //padre
			wait(); //espera a los hijos
		} break;
	}
	
	
	return 0;
}
