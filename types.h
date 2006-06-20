#ifndef _STRUCTS_HEADER_
#define _STRUCTS_HEADER_
#include <time.h>

#define TRUE 1
#define FALSE 0

/* 
 * memory allocation definition
 */
#define MALLOC(type) (type *)malloc(sizeof(type))
#define NMALLOC(n,type) (type *)malloc(n*sizeof(type))

/* how many bits has the key */
#define KBITS 128

/* how many bits has the message */
#define MBITS 64


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
	unsigned int bit;
};
typedef struct best_result best_result;


struct tabu_search_params{
	unsigned long long tabu_list_length;
	unsigned long long tabu_iterations;
	unsigned long long tabu_max_decrease;
	unsigned long long change_move_limit;
	float key_eval_percent;
};
typedef struct tabu_search_params ts_params;


/******* ts ******/

/*
 * data structure for input data
 */

struct container_node{
	unsigned long plain_message[2];
	unsigned long key[4];
	unsigned long cipher_message[2];
	int size_array;
};
typedef struct container_node cipher_cont;


struct input_opt{
	int have_input;
	int generate_report;
	int save_output;
	
	int paranoid_leve;
	int middle_op;
	int print_iter;
	
	char inputfile[255];
	char outfile[255];
	unsigned long long tabu_list_length;
	unsigned long long tabu_iterations;
	unsigned long long tabu_max_decrease;
	unsigned long long change_move_limit;	
	float key_eval_percent;
};
typedef struct input_opt input_options;

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
	void (*print_paranoid_all)(paranoid *,FILE *);
};
typedef struct output_report output_report;



struct tabu_movement{
	void (*move)(unsigned long *,tabu_list *,unsigned long *,unsigned int *,unsigned int *,best_result *,ts_params *,output_report *,cipher_cont *,int);
};
typedef struct tabu_movement movement;




#endif