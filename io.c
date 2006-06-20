#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "io.h"
#include "types.h"
#include "tabu_search.h"

cipher_cont* read_input(char* filename){
	
	FILE *infile;
	
	cipher_cont *t_cipher;
	
	int i=0;
	int j=0;
	
	unsigned long plain[MAX_FILE_LINES][2];
	unsigned long cipher[MAX_FILE_LINES][2];
	
	char v[255];

	if(!(infile=fopen(filename,"r"))){
		fprintf(stderr,"ERROR: failed to open intput file: %s\n",filename);
		exit(0);	
	}
	
	fscanf(infile,"%s",v);
	fscanf(infile,"%s",v);
	fscanf(infile,"%s",v);
	fscanf(infile,"%s",v);
	
	while(!feof(infile)){
		fscanf(infile,"%s",v);
		
		plain[i][1]=strtoull(v+8,NULL,16);
		v[8]='\0';
		plain[i][0]=strtoull(v,NULL,16);
		
		fscanf(infile,"%s",v);
		
		cipher[i][1]=strtoull(v+8,NULL,16);
		v[8]='\0';
		cipher[i][0]=strtoull(v,NULL,16);

		i++;
	}

	t_cipher=NMALLOC(i,cipher_cont);
	
	for(j=0;j<i;j++){
		t_cipher[j].plain_message[0]=plain[j][0];
		t_cipher[j].plain_message[1]=plain[j][1];
		t_cipher[j].cipher_message[0]=cipher[j][0];
		t_cipher[j].cipher_message[1]=cipher[j][1];
	}
	t_cipher[0].size_array=i;
	fclose(infile);
	return t_cipher;
}

void parse_arguments(int argc,char** argv,input_options* options){
	
	int i;
	unsigned long tmp=0;
	options->have_input=FALSE;
	options->generate_report=TRUE;
	options->save_output=FALSE;
	options->tabu_list_length=0;
	options->tabu_iterations=0;
	options->tabu_max_decrease=0;
	options->change_move_limit=0;
	options->key_eval_percent=0;
	options->paranoid_leve=0;
	options->middle_op=FALSE;
	options->print_iter=FALSE;
	
	for(i=0;i<argc;i++){
		if(strcmp(argv[i],"-i")==0){
			options->have_input=TRUE;
			if(i+1<argc){	
				strcpy(options->inputfile,argv[i+1]);
				i++;
			}
		}
		if(strcmp(argv[i],"-o")==0){
			options->save_output=TRUE;
			
			if(i+1<argc){
				strcpy(options->outfile,argv[i+1]);
				i++;
			}
		}
		if(strcmp(argv[i],"-tstl")==0){
			if(i+1<argc){
				options->tabu_list_length=strtoull(argv[i+1],NULL,0);
				i++;
			}
		}
		if(strcmp(argv[i],"-tsiter")==0){
			if(i+1<argc){
				options->tabu_iterations=strtoull(argv[i+1],NULL,0);
				i++;
			}
		}
		if(strcmp(argv[i],"-tsdesc")==0){
			if(i+1<argc){
				options->tabu_max_decrease=strtoull(argv[i+1],NULL,0);
				i++;
			}
		}
		if(strcmp(argv[i],"-tsmch")==0){
			if(i+1<argc){
				options->change_move_limit=strtoull(argv[i+1],NULL,0);
				i++;
			}
		}
		if(strcmp(argv[i],"-tskep")==0){
			if(i+1<argc){
				tmp=strtoull(argv[i+1],NULL,0);
				options->key_eval_percent=tmp;
				options->key_eval_percent=options->key_eval_percent/100;
				i++;
			}
		}
		
		if(strcmp(argv[i],"-mop")==0){
			options->middle_op=TRUE;
		}
		
		if(strcmp(argv[i],"-paranoid")==0){
			if(i+1<argc){
				options->paranoid_leve=(int)strtoull(argv[i+1],NULL,0);
			}
		}
		if(strcmp(argv[i],"-iter")==0){
			options->print_iter=TRUE;
		}
		
		if(strcmp(argv[i],"--help")==0){
			print_options(argv[0]);
			exit(0);
		}	
	}
}

void print_options(char *name){
	fprintf(stdout,"Usage: %s -i <input_file> [options] [tabu_search_opts]\n",name);
	fprintf(stdout,"\n");
	fprintf(stdout,"options: \n");
	fprintf(stdout,"-o <out_file>\t generate output report to a file \n");
	fprintf(stdout,"WARNING:The use of this options will increase execution time \n");
	fprintf(stdout,"-iter\t\t print iteration values\n");
	fprintf(stdout,"-mop\t\t print middle operations\n");
	fprintf(stdout,"-paranoid\t set paranoid debug leve (1,2,3)\n");
	fprintf(stdout,"\t\t 1: verbose middle movement final operations\n");
	fprintf(stdout,"\t\t 2: verbose middle movement operations\n");
	fprintf(stdout,"\t\t 3: verbose middle movement operations with evaluation step\n");
	fprintf(stdout,"\n");
	fprintf(stdout,"tabu search options: \n");
	fprintf(stdout,"-tstl <integer>\t tabu list size (min 1 ,max 31)\n");
	fprintf(stdout,"-tsiter <long>\t tabu search iteration number (min 1 ,max LONG_MAX)\n");
	fprintf(stdout,"-tsdesc <long>\t tabu search maximun contiune decreace(min 1)\n");
	fprintf(stdout,"-tsmch  <long>\t tabu search movement change limit\n");
	fprintf(stdout,"-tskep   <long>\t tabu search key evaluation percent (1 - 100)\n");
	fprintf(stdout,"\n");
	fprintf(stdout,"example: %s -i input.data -o report.data -p -tstl 15 -tsiter 5000 -tsdesc 128 -tsmch 15 -tskl 90\n",name);
	fprintf(stdout,"\n");
}

void print_bit(unsigned long nume){
	int i;
	unsigned long bit=1;
	char num[33];
	for(i=0;i<32;i++){
		if(nume&bit){
			num[31-i]='1';
		}
		else{
			num[31-i]='0';
		}
		bit=bit<<1;
	}
	printf("%s\n",num);
}

void print_init(ts_params *params,input_options *options,FILE *file){
	fprintf(file,"\n");
	fprintf(file,"INPUT FILE:\t\t\t %s\n",options->inputfile);
	if(options->save_output==FALSE){
		fprintf(file,"SAVE REPORT TO FILE:\t\t\t OFF\n");
	}
	else{
		fprintf(file,"SAVE REPORT TO FILE:\t\t ON\n");
		fprintf(file,"OUTPUT FILE:\t\t\t%s\n",options->outfile);
	}
	fprintf(file,"TABU LIST LENGTH:\t\t\t %lld\n",params->tabu_list_length);
	fprintf(file,"TABU SEARCH ITERATIONS:\t\t\t %lld\n",params->tabu_iterations);
	fprintf(file,"TABU SEARCH DECREACE LIMIT:\t\t %lld\n",params->tabu_max_decrease);
	fprintf(file,"TABU MOVEMENT CHANGE LIMIT:\t\t %lld\n",params->change_move_limit);
	fprintf(file,"TABU KEY EVALUATION PERCENT:\t\t %f\n",params->key_eval_percent);
	fprintf(file,"\n");
}

void print_end(final_report *report,FILE *file){
	fprintf(file,"\n");
	fprintf(file,"FINAL REPORT\n");
	fprintf(file,"BEST LEFT RESULT: %08lX %08lX\n",report->left->key[0],report->left->key[1]);
	fprintf(file,"BEST RIGHT RESULT: %08lX %08lX\n",report->right->key[0],report->right->key[1]);
	fprintf(file,"BEST LEFT SCORE: %f\n",report->left->value);
	fprintf(file,"BEST RIGHT SCORE: %f\n",report->right->value);
	fprintf(file,"BEST LEFT RESULT PG TIME: %f\n",report->clock_left);
	fprintf(file,"BEST RIGHT RESULT PG TIME: %f\n",report->clock_right);
	fprintf(file,"BEST LEFT RESULT TIME: %f\n",difftime(report->end_left,report->init_left));
	fprintf(file,"BEST RIGHT RESULT TIME: %f\n",difftime(report->end_right,report->init_right));
	fprintf(file,"GLOBAL PG TIME: %f\n",report->clock_global);
	fprintf(file,"GLOBAL TIME: %f\n",difftime(report->end_global,report->init_global));
	fprintf(file,"LEFT KEY RESTART: %d\n",report->restart_left_control-report->change_left_count);
	fprintf(file,"RIGHT KEY RESTART: %d\n",report->restart_right_control-report->change_right_count);
	fprintf(file,"LEFT MOVEMENT CHANGE: %d\n",report->change_left_count);
	fprintf(file,"RIGHT MOVEMENT CHANGE: %d\n",report->change_right_count);
	fprintf(file,"LEFT ITERATION: %d\n",report->left_iter);
	fprintf(file,"RIGHT ITERATION: %d\n",report->right_iter);
	fprintf(file,"\n");
}

/*
 * print selected key for movement with score, bit and tabuname
 */
void print_middle(unsigned long key,float score,unsigned int bit,int block,int tabuname,FILE *file){
	fprintf(file,"->KEY:%08lX\t SCORE:%.02f\t BIT:%d\t BLOCK:%d\t TABU:%d\n",key,score,bit,block,tabuname);
}
void print_iteration(best_result *best,int iter,int block,FILE *file){
	fprintf(file,"BEST:%08lX\t SCORE:%.02f\t ITER:%d\t BLOCK:%d\n",best->key[1],best->value,block,iter);
}


void print_paranoid(paranoid *paranoid,FILE *file){
	unsigned int name;
	fprintf(file,"->KEY:%08lX\t BLOCK:%d\t TABU LIST ELEMENT:%d\n",paranoid->key,paranoid->block,paranoid->tabu);
	name=paranoid->list->name;
	paranoid->list=paranoid->list->next;
	while(1){
		if(paranoid->list->name==name)
			break;
		fprintf(file,"\t\tTABU ELEMENT:%08lX\tVALUE:%.02f\tBIT:%d\tNAME:%d\n",paranoid->list->key,paranoid->list->value,paranoid->list->bit_position,paranoid->list->name);
		paranoid->list=paranoid->list->next;
	}
}

void print_paranoid_move(paranoid *paranoid,FILE *file){
	fprintf(file,"-->KEY:%08lX\tSCORE:%.02f\tBIT:%d\tBLOCK:%d\n",paranoid->key,paranoid->score,paranoid->bit,paranoid->block);
}

void print_paranoid_all(paranoid *paranoid,FILE *file){
	fprintf(file,"--->KEY:%08lX\tKEYNUM:%d\tBLOCK:%d\tEVALKEY:%08lX\n",paranoid->key,paranoid->bit,paranoid->block,paranoid->evalkey);
}


void void_print_middle(unsigned long key,float score,unsigned int bit,int block,int tabuname,FILE *fp){
}
void void_print_iteration(best_result *best,int block,int iter,FILE *fp){
}
void void_print_paranoid(paranoid *paranoid,FILE *fp){
}
void void_print_paranoid_move(paranoid *paranoid,FILE *fp){
}
void void_print_paranoid_all(paranoid *paranoid,FILE *fp){
}

/*
void print_body(input_options *options,best_result *best,tabu_list *tabu,unsigned long *mistakes){
	int mutations=0;
	int opcode=0;
	FILE *file;
	if(options->generate_report==TRUE){
		if(options->print_output==TRUE&&options->save_output==TRUE){
			mutations=2;
		}
		else{
			mutations=1;
			if(options->print_output==TRUE){
				opcode=2;
			}
			if(options->save_output==TRUE){
				opcode=1;
			}
		}
		while(mutations>0){
			if(opcode%2==0){
				file=stdout;
			}
			else{
				if(!(file=fopen(options->outfile,"ra+"))){
					fprintf(stderr,"ERROR: failed to open output file: %s\n",options->outfile);
					exit(0);
				}
			}
			// begin file operation * /
			fprintf(file,"TABU SEARCH RESULT KEY: %#llX \t\t",best->value);
			fprintf(file,"EVAL VALUE: %f\t\t",best->eval_value);
			fprintf(file,"MISTAKES: %ld\n",(long)*mistakes);
			//begin file operation * / 
			if(opcode%2!=0){
				fclose(file);
			}
			opcode--;
			mutations--;
		}
	}	
}

void print_csv(input_options *options,best_result *best){
	FILE *file;
	char newfile[255];
	strcpy(newfile,options->outfile);
	strcat(newfile,".csv");
	if(options->generate_report==TRUE){
		if(options->save_output==TRUE){
			if(!(file=fopen(newfile,"wa+"))){
				fprintf(stderr,"ERROR: failed to open|create output file: %s\n",options->outfile);
				exit(0);
			}
			fprintf(file,"%llX,%0.4f\n",best->value,best->eval_value);
		}
	}
}

void print_end(input_options *options,best_result *best){
	int mutations=0;
	int opcode=0;
	FILE *file;
	if(options->generate_report==TRUE){
		if(options->print_output==TRUE&&options->save_output==TRUE){
			mutations=2;
		}
		else{
			mutations=1;
			if(options->print_output==TRUE){
				opcode=2;
			}
			if(options->save_output==TRUE){
				opcode=1;
			}
		}
		while(mutations>0){
			if(opcode%2==0){
				file=stdout;
			}
			else{
				if(!(file=fopen(options->outfile,"ra+"))){
					fprintf(stderr,"ERROR: failed to open output file: %s\n",options->outfile);
					exit(0);
				}
			}
			//begin file operation * /
			fprintf(file,"TABU SEARCH BEST RESULT KEY: %#llX \t\t",best->value);
			fprintf(file,"EVAL VALUE: %f\n",best->eval_value);
			//begin file operation
			if(opcode%2!=0){
				fclose(file);
			}
			opcode--;
			mutations--;
		}
	}	
}

void print_middle_body(input_options *options,best_result *best ,tabu_list *tabu,unsigned long *mistakes,unsigned long long *key,int iteration,unsigned int tabu_control){
	int mutations=0;
	int opcode=0;
	int i;
	 
	FILE *file;
	if(options->generate_report==TRUE){
		if(options->print_output==TRUE&&options->save_output==TRUE){
			mutations=2;
		}
		else{
			mutations=1;
			if(options->print_output==TRUE){
				opcode=2;
			}
			if(options->save_output==TRUE){
				opcode=1;
			}
		}
		while(mutations>0){
			if(opcode%2==0){
				file=stdout;
			}
			else{
				if(!(file=fopen(options->outfile,"wr+"))){
					fprintf(stderr,"ERROR: failed to create output file: %s\n",options->outfile);
					exit(0);
				}
			}

			for(i=0;i<options->tabu_list_length;i++){
				if(tabu->name==tabu_control-1)
					break;
				tabu=tabu->next;
			}
			
			fprintf(file,"ITERATION:  %i \t",iteration);
			fprintf(file,"CURRENT KEY: %#llX\t",tabu->value);
			fprintf(file,"CURRENT VALUE: %f \t",tabu->eval_value);
			fprintf(file,"CURRENT MOD: %d \t",tabu->bit_position);
			fprintf(file,"BEST KEY: %#llX \t",best->value);
			fprintf(file,"BEST VALUE: %f \t",best->eval_value);
			fprintf(file,"MISTAKES: %lld \n",(long long)*mistakes);
			
			for(i=0;i<options->tabu_list_length;i++){
				fprintf(stdout,"tabu: %d %#llX\t",i,tabu->value);
				fprintf(stdout,"value: %f \t",tabu->eval_value);
				fprintf(stdout,"bit: %d\t",tabu->bit_position);
				fprintf(stdout,"name: %d\n",tabu->name);
				tabu=tabu->next;
			}

			if(opcode%2!=0){
				fclose(file);
			}
			opcode--;
			mutations--;
		}
	}
}*/