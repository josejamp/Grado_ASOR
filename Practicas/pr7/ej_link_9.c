#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char** argv){
	
	struct stat buf;
	
	//abrimos archivo
	int fd = open(argv[1], O_RDWR | O_CREAT, 0640);
	
	//obtenemos el estado de los ficheros
	fstat(fd, &buf);

	//nombre del enlace simbolico
	char n_link[80];
	strcpy(n_link, argv[1]);
	strcat(n_link, ".sym");

	//nombre del enlace duro
	char h_link[80];
	strcpy(h_link, argv[1]);
	strcat(h_link, ".hard");

	//si es un fichero normal
	if(S_ISREG(buf.st_mode)){
		printf("fichero normal\n");
		
		//cremos un enlace duro
		link(argv[1], n_link);
		
		//creamos un enlace simbolico
		symlink(argv[1], h_link);		
		
	}
	
	return 0;
}
