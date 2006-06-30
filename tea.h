#ifndef _TEA_HEADER_
#define _TEA_HEADER_


/** \def TEA_CYCLES                                                                                 
 * Cycles for TEA                                                                                     
 */
#define TEA_CYCLES 1

/** \def TEA_DELTA_KEY                                                                                 
 * TEA cypher key schedule                                                                                     
 */
#define TEA_DELTA_KEY 0x9E3779B9

/** \def TEA_SUM                                                                                 
 * TEA cypher sum                                                                                     
 */
#define TEA_SUM TEA_DELTA_KEY << 5

/* TEA cypher function */
void tea_encrypt(unsigned long*,unsigned long*,const unsigned long *);

/* TEA decypher  function */
void tea_decrypt(unsigned long*,unsigned long*,const unsigned long *);

/* get first right key block (32 bits block) from equation of relation in TEA1 with plain text*/
void alpha_tea(unsigned long *,unsigned long *,unsigned long *);

/* get first right key block (32 bits block) from equation of relation in TEA1 with plain text*/
void beta_tea(unsigned long *,unsigned long *,unsigned long *);

/* get first left key block (32 bits block) from equation of relation in TEA1 with cipher text */
void gamma_tea(unsigned long *, unsigned long *, unsigned long *);

/* get first right key block (32 bits block) from equation of relation in TEA1 with cipher text*/
void delta_tea(unsigned long *, unsigned long *, unsigned long *);

#endif