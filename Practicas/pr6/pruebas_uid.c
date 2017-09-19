#include <errno.h>
#include <unistd.h>
#include <stdio.h>

int main(){
	
	int error;
	
	//Comprobamos el user id
	if(error = setuid(0) != 0){
			
		printf("Errno es: %i\n", errno);
		perror("Error setuid");
		
	}

	return 0;	
}
