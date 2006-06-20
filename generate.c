#include <stdio.h>
#include <stdlib.h>
#include "tea.h"
#include "io.h"
// ./generate file seed number
int main(int argc,char **argv){
	
	FILE *fp;
	unsigned int randomic;
	long seed=0x0;
	long number=0;
	int i;
	unsigned long key[4]={0x0,0x0,0x0,0x0};
	unsigned long message[2]={0x0,0x0};
	unsigned long cipher[2]={0x0,0x0};
	
	if((fp=fopen(argv[1],"w+"))==NULL){
		fprintf(stderr,"ERROR CREATING FILE:%s\n",argv[1]);
	}
	
	seed=strtol(argv[2],NULL,0);
	number=strtol(argv[3],NULL,0);
	
	srand((unsigned int) seed);
	rand();
	rand();
	if((randomic=rand())>0){
		key[0]=(unsigned long)randomic;
	}
	if((randomic=rand())>0){
		key[1]=(unsigned long)randomic;
	}
	if((randomic=rand())>0){
		key[2]=(unsigned long)randomic;
	}
	if((randomic=rand())>0){
		key[3]=(unsigned long)randomic;
	}
	fprintf(fp,"Texto ClaroF\tTexto Cifrado||%08X%08X%08X%08X \n",key[0],key[1],key[2],key[3]);
	fprintf(fp,"\n");
	for(i=0;i<number;i++){
		message[0]=(unsigned long)rand();
		message[1]=(unsigned long)rand();
		tea_encrypt(message,cipher,key);
		fprintf(fp,"%08X%08X\t%08X%08X\n",message[0],message[1],cipher[0],cipher[1]);
	}
	fclose(fp);
	fprintf(stdout,"CREATION FINALIZE\n");
	fprintf(stdout,"KEY:%08X %08X %08X %08X\n",key[0],key[1],key[2],key[3]);
	return(1);
}