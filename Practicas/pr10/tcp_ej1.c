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

	//devuelve las direcciones de Internet
	int rc = getaddrinfo(argv[1], argv[2], &hints, &result);

	//abrimos el socket
	int sd = socket(result->ai_family, result->ai_socktype, 0);

	//lo fijamos a las direcciones
	bind(sd, result->ai_addr, result->ai_addrlen);

	//escuchamos
	listen(sd, 5);

	//aceptamos conexion y sobreescribimos result
	int sdcon = accept(sd, result->ai_addr, &result->ai_addrlen);
	
	//mientras no acabar
	int acabar = 0;

	//para obtener los datos de la conexion del cliente
	char serv[NI_MAXSERV];
	char host[NI_MAXHOST];

	//obtenemos la info del cliente, sus datos han sobreescrito result
	getnameinfo( result->ai_addr, result->ai_addrlen, host, NI_MAXHOST, serv, NI_MAXSERV, NI_NUMERICHOST | NI_NUMERICSERV);
		
	//mostramos los datos de conexion
	printf("Conexion desde host: %s Puerto: %s\n", host, serv);

	while(!acabar){
		
		//buffer del cliente
		char buffer[80];
		
		//recibimos del cliente
		int rc = recv(sdcon, buffer, 80, 0);

		//mandamos al cliente
		send(sdcon, buffer, rc, 0);		
		
		//si no recibimos nada acabamos
		if(rc==0) acabar=1;
	}
	
	// cerramos la sesion con el cliente
	close(sdcon); 
	
	//liberamos memoria
	freeaddrinfo(result);	

	//cerramos el puerto
	close(sd);
	
	
	
	return 0;
}
