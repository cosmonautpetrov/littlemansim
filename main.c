#include "main.h"

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
	struct lmc* sim = malloc(sizeof(lmc));
	lmc->dat = data;
	lmc->mem = malloc(sizeof(char)*mem_length);

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
	data[sz]='\0';

	fclose(fp);

	return data;
}
