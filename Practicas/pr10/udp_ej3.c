#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

int const IN = 0;

int main(int argc, char** argv){

	//estructuras addr_info
	struct addrinfo hints;
	struct addrinfo *result, *ptr;

	//inicializamos la estructura hints
	hints.ai_flags = AI_PASSIVE; //devuelve 0.0.0.0 o ::
	hints.ai_family = AF_UNSPEC; //ipv4 o ipv6
	hints.ai_socktype = SOCK_DGRAM; //udp
	hints.ai_protocol = 0; //protocolo por defecto

	//devuelve las direcciones de Internet
	int rc = getaddrinfo(argv[1], argv[2], &hints, &result);

	//abrimos el socket
	int sd = socket(result->ai_family, result->ai_socktype, 0);

	//lo fijamos a las direcciones
	bind(sd, result->ai_addr, result->ai_addrlen);

	//mientras no acabar
	int acabar = 0;

	while(!acabar){

		//buffer del cliente
		char buffer[80];
		//respuesta del servidor
		char respuesta[80];
		//para obtener los datos de la conexion del cliente
		char serv[NI_MAXSERV];
		char host[NI_MAXHOST];

		//inicializamos conjunto de escucha
		fd_set read_set;
		FD_ZERO(&read_set);
		FD_SET(sd, &read_set);
		FD_SET(IN, &read_set);

		//buscamos el mayor
		int mayor = 0;
		if(sd > IN) mayor = sd;
		else mayor = IN;

		//hacemos el select para escuchar
		select(mayor+1, &read_set, NULL, NULL, NULL);

		//comprobamos que entrada ha escrito
		int is_cliente=0, is_stdin=0;
		if(FD_ISSET(sd, &read_set)){
			is_cliente=1;
		}
		else if(FD_ISSET(IN, &read_set)){
			is_stdin=1;
		}

		
		//estructura que permite ser ipv4 o ipv6
		struct sockaddr_storage cliente;

		//tamanio del cliente
		socklen_t cliente_len = sizeof(cliente);

		//si ha escrito el cliente
		if(is_cliente){

			//obtenemos el mensaje del cliente
			int c = recvfrom(sd, buffer, 80, 0,(struct sockaddr *)&cliente, &cliente_len);
			buffer[c] = '\0'; //final de String


		} //si ha escrito en stdin
		else if(is_stdin){

			//leemos de pantalla
			int num = read(IN, buffer, 80);
			buffer[num] = '\0';

		}
		
		//solo mostramos si es "t" o "d"
		int mostrar = 0;
		
		//inicializamos la longitud de la respuesta
		int resp_len = 0;

		//si es una t
		if((strcmp(buffer, "t")==0) || (strcmp(buffer, "t\n")==0)){

			//obtenemos la fecha
			time_t t = time(NULL);
			struct tm tm = *localtime(&t);
	
			//nos quedamos con la hora
			resp_len = strftime (respuesta, 80, "%R", &tm );	
			respuesta[resp_len] = '\0';

			//hay que mostrar
			mostrar = 1;

		} //si es una d
		else if((strcmp(buffer, "d")==0) || (strcmp(buffer, "d\n")==0)){
			
			//obtenemos la fecha
			time_t t = time(NULL);
			struct tm tm = *localtime(&t);
	
			//nos quedamos con la hora
			resp_len = strftime (respuesta, 80, "%F", &tm );	
			respuesta[resp_len] = '\0';

			//hay que mostrar
			mostrar = 1;
			
		} //si es "q" acabamos
		else if((strcmp(buffer, "q")==0) || (strcmp(buffer, "q\n")==0)) {
		
			acabar = 1;

		}

		//si es por red mostramos la info del cliente
		if(is_cliente){
			//obtenemos la info del cliente
			getnameinfo( (struct sockaddr *) &cliente, cliente_len, host, NI_MAXHOST, serv, NI_MAXSERV, NI_NUMERICHOST | NI_NUMERICSERV);

			//mostramos los datos de conexion
			printf("Conexion desde host: %s Puerto: %s\n", host, serv);
		}

		if(mostrar){ //mostramos lo que tengamos que mostrar

			if(is_cliente){
				//obtenemos el mensaje del cliente
				int c = sendto(sd, respuesta, resp_len, 0,(struct sockaddr *)&cliente, cliente_len);

				mostrar = 0;
			}
			else if(is_stdin){
				printf("%s\n", respuesta);

				mostrar = 0;
			}
		}

	}

	//cerramos
	close(sd);
	freeaddrinfo(result);
	return 0;
}
