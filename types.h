/** 
 * \file types.h
 * \brief types definition for all components of TS application
 * \ingroup all
 */
#ifndef _STRUCTS_TYPES_HEADER_
#define _STRUCTS_TYPES_HEADER_
#include <time.h>

/** \def TRUE                                                                                
 * True constant definition.                                                                         
 */
#define TRUE 1

/** \def FALSE                                                                                
 * False constant definition.                                                                         
 */
#define FALSE 0

/** \def MALLOC(type)                                                                                
 * Memory allocation of size sizeof(type).                                                                         
 */
#define MALLOC(type) (type *)malloc(sizeof(type))

/** \def NMALLOC(n,type)                                                                                
 * Memory allocation of size n*sizeof(type).                                                                         
 */
#define NMALLOC(n,type) (type *)malloc(n*sizeof(type))


/**
 * \struct container_node
 * \brief input data structure
 * Data structure that contains the input data (plain, cipher)
 */
struct container_node{
	unsigned long plain_message[2];     /**< 64 bits message splited in two 32 bits blocks */
	unsigned long cipher_message[2];    /**< 64 bits cipher message splited in two 32 bits blocks */
	int size_array;					    /**< number of container nodes */
};
/**
 * \typedef cipher_cont
 * \brief alias for container_node
 */
typedef struct container_node cipher_cont;

/**
 * \struct input_opt
 * \brief Tabu search input options
 * General Tabu search input options data structure
 */
struct input_opt{
	int have_input;                       /**< if have input file */
	int generate_report;                  /**< if generate report (ALWAYS TRUE) */
	int save_output;					  /**< if save output to a file */
	int paranoid_leve;				      /**< wich paranoid level would be used (DEFAULT 0) */
	int middle_op;						  /**< if it's necessary to print middle operations */
	int print_iter;						  /**< if it's necessary to print iteration operations */
	char inputfile[255];				  /**< name for the input file */
	char outfile[255];					  /**< name for the output file */
	unsigned long long tabu_list_length;  /**< tabu list lenght (DEFAULT 0) */
	unsigned long long tabu_iterations;	  /**< tabu iterations (DEFAULT 0) */
	unsigned long long tabu_max_decrease; /**< tabu performance max decrease (DEFAULT 0) */
	unsigned long long change_move_limit; /**< tabu number of mistakes to change movement*/
	float key_eval_percent;               /**< percer for evaluation key */ 
};
/**
 * \typedef input_options
 * \brief alias for input_opt structure
 */
typedef struct input_opt input_options;

/**
 * \struct test_input_opt
 * \brief Cipher Test input options
 * Cipher Test input options data
 */
struct test_input_opt{
	char inputfile[255];	/**< name for the input file */
	char outfile[255];		/**< name for the output file */
	int save_output;		/**< if save output to a file */
	int have_input;			/**< if have input file */
	unsigned long long key1;  /** < block 1 for input key */
	unsigned long long key2;  /** < block 2 for input key */
	unsigned long long key3;  /** < block 3 for input key */
	unsigned long long key4;  /** < block 4 for input key */
};
/**
 * \typedef test_input_options
 * \brief alias for test_input_opt
 */
typedef struct test_input_opt test_input_options;

/**
 * \struct full_test_input_opt
 * \brief Structure that support input options for full test tabu search
 * input options for full test tabu search
 */
struct full_test_input_opt{
	char inputfile[255];					  /**< name for the input file */
	char outfile[255];						  /**< name for the output file */
	int save_output;						  /**< if save output to a file */
	int have_input;							  /**< if save output to a file */
	unsigned long long max_tabu_list_length;  /**< maximal tabu list lenght */
	unsigned long long max_tabu_iterations;	  /**< maximal tabu iterations */
	unsigned long long max_tabu_max_decrease; /**< maximal tabu performance max decrease */
	unsigned long long max_change_move_limit; /**< maximal number of mistakes to change movement*/
	unsigned long long init_tabu_list_length; /**< initial tabu list lenght */
	unsigned long long init_tabu_iterations;  /**< initial tabu iterations */
	unsigned long long init_tabu_max_decrease;/**< initial performance max decrease */
	unsigned long long init_change_move_limit;/**< initial number of mistakes to change movement*/
	unsigned long long var_tabu_list_length;  /**< variation of tabu list lenght */
	unsigned long long var_tabu_iterations;	  /**< variation of tabu iterations */
	unsigned long long var_tabu_max_decrease; /**< variation of tabu performance max decrease */
	unsigned long long var_change_move_limit; /**< variation of mistakes number to change movement*/
	float min_key_eval_percent;               /**< initial percent for evaluation key */ 
	float var_key_eval_percent;               /**< variation of percent for evaluation key */ 
};
/**
 * \typedef full_test_input_options
 * \brief alias for full_test_input_opt
 */
typedef struct full_test_input_opt full_test_input_options;	

/**
 * \struct generate_options
 * \brief generate plain-cipher input options
 * Container for options in generation of random plain-cipher 
 */
struct generate_options{
	char outfile[255];				/**< output filename */
	int userandom;					/**< if the key is random generated */
	int usefile;					/**< if outfile would be used, if not use STDOUT */
	int usekey;						/**< if key would be given */
	unsigned long seed;				/**< seed for random */
	unsigned long amount;			/**< amount of plain-cipher messages */
	unsigned long key[4];			/**< if no randomd key, the key needs to be given */
};
/**
 * \typedef generate_options
 * \brief alias for generate_options
 */
typedef struct generate_options generate_options;

/**
 * \struct tabu_list
 * \brief Tabu List implemetation data structure
 * The tabu list, its a circular linked list which contains forbidden movements
 */
struct tabu_list{
	unsigned long key;         /**< key value for this tabu        */
	unsigned int bit_position; /**< bit modification for this tabu */
	float value;               /**< evaluation value for this tabu */
	unsigned int name;         /**< name for this element          */
	struct tabu_list *next;    /**< next element in the tabu list  */
};
/**
 * \typedef tabu_list
 * \brief alias for tabu_list
 */
typedef struct tabu_list tabu_list;


/**
 * \struct best_result
 * \brief Tabu Search best result implementation
 * Best result for tabu search
 */
struct best_result{
	unsigned long key[2];      /**< key value for this result */
	float value;               /**< evalutation value for this result */
	unsigned int bit;          /**< bit modified for this result */
};
/**
 * \typedef best_result
 * \brief alias for best_result
 */
typedef struct best_result best_result;


/**
 * \struct tabu_search_params
 * \brief Tabu Search parameters
 * A set of parameters to perform tabu search
 */
struct tabu_search_params{
	unsigned long long tabu_list_length;  /**< tabu list length */
	unsigned long long tabu_iterations;   /**< maximal number of iterations */
	unsigned long long tabu_max_decrease; /**< performance decreace limit */
	unsigned long long change_move_limit; /**< mistakes for change the movement */
	float key_eval_percent;               /**< percent of equality of key bits*/
};
/**
 * \typedef ts_params
 * \brief alias for tabu_search_params
 */
typedef struct tabu_search_params ts_params;


/**
 * \struct final_report
 * \brief Final report for tabu search
 * Structure that support data for final report generation.
 */
struct final_report{
	best_result *left; 				        /**< best result for left block */
	best_result *right;						/**< best result for left block */
	time_t init_left;						/**< initial time for left block */
	time_t init_right;						/**< initial time for right block */
	time_t init_global;						/**< initial global time */
	time_t end_left;						/**< end time for left block */
	time_t end_right;						/**< end time for right block */
	time_t end_global;						/**< end global time */
	clock_t clock_left;						/**< program clock for left block*/
	clock_t clock_right;					/**< program clock for right block*/
	clock_t clock_global;					/**< global program clock*/
	unsigned int change_left_count;			/**< movement change for left block */
	unsigned int change_right_count;		/**< movement change for right block */
	unsigned int restart_left_control;		/**< restarts for left block */
	unsigned int restart_right_control;		/**< restarts for right block */
	unsigned int left_iter;					/**< iterations for left block */
	unsigned int right_iter;				/**< iterations for right block */
};
/**
 * \typedef final_report
 * \brief alias for final_report
 */
typedef struct final_report final_report;

/**
 * \struct paranoid_level
 * \brief Paranoid debug support
 * Structure that support paranoid debug for tabu search operations, in order to work
 * each attribute has a different meaning for each different context.
 */
struct paranoid_level{
	unsigned long key;
	float score;
	int block;
	unsigned long evalkey;
	tabu_list *list;
	unsigned int tabu;
	unsigned int bit;
	unsigned int percent;
	unsigned int zeros;
	unsigned int ones;
	unsigned int element;
};
/**
 * \typedef paranoid
 * \brief alias for paranoid_level
 */
typedef struct paranoid_level paranoid;

/**
 * \struct output_report
 * \brief Structure to support report and debug generation
 * Support for report generation (initial al final report), and support for
 * debugging options, function pointer aids change the function for each
 * different context.
 */
struct output_report{
	input_options *options;                                              	/**< input options for this tabu serach program */
	paranoid *par;														 	/**< Paranoid container for misc purpose */
	paranoid *pardeb;													 	/**< Paranoid container for misc purpose */
	FILE *report_file;													 	/**< where to write reports */
	void (*print_init)(ts_params *,input_options *,FILE *);              	/**< print the initial report */
	void (*print_end)(final_report *,FILE *);                            	/**< print final report */
	void (*print_middle)(unsigned long,float,unsigned int,int,int,FILE *);  /**< print tabu search middle operations */
	void (*print_iteration)(best_result *,int,int,FILE *);					/**< print tabu search iteration resutls */
	void (*print_paranoid)(paranoid *,FILE *);								/**< paranoid debug level 1, print tabu op */
	void (*print_paranoid_move)(paranoid *,FILE *);							/**< paranoid debug level 2, print movement */
	void (*print_paranoid_eval)(paranoid *,FILE *);							/**< paranoid debug level 3, print evaluation function */
	void (*print_paranoid_all)(paranoid *,FILE *);							/**< paranoid debug level 4, print key kegeneration for key eval */ 
};
/**
 * \typedef output_report
 * \brief alias for output_report
 */
typedef struct output_report output_report;

/**
 * \struct tabu_movement
 * \brief Structure to support tabu search morphic movement
 * Function pointer aids to support multiple tabu search movements, this structure provides
 * the mechanism to link movement and tabu search call.
 */
struct tabu_movement{
	void (*move)(unsigned long *,tabu_list *,unsigned long *,unsigned int *,unsigned int *,best_result *,ts_params *,output_report *,cipher_cont *,int); /**< Tabu search movement */
};
/**
 * \typedef movement
 * \brief alias for tabu_movement
 */
typedef struct tabu_movement movement;

#endif