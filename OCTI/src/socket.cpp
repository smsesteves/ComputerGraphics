/*
* This program creates a stream socket and then begins an infinite loop.
* Each time through the loop, it accepts a connection, reads and prints out received messages
* until there is nothing coming through (the connection is closed).
* The process terminates when "quit!" is received through the socket.
* Command line:
*	simple_sr.exe
*/

#include <winsock2.h>	// 1st step for Winsock 2 port
#include "socket.h"
#define BUFS	1024
#define NAMS	64

// Helper macro for displaying errors
#define perror(s)	\
	fprintf(stderr,"\n%s %d\n", s, WSAGetLastError())

char nserver[NAMS];
struct sockaddr_in server,client;
SOCKET sock, msgsock;
int length = sizeof (struct sockaddr_in);
char buf[256];

int criarSocket()
{
	WORD wVersionRequested = MAKEWORD(1,1);	// request Winsock 1.1
	WSADATA wsaData;




	// Initialize Winsockets
	if (WSAStartup(wVersionRequested, &wsaData) == 0)	// allways needed
		printf("\nVersion allowed: %d.%d\n",
		LOBYTE(wsaData.wHighVersion),HIBYTE(wsaData.wHighVersion));
	else
	{
		fprintf(stderr,"\n Wrong version\n");
		WSACleanup();
		exit(1);
	}
	/* Create socket */
	sock = socket(PF_INET, SOCK_STREAM, 0);
	if (sock == INVALID_SOCKET)
	{
		perror("Opening stream socket");
		exit(1);
	}
	//setbuf(stdout, NULL);	// do not buffer output - DEBUGING!!





	/* Name socket as suggested by the system */
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = 0;	/* system will suggest port number */
	if (bind(sock, (struct sockaddr *)&server, sizeof server) == SOCKET_ERROR)
	{
		perror("Binding stream socket");
		exit(1);
	}

	/* Find out assigned port number and print it out */
	if (getsockname(sock, (struct sockaddr *)&server, &length) == SOCKET_ERROR)
	{
		perror("Getting socket name");
		exit(1);
	}
	if (gethostname(nserver, NAMS) == SOCKET_ERROR)
	{
		perror("Getting hostname");
		exit(1);
	}
	printf("\nServer address (hostname portnumber): %s %d\n",
		nserver, ntohs(server.sin_port));

	/* Start accepting connections */
	if (listen(sock, 5) == SOCKET_ERROR)	/* 5 refers to receiving queue length */
	{
		perror("Setting receive queue");
		exit(1);
	}

	for(;;)
	{
		struct hostent *host;
		msgsock = accept(sock, (struct sockaddr *)&client, &length);
		if (msgsock == INVALID_SOCKET)
		{
			perror("Accept");
			continue;
		}
		///*DEBUG*/ printf("\nConnection accepted\n"); /*DEBUG*/
		// get client identification
		host = gethostbyaddr((char *)&client.sin_addr, sizeof (client.sin_addr), AF_INET);
		if (host == NULL)
		{
			perror("Trying to get host by addr");
			exit(2);
		}
		break;
	}

	///*DEBUG*/ printf("\nC



	/* With the present code this statement is never reached */
} /* main */


void enviaMensagem(const char* buf)
{

	for (;;)			/* server infinite(?) cycle */
	{
		
		///*DEBUG*/ printf("\nConnecting host-port: %s-%d\n", host->h_name, ntohs(client.sin_port)); /*DEBUG*/
		if(send (msgsock, buf, strlen(buf)+1, 0)!=-1)
		{
			break;
		}
	} 

}
void fechaSocket()
{
	// Main cycle
	for (;;)			/* server infinite(?) cycle */
	{
		struct hostent *host;
		msgsock = accept(sock, (struct sockaddr *)&client, &length);
		if (msgsock == INVALID_SOCKET)
		{
			perror("Accept");
			continue;
		}
		///*DEBUG*/ printf("\nConnection accepted\n"); /*DEBUG*/
		// get client identification
		host = gethostbyaddr((char *)&client.sin_addr, sizeof (client.sin_addr), AF_INET);
		if (host == NULL)
		{
			perror("Trying to get host by addr");
			break;
		}
		///*DEBUG*/ printf("\nConnecting host-port: %s-%d\n", host->h_name, ntohs(client.sin_port)); /*DEBUG*/

		if (closesocket(msgsock) == SOCKET_ERROR)
			perror("Closing message socket");
		else
			break;
	} // for()
}

char* leMensagem()
{

	// Main cycle
	for (;;)			/* server infinite(?) cycle */
	{
		
		///*DEBUG*/ printf("\nConnecting host-port: %s-%d\n", host->h_name, ntohs(client.sin_port)); /*DEBUG*/
		if(recv(msgsock, buf, BUFS, 0)>0)
		{
			break;
		}
	} 
	return buf;
}