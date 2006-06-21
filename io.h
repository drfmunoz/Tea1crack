#ifndef _IO_HEADER_
#define _IO_HEADER_
#include "types.h"

/*
 * maximun number of lines that can have input file
 */

#define MAX_FILE_LINES 1010


/*
void print_init(input_options *,unsigned long long *);
void print_body(input_options *,best_result *,tabu_list *,unsigned long *);
void print_middle_body(input_options *,best_result *,tabu_list *,unsigned long *,unsigned long long *,int,unsigned int);
void print_csv(input_options *,best_result *);
void print_end(input_options *,best_result *);
*/



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


void print_middle(unsigned long,float,unsigned int,int,int,FILE *);


void void_print_middle(unsigned long,float,unsigned int,int,int,FILE *);

void print_iteration(best_result *,int,int,FILE *);
void void_print_iteration(best_result *,int,int,FILE *);

void print_paranoid(paranoid *,FILE *);
void print_paranoid_move(paranoid *,FILE *);
void print_paranoid_all(paranoid *,FILE *);

void void_print_paranoid(paranoid *,FILE *);
void void_print_paranoid_move(paranoid *,FILE *);
void void_print_paranoid_all(paranoid *,FILE *);

#endif