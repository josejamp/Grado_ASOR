#include <sys/utsname.h>
#include <stdio.h>

int main(){

	//informacion sobre el kernel
	struct utsname buf;
	
	int error;

	if(error = uname(&buf) != 0){
		
		perror("Error");
		
	}
	else{
		
		printf("Nombre del sistema: %s\n", buf.sysname);
		printf("Nombre del nodo: %s\n", buf.nodename);
		printf("Lanzamiento: %s\n", buf.release);
		printf("Version: %s\n", buf.version);
		printf("Maquina: %s\n", buf.machine);
		
	}

	return 0;
}
