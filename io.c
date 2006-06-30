/** 
 * \file io.c
 * \brief input output functions
 * \ingroup io
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "io.h"
#include "types.h"
#include "tabu_search.h"

/**
 * Read input file and put the content into corresponding structure
 * \param filename Filename of input file
 */
cipher_cont* read_input(char* filename)
{
	
	FILE *infile;
	
	cipher_cont *t_cipher;
	
	int i=0;
	int j=0;
	
	unsigned long plain[MAX_FILE_LINES][2];
	unsigned long cipher[MAX_FILE_LINES][2];
	
	char v[255];

	if(!(infile=fopen(filename,"r")))
	{
		fprintf(stderr,"ERROR: failed to open intput file: %s\n",filename);
		exit(0);	
	}
	
	fscanf(infile,"%s",v);
	fscanf(infile,"%s",v);
	fscanf(infile,"%s",v);
	fscanf(infile,"%s",v);
	
	while(!feof(infile))
	{
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
	
	for(j=0;j<i;j++)
	{
		t_cipher[j].plain_message[0]=plain[j][0];
		t_cipher[j].plain_message[1]=plain[j][1];
		t_cipher[j].cipher_message[0]=cipher[j][0];
		t_cipher[j].cipher_message[1]=cipher[j][1];
	}
	t_cipher[0].size_array=i;
	fclose(infile);
	return t_cipher;
}
/**
 * Convert full_test_input_options to input_options
 * \param options Tabu Serach general input options
 */
input_options* convert_full_test_opt_to_gen(full_test_input_options* options)
{
	input_options *t_options;
	if((t_options=MALLOC(input_options))==NULL)
	{
		fprintf(stderr,"ERROR: FAILED TO ALLOCATE MEMORY\n");
		exit(1);
	}
	t_options->have_input=options->have_input;
	t_options->generate_report=TRUE;
	t_options->save_output=options->save_output;
	t_options->tabu_list_length=options->init_tabu_list_length;
	t_options->tabu_iterations=options->init_tabu_iterations;
	t_options->tabu_max_decrease=options->init_tabu_max_decrease;
	t_options->change_move_limit=options->init_change_move_limit;
	t_options->key_eval_percent=options->min_key_eval_percent;
	strcpy(t_options->outfile,options->outfile);
	t_options->paranoid_leve=0;
	t_options->middle_op=FALSE;
	t_options->print_iter=FALSE;
	return(t_options);
}
/**
 *
 * \param argc
 * \param argv
 * \param options
 */
void parse_full_test_arguments(int argc,char** argv,full_test_input_options* options)
{

	int i;
	unsigned long tmp;
	options->save_output=FALSE;
	options->have_input=FALSE;
	options->max_tabu_list_length=0;  
	options->max_tabu_iterations=0;	
	options->max_tabu_max_decrease=0;
	options->max_change_move_limit=0; 
	options->init_tabu_list_length=0; 
	options->init_tabu_iterations=0;	
	options->init_tabu_max_decrease=0; 
	options->init_change_move_limit=0;
	options->var_tabu_list_length=0; 
	options->var_tabu_iterations=0;	  
	options->var_tabu_max_decrease=0; 
	options->var_change_move_limit=0; 
	options->min_key_eval_percent=0;             
	options->var_key_eval_percent=0;
	
	for(i=0;i<argc;i++)
	{
		if(strcmp(argv[i],"-i")==0)
		{
			options->have_input=TRUE;
			if(i+1<argc)
			{	
				strcpy(options->inputfile,argv[i+1]);
				i++;
			}
		}
		if(strcmp(argv[i],"-o")==0)
		{
			options->save_output=TRUE;
			
			if(i+1<argc)
			{
				strcpy(options->outfile,argv[i+1]);
				i++;
			}
		}
		if(strcmp(argv[i],"--help")==0)
		{
			print_full_test_options(argv[0]);
			exit(0);
		}
		if(strcmp(argv[i],"-maxtstl")==0)
		{
			if(i+1<argc)
			{
				options->max_tabu_list_length=strtoull(argv[i+1],NULL,0);
				i++;
			}
		}
		if(strcmp(argv[i],"-maxtsiter")==0)
		{
			if(i+1<argc)
			{
				options->max_tabu_iterations=strtoull(argv[i+1],NULL,0);
				i++;
			}
		}
		if(strcmp(argv[i],"-maxtsmdec")==0)
		{
			if(i+1<argc)
			{
				options->max_tabu_max_decrease=strtoull(argv[i+1],NULL,0);
				i++;
			}
		}
		if(strcmp(argv[i],"-maxtschm")==0)
		{
			if(i+1<argc)
			{
				options->max_change_move_limit=strtoull(argv[i+1],NULL,0);
				i++;
			}
		}
		if(strcmp(argv[i],"-itstl")==0)
		{
			if(i+1<argc)
			{
				options->init_tabu_list_length=strtoull(argv[i+1],NULL,0);
				i++;
			}
		}
		if(strcmp(argv[i],"-itsiter")==0)
		{
			if(i+1<argc)
			{
				options->init_tabu_iterations=strtoull(argv[i+1],NULL,0);
				i++;
			}
		}
		if(strcmp(argv[i],"-itsmdec")==0)
		{
			if(i+1<argc)
			{
				options->init_tabu_max_decrease=strtoull(argv[i+1],NULL,0);
				i++;
			}
		}
		if(strcmp(argv[i],"-itschm")==0)
		{
			if(i+1<argc)
			{
				options->init_change_move_limit=strtoull(argv[i+1],NULL,0);
				i++;
			}
		}
		if(strcmp(argv[i],"-vartstl")==0)
		{
			if(i+1<argc)
			{
				options->var_tabu_list_length=strtoull(argv[i+1],NULL,0);
				i++;
			}
		}
		if(strcmp(argv[i],"-vartsiter")==0){
			if(i+1<argc){
				options->var_tabu_iterations=strtoull(argv[i+1],NULL,0);
				i++;
			}
		}
		if(strcmp(argv[i],"-vartsmdec")==0)
		{
			if(i+1<argc)
			{
				options->var_tabu_max_decrease=strtoull(argv[i+1],NULL,0);
				i++;
			}
		}
		if(strcmp(argv[i],"-vartschm")==0)
		{
			if(i+1<argc)
			{
				options->var_change_move_limit=strtoull(argv[i+1],NULL,0);
				i++;
			}
		}
		if(strcmp(argv[i],"-mintskep")==0)
		{
			if(i+1<argc)
			{
				tmp=strtoull(argv[i+1],NULL,0);
				options->min_key_eval_percent=tmp;
				options->min_key_eval_percent=options->min_key_eval_percent/100;
				i++;
			}
		}
		if(strcmp(argv[i],"-vartskep")==0)
		{
			if(i+1<argc)
			{
				tmp=strtoull(argv[i+1],NULL,0);
				options->var_key_eval_percent=tmp;
				options->var_key_eval_percent=options->var_key_eval_percent/100;
				i++;
			}
		}
	}            
}
/**
 *
 * \param argc
 * \param argv
 * \param options
 */
void parse_test_arguments(int argc,char** argv,test_input_options* options)
{
	int i;
	options->save_output=FALSE;
	options->have_input=FALSE;
	options->key1=0x0;
	options->key2=0x0;
	options->key3=0x0;
	options->key4=0x0;
	for(i=0;i<argc;i++){
		if(strcmp(argv[i],"-i")==0)
		{
			options->have_input=TRUE;
			if(i+1<argc)
			{	
				strcpy(options->inputfile,argv[i+1]);
				i++;
			}
		}
		if(strcmp(argv[i],"-o")==0)
		{
			options->save_output=TRUE;
			if(i+1<argc)
			{
				strcpy(options->outfile,argv[i+1]);
				i++;
			}
		}
		if(strcmp(argv[i],"--help")==0)
		{
			print_test_options(argv[0]);
			exit(0);
		}
		if(strcmp(argv[i],"-key")==0)
		{
			if(i+4<argc)
			{
				options->key1=strtoull(argv[i+1],NULL,16);
				options->key2=strtoull(argv[i+2],NULL,16);
				options->key3=strtoull(argv[i+3],NULL,16);
				options->key4=strtoull(argv[i+4],NULL,16);
				i++;
			}
		}
	}
}
/**
 *
 * \param argc
 * \param argv
 * \param options
 */
void parse_generate_arguments(int argc,char** argv,generate_options *options)
{
	int i;
	options->userandom=TRUE;				
	options->usefile=FALSE;		
	options->usekey=FALSE;			
	options->seed=0;			
	options->amount=0;			
	for(i=0;i<argc;i++)
	{
		if(strcmp(argv[i],"-o")==0)
		{
			options->usefile=TRUE;
			if(i+1<argc)
			{	
				strcpy(options->outfile,argv[i+1]);
				i++;
			}
		}
		if(strcmp(argv[i],"--help")==0)
		{
			print_generate_options(argv[0]);
			exit(0);
		}
		if(strcmp(argv[i],"-key")==0)
		{
			options->usekey=TRUE;
			options->userandom=FALSE;
			if(i+4<argc)
			{
				options->key[0]=strtoull(argv[i+1],NULL,16);
				options->key[1]=strtoull(argv[i+2],NULL,16);
				options->key[2]=strtoull(argv[i+3],NULL,16);
				options->key[3]=strtoull(argv[i+4],NULL,16);
				i++;
			}
		}
		if(strcmp(argv[i],"-n")==0)
		{
			if(i+1<argc)
			{
				options->amount=strtoull(argv[i+1],NULL,0);
				i++;
			}

		}
		if(strcmp(argv[i],"-seed")==0)
		{
			if(i+1<argc)
			{
				options->seed=strtoull(argv[i+1],NULL,0);
				i++;
			}
		}
	}	
}
/**
 *
 * \param argc
 * \param argv
 * \param options
 */
void parse_ts_arguments(int argc,char** argv,input_options* options)
{
	
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
	
	for(i=0;i<argc;i++)
	{
		if(strcmp(argv[i],"-i")==0)
		{
			options->have_input=TRUE;
			if(i+1<argc){	
				strcpy(options->inputfile,argv[i+1]);
				i++;
			}
		}
		if(strcmp(argv[i],"-o")==0)
		{
			options->save_output=TRUE;
			if(i+1<argc)
			{
				strcpy(options->outfile,argv[i+1]);
				i++;
			}
		}
		if(strcmp(argv[i],"-tstl")==0)
		{
			if(i+1<argc)
			{
				options->tabu_list_length=strtoull(argv[i+1],NULL,0);
				i++;
			}
		}
		if(strcmp(argv[i],"-tsiter")==0)
		{
			if(i+1<argc)
			{
				options->tabu_iterations=strtoull(argv[i+1],NULL,0);
				i++;
			}
		}
		if(strcmp(argv[i],"-tsdesc")==0)
		{
			if(i+1<argc)
			{
				options->tabu_max_decrease=strtoull(argv[i+1],NULL,0);
				i++;
			}
		}
		if(strcmp(argv[i],"-tsmch")==0)
		{
			if(i+1<argc)
			{
				options->change_move_limit=strtoull(argv[i+1],NULL,0);
				i++;
			}
		}
		if(strcmp(argv[i],"-tskep")==0)
		{
			if(i+1<argc)
			{
				tmp=strtoull(argv[i+1],NULL,0);
				options->key_eval_percent=tmp;
				options->key_eval_percent=options->key_eval_percent/100;
				i++;
			}
		}
		
		if(strcmp(argv[i],"-mop")==0)
		{
			options->middle_op=TRUE;
		}
		
		if(strcmp(argv[i],"-paranoid")==0)
		{
			if(i+1<argc)
			{
				options->paranoid_leve=(int)strtoull(argv[i+1],NULL,0);
			}
		}
		if(strcmp(argv[i],"-iter")==0)
		{
			options->print_iter=TRUE;
		}
		
		if(strcmp(argv[i],"--help")==0)
		{
			print_ts_options(argv[0]);
			exit(0);
		}	
	}
}
void print_full_test_options(char *name){
	fprintf(stdout,"Usage: %s -i <input_file> [options]\n",name);
	fprintf(stdout,"\n");
	fprintf(stdout,"options: \n");
	fprintf(stdout,"-o\t\t<out_file>\t generate output report to a file (RECOMENDED)\n");
	fprintf(stdout,"-maxtstl\t<long>\t\t max tabu search list length\n");
	fprintf(stdout,"-maxtsiter\t<long> \t\t max tabu search iteration\n");
	fprintf(stdout,"-maxtsmdec\t<long>\t\t max tabu search performance decreace\n");
	fprintf(stdout,"-maxtschm\t<long>\t\t max tabu searh mistakes for change movement\n");
	fprintf(stdout,"-itstl\t\t<long>\t\t initial tabu search list length\n");
	fprintf(stdout,"-itsiter\t<long>\t\t initial tabu search iteration\n");
	fprintf(stdout,"-itsmdec\t<long>\t\t initial tabu search performance decreace\n");
	fprintf(stdout,"-itschm\t\t<long>\t\t initial tabu searh mistakes for change movement\n");
	fprintf(stdout,"-vartstl\t<long>\t\t variation of tabu search list length\n");
	fprintf(stdout,"-vartsiter\t<long> \t\t variation of tabu search iteration\n");
	fprintf(stdout,"-vartsmdec\t<long>\t\t variation of tabu search performance decreace\n");
	fprintf(stdout,"-vartschm\t<long>\t\t variation of tabu searh mistakes for change movement\n");
	fprintf(stdout,"-mintskep\t<long>\t\t minimal key evaluation percent\n");
	fprintf(stdout,"-vartskep\t<long>\t\t variation of key evaluation percent\n");	
	fprintf(stdout,"\n");
	fprintf(stdout,"example: %s -i input.data -o report.data\n",name);
	fprintf(stdout,"example: %s -i input.data -o report.data -maxtstl 32 -maxtsiter 5000 -maxtsmdec 64 -maxtschm 4 -itstl 1 -itsiter 200 -itsmdec 10 -itschm 1 -vartstl 2 -vartsiter 100 -vartsmdec 4 -vartschm 1 -mintskep 1 -vartskep 5\n",name);
	fprintf(stdout,"\n");
}
void print_ts_options(char *name){
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
	fprintf(stdout,"\t\t 4: verbose middle movement operations with evaluation step with keys\n");
	fprintf(stdout,"\n");
	fprintf(stdout,"tabu search options: \n");
	fprintf(stdout,"-tstl <integer>\t tabu list size (min 1 ,max 31, DEFAULT 16)\n");
	fprintf(stdout,"-tsiter <long>\t tabu search iteration number (min 1 ,max LONG_MAX, DEFAULT 2000)\n");
	fprintf(stdout,"-tsdesc <long>\t tabu search maximun contiune decreace(min 1, DEFAULT 64)\n");
	fprintf(stdout,"-tsmch  <long>\t tabu search movement change limit (DEFAULT 1)\n");
	fprintf(stdout,"-tskep  <long>\t tabu search key evaluation percent (1 - 100, DEFAULT 99)\n");
	fprintf(stdout,"\n");
	fprintf(stdout,"example: %s -i input.data -o report.data -tstl 15 -tsiter 5000 -tsdesc 128 -tsmch 15 -tskep 90\n",name);
	fprintf(stdout,"example: %s -i input.data -o report.data -iter -mop -paranoid 4\n",name);
	fprintf(stdout,"\n");
}
void print_test_options(char *name){
	fprintf(stdout,"Usage: %s -i <input_file> [options] -key hexa_key\n",name);
	fprintf(stdout,"\n");
	fprintf(stdout,"options: \n");
	fprintf(stdout,"-o <out_file>\t generate output report to a file \n");
	fprintf(stdout,"\n");
	fprintf(stdout,"example: %s -i input.data -o report.data -key 0x4A99E951 0x3EA4EB1A 0x3D471817 0x067EAD6F\n",name);
	fprintf(stdout,"\n");	
}
void print_generate_options(char *name){
	fprintf(stdout,"Usage: %s -seed <long> -n <int> [options]\n",name);
	fprintf(stdout,"\n");
	fprintf(stdout,"options: \n");
	fprintf(stdout,"-o <out_file>\t generate outputs to a file \n");
	fprintf(stdout,"-key <hexa_blocks>\t use given key instead a random key \n");
	fprintf(stdout,"\n");
	fprintf(stdout,"example: %s -seed 2838898 -n 1000 -key 0x4A99E951 0x3EA4EB1A 0x3D471817 0x067EAD6F -o generated.data \n",name);
	fprintf(stdout,"example: %s -seed 2838898 -n 1000 -o generated.data \n",name);
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

output_report *open_report(input_options *options){
	
	output_report *report;
	
	if((report=MALLOC(output_report))==NULL){
		fprintf(stderr,"ERROR: FAILED TO ALLOCATE MEMORY\n");
		exit(1);
	}
	
	if(options->save_output){
		if(!(report->report_file=fopen(options->outfile,"w+"))){
			fprintf(stderr,"ERROR: CANNOT CREATE REPORT OUTPUT FILE: %s\n",options->outfile);
			exit(1);
		}
	}
	else report->report_file=NULL;
	
	report->options=options;
	
	report->print_init=(void *)&print_init;
	report->print_end=(void *)&print_end;
	
	if(options->middle_op)	
		report->print_middle=(void *)&print_middle;
	else	
		report->print_middle=(void *)&void_print_middle;
		
	if(options->print_iter)
		report->print_iteration=(void *)&print_iteration;
	else
		report->print_iteration=(void *)&void_print_iteration;
	if(options->paranoid_leve==4){
		report->print_paranoid=(void *)&print_paranoid;
		report->print_paranoid_move=(void *)&print_paranoid_move;
		report->print_paranoid_eval=(void *)&print_paranoid_eval;
		report->print_paranoid_all=(void *)&print_paranoid_all;
	}
	if(options->paranoid_leve==3){
		report->print_paranoid=(void *)&print_paranoid;
		report->print_paranoid_move=(void *)&print_paranoid_move;
		report->print_paranoid_eval=(void *)&print_paranoid_eval;
		report->print_paranoid_all=(void *)&void_print_paranoid_all;
	}
	else{
		if(options->paranoid_leve==2){
			report->print_paranoid=(void *)&print_paranoid;
			report->print_paranoid_move=(void *)&print_paranoid_move;
			report->print_paranoid_eval=(void *)&void_print_paranoid_eval;
			report->print_paranoid_all=(void *)&void_print_paranoid_all;
		}
		else{
			if(options->paranoid_leve==1){
				report->print_paranoid=(void *)&print_paranoid;
				report->print_paranoid_move=(void *)&void_print_paranoid_move;
				report->print_paranoid_eval=(void *)&void_print_paranoid_eval;
				report->print_paranoid_all=(void *)&void_print_paranoid_all;
			}
			else{
				if(options->paranoid_leve==0){
					report->print_paranoid=(void *)&void_print_paranoid;
					report->print_paranoid_move=(void *)&void_print_paranoid_move;
					report->print_paranoid_eval=(void *)&void_print_paranoid_eval;
					report->print_paranoid_all=(void *)&void_print_paranoid_all;
				}
			}
		}
	}
	return(report);
}
void close_report(output_report *report){
	if(report->options->save_output){
		fclose(report->report_file);
	}
}
void report_use_test_matrix(output_report *report){
	report->print_init=(void *)&print_init_test_matrix;
	report->print_end=(void *)&print_end_test_matrix;
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
void print_init_test_matrix(ts_params *params,input_options *options,FILE *file){
	fprintf(file,"%lld\t%lld\t%.02f\t%lld\t",params->tabu_iterations,params->tabu_list_length,params->key_eval_percent,params->tabu_max_decrease);
}
void print_end_test_matrix(final_report *report,FILE *file){
	fprintf(file,"%08lX %08lX\t%.02f\t%08lX %08lX\t%.02f\t%d\t%d\t%.02f\t%.02f\t%0.2f\t%.02f\n"
	,report->left->key[0],report->left->key[1],report->left->value
	,report->right->key[0],report->right->key[1],report->right->value
	,report->left_iter,report->right_iter
	,(float)(report->clock_left/CLOCKS_PER_SEC),(float)(report->clock_right/CLOCKS_PER_SEC)
	,difftime(report->end_left,report->init_left),difftime(report->end_right,report->init_right)
	);
}
void print_mold_test_matrix(FILE *file){
	fprintf(file,"TS ITER\tTS TL\tTS EP\tMDEC\t\t BR L\t\tBRL S\tBR R\t\t\tBRR S\tBRLITER\tBRRITER\tBRLPG\tBRRPG\tBRLT\tBRRT\n");
}
void print_end(final_report *report,FILE *file){
	fprintf(file,"\n");
	fprintf(file,"FINAL REPORT\n");
	fprintf(file,"BEST LEFT RESULT: %08lX %08lX\n",report->left->key[0],report->left->key[1]);
	fprintf(file,"BEST RIGHT RESULT: %08lX %08lX\n",report->right->key[0],report->right->key[1]);
	fprintf(file,"BEST LEFT SCORE: %f\n",report->left->value);
	fprintf(file,"BEST RIGHT SCORE: %f\n",report->right->value);
	//fprintf(file,"BEST LEFT RESULT PG TIME: %f\n",report->clock_left);
	//fprintf(file,"BEST RIGHT RESULT PG TIME: %f\n",report->clock_right);
	fprintf(file,"BEST LEFT RESULT TIME: %f\n",difftime(report->end_left,report->init_left));
	fprintf(file,"BEST RIGHT RESULT TIME: %f\n",difftime(report->end_right,report->init_right));
	//fprintf(file,"GLOBAL PG TIME: %f\n",report->clock_global);
	fprintf(file,"GLOBAL TIME: %f\n",difftime(report->end_global,report->init_global));
	fprintf(file,"LEFT KEY RESTART: %d\n",report->restart_left_control);
	fprintf(file,"RIGHT KEY RESTART: %d\n",report->restart_right_control);
	fprintf(file,"LEFT MOVEMENT CHANGE: %d\n",report->change_left_count);
	fprintf(file,"RIGHT MOVEMENT CHANGE: %d\n",report->change_right_count);
	fprintf(file,"LEFT ITERATION: %d\n",report->left_iter);
	fprintf(file,"RIGHT ITERATION: %d\n",report->right_iter);
	fprintf(file,"\n");
}
/* print middle operations for tabu serah */
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

void print_paranoid_eval(paranoid *paranoid,FILE *file){
	fprintf(file,"--->BIT:%d\tPERCENT:%d\tONES:%d\tZEROS:%d\tELEMET:%d\n",paranoid->bit,paranoid->percent,paranoid->ones,paranoid->zeros,paranoid->element);
}

void print_paranoid_all(paranoid *paranoid,FILE *file){
	fprintf(file,"--->KEY:%08lX\tKEYNUM:%d\tBLOCK:%d\tEVALKEY:%08lX\n",paranoid->key,paranoid->bit,paranoid->block,paranoid->evalkey);
}

/* void printing for non-print function pointer asigment */
void void_print_middle(unsigned long key,float score,unsigned int bit,int block,int tabuname,FILE *fp){
}
void void_print_iteration(best_result *best,int block,int iter,FILE *fp){
}
void void_print_paranoid(paranoid *paranoid,FILE *fp){
}
void void_print_paranoid_move(paranoid *paranoid,FILE *fp){
}
void void_print_paranoid_eval(paranoid *paranoid,FILE *fp){
}
void void_print_paranoid_all(paranoid *paranoid,FILE *fp){
}