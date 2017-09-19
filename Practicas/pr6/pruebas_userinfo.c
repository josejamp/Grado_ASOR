#include <pwd.h>
#include <sys/types.h>
#include <stdio.h>

int main(int argc, char ** argv){

	//informacion del usuario
	struct passwd *p;

	//buscamos por el nombre del usuario
	p = getpwnam(argv[1]);

	if(p == NULL){
		perror("Error");
		return -1;
	}

	printf("Nombre del usuario: %s\n", p->pw_name);

	printf("ID del usuario: %i\n", p->pw_uid);
	

	return 0;
}
