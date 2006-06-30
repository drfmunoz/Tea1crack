/** 
 * \file ts_full_test.h
 * \brief Tabu Search full test constants
 * \ingroup all
 * \author Freddy Mun~oz Ramirez <frmunoz(at)inf.utfsm.cl>
 * \date Autumn 2006
 * \license <br> This code can be re-distributed under MIT License
 */
#ifndef _TS_FULL_TEST_H_
#define _TS_FULL_TEST_H_
/** \def TS_LIST_INCREMENT                                                                                  
 * Tabu list lenght increment                                                                               
 */
#define TS_LIST_INCREMENT 2
/** \def TS_ITER_INCREMENT                                                                                 
 * Tabu search iteration increment                                                                       
 */
#define TS_ITER_INCREMENT 100
/** \def TS_PERCENT_INCREMENT                                                                                 
 * Tabu search evaluation key percent increment                                                                                
 */
#define TS_PERCENT_INCREMENT 5
/** \def TS_MAX_DEC_INCREMENT                                                                                 
 *  Tabu search decrement performance increment                                                                                
 */
#define TS_MAX_DEC_INCREMENT 1
/** \def TS_CHM_INCREMENT                                                                                 
 *  Tabu search change movement increment                                                                                
 */
#define TS_CHM_INCREMENT 1
/** \def TS_LIS_MAX                                                                                 
 *  Tabu search max list lenght number                                                                                
 */
#define TS_LIS_MAX 31
/** \def TS_ITER_MAX                                                                                 
 *  Tabu search max iteration number                                                                                
 */
#define TS_ITER_MAX 5000
/** \def TS_MAX_DEC_MAX                                                                                 
 *  Tabu search max performance decremente                                                                   
 */
#define TS_MAX_DEC_MAX 64
/** \def TS_CHM_MAX                                                                                 
 *  Tabu search max change movement limit                                                                                 
 */
#define TS_CHM_MAX 4
/** \def TS_INIT_LIST                                                                                 
 *  Tabu list initial lenght                                                                     
 */
#define TS_INIT_LIST 2
/** \def TS_INIT_ITER                                                                                 
 * Tabu search initial iterations                                                         
 */
#define TS_INIT_ITER 1000
/** \def TS_INIT_MAX_DEC                                                                                 
 * Tabu search initial performance decrement limit                                                         
 */
#define TS_INIT_MAX_DEC 64
/** \def TS_INIT_CHM                                                                                 
 * Tabu search initial change movement limit                                                                                 
 */
#define TS_INIT_CHM 4
/** \def TS_INIT_PERCENT                                                                                 
 * Tabu search initial key evaluation percent                                                                                 
 */
#define TS_INIT_PERCENT 10

#endif