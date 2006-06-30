/** 
 * \file io.h
 * \brief input output constant and functions definition
 * \ingroup io
 * \author Freddy Mun~oz Ramirez <frmunoz(at)inf.utfsm.cl>
 * \date Autumn 2006
 * \license <br> This code can be re-distributed under MIT License
 */
#ifndef _IO_HEADER_
#define _IO_HEADER_
#include "types.h"

/** \def MAX_FILE_LINES                                                                                
 * Maximal number of lines in input file                                                                         
 */
#define MAX_FILE_LINES 6000


cipher_cont* read_input(char*);
void parse_ts_arguments(int,char**,input_options *);
void parse_test_arguments(int,char**,test_input_options* );
void parse_full_test_arguments(int,char**,full_test_input_options* );
void parse_generate_arguments(int,char**,generate_options *);
void print_ts_options(char*);
void print_test_options(char*);
void print_full_test_options(char *);
void print_generate_options(char *);
void print_init(ts_params *,input_options *,FILE *);
void print_end(final_report *,FILE *);
void print_init_test_matrix(ts_params *,input_options *options,FILE *);
void print_end_test_matrix(final_report *,FILE *);
void print_middle(unsigned long,float,unsigned int,int,int,FILE *);
void print_iteration(best_result *,int,int,FILE *);
void print_paranoid(paranoid *,FILE *);
void print_paranoid_move(paranoid *,FILE *);
void print_paranoid_eval(paranoid *,FILE *);
void print_paranoid_all(paranoid *,FILE *);
void void_print_middle(unsigned long,float,unsigned int,int,int,FILE *);
void void_print_iteration(best_result *,int,int,FILE *);
void void_print_paranoid(paranoid *,FILE *);
void void_print_paranoid_move(paranoid *,FILE *);
void void_print_paranoid_eval(paranoid *,FILE *);
void void_print_paranoid_all(paranoid *,FILE *);
output_report *open_report(input_options *options);
void close_report(output_report *);
void report_use_test_matrix(output_report *);
void print_mold_test_matrix(FILE *);
input_options* convert_full_test_opt_to_gen(full_test_input_options*);


#endif