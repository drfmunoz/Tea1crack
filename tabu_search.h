/** 
 * \file tabu_search.h
 * \brief tabu search constants and function prototypes
 * \ingroup tabus_search
 */
#ifndef _TABUSEARCH_HEADER_
#define _TABUSEARCH_HEADER_

#include "types.h"
#include <limits.h>


/** \def DEFAULT_TABU_LIST_LENGTH                                                                                  
 * Default tabu list lenght                                                                                     
 */
#define DEFAULT_TABU_LIST_LENGTH 16


/** \def DEFAULT_TABU_CYCLES                                                                                 
 * Default number of cycles which perform tabu search                                                                                   
 */
#define DEFAULT_TABU_CYCLES 2000

/** \def CHANGE_MOVE_LIMIT                                                                                 
 * Default Limit for change the movement, the same limit would be used to return to original movement                                                                                
 */
#define CHANGE_MOVE_LIMIT 2

/** \def PERCENT_MULTI                                                                                 
 * Default percent of bits that the keys in the universe will have in common                                                                               
 */
#define PERCENT_MULTI 0.99

/** \def DEFAULT_TABU_RESTART_LIMIT                                                                                 
 * Default number of allowed bad results consecutives before restart.                                                                              
 */
#define DEFAULT_TABU_RESTART_LIMIT 64


/** \def POST_LIMIT                                                                                 
 * alias for LONG_MAX                                                                            
 */
#define POST_LIMIT LONG_MAX


/** \def TEA_DUAL_BLOCK                                                                                 
 * Size of one key block (a key is composed of 4 key blocks)                                                                            
 */
#define TEA_DUAL_BLOCK 32


/** \def TABU_END_LIMIT                                                                                
 * Value that the best result have to reach to finish.                                                                          
 */
#define TABU_END_LIMIT 32


/** \def LEFT                                                                                
 * Left direction/block constant definition.                                                                         
 */
#define LEFT -1

/** \def RIGHT                                                                                
 * Right direction/block constant definition                                                                        
 */
#define RIGHT 1


void move_alpha(unsigned long *,tabu_list *,unsigned long *,unsigned int *,unsigned int *,best_result *,ts_params *,output_report *,cipher_cont *,int);
void move_beta(unsigned long *,tabu_list *,unsigned long *,unsigned int *,unsigned int *,best_result *,ts_params *,output_report *,cipher_cont *,int);
float evaluate(unsigned long,cipher_cont *,int,output_report *,ts_params *);
void tabusearch(cipher_cont *,input_options *,output_report *);
void generate_initial_solution(unsigned long *);
void restart_left(unsigned long *);
void restart_right(unsigned long *);
ts_params *create_params(input_options *);
tabu_list *create_tabu_list(ts_params *);
void restart_tabu(tabu_list *,ts_params *);
void free_tabu(tabu_list *,unsigned int);

#endif