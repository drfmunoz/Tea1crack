#include <stdio.h>
#include <stdlib.h>

#include "tea.h"
#include "tabu_search.h"
#include "io.h"
#include "types.h"



int main(int argc,char** argv){
	
	input_options *options;
	cipher_cont *cipher=NULL;
	output_report *report;
	
	if((options=MALLOC(input_options))==NULL){
		fprintf(stderr,"ERROR: FAILED TO ALLOCATE MEMORY\n");
		exit(1);
	}
	/*
	 * parse input parameters
	 */
	if(argc>1){
		parse_ts_arguments(argc,argv,options);
		if(options->have_input==FALSE){
			fprintf(stderr,"ERROR: NO INPUT FILE");
			return(1);
		}
	}
	else{
		print_ts_options(argv[0]);
		return(1);
	}
	/* create report*/
	report=open_report(options);
	/* read input from file */
	cipher=read_input(options->inputfile);
	/* perform tabu search */
	fprintf(stdout,"INIT TABU SEARCH\n");
	tabusearch(cipher,options,report);
	fprintf(stdout,"END TABU SEARCH\n");
	/* end program */
	close_report(report);
	free((char *)options);
	free((char *)report);
	free((char *)cipher);
	return(0);
}