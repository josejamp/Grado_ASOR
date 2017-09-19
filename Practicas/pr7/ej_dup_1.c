#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>


int main(int argc, char** argv){
	
	//fichero al que se redireccionara
	int fd = open(argv[1], O_RDWR | O_CREAT |O_APPEND, 0600);

	//guardamos el descriptor de la salida estandar
	int save_out = dup(fileno(stdout));

	//duplicamos la salida estandar con el archivo
	if(dup2(fd, fileno(stdout)) == -1) perror("Error");
	
	//escribimos para probar
	puts("Adios\n");
	
	//cerramos flujos
	fflush(stdout); close(fd);
	
	/*********************************
		Tambien se puede:
		dup2(fd,1);
	********************************/
	
	return 0;
}
