#include <sys/types.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <netdb.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <unistd.h>

int const COLA = 5;

void sigchld_handler(int sig)
{
	int status;
	wait(&status);
}

void haz_cosas(int sd, int sdcon, struct sockaddr_storage cliente, socklen_t cliente_len){
	
	//mientras no acabar
	int acabar = 0;

	//para obtener los datos de la conexion del cliente
	char serv[NI_MAXSERV];
	char host[NI_MAXHOST];
	
	//obtenemos la info del cliente
	getnameinfo( (struct sockaddr *) &cliente, cliente_len, host, NI_MAXHOST, serv, NI_MAXSERV, NI_NUMERICHOST | NI_NUMERICSERV);
	
		
	//mostramos los datos de conexion
	printf("Conexion desde host: %s Puerto: %s\n", host, serv);

	while(!acabar){ //recibimos mensajes del cliente hasta que corte
		
		//buffer del cliente
		char buffer[80];
		//control para que no se salga
		int i = 0;
		int rc = 0;

		//controlamos que se reciba bien, usando '\n' como delimitador
		do{

			//recibimos del cliente
			rc = recv(sdcon, &(buffer[i]), sizeof(char), 0);

		} while(i < 79 && rc >= 1 && buffer[i++] != '\n');
		buffer[i] = '\0';

		//mandamos al cliente
		send(sdcon, buffer, strlen(buffer), 0);		
		
		//si no recibimos nada acabamos
		if(rc==0) acabar=1;
	}
	
	// cerramos la sesion con el cliente
	close(sdcon); 
	
}


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

	//para ipv4 e ipdv6
	int off = 0;
	setsockopt(sd, IPPROTO_IPV6, IPV6_V6ONLY, &off, sizeof(int));

	//lo fijamos a las direcciones
	bind(sd, result->ai_addr, result->ai_addrlen);

	//escuchamos
	listen(sd, COLA);

	while(1){

		//manejador para esperar a hijos
		struct sigaction sa;
		sa.sa_handler = sigchld_handler;
		sa.sa_flags = SA_RESTART;
		sigaction(SIGCHLD, &sa, 0);

		//estructura para guardar los datos del cliente
		struct sockaddr_storage cliente;
		socklen_t cliente_len = sizeof(cliente);

		//aceptamos conexion y sobreescribimos result
		int sdcon = accept(sd, (struct sockaddr *) &cliente, &cliente_len);

		//creamos hijos
		pid_t pid = fork();

		if(pid==0){
			haz_cosas(sd, sdcon, cliente, cliente_len);
			_exit(0);
		}

	}
	
	//liberamos memoria
	freeaddrinfo(result);
	
	//cerramos el puerto
	close(sd);
	
	
	
	return 0;
}
