#ifndef _MAIN_H_
#define _MAIN_H_

#include <stdio.h>
#include <stdlib.h>

//data for little man computer
struct lmc{
	unsigned char reg,mem_size,flags;
	char* mem; //instructions
	char* dat; //data
	unsigned int ip;
};

//functions for little man computer opcodes
unsigned char hlt(struct lmc* src);
unsigned char add(struct lmc* src);
unsigned char sub(struct lmc* src);
unsigned char sta(struct lmc* src);
unsigned char lda(struct lmc* src);
unsigned char bra(struct lmc* src);
unsigned char brz(struct lmc* src);
unsigned char brp(struct lmc* src);
unsigned char inp(struct lmc* src);
unsigned char out(struct lmc* src);

#endif

