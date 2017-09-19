#include <sched.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char** args){
	
	//ejecutamos con execvp 
	int salida = execvp(args[1], args+1);
	
	return 0;
}
