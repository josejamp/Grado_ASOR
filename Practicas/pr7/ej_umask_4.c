#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


int main(int argc, char** argv){
	
	//modificamos la mascara para que los nuevos
	//ficheros no tengan permiso de escritura para el grupo
	// y ningun permiso para otros
	umask(027);
	
	int fd = open(argv[1], O_RDWR | O_CREAT);
			
	
	return 0;
}
