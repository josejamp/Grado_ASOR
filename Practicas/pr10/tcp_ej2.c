#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <time.h>
#include <string.h>


int main(int argc, char** argv){
	
	//estructuras addr_info
	struct addrinfo hints;
	struct addrinfo *result, *ptr;

	//inicializamos la estructura hints
	hints.ai_flags = AI_PASSIVE; //devuelve 0.0.0.0 o ::
	hints.ai_family = AF_UNSPEC; //ipv4 o ipv6
	hints.ai_socktype = SOCK_STREAM; //tcp
	hints.ai_protocol = 0; //protocolo por defecto

	//obtenemos los datos del servidor
	int rc = getaddrinfo(argv[1], argv[2], &hints, &result);
	if(rc != 0) perror("Error en getaddrinfo():");

	//abrimos el socket
	int sd = socket(result->ai_family, result->ai_socktype, 0);
	if(sd < 0) perror("Error en socket():");

	//nos conectamos al servidor
	if( connect(sd, result->ai_addr, result->ai_addrlen) != 0 )
		perror("Error en connect()");

	//mientrass no se envie 'Q'
	int acabar = 0;
	
	while(!acabar){

		//buffer del cliente
		char buffer[80];

		//leemos de pantalla
		int num = scanf("%s", buffer);
		num = strlen(buffer);
		if(strcmp(buffer, "Q") == 0) acabar=1;
		else{
		
			//enviamos al servidor
			int rs = send(sd, buffer, num+1, 0);
	
			//recibimos respuesta del servidor
			int rc = recv(sd, buffer, 80, 0);
			
			//mostramos por pantalla
			printf("%s\n", buffer);
		}
	}
	
	//cerramos el puerto
	close(sd);

	return 0;
}
