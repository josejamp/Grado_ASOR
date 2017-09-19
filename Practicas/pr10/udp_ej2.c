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
	hints.ai_socktype = SOCK_DGRAM; //udp
	hints.ai_protocol = 0; //protocolo por defecto

	//obtenemos los datos del servidor
	int rc = getaddrinfo(argv[1], argv[2], &hints, &result);
	if(rc != 0) perror("Error en getaddrinfo():");

	//abrimos el socket
	int sd = socket(result->ai_family, result->ai_socktype, 0);
	if(sd < 0) perror("Error en socket():");

	//buffer del cliente
	char buffer[80];
	//respuesta del servidor
	char respuesta[80];
	//para obtener los datos de la conexion del cliente
	char serv[NI_MAXSERV];
	char host[NI_MAXHOST];

	//estructura que permite ser ipv4 o ipv6
	struct sockaddr_storage servidor;

	//enviamos el comando al servidor
	int c = sendto(sd, argv[3], strlen(argv[3]), 0, result->ai_addr, result->ai_addrlen);
	if(c < 0) perror("Error en sento");

	//recibimos la respuesta
	int resp_len = recvfrom(sd, respuesta, 80, 0, result->ai_addr, &result->ai_addrlen);
	if(resp_len < 0) perror("Error en recfrom()");
	respuesta[resp_len] = '\0';

	printf("%s\n", respuesta);
	

	return 0;
}
