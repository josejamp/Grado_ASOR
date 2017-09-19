#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

int main(){

	//Recorremos todos los errores del sistema
	//y mostramos sus mensajes
	int i;
	
	for(i = 0; i < sys_nerr; i++){
		
		printf("Error: %s\n", strerror(i));
		
	}
	
	return 0;
}
