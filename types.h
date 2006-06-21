#ifndef _STRUCTS_TYPES_HEADER_
#define _STRUCTS_TYPES_HEADER_
#include <time.h>

#define TRUE 1
#define FALSE 0

/* 
 * memory allocation definition
 */
#define MALLOC(type) (type *)malloc(sizeof(type))
#define NMALLOC(n,type) (type *)malloc(n*sizeof(type))

/*
 *
 * IO AND CONTAINER DATA STRUCTURES -------------------------------------------
 * 
 */


/*
 * data structure for input data
 */

struct container_node{
	unsigned long plain_message[2];     /* 64 bits message splited in two 32 bits blocks */
	unsigned long cipher_message[2];    /* 64 bits cipher message splited in two 32 bits blocks */
	int size_array;					    /* number of keys */
};
typedef struct container_node cipher_cont;

/*
 * general tabu search options data structure
 */
struct input_opt{
	int have_input;                       /* if have input file */
	int generate_report;                  /* if generate report (ALWAYS TRUE) */
	int save_output;					  /* if save output to a file */
	int paranoid_leve;				      /* wich paranoid level would be used (DEFAULT 0) */
	int middle_op;						  /* if it's necesary to print middle operations */
	int print_iter;						  /* if it's necesary to print iteration operations */
	char inputfile[255];				  /* name for the input file */
	char outfile[255];					  /* name for the output file */
	unsigned long long tabu_list_length;  /* tabu list lenght (DEFAULT 0) */
	unsigned long long tabu_iterations;	  /* tabu iterations (DEFAULT 0) */
	unsigned long long tabu_max_decrease; /* tabu performance max decrease (DEFAULT 0) */
	unsigned long long change_move_limit; /* tabu number of mistakes to change movement*/
	float key_eval_percent;               /* percer for evaluation key */ 
};
typedef struct input_opt input_options;

/*
 * general test options data structure
 */
struct test_input_opt{
	char inputfile[255];
	char outfile[255];
	int save_output;
};
typedef struct test_input_opt test_input_options;
	
/*
 *
 * TABU SEARCH SPECIFIC DATA STRUCTURES -------------------------------------------
 * 
 */


/* 
 * tabu list data structure
 */
struct tabu_list{
	unsigned long key;         /* key value for this tabu        */
	unsigned int bit_position; /* bit modification for this tabu */
	float value;               /* evaluation value for this tabu */
	unsigned int name;         /* name for this element          */
	struct tabu_list *next;    /* next element in the tabu list  */
};
typedef struct tabu_list tabu_list;


/*
 * best result data structure
 */
struct best_result{
	unsigned long key[2];      /* key value for this result */
	float value;               /* evalutation value for this result */
	unsigned int bit;          /* bit modified for this result */
};
typedef struct best_result best_result;


/*
 * tabu search parameter data structure
 */
struct tabu_search_params{
	unsigned long long tabu_list_length;  /* tabu list length */
	unsigned long long tabu_iterations;   /* maximal number of iterations */
	unsigned long long tabu_max_decrease; /* performance decreace limit */
	unsigned long long change_move_limit; /* mistakes for change the movement */
	float key_eval_percent;               /* percent of equality of key bits*/
};
typedef struct tabu_search_params ts_params;


/*
 *
 * REPORT GENERATION AND PARANOID DATA STRUCUTRES -------------------------------------------
 * 
 */


/*
 * printing report level structures
 */
struct final_report{
	best_result *left;
	best_result *right;
	time_t init_left;
	time_t init_right;
	time_t init_global;
	time_t end_left;
	time_t end_right;
	time_t end_global;
	clock_t clock_left;
	clock_t clock_right;
	clock_t clock_global;
	unsigned int change_left_count;
	unsigned int change_right_count;
	unsigned int restart_left_control;
	unsigned int restart_right_control;
	unsigned int left_iter;
	unsigned int right_iter;
};
typedef struct final_report final_report;


struct paranoid_level{
	unsigned long key;
	float score;
	unsigned int bit;
	int block;
	unsigned int tabu;
	unsigned long evalkey;
	tabu_list *list;
	
	
	unsigned int percent;
	unsigned int zeros;
	unsigned int ones;
	unsigned int element;


};
typedef struct paranoid_level paranoid;


struct output_report{
	input_options *options;
	paranoid *par;
	paranoid *pardeb;
	FILE *report_file;
	void (*print_init)(ts_params *,input_options *,FILE *);
	void (*print_end)(final_report *,FILE *);
	void (*print_middle)(unsigned long,float,unsigned int,int,int,FILE *);
	void (*print_iteration)(best_result *,int,int,FILE *);
	void (*print_paranoid)(paranoid *,FILE *);
	void (*print_paranoid_move)(paranoid *,FILE *);
	void (*print_paranoid_eval)(paranoid *,FILE *);
	void (*print_paranoid_all)(paranoid *,FILE *);
};
typedef struct output_report output_report;


/*
 *  tabu search movement data structure
 */
struct tabu_movement{
	/* movement function pointier definition */
	void (*move)(unsigned long *,tabu_list *,unsigned long *,unsigned int *,unsigned int *,best_result *,ts_params *,output_report *,cipher_cont *,int);
};
typedef struct tabu_movement movement;


#endif