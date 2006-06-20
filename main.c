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
	
	FILE *outreport;
	
	options=MALLOC(input_options);
	
	/*
	 * parse input parameters
	 */
	if(argc>1){
		parse_arguments(argc,argv,options);
		if(options->have_input==FALSE){
			fprintf(stderr,"ERROR: NO INPUT FILE");
			return(1);
		}
	}
	else{
		print_options(argv[0]);
		return(1);
	}
	
	/* report creation options */
	report=MALLOC(output_report);
	
	if(options->save_output){
		if(!(outreport=fopen(options->outfile,"w+"))){
			fprintf(stderr,"ERROR: CANNOT CREATE REPORT FILE: %s\n",options->outfile);
			exit(1);
		}
		report->report_file=outreport;
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
	if(options->paranoid_leve==3){
		report->print_paranoid=(void *)&void_print_paranoid;
		report->print_paranoid_move=(void *)&print_paranoid_move;
		report->print_paranoid_all=(void *)&print_paranoid_all;	
	}
	else{
		if(options->paranoid_leve==2){
			report->print_paranoid=(void *)&void_print_paranoid;
			report->print_paranoid_move=(void *)&print_paranoid_move;
			report->print_paranoid_all=(void *)&void_print_paranoid_all;
		}
		else{
			if(options->paranoid_leve==1){
				report->print_paranoid=(void *)&print_paranoid;
				report->print_paranoid_move=(void *)&void_print_paranoid_move;
				report->print_paranoid_all=(void *)&void_print_paranoid_all;
			}
			else{
				if(options->paranoid_leve==0){
					report->print_paranoid=(void *)&void_print_paranoid;
					report->print_paranoid_move=(void *)&void_print_paranoid_move;
					report->print_paranoid_all=(void *)&void_print_paranoid_all;
				}
			}
		}
	}
		
	/* end report creation options */
	
	
	
	/* read input file */
	cipher=read_input(options->inputfile);
	/* perform tabu search */
	fprintf(stdout,"INIT TABU SEARCH\n");
	
	/* which is the best result accord to parameters*/
	tabusearch(cipher,options,report);

	fprintf(stdout,"END TABU SEARCH\n");
	/* end program */
	
	
	if(options->save_output){
		fclose(outreport);
	}
	
	free((char *)options);
	free((char *)report);
	free((char *)cipher);
	return(0);
}