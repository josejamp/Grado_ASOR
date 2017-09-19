#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main(){
	
	// en vez de meterlo todo en el bucle se puede abrir
	// con modo O_RDWR

	while(1){

		// conjunto de descriptores de ficheros a observar
		fd_set conjunto;
	
		printf("Abrimos fd1\n");
		// abrimos los archivos de modo no bloqueante
		int fd1 = open("tuberia", O_RDONLY | O_NONBLOCK);
		//int fd1 = open("tuberia", O_RDONLY );
		printf("Abrimos fd2\n");
		int fd2 = open("tuberia2", O_RDONLY | O_NONBLOCK);
		//int fd2 = open("tuberia2", O_RDONLY );

		// inicializamos el conjunto
		FD_ZERO(&conjunto);

		// metemos los descriptores de los ficheros abiertos
		FD_SET(fd1, &conjunto);
		FD_SET(fd2, &conjunto);
	
		// buscamos el mayor de los descriptores
		int mayor = (fd1 > fd2)? fd1:fd2;

		printf("Antes de select\n");
		// "escuchamos"
		int cambios = select(mayor+1, &conjunto, NULL, NULL, NULL);
		printf("Despues de select\n");

		char buffer[256];

		// descubrimos cual ha cambiado
		if(FD_ISSET(fd1, &conjunto)){
		
			//leemos
			int size = read(fd1, buffer, 256);
			buffer[size] = '\0';
			if(size > 0) printf("%s", buffer);
			while(size > 0){
				size = read(fd1, buffer, 256);
				buffer[size] = '\0';
				if(size > 0) printf("%s", buffer);
			}
			printf("\n");
		
		}
		else if(FD_ISSET(fd2, &conjunto)){
		
			//leemos
			int size = read(fd2, buffer, 256);
			buffer[size] = '\0';
			if(size > 0) printf("%s", buffer);
			while(size > 0){
				size = read(fd2, buffer, 256);
				buffer[size] = '\0';
				if(size > 0) printf("%s", buffer);
			}
			printf("\n");

		}

		close(fd1);
		close(fd2);

	}



	
	
	return 0;
}
