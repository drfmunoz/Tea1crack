#include <stdio.h>
#include "tea.h"
#include "io.h"
#include "types.h"

main(int argc,char **argv){
	test_input_options *options;
	
	cipher_cont *cipher=NULL;
	
	options=MALLOC(input_options);
	
	unsigned long key[4]={0x1C408439,0x0152804D,0xA01D71EF,0xBC24EFF1};
									
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
		print_options(argv[0]);
		return(0);
	}
	
	cipher=read_input(options->inputfile);
	
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
	
	
	
//	printf("%08X %08X %08X %08X\n",key[0],key[1],key[2],key[3]);
//	printf("%08X %08X\n",mess[0],mess[1]);
//	printf("%08X %08X\n",ciph[0],ciph[1]);

	return(1);
}