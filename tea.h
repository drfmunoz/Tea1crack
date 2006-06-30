/** 
 * \file tea.h
 * \brief TEA constant and functions definitions
 * \ingroup tea
 * \author Freddy Mun~oz Ramirez <frmunoz(at)inf.utfsm.cl>
 * \date Autumn 2006
 * \license <br> This code can be re-distributed under MIT License
 */
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

void tea_encrypt(unsigned long*,unsigned long*,const unsigned long *);
void tea_decrypt(unsigned long*,unsigned long*,const unsigned long *);
void alpha_tea(unsigned long *,unsigned long *,unsigned long *);
void beta_tea(unsigned long *,unsigned long *,unsigned long *);
void gamma_tea(unsigned long *, unsigned long *, unsigned long *);
void delta_tea(unsigned long *, unsigned long *, unsigned long *);

#endif