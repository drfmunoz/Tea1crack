#include <stdio.h>
#include <stdlib.h>

#include "tea.h"
#include "tabu_search.h"
#include "io.h"
#include "types.h"
#include "ts_full_test.h"


int main(int argc,char** argv){
	
	input_options *options;
	full_test_input_options *test_options;
	
	cipher_cont *cipher=NULL;
	output_report *report;
	int lock=TRUE;
	
	unsigned long long tabu_list_length=0;
	unsigned long long tabu_iterations=0;	
	unsigned long long tabu_max_decrease=0; 
	unsigned long long change_move_limit=0; 
	float key_eval_percent=0;           
	
	if((test_options=MALLOC(full_test_input_options))==NULL){
		fprintf(stderr,"ERROR: FAILED TO ALLOCATE MEMORY\n");
		exit(1);
	}
	/*
	 * parse input parameters
	 */
	if(argc>1){
		parse_full_test_arguments(argc,argv,test_options);
		if(test_options->have_input==FALSE){
			fprintf(stderr,"ERROR: NO INPUT FILE");
			return(1);
		}
	}
	else{
		print_full_test_options(argv[0]);
		return(1);
	}
		
	
	
	if(test_options->max_tabu_list_length==0){
		test_options->max_tabu_list_length=TS_LIS_MAX;
	} 
	if(test_options->max_tabu_iterations==0){
		test_options->max_tabu_iterations=TS_ITER_MAX;
	}

	if(test_options->max_tabu_max_decrease==0){
		test_options->max_tabu_max_decrease=TS_MAX_DEC_MAX;
	}
	if(test_options->max_change_move_limit==0){
		test_options->max_change_move_limit=TS_CHM_MAX;
	}
	if(test_options->init_tabu_list_length==0){
		test_options->init_tabu_list_length=TS_INIT_LIST;
	}

	if(test_options->init_tabu_iterations==0){
		test_options->init_tabu_iterations=TS_INIT_ITER;
	}

	if(test_options->init_tabu_max_decrease==0){
		test_options->init_tabu_max_decrease=TS_INIT_MAX_DEC;
	}
 
	if(test_options->init_change_move_limit==0){
		test_options->init_change_move_limit=TS_INIT_CHM;
	}

	if(test_options->var_tabu_list_length==0){
		test_options->var_tabu_list_length=TS_LIST_INCREMENT;
	}

	if(test_options->var_tabu_iterations==0){
		test_options->var_tabu_iterations=TS_ITER_INCREMENT;
	}
  
	if(test_options->var_tabu_max_decrease==0){
		test_options->var_tabu_max_decrease=TS_MAX_DEC_INCREMENT;
	}

	if(test_options->var_change_move_limit==0){
		test_options->var_change_move_limit=TS_CHM_INCREMENT;
	}

	if(test_options->min_key_eval_percent==0){
		test_options->min_key_eval_percent=(float)(TS_INIT_PERCENT/100);
	}
           
	if(test_options->var_key_eval_percent==0){
		test_options->var_key_eval_percent=(float)(TS_PERCENT_INCREMENT/100);
	}
	
	options=convert_full_test_opt_to_gen(test_options);
	
	/* create report*/
	report=open_report(options);
	report_use_test_matrix(report);
	/* read input from file */
	
	cipher=read_input(test_options->inputfile);
	/* perform tabu search */
	
	printf("init test matrix\n");
	print_mold_test_matrix(stdout);
	
	if(options->save_output)
		print_mold_test_matrix(report->report_file);
	while(lock){
		options->tabu_list_length=tabu_list_length;  /* tabu list lenght (DEFAULT 0) */
		options->tabu_iterations=tabu_iterations;	  /* tabu iterations (DEFAULT 0) */
		options->tabu_max_decrease=tabu_max_decrease; /* tabu performance max decrease (DEFAULT 0) */
		options->key_eval_percent=key_eval_percent;               /* percer for evaluation key */
		options->change_move_limit=change_move_limit;
		tabusearch(cipher,options,report);
		if(tabu_iterations<=test_options->max_tabu_iterations){
			if(tabu_list_length<=test_options->max_tabu_list_length){
				if(key_eval_percent<=1){
					if(tabu_max_decrease<test_options->max_tabu_max_decrease){
						if(change_move_limit<test_options->max_change_move_limit){
							change_move_limit+=test_options->var_change_move_limit;
						}
						else{
							change_move_limit=test_options->init_change_move_limit;
							tabu_max_decrease+=test_options->var_tabu_max_decrease;
						}
					}
					else{
						tabu_max_decrease=test_options->init_tabu_max_decrease;
						change_move_limit=test_options->init_change_move_limit;
						key_eval_percent+=test_options->var_key_eval_percent;
					}
				}else{
					tabu_list_length+=test_options->var_tabu_list_length;
					key_eval_percent=test_options->min_key_eval_percent;
					tabu_max_decrease=test_options->init_tabu_max_decrease;
					change_move_limit=test_options->init_change_move_limit;							
				}
			}
			else{
				tabu_iterations+=test_options->var_tabu_iterations;
				tabu_list_length=test_options->init_tabu_list_length;
				tabu_max_decrease=test_options->init_tabu_max_decrease;
				key_eval_percent=test_options->min_key_eval_percent;       
				change_move_limit=test_options->init_change_move_limit;
			}
		}
		else{
			lock=FALSE;
		}
	}
	printf("end test matrix\n");	
	/* end program */
	close_report(report);
	free((char *)options);
	free((char *)test_options);
	free((char *)report);
	free((char *)cipher);
	return(0);
}
