
#ifndef SOCKET_H
#define SOCKET_H


#include <stdio.h>
#include <string.h>	// for memset()...
#include <ctype.h>	// for tolower()...
#include <stdlib.h>	// for exit()...


int criarSocket();
void enviaMensagem(const char* buf);
void fechaSocket();
	
char* leMensagem();

#endif