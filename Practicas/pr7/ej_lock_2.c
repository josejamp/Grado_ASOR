#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>


int main(int argc, char** argv){
	
	//descriptor de fichero
	int fd = open(argv[1], O_RDWR | O_CREAT |O_APPEND, 0600);

	//creamos los cerrojos
	struct flock lock, savelock;
	
	//inicializamos los campos
	lock.l_type    = F_WRLCK;  //lock de write
	lock.l_start   = 0; //empezamos en el byte 0
	lock.l_whence  = SEEK_SET; //desde el principio
	lock.l_len     = 0; //bloqueamos hasta el final
 	savelock = lock;

	//sobreescribimos en lock el cerrojo que ya tenia el fichero fd
	int k = fcntl(fd, F_GETLK, &lock);

	//si estaba desbloqueado
	if(lock.l_type == F_UNLCK){
		
		//obtenemos el tiempo
		time_t t;
	
		time(&t);
		
		char buffer[80];
		strcpy(buffer, ctime(&t));	
		
		/** FALTA PONER EL CERROJO? **/
		
		//escribimos la fecha
		int desp = write( fd, buffer, strlen(buffer));
	
		sleep(5);
		
		/** LO CERRAMOS AHORA?
		DEBERIAMOS HACER UNLOCK
		***/
		fcntl(fd, F_SETLK, &savelock);

	}
	
	return 0;
}
