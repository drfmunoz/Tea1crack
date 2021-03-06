/** 
 * \file tabu_search.c
 * \brief Tabu Search functions
 * \ingroup tabus_search
 * \author Freddy Mun~oz Ramirez <frmunoz(at)inf.utfsm.cl>
 * \date Autumn 2006
 * \license <br> This code can be re-distributed under MIT License
 */
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>

#include "tabu_search.h"
#include "tea.h"
#include "io.h"
#include "types.h"

/** Tabus Search movement alpha: change the ith bit of one 32 bit key block, it also get the value for evaluation function and put the best movement value into tabu list.<br>
	first movement:<br>
	generate only 32 bits movements for 32 bits block key[1] and key[3]  moving with left bits shift XOR.<br>
	example:<br>
	
			&nbsp;&nbsp;&nbsp;010101010101<br>
			^&nbsp;000000000001<br>
		    &nbsp;&nbsp;&nbsp;------------<br>
			&nbsp;&nbsp;&nbsp;010101010100<br>
			<br>
			&nbsp;&nbsp;&nbsp;000000000001 << 1 = 000000000010<br>
			<br>
			&nbsp;&nbsp;&nbsp;010101010101<br>
			^&nbsp;000000000010<br>
			&nbsp;&nbsp;&nbsp;------------<br>
			&nbsp;&nbsp;&nbsp;010101010111<br>
			<br>
			and so on.<br>
 * \param key Key for this movement (a 128 bit key in 4 blocks of 32 bits)
 * \param list  Tabu list for this move, corresponding to current key block
 * \param mistakes Mistakes counter tracker
 * \param control Control wich element is the next in the tabu list
 * \param found If the element was found
 * \param best The current best result
 * \param params General parameter for tabu search 
 * \param report Report generator
 * \param cpmess Ciphers and Plain messages
 * \param block name for this block (LEFT OR RIGHT)
 */
void move_alpha(unsigned long *key,tabu_list *list,unsigned long *mistakes,unsigned int *control,unsigned int *found,best_result *best,ts_params *params,output_report *report,cipher_cont *cpmess,int block)
{
	
	unsigned int i,j;
	unsigned long bits=2;
	unsigned long keys[TEA_DUAL_BLOCK];/*< where to put key changes*/
	float scores[TEA_DUAL_BLOCK];      /*< where to put the scores*/
	float score=0;
	unsigned int tabu=FALSE;           /*< if tabu move */
	unsigned int position=0;
	
	/* if this key block has been found, then skip all operations */
	if(*found!=FALSE)
	{
		return;
	}
	/*   32 bits for the key block    */
	for(i=0;i<TEA_DUAL_BLOCK;i++)
	{
		scores[i]=-POST_LIMIT;
		/* check tabu list for this tabu movement */
		for(j=0;j<params->tabu_list_length;j++)
		{
			if(list->bit_position==i)
			{
				tabu=TRUE;
				break;
			}
			list=list->next;
		}
		if(tabu==FALSE)
		{
			/* movement for the left key block */
			if(block==LEFT)
			{
				keys[i]=0x0;
				keys[i]=key[1]^bits;
			}
			/* movement for the right key block */
			else
			{
				keys[i]=0x0;
				keys[i]=key[3]^bits;
			}

			scores[i]=evaluate(keys[i],cpmess,block,report,params);
		}
		if(report->options->paranoid_leve>1)
		{
			report->par->key=keys[i];
			report->par->score=scores[i];
			report->par->bit=i;
			report->par->block=block;
			report->par->tabu=tabu;
			(report->print_paranoid_move)(report->par,stderr);
		}
		tabu=FALSE;
		bits=bits<< 1;
	}
	score=-POST_LIMIT;
	/* find the best result for this movement */
	for(i=0;i<TEA_DUAL_BLOCK;i++)
	{
			if(scores[i]>score&&scores[i]!=-POST_LIMIT)
			{
				position=i;
				score=scores[position];
			}
	}
	/* advance tabu list control */
	if(*control==params->tabu_list_length)
	{
		*control=1;
	}
	else{
		*control+=1;
	}
	/* add element move to tabu list */
	while(1)
	{
		if(list->name==(*control-1))
		{
			list->key=keys[position];
			list->value=score;
			list->bit_position=position;
			break;
		}
		else list=list->next;
	}
	/* check if this movement is better that the current best */	
	if(score > best->value)
	{
		best->value=score;
		best->key[0]=0x0;
		best->key[1]=keys[position];
		best->bit=position;
		*mistakes=0;
	}
	else
	{
		/* if not best, then increase mistakes counter */
		*mistakes+=1;
	}

	if(block==LEFT)
	{
		key[0]=0x0;
		key[1]=keys[position];
	}
	else
	{
		key[2]=0x0;
		key[3]=keys[position];
	}
	(report->print_middle)(keys[position],score,position,block,list->name,stderr);
}
/** Tabus Search movement beta: swap ith bit with ith+1 bit of one 32 bit key block, it also get the value for evaluation function and put the best movement value into tabu list.<br>
	second movement:<br>
	generate only 31 bits movements for 32 bits block key[1] and key[3]  swaping different bits.<br>
	(if two bits are equals, then no move... bit pairs 00 or 11 generate no move)<br>
	example:<br>
	
			010101010101<br>
			swap&nbsp;1<br>
			------------<br>
			010101010110<br>
			010101010101<br>
			swap&nbsp;2<br>
			------------<br>
			010101010011<br>
			
			and so on.

everything in this movement its like fisrt movement, but the movement it self changes.
 * \param key Key for this movement (a 128 bit key in 4 blocks of 32 bits)
 * \param list  Tabu list for this move, corresponding to current key block
 * \param mistakes Mistakes counter tracker
 * \param control Control wich element is the next in the tabu list
 * \param found If the element was found
 * \param best The current best result
 * \param params General parameter for tabu search 
 * \param report Report generator
 * \param cpmess Ciphers and Plain messages
 * \param block Name for this block (LEFT OR RIGHT)
 */
void move_beta(unsigned long *key,tabu_list *list,unsigned long *mistakes,unsigned int *control,unsigned int *found,best_result *best,ts_params *params,output_report *report,cipher_cont *cpmess,int block)
{
	unsigned int i,j;
	unsigned long bits=2;
	unsigned long keys[TEA_DUAL_BLOCK];
	float scores[TEA_DUAL_BLOCK];
	float score=0;
	unsigned long and_const=LONG_MAX;
	unsigned int tabu=FALSE;
	unsigned int position=0;
	
	if(*found!=FALSE)
	{
		return;
	}
	for(i=1;i<TEA_DUAL_BLOCK;i++)
	{
		scores[i]=-POST_LIMIT;

		for(j=0;j<params->tabu_list_length;j++)
		{
			if(list->bit_position==i)
			{
				tabu=TRUE;
				break;
			}
			list=list->next;
		}
		if(tabu==FALSE)
		{
			/* movement for the left key block */
			if(block==LEFT)
			{
				keys[i]=0x0;
				if(!((key[1]&bits)&&(key[1]&bits>>1))&&!(((key[1]^and_const)&bits)&&((key[1]^and_const)&bits>>1)))
				{
					keys[i]=key[1]^bits;
					keys[i]=keys[i]^bits>>1;
				}
				else keys[i]=key[1];
			}
			/* movement for the right key block */
			else{
				keys[i]=0x0;
				
				if(!((key[3]&bits)&&(key[3]&bits>>1))&&!(((key[3]^and_const)&bits)&&((key[3]^and_const)&bits>>1)))
				{
					keys[i]=key[3]^bits;
					keys[i]=keys[i]^bits>>1;
				}
				else keys[i]=key[3];
			}
			scores[i]=evaluate(keys[i],cpmess,block,report,params);
		}
		if(report->options->paranoid_leve>1)
		{
			report->par->key=keys[i];
			report->par->score=scores[i];
			report->par->bit=i;
			report->par->block=block;
			report->par->tabu=tabu;
			(report->print_paranoid_move)(report->par,stderr);
		}
		tabu=FALSE;
		bits=bits << 1;
	}
	score=-POST_LIMIT;

	for(i=0;i<TEA_DUAL_BLOCK;i++)
	{
		if(scores[i]>score&&scores[i]!=-POST_LIMIT)
		{
			position=i;
			score=scores[position];
		}
	}
	if(*control==params->tabu_list_length)
	{
		*control=1;
	}
	else
	{
		*control+=1;
	}
	while(1)
	{
		if(list->name==(*control-1))
		{
			list->key=keys[position];
			list->value=score;
			list->bit_position=position;
			break;
		}
		else list=list->next;
	}
	if(score > best->value)
	{
		best->value=score;
		best->key[0]=0x0;
		best->key[1]=keys[position];
		best->bit=position;
		*mistakes=0;
	}
	else{
		*mistakes+=1;
	}
	if(block==LEFT)
	{
		key[0]=0x0;
		key[1]=keys[position];
	}
	else
	{
		key[2]=0x0;
		key[3]=keys[position];
	}
	(report->print_middle)(keys[position],score,position,block,list->name,stderr);
}
/**     In order to accomplish the evalutaion for key generation its necesary to compare the mirror bits 
		from right to left, and select the worst score betwen all comparision of all keys
		it's means if a key have 3 points and another 2, our best score is 2 with some percent of
		accuracy.<br>
		
		(remember the best score is the worst one)<br><br>
		
		also its necesary that the bits be in correlative order that means<br>
		
		&nbsp;&nbsp;&nbsp;10100100001<br>
		&&nbsp;10101011011<br>
	    &nbsp;&nbsp;&nbsp;-----------<br>
		&nbsp;&nbsp;&nbsp;10100000001     < --- this have just one bit of coincidences<br>
		<br>
		&nbsp;&nbsp;&nbsp;10100100001<br>
		&&nbsp;10101011001<br>
		&nbsp;&nbsp;&nbsp;-----------<br>
		&nbsp;&nbsp;&nbsp;10100000001<br>     	
		&&nbsp;01010000110<br>
		&nbsp;&nbsp;&nbsp;-----------<br>
		&nbsp;&nbsp;&nbsp;11110000111		< --- this have three bit of coincidence<br>	
		take just the equals bits (no matters if 0 or 1), its must be equals and correlatives.
 *
 * \param key Key to evaluate
 * \param cpmess Ciphers and Plain messages
 * \param block Name for this block (LEFT OR RIGHT)
 * \param report Report generator
 * \param params General parameter for tabu search
 */
float evaluate(unsigned long key,cipher_cont *cpmess,int block,output_report *report,ts_params *params)
{
	unsigned long composed_key[4]={0x0,0x0,0x0,0x0}; /*< key composed with key part to generate new key blocks */
	unsigned int i,j;
	int value_ones=0;                                /*< number of zeros */
	int value_zeros=0;                               /*< numer of ones */
	int percent_value=0;                             /*< accuracy percent for evaluation */
	float value=0;                                   /*< final evaluation value */
	unsigned long bits=1;                            /*< bits to move */
	unsigned long *key_compare;                      /*< store new generated key*/
	unsigned long and_const=LONG_MAX;                /*< 32 bits of ones */
	
	if((key_compare=NMALLOC(cpmess[0].size_array,unsigned long))==NULL)
	{
		fprintf(stderr,"ERROR: FAILED TO ALLOCATE MEMORY\n");
		exit(1);
	}
	
	if(block==LEFT)
	{
		composed_key[1]=key;
	}
	else
	{
		composed_key[3]=key;
	}
	
	if(report->options->paranoid_leve>2)
	{
		if((report->pardeb=MALLOC(paranoid))==NULL)
		{
			fprintf(stderr,"ERROR: FAILED TO ALLOCATE MEMORY\n");
			exit(1);
		}
	}
	
	for(i=0;i<(cpmess[0].size_array);i++)
	{
		if(block==LEFT)
		{
			gamma_tea(cpmess[i].plain_message,cpmess[i].cipher_message,composed_key);
			key_compare[i]=composed_key[0];
		}
		else
		{
			delta_tea(cpmess[i].plain_message,cpmess[i].cipher_message,composed_key);
			key_compare[i]=composed_key[2];
		}
		if(report->options->paranoid_leve>3)
		{
			report->pardeb->key=key;
			report->pardeb->bit=i;
			report->pardeb->block=block;
			report->pardeb->evalkey=key_compare[i];
		}
		(report->print_paranoid_all)(report->pardeb,stderr);
	}
	/* our key compare percent */
	percent_value=(int)((params->key_eval_percent)*cpmess[0].size_array);
	
	if(report->options->paranoid_leve>2)
	{
		report->pardeb->percent=percent_value;
	}
	for(i=0;i<TEA_DUAL_BLOCK;i++)
	{
		value_zeros=0;
		value_ones=0;
		for(j=0;j<(cpmess[0].size_array);j++)
		{
			/* if the ith bit is one */
			if((key_compare[j]&bits)!=0)
			{
				value_ones++;
			}
			else{
				/* if the ith bit is zero */
				if(((key_compare[j]^and_const)&bits)!=0)
				{
					value_zeros++;
				}
			}			
		}
		bits=bits<<1;
		if(report->options->paranoid_leve>2)
		{
			report->pardeb->bit=j;
			report->pardeb->zeros=value_zeros;
			report->pardeb->ones=value_ones;
			report->pardeb->element=i;
		}
		(report->print_paranoid_eval)(report->pardeb,stderr);
		/*
		 * if the amount of mirror bits it superior that the percent number of bits, then accept the mirror, otherwise
		 * return with worst value.
		 */
		if(value_ones>percent_value||value_zeros>percent_value)
		{
			value++;
		}
		else{
			break;
		}
	}
	if(report->options->paranoid_leve>2)
	{
		free((char *)report->pardeb);
	}
	free((char *)key_compare);
	return(value);
}
/** General Tabu Search, it triggers the movements, and perform each iteration (include convergency if condition)
 *
 * \param cpmess Ciphers and Plain messages
 * \param options Tabu Search general options
 * \param report Report generator
 */
void tabusearch(cipher_cont *cpmess,input_options *options,output_report *report)
{
	
	
	best_result *best_left;					 /*< best result container for left key block */
	best_result *best_right;    			 /*< best result container for right key block */
	ts_params *params;          			 /*< params for tabu search movement and other criteria */ 
	tabu_list *list_left;					 /*< tabu list for left key block */
	tabu_list *list_right;					 /*< tabu list for right key block */
	unsigned long key[4];   				 /*< a 128 bits key*/
	unsigned long mistakes_left=0; 		 	 /*< how many mistakes are in the left serach */
	unsigned long mistakes_right=0; 		 /*< how many mistakes are in the right serach */
	unsigned int control_left=0;   			 /*< which is the current modified element in the left list */
	unsigned int control_right=0;    		 /*< which is the current modified element in the right list */
	unsigned int found_left=FALSE; 		 /*< if the left key has been found */
	unsigned int found_right=FALSE;		 /*< if the right key has been found */
	unsigned int restart_left_control=0;  	 /*< restart count for left key block */
	unsigned int restart_right_control=0;	 /*< restart counter for right key block */
	unsigned int restart_left_mv_control=0;  /*< restart count for left key block */
	unsigned int restart_right_mv_control=0; /*< restart counter for right key block */
	unsigned int change_left_count=0;    	 /*< movement change counter for left key block */
	unsigned int change_right_count=0;    	 /*< movement change counter for right key block */
	unsigned int left_iter=0;             	 /*< left iteration number */
	unsigned int right_iter=0;            	 /*< right iteration number */
	unsigned int i=0;						 /*< just a counter */
	unsigned long bit=1;
	movement *move_left;					 /*< movement for left key block */
	movement *move_right;					 /*< movement for right key block */
	final_report *report_final; 			 /*< structure for final report generation */
	time_t init_right_seconds;               
	time_t end_right_seconds;
	time_t init_left_seconds;
	time_t end_left_seconds;
	time_t init_global_seconds;
	time_t end_global_seconds;
	clock_t global_clock; 		 			 /*< clock count for global tabu search */
	clock_t right_clock; 					 /*< clock count for right tabu search */
	clock_t left_clock;   					 /*< clock count for left tabu search */
	
	time(&init_global_seconds);
	
	if((move_left=MALLOC(movement))==NULL)
	{
		fprintf(stderr,"ERROR: FAILED TO ALLOCATE MEMORY\n");
		exit(1);
	}
	if((move_right=MALLOC(movement))==NULL)
	{
		fprintf(stderr,"ERROR: FAILED TO ALLOCATE MEMORY\n");
		exit(1);
	}
	
	/* initialize movements */
	move_left->move=(void *)&move_alpha;
	move_right->move=(void *)&move_alpha;
	
	/* generate a initial random solucion for the problem */
	generate_initial_solution(key);

	/* generate tabu search parameters */
	params=create_params(options);

	/* generate tabu list for 2 key blocks*/
	list_left=create_tabu_list(params);
	list_right=create_tabu_list(params);
	
	/* activate best result data structure for 2 key blocks */
	if(!((best_left=MALLOC(best_result))==NULL))
	{
		best_left->key[0]=key[0];
		best_left->key[1]=key[1];
		best_left->bit=0;
		best_left->value=evaluate(key[1],cpmess,LEFT,report,params);
	}
	else
	{
		fprintf(stderr,"ERROR: FAILED TO ALLOCATE MEMORY\n");
		exit(1);
	}
	if(!((best_right=MALLOC(best_result))==NULL))
	{
		best_right->key[0]=key[2];
		best_right->key[1]=key[3];
		best_right->bit=0;
		best_right->value=evaluate(key[3],cpmess,RIGHT,report,params);
	}
	else
	{
		fprintf(stderr,"ERROR: FAILED TO ALLOCATE MEMORY\n");
		exit(1);
	}
	
	(report->print_init)(params,report->options,stdout);
	if(report->options->save_output)
	{
		(report->print_init)(params,report->options,report->report_file);
	}
	
	time(&init_left_seconds);
	time(&init_right_seconds);
	
	if(report->options->paranoid_leve>0)
	{
		if((report->par=MALLOC(paranoid))==NULL)
		{
			fprintf(stderr,"ERROR: FAILED TO ALLOCATE MEMORY\n");
			exit(1);
		}
	}

	
	for(i=0;i<params->tabu_iterations;i++)
	{
		if(found_left==FALSE)
		{
			/*
			 * Individual movement selection for left key block 
			 */
			if(restart_left_mv_control>=params->change_move_limit)
			{
				key[1]=best_left->key[1];
				restart_tabu(list_left,params);
				if(change_left_count%2!=0)
				{
					move_left->move=(void *)&move_alpha;
				}
				else
				{
					move_left->move=(void *)&move_beta;
				}
				change_left_count++;
				restart_left_mv_control=0;
			}
			/* just move */
			if(report->options->paranoid_leve>0)
			{
				report->par->key=key[1];
				report->par->block=LEFT;
				report->par->tabu=control_left;
				report->par->list=list_left;
			}
			(report->print_paranoid)(report->par,stderr);
			(move_left->move)(key,list_left,&mistakes_left,&control_left,&found_left,best_left,params,report,cpmess,LEFT);
			(report->print_iteration)(best_left,LEFT,i+1,stderr);
			
			/*
			 * Convergency condition and restart condition for left block key
			 */
			
			if((best_left->value)>=TABU_END_LIMIT)
			{
				time(&end_left_seconds);
				left_clock=clock();
				left_iter=i+1;
				found_left=TRUE;
				bit=1;
				bit=bit<<31;
				/* a tricky 31th bit swap */
			/*	if(!((best_left->key[1]&bit)&&(best_left->key[1]&bit<<1))&&!(((best_left->key[1]^LONG_MAX)&bit)&&((best_left->key[1]^LONG_MAX)&bit<<1))){
					best_left->key[1]=best_left->key[1]^bit;
					best_left->key[1]=best_left->key[1]^bit<<1;
				}*/

			}
			if(mistakes_left>=params->tabu_max_decrease)
			{
				restart_left_control++;
				restart_left_mv_control++;
				restart_left(key);
				if(evaluate(key[1],cpmess,LEFT,report,params)>=best_left->value)
				{
					best_left->key[0]=key[0];
					best_left->key[1]=key[1];
					best_left->bit=0;
					best_left->value=evaluate(key[1],cpmess,LEFT,report,params);
				}
				restart_tabu(list_left,params);
				mistakes_left=0;
			}
		}

		if(found_right==FALSE)
		{
			/*
			 *Individual movement selection for right key block
			 */
			if(restart_right_mv_control>=params->change_move_limit)
			{
				key[3]=best_right->key[1];
				restart_tabu(list_right,params);
				if(change_right_count%2==0)
					move_right->move=(void *)&move_alpha;
				else
					move_right->move=(void *)&move_beta;
				change_right_count++;
				restart_right_mv_control=0;
			}
			/* just move */
			if(report->options->paranoid_leve>0)
			{
				report->par->key=key[3];
				report->par->block=RIGHT;
				report->par->tabu=control_right;
				report->par->list=list_right;
			}
			(report->print_paranoid)(report->par,stderr);
			(move_right->move)(key,list_right,&mistakes_right,&control_right,&found_right,best_right,params,report,cpmess,RIGHT);
			(report->print_iteration)(best_right,RIGHT,i+1,stderr);

			/*
			 * Convergency condition and restart condition for right block key
			 */
			if((best_right->value)>=TABU_END_LIMIT)
			{
				time(&end_right_seconds);
				right_clock=clock();
				right_iter=i+1;
				found_right=TRUE;
				bit=1;
				bit=bit<<31;
				/* a tricky 31th bit swap */
			/*	if(!((best_right->key[1]&bit)&&(best_right->key[1]&bit<<1))&&!(((best_right->key[1]^LONG_MAX)&bit)&&((best_right->key[1]^LONG_MAX)&bit<<1))){
					best_right->key[1]=best_left->key[1]^bit;
					best_right->key[1]=best_left->key[1]^bit<<1;
				}*/
				
			}
			if(mistakes_right>=params->tabu_max_decrease)
			{
				restart_right_control++;
				restart_right_mv_control++;
				restart_right(key);
				if(evaluate(key[3],cpmess,RIGHT,report,params)>=best_right->value)
				{
					best_right->key[0]=key[2];
					best_right->key[1]=key[3];
					best_right->bit=0;
					best_right->value=evaluate(key[3],cpmess,RIGHT,report,params);
				}
				restart_tabu(list_right,params);
				mistakes_right=0;
			}
		}
		/* if the left and right block converges, then stop */
		if(found_left==TRUE&&found_right==TRUE)
		{
			break;
		}
		
	}
	
	if(report->options->paranoid_leve>0)
	{
		free((char *)report->par);
	}
	
	if(found_left==FALSE)
	{
		time(&end_left_seconds);
		left_clock=clock();
		left_iter=i;
	}

	if(found_right==FALSE)
	{
		time(&end_right_seconds);
		right_clock=clock();
		right_iter=i;
	}

	time(&end_global_seconds);
	global_clock=clock();
		
	gamma_tea(cpmess[0].plain_message,cpmess[0].cipher_message,best_left->key);
	key[2]=best_right->key[0];
	key[3]=best_right->key[1];
	delta_tea(cpmess[0].plain_message,cpmess[0].cipher_message,key);
	best_right->key[0]=key[2];
	
	if((report_final=MALLOC(final_report))==NULL)
	{
		fprintf(stderr,"ERROR: FAILED TO ALLOCATE MEMORY\n");
		exit(1);
	}
	/* mold final report structure */
	report_final->left=best_left;
	report_final->right=best_right;
	report_final->init_left=init_left_seconds;
	report_final->init_right=init_right_seconds;
	report_final->init_global=init_global_seconds;
	report_final->end_left=end_left_seconds;
	report_final->end_right=end_right_seconds;
	report_final->end_global=end_global_seconds;
	report_final->clock_left=left_clock;
	report_final->clock_right=right_clock;
	report_final->clock_global=global_clock;
	report_final->change_left_count=change_left_count;
	report_final->change_right_count=change_right_count;
	report_final->restart_left_control=restart_left_control;
	report_final->restart_right_control=restart_right_control;
	report_final->left_iter=left_iter;
	report_final->right_iter=right_iter;
	
	(report->print_end)(report_final,stdout);
	if(report->options->save_output)
		(report->print_end)(report_final,report->report_file);
		
	/* free all used memory */
	free_tabu(list_right->next,list_right->name);
	free_tabu(list_left->next,list_left->name);
	free((char *)list_right);
	free((char *)list_left);
	free((char *)best_right);
	free((char *)best_left);
	free((char *)params);
	free((char *)move_left);
	free((char *)move_right);
	free((char *)report_final);
}
/**
 * Generate a random initial key solution.
 * \param key where to put the new key
 */
void generate_initial_solution(unsigned long *key)
{
	unsigned int randomic;
	time_t seconds;
	time(&seconds);
	srand((unsigned int) seconds+key[0]);
	rand();
	if((randomic=rand())>0)
	{
		key[2]=(unsigned long)randomic;
	}
	if((randomic=rand())>0)
	{
		key[3]=(unsigned long)randomic;
	}
	if((randomic=rand())>0)
	{
		key[1]=(unsigned long)randomic;
	}
	if((randomic=rand())>0)
	{
		key[0]=(unsigned long)randomic;
	}
}
/**
 * Restart the left key block with a random key
 * \param key where to put the new key
 */
void restart_left(unsigned long *key)
{
	unsigned int randomic;
	time_t seconds;
	
	time(&seconds);
	
	srand((unsigned int) seconds+key[3]);
	rand();
	rand();
	if((randomic=rand())>0)
	{
		key[1]=(unsigned long)randomic;
	}
	else
	{
		key[1]=key[1]<<1;
	}
}
/**
 * Restart the right key block with a random key
 * \param key where to put the new key block
 */
void restart_right(unsigned long *key)
{
	unsigned int randomic;
	time_t seconds;
	
	time(&seconds);
	
	srand((unsigned int) seconds+key[0]);
	rand();
	rand();
	if((randomic=rand())>0)
	{
		key[3]=(unsigned long)randomic;
	}
	else
	{
		key[3]=key[3]>>1;
	}
}
/**
 * Create Tabu Search Params from Tabu Search general options
 * \param options Tabu Search general options
 */
ts_params *create_params(input_options *options)
{
	ts_params *params;
	if(!((params=MALLOC(ts_params))==NULL))
	{
		if(options->tabu_list_length==0)
		{
			params->tabu_list_length=DEFAULT_TABU_LIST_LENGTH;
		}
		else
		{
			params->tabu_list_length=options->tabu_list_length;
		
		}
		if(options->tabu_iterations==0)
		{
			params->tabu_iterations=DEFAULT_TABU_CYCLES;
		}
		else
		{
			params->tabu_iterations=options->tabu_iterations;
		}
		if(options->tabu_max_decrease==0)
		{
			params->tabu_max_decrease=DEFAULT_TABU_RESTART_LIMIT;
		}
		else
		{
			params->tabu_max_decrease=options->tabu_max_decrease;
		}
		if(options->change_move_limit==0)
		{
			params->change_move_limit=CHANGE_MOVE_LIMIT;
		}
		else
		{
			params->change_move_limit=options->change_move_limit;
		}
		if(options->key_eval_percent==0)
		{
			params->key_eval_percent=PERCENT_MULTI;	
		}
		else
		{
			params->key_eval_percent=options->key_eval_percent;
		}
	}
	else
	{
		fprintf(stderr,"ERROR: FAILED TO ALLOCATE MEMORY\n");
		exit(1);
	}
	return(params);
}
/**
 * Create a new empty Tabu list with lenght specified in parameters
 * \param params Parameters for this tabu search
 */
tabu_list *create_tabu_list(ts_params *params)
{
	
	int i;
	tabu_list *tabu;
	tabu_list *tabu_t;
	
	if((tabu=MALLOC(tabu_list))==NULL)
	{
		fprintf(stderr,"ERROR: FAILED TO ALLOCATE MEMORY\n");
		exit(1);
	}
	tabu_t=tabu;
	for(i=0;i<params->tabu_list_length;i++)
	{
		tabu_t->key=0x0;
		tabu_t->bit_position=POST_LIMIT;
		tabu_t->value=0;
		tabu_t->name=i;
		if(i<params->tabu_list_length-1){
			if((tabu_t->next=MALLOC(tabu_list))==NULL)
			{
				fprintf(stderr,"ERROR: FAILED TO ALLOCATE MEMORY\n");
				exit(1);
			}
		}
		else
		{ 
			tabu_t->next=tabu; 
			break;
		}
		tabu_t=tabu_t->next;
	}
	return(tabu);
}
/**
 * Change all values of Tabu list to empty default values
 * \param tabu_t Tabu list
 * \param params Parameters for this tabu search
 */
void restart_tabu(tabu_list *tabu_t,ts_params *params)
{
	int i;
	for(i=0;i<params->tabu_list_length;i++)
	{
		tabu_t->key=0;
		tabu_t->bit_position=POST_LIMIT;
		tabu_t->value=0;
		tabu_t->name=i;
		tabu_t=tabu_t->next;
	}
}
/**
 * Free all memory used by tabu list elements
 * \param tabu Tabu list
 * \param name name for the initial element of tabu list
 */
void free_tabu(tabu_list *tabu,unsigned int name)
{
	if(tabu->name==name)
	{
		return;
	}
	else{
		free_tabu(tabu->next,name);
		free((char *)tabu);
	}
}
