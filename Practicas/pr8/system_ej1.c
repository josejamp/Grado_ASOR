#include <sched.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char** args){
	
	//ejecutamos lo que haya en args[1]
	int salida = system(args[1]);
	
	
	return 0;
}
