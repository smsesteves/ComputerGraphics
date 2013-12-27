#ifndef SOCKET_H
#define SOCKET_H


#include <stdio.h>
#include <string.h>	// for memcpy()...
#include <stdlib.h>	// for atoi()...
#include <ctype.h>	// for tolower()...


//bool estaConectado;
int connectToSocket(char* hostname);
void closeSocket();
void sendMessage(const char* buf);
char* readMessage();


#endif