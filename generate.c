/** 
 * \file generate.c
 * \brief Generation of test set for TEA Tabu Search
 * \ingroup test
 * \author Freddy Mun~oz Ramirez <frmunoz(at)inf.utfsm.cl>
 * \date Autumn 2006
 * \license <br> This code can be re-distributed under MIT License
 */
#include <stdio.h>
#include <stdlib.h>
#include "tea.h"
#include "io.h"
#include "types.h"
/**
 * Generate a test set with TEA cipher
 * \param arcg number of input arguments
 * \param argv input argument string
 */
int main(int argc,char **argv){
	
	FILE *fp;
	generate_options *options;
	unsigned int randomic;
	long seed=0x0;
	unsigned long number=0;
	int i;
	unsigned long key[4]={0x0,0x0,0x0,0x0};
	unsigned long message[2]={0x0,0x0};
	unsigned long cipher[2]={0x0,0x0};
	
	if((options=MALLOC(generate_options))==NULL){
		fprintf(stderr,"ERROR: FAILED TO ALLOCATE MEMORY\n");
		exit(1);
	}
	
	if(argc>1){
		parse_generate_arguments(argc,argv,options);
		if(options->seed==0){
			fprintf(stderr,"SEED CANNOT BE 0 OR MUST BE ENTERED\n");
			return(1);
		}
		if(options->amount==0){
			fprintf(stderr,"AMOUNT CANNOT BE 0 OR MUST BE ENTERED\n");
			return(1);
		}
	}
	else{
		print_generate_options(argv[0]);
		return(1);
	}
	
	
	if(options->usefile){
		if((fp=fopen(options->outfile,"w+"))==NULL){
			fprintf(stderr,"ERROR CREATING FILE:%s\n",options->outfile);
		}
	}
	else fp=stdout;
	
	
	seed=options->seed;
	number=options->amount;
	
	srand((unsigned int) seed);
	rand();
	rand();
	
	if(!options->usekey){
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
	}
	else{
		key[0]=options->key[0];
		key[1]=options->key[1];
		key[2]=options->key[2];
		key[3]=options->key[3];
	}
	fprintf(fp,"Texto ClaroF\tTexto Cifrado||%08lX%08lX%08lX%08lX \n",key[0],key[1],key[2],key[3]);
	fprintf(fp,"\n");
	for(i=0;i<number;i++){
		message[0]=(unsigned long)rand();
		message[1]=(unsigned long)rand();
		tea_encrypt(message,cipher,key);
		fprintf(fp,"%08lX%08lX\t%08lX%08lX\n",message[0],message[1],cipher[0],cipher[1]);
	}
	if(options->usefile)
		fclose(fp);
	fprintf(stdout,"CREATION FINALIZED\n");
	fprintf(stdout,"KEY:%08lX %08lX %08lX %08lX\n",key[0],key[1],key[2],key[3]);
	return(1);
}