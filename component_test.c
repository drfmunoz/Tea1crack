#include <stdio.h>
#include <stdlib.h>
#include "tea.h"
#include "io.h"

int main(int argc,char **argv){
	
	input_options *options;
	
	cipher_cont *cipher=NULL;
	
	int i;
	options=MALLOC(input_options);
	
	/*
	 * parse input parameters
	 */
	if(argc>1){
		parse_arguments(argc,argv,options);
		if(options->have_input==FALSE){
			fprintf(stderr,"ERROR: NO INPUT FILE");
			return(0);
		}
	}
	else{
		print_options(argv[0]);
		return(0);
	}
	
	unsigned long key[4]={0x551D355C,0x0152804E,0x901D71EE,0xBC24EFF2};
	
	cipher=read_input(options->inputfile);
	
	for(i=0;i < (cipher[0].size_array);i++){
		tea_encrypt(cipher[i].plain_message,cipher[i].cipher_message,key);
		printf(">>\n");
		
		printf("PP: %08X %08X %08X %08X\n",key[0],key[1],key[2],key[3],key[4]);
		key[0]=0x0;
		key[2]=0x0;
		gamma_tea(cipher[i].plain_message,cipher[i].cipher_message,key);
		printf("GT: %08X %08X %08X %08X\n",key[0],key[1],key[2],key[3],key[4]);
		delta_tea(cipher[i].plain_message,cipher[i].cipher_message,key);
		printf("DT: %08X %08X %08X %08X\n",key[0],key[1],key[2],key[3],key[4]);
		key[1]=0x0;
		key[3]=0x0;
		alpha_tea(cipher[i].plain_message,cipher[i].cipher_message,key);
		printf("AT: %08X %08X %08X %08X\n",key[0],key[1],key[2],key[3],key[4]);
		beta_tea(cipher[i].plain_message,cipher[i].cipher_message,key);
		printf("BT: %08X %08X %08X %08X\n",key[0],key[1],key[2],key[3],key[4]);
		printf("<<\n");
	}
	return(0);
}