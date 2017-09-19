#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

/**
 Simulamos el comando stat
 **/
int main(int argc, char** argv){
	
	struct stat buf;
	
	//abrimos el archivo
	int fd = open(argv[1], O_RDWR | O_CREAT, 0640);
	
	//obtenemos el estado de fichero mediante su descriptor
	fstat(fd, &buf);

	if(S_ISREG(buf.st_mode)){ //si es un fichero normal
		printf("fichero normal\n");
	}
	else if(S_ISDIR(buf.st_mode)){ //si es un directorio
		printf("escritorio\n");
	}
	//num major	
	printf("Major: %ld\n", major(buf.st_dev));
	//num minor
	printf("Minor: %ld\n", minor(buf.st_dev));
	// Nodo-i
	printf("iNodo: %ld\n", buf.st_ino);
	//Ultimo acceso al fichero
	printf("Ultimo acceso: %s\n", ctime(&buf.st_atime));
	
	return 0;
}
