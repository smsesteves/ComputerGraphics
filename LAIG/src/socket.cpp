
#include "socket.h"
#include <winsock2.h>
#include <iostream>

#define BUFS	1024
#define NAMS	64

/**********************/
int port = 56142;
/**********************/


// Helper macro for displaying errors
#define perror(s)	\
	fprintf(stderr,"\n%s %d\n", s, WSAGetLastError())

char nclient[NAMS];
char buf[256];

SOCKET sock;


int connectToSocket(char* hostname)
{
	//std::cout << "Insere a porta " << std::endl;
	//std::cin >> sock;
	WORD wVersionRequested = MAKEWORD(1,1);	// request Winsock 1.1
	WSADATA wsaData;
	struct sockaddr_in server;
	struct hostent *hp;
	char buf[BUFS];
	int i;	// loop counter

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
	sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == INVALID_SOCKET)
		{
		perror("Opening stream socket");
		exit(1);
		}
	setbuf(stdout, NULL);	// do not buffer output - DEBUGING!!

	/* Connect socket using server name indicated in the command line */
	server.sin_family = AF_INET;
	hp = gethostbyname(hostname);
	if (hp == NULL)
		{
		perror("Trying to get host by name");
		exit(2);
		}
	memcpy((char *)&server.sin_addr, (char *)hp->h_addr, hp->h_length);
	server.sin_port = htons((short)port);

	if (connect(sock, (struct sockaddr *)&server, sizeof server) == SOCKET_ERROR)
	{
	perror("Connecting stream socket");
	exit(1);
	}
}

void sendMessage(const char* buf){
	if (send (sock, buf, strlen(buf)+1, 0) == SOCKET_ERROR)
		perror("Writing on stream socket");
}

char* readMessage(){
	int nread = recv(sock, buf, BUFS, 0);
		//printf("%s\n",buf);

	return buf;
}

void closeSocket(){
	if (closesocket(sock) == SOCKET_ERROR)
		perror("Closing message socket");
	//exit(0);
}