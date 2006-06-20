#ifndef _TABUSEARCH_HEADER_
#define _TABUSEARCH_HEADER_

#include "types.h"
/*
 * default length of tabu list... it cannot be the same as the number of movements
 */
#define DEFAULT_TABU_LIST_LENGTH 16

/*
 * default number of cycles which perform tabu search
 */
#define DEFAULT_TABU_CYCLES 2000

/*
 *default number of allowed bad results consecutives before stop.
 */
#define DEFAULT_TABU_RESTART_LIMIT 64

/*
 * an unrechable limit for initialize tabu list
 */
#define POST_LIMIT 99999

/*
 * limit for change the movement, the same limit would be used to return to movements
 */
#define CHANGE_MOVE_LIMIT 4

/*
 * percent of bits that the keys in the universe have to have in common
 */
#define PERCENT_MULTI 0.99

/*
 * key block bit division
 */
#define TEA_DUAL_BLOCK 32

/*
 * value that the best result have to reach to finish.
 */
#define TABU_END_LIMIT 32

#define LEFT -1

#define RIGHT 1

/* first movement for tabu, change one by one bit value */
//void move_alpha(unsigned long *,tabu_list *,tabu_list *,unsigned long *,unsigned long *,unsigned int *,unsigned int *,unsigned int *,unsigned int *,best_result *,best_result *,ts_params *,output_report *,cipher_cont *);
void move_alpha(unsigned long *,tabu_list *,unsigned long *,unsigned int *,unsigned int *,best_result *,ts_params *,output_report *,cipher_cont *,int);

/* first movement for tabu, swap value */
//void move_beta(unsigned long *,tabu_list *,tabu_list *,unsigned long *,unsigned long *,unsigned int *,unsigned int *,unsigned int *,unsigned int *,best_result *,best_result *,ts_params *,output_report *,cipher_cont *);
void move_beta(unsigned long *,tabu_list *,unsigned long *,unsigned int *,unsigned int *,best_result *,ts_params *,output_report *,cipher_cont *,int);


/* evaluate based on TEA descomposition */
float evaluate(unsigned long,cipher_cont *,int,output_report *,ts_params *);

void tabusearch(cipher_cont *,input_options *,output_report *);

void generate_initial_solution(unsigned long *,cipher_cont *);

void restart_left(unsigned long *);
void restart_right(unsigned long *);

ts_params *create_params(input_options *);
tabu_list *create_tabu_list(ts_params *);
void restart_tabu(tabu_list *,ts_params *);

#endif