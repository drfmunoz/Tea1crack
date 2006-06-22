#ifndef _IO_HEADER_
#define _IO_HEADER_
#include "types.h"

/*
 * maximun number of lines that can have input file
 */

#define MAX_FILE_LINES 1010


/*
 * reads data from input file and retur a pointer to an array
 */
cipher_cont* read_input(char*);


/*
 * parse standart input for options
 */
void parse_ts_arguments(int,char**,input_options *);
void parse_test_arguments(int argc,char** argv,test_input_options* options);


/*
 * print tabu serach usage options function prototype
 */ 
void print_ts_options(char*);


/*
 * print test usage options function prototype
 */
void print_test_options(char*);


/*
 * print bits function prototype
 */
void print_bit(unsigned long nume);


/*
 * print tabu search init function prototype
 */
void print_init(ts_params *,input_options *,FILE *);


/*
 * print tabu search result function prototype
 */
void print_end(final_report *,FILE *);



void print_init_test_matrix(ts_params *,input_options *options,FILE *);
void print_end_test_matrix(final_report *,FILE *);

/*
 * print middle tabu search operations function prototype
 */
void print_middle(unsigned long,float,unsigned int,int,int,FILE *);


/*
 * print iteration step for tabu search function prototype
 */
void print_iteration(best_result *,int,int,FILE *);


/* 
 * paranoid level function for tabus search, debug almost movement, 
 * tabu list, and evaluation function. function prototype
 */
void print_paranoid(paranoid *,FILE *);
void print_paranoid_move(paranoid *,FILE *);
void print_paranoid_eval(paranoid *,FILE *);
void print_paranoid_all(paranoid *,FILE *);


/*
 * void function prototype declaration for non printable function pointer
 */
void void_print_middle(unsigned long,float,unsigned int,int,int,FILE *);
void void_print_iteration(best_result *,int,int,FILE *);
void void_print_paranoid(paranoid *,FILE *);
void void_print_paranoid_move(paranoid *,FILE *);
void void_print_paranoid_eval(paranoid *,FILE *);
void void_print_paranoid_all(paranoid *,FILE *);


/*
 * create a report function prototype
 */
output_report *open_report(input_options *options);


/*
 * close a report function prototype
 */
void close_report(output_report *);

void report_use_test_matrix(output_report *);

void print_mold_test_matrix(FILE *);


#endif