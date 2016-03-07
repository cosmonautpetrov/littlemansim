#include "main.h"

unsigned char (*op[OP_NUM])(struct lmc* src);

int main(int argc, char* argv[]){
	
	//check for proper input
	if(argc==1 || argc > 3){
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

	//if everything checks out, create lmc and start simulating
	struct lmc* sim = malloc(sizeof(struct lmc));
	sim->dat = data;
	sim->mem = malloc(sizeof(char)*mem_length);

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
	
	for(sim->ip=0;sim->dat[sim->ip]!='\0';sim->ip+=2){
		op[sim->dat[sim->ip]](sim);
	}

	cleanup(sim);
	return 0;

}

char* ftd(char* src){

	FILE* fp;

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

int cleanup(struct lmc* src){
	free(src->dat);
	free(src->mem);
	free(src);
	return 0;
}

unsigned char hlt(struct lmc* src){
	return 0;
}
unsigned char add(struct lmc* src){
	return 0;
}
unsigned char sub(struct lmc* src){
	return 0;
}
unsigned char sta(struct lmc* src){
	return 0;
}
unsigned char lda(struct lmc* src){
	return 0;
}
unsigned char bra(struct lmc* src){
	return 0;
}
unsigned char brz(struct lmc* src){
	return 0;
}
unsigned char brp(struct lmc* src){
	return 0;
}
unsigned char inp(struct lmc* src){
	printf("get input\n");
	return 0;
}
unsigned char out(struct lmc* src){
	printf("so and so function\n");
	return 0;
}
