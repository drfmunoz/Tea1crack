/** 
 * \file tea.c
 * \brief TEA Implementation
 * \ingroup tea
 * \author Freddy Mun~oz Ramirez <frmunoz(at)inf.utfsm.cl>
 * \date Autumn 2006
 * \license <br> This code can be re-distributed under MIT License
 */
#include "tea.h"
/**
 * TEA cipher implementation BASE TEA CODE FROM: http://www.simonshepherd.supanet.com/source.htm#ansi<br>
 * \param v Plain message
 * \param w Where to put cipher message
 * \param k Key
 */
void tea_encrypt(unsigned long *v,unsigned long *w,const unsigned long *k)
{
	register unsigned long y=v[0],z=v[1],sum=0,delta=TEA_DELTA_KEY, a=k[0],b=k[1],c=k[2],d=k[3],n=TEA_CYCLES;
	while(n-->0)
	{
		sum += delta;
		y += ((z << 4)+a) ^ (z+sum) ^ ((z >> 5)+b);
		z += ((y << 4)+c) ^ (y+sum) ^ ((y >> 5)+d);
	}
	w[0]=y; w[1]=z;
}
/**
 * TEA decipher implementation BASE TEA CODE FROM: http://www.simonshepherd.supanet.com/source.htm#ansi<br>
 * \param w Cipher message
 * \param v Where to put plain message
 * \param k Key
 */	
void tea_decrypt(unsigned long *v,unsigned long *w, const unsigned long *k)
{
	register unsigned long  y=v[0],z=v[1],sum=TEA_SUM,delta=TEA_DELTA_KEY,a=k[0],b=k[1],c=k[2],d=k[3],n=TEA_CYCLES;
	/* sum = delta<<5, in general sum = delta * n */
	sum=TEA_DELTA_KEY;
	while(n-->0)
	{
		z -= ((y << 4)+c) ^ (y+sum) ^ ((y >> 5)+d);
		y -= ((z << 4)+a) ^ (z+sum) ^ ((z >> 5)+b);
		sum -= delta;
	}
	w[0]=y; w[1]=z;
}
/**
 * TEA1 key descomposition for left key block, its calculate the  recidual key part (with minus noise) and mold it into key structure
 * a justification for the operation involved in this function can be found in http://www.inf.utfsm.cl/~frmunoz/research/tea
 * \param plan Plain Message
 * \param cipher Cipher Message
 * \param key Key candidate to calculate recidual key part IMPORTANT KEY CANDITATE keyp[0]
 */
void alpha_tea(unsigned long *plain,unsigned long *cipher,unsigned long *key)
{
	register unsigned long y=0;
	register unsigned long delta=TEA_DELTA_KEY;
	register unsigned long radix_left=0;
	register unsigned long radix_right=0;
	register unsigned long weaved_body=0;
	y=plain[0]+cipher[0];
	weaved_body=y^(plain[1]+delta);
	radix_left=plain[1]<<4;
	radix_right=plain[1]>>5;
	key[1]=((key[0]+radix_left)^weaved_body)-radix_right;
	
	
}
/**
 * TEA1 key descomposition for right key block, its calculate the  recidual key part (with minus noise) and mold it into key structure
 * a justification for the operation involved in this function can be found in http://www.inf.utfsm.cl/~frmunoz/research/tea 
 * \param plan Plain Message
 * \param cipher Cipher Message
 * \param key Key candidate to calculate recidual key part IMPORTANT KEY CANDITATE keyp[2]
 */
void beta_tea(unsigned long *plain,unsigned long *cipher,unsigned long *key)
{
	register unsigned long y=0;
	register unsigned long z=0;
	register unsigned long delta=TEA_DELTA_KEY;
	register unsigned long radix_left=0;
	register unsigned long radix_right=0;
	register unsigned long weaved_body=0;
	y=plain[0];
	z=plain[1]+cipher[1];
	weaved_body=z^(cipher[0]+delta);
	radix_left=cipher[0]<<4;
	radix_right=cipher[0]>>5;
	key[3]=((key[2]+radix_left)^weaved_body)-radix_right;
}
/**
 * TEA1 key descomposition for left key block, its calculate the  recidual key part (with minus noise) and mold it into key structure
 * a justification for the operation involved in this function can be found in http://www.inf.utfsm.cl/~frmunoz/research/tea
 * \param plan Plain Message
 * \param cipher Cipher Message
 * \param key Key candidate to calculate recidual key part IMPORTANT KEY CANDITATE keyp[1]
 */
void gamma_tea(unsigned long *plain, unsigned long *cipher, unsigned long *key)
{
	
	register unsigned long y=0;
	register unsigned long delta=TEA_DELTA_KEY;
	register unsigned long middle_exp=0;
	register unsigned long radix_left=0;
	register unsigned long radix_right=0;
	register unsigned long weaved_body=0;
	y=cipher[0]-plain[0];
	middle_exp=plain[1]+delta;
	radix_left= plain[1] << 4;
	radix_right= plain[1] >> 5 ;
	weaved_body=y^middle_exp;
	/* generate a key by equation generated from TEA schedule 1 cycle weakness */
	key[0]=(weaved_body^(radix_right+key[1]))-radix_left;
}
/**
 * TEA1 key descomposition for right key block, its calculate the  recidual key part (with minus noise) and mold it into key structure
 * a justification for the operation involved in this function can be found in http://www.inf.utfsm.cl/~frmunoz/research/tea
 * \param plan Plain Message
 * \param cipher Cipher Message
 * \param key Key candidate to calculate recidual key part IMPORTANT KEY CANDITATE keyp[3]
 */
void delta_tea(unsigned long *plain, unsigned long *cipher, unsigned long *key)
{
	register unsigned long y=0;
	register unsigned long z=0;
	register unsigned long delta=TEA_DELTA_KEY;
	register unsigned long middle_exp=0;
	register unsigned long radix_left=0;
	register unsigned long radix_right=0;
	register unsigned long weaved_body=0;
	y=cipher[0];
	z=cipher[1]-plain[1];
	middle_exp=y+delta;
	radix_left= y << 4;
	radix_right= y >> 5 ;
	weaved_body=middle_exp^z;
	/* generate a key by equation generated from TEA schedule 1 cycle weakness */
	key[2]=(weaved_body^(radix_right+key[3]))-radix_left;
}


