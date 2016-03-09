#include "main.h"

unsigned char (*op[OP_NUM])(struct lmc* src);

int main(int argc, char* argv[]){
	
	//check for proper input
	if(argc==1 || argc > 4){
		printf("%s: <filename> <memory length>\n",argv[0]);
		return -1;
	}

	//check to see if file exists, if it does read it in as data
	char* data = ftd(argv[1]);
	if(!data){
		printf("%s: please input valid file\n",argv[0]);
		return -1;
	}

	//check to see if memory is input as a number, if not request proper input
	int mem_length = atoi(argv[2]);
	if(!mem_length){
		printf("%s: please input valid memory length\n",argv[0]);
		free(data);
		return -1;
	}

	//check if debug flag set
	if(argc > 3){
			
	}

	//if everything checks out, create lmc and start simulating
	struct lmc* sim = malloc(sizeof(struct lmc));
	sim->dat = data;
	sim->mem = malloc(sizeof(char)*mem_length);
	sim->mem_size = mem_length;
	//make table of function pointers to opcodes
	op[0]=hlt;
	op[1]=add;
	op[2]=sub;
	op[3]=sta;
	op[4]=lda;
	op[5]=bra;
	op[6]=brz;
	op[7]=brp;
	op[8]=inp;
	op[9]=out;	
	
	//main loop, loop through loaded program until it ends
	for(sim->ip=0;sim->dat[sim->ip]!='\0';){
		print_debug(sim);
		op[sim->dat[sim->ip]](sim);//call corresponding opcode
	}

	//cleanup
	cleanup(sim);
	return 0;

}

//file to data
char* ftd(char* src){

	FILE* fp;
	
	//if you can't open a file, return
	if(!(fp = fopen(src, "r"))){
		return 0;
	}

	fseek(fp,0,SEEK_END);
	int sz = ftell(fp);
	rewind(fp);

	char* data = malloc(sizeof(char)*(sz+1));

	fread(data,sizeof(char),sz,fp);

	data[sz]='\0';

	fclose(fp);

	return data;
}

//frees little man sim and any associated data
int cleanup(struct lmc* src){
	free(src->dat);
	free(src->mem);
	free(src);
	return 0;
}

int print_debug(struct lmc* src){
	printf("---------------------------\n");
	printf("ip: %i reg: %i mem_size: %i inst: %i\n",src->ip,src->reg,src->mem_size,src->dat[src->ip]);
	int i;
	for(i=0;i<src->mem_size;i++){
		if(i%10==0)
			printf("\n%i: ",i);
		printf("%i ",src->mem[i]);
	}
	printf("\n---------------------------\n");
	return 0;	
}

unsigned char hlt(struct lmc* src){
	cleanup(src);
	exit(1);
	return 0;
}
unsigned char add(struct lmc* src){
	int addr = src->dat[src->ip+1];
	src->reg += src->mem[addr];
	src->ip += 2;
	return 0;
}
unsigned char sub(struct lmc* src){
	int addr = src->dat[src->ip+1];
	src->reg -= src->mem[addr];
	src->ip += 2;
	return 0;
}
unsigned char sta(struct lmc* src){
	int addr = src->dat[src->ip+1];
	src->mem[addr] = src->reg;
	src->ip += 2;
	return 0;
}
unsigned char lda(struct lmc* src){
	int addr = src->dat[src->ip+1];
	src->reg = src->mem[addr];
	src->ip += 2;
	return 0;
}
unsigned char bra(struct lmc* src){
	src->ip = src->dat[src->ip+1];
	return 0;
}
unsigned char brz(struct lmc* src){
	if(!src->reg)
		src->ip = src->dat[src->ip+1];
	else
		src->ip+=2;
	return 0;
}
unsigned char brp(struct lmc* src){
	if(src->reg > 0)
		src->ip = src->dat[src->ip+1];
	else
		src->ip+=2;
	return 0;
}
unsigned char inp(struct lmc* src){
	src->reg=getchar();
	src->ip++;
	return 0;
}
unsigned char out(struct lmc* src){
	putchar(src->reg);
	src->ip++;
	return 0;
}
