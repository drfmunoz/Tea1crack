#include <stdio.h>
#include <stdlib.h>
#include "tea.h"
#include "io.h"
#include "types.h"

int main(int argc,char **argv){
	test_input_options *options;
	
	cipher_cont *cipher=NULL;
	
	options=MALLOC(test_input_options);
	
	unsigned long key[4]={0x0,0x0,0x0,0x0};
									
	unsigned long messcipher[2]={0x0,0x0};
	unsigned long decipher[2]={0x0,0x0};
	
	int i;
	
	/*
	 * parse input parameters
	 */
	if(argc>1){
		parse_test_arguments(argc,argv,options);
		if(options->have_input==FALSE){
			fprintf(stderr,"ERROR: NO INPUT FILE");
			return(0);
		}
	}
	else{
		print_test_options(argv[0]);
		return(0);
	}
	
	cipher=read_input(options->inputfile);
	
	key[0]=options->key1;
	key[1]=options->key2;
	key[2]=options->key3;
	key[3]=options->key4;
		
		
	for(i=0;i < (cipher[0].size_array)-1;i++){
		messcipher[1]=0x0;
		messcipher[0]=0x0;
		decipher[1]=0x0;
		decipher[0]=0x0;
		tea_encrypt(cipher[i].plain_message,messcipher,key);
		tea_decrypt(cipher[i].cipher_message,decipher,key);
		printf("PLAIN-ACIPHER %08lX %08lX\t",cipher[i].plain_message[0],cipher[i].plain_message[1]);
		printf("%08lX %08lX\n",messcipher[0],messcipher[1]);
		printf("DPLAIN-CIPHER %08lX %08lX\t",decipher[0],decipher[1]);
		printf("%08lX %08lX\n",cipher[i].cipher_message[0],cipher[i].cipher_message[1]);
	}
	return(1);
}