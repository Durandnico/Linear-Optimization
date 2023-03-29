/* **************************************************************************** */
/*                                                                              */
/*                                                       ::::::::  :::   :::    */
/*  Linear Optimisation                                 :+:    :+: :+:   :+:    */
/*                                                    +:+         +:+ +:+       */
/*   By: Durandnico <durandnico@cy-tech.fr>          +#+          +#++:         */
/*                                                 +#+           +#+            */
/*   Created: 28/03/2023 14:37:26 by Durandnico   #+#    #+#    #+#             */
/*   Updated: None                                ########     ###              */
/*                                                                              */
/* **************************************************************************** */


/*! 
 *  \file linear_opti.h
 *  \author DURAND Nicolas Erich Pierre <nicolas.durand@cy-tech.fr>
 *  \version 1.0
 *  \date Tue 28 March 2023 - 14:37:26
 *
 *  \brief Headers of linear_opti.c
 *
 *
 */

#pragma once
#ifndef __LINEAR_OPTI_H
#define __LINEAR_OPTI_H

// librairies
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <time.h>



/* *******************************    DEFINE    ******************************* */

/*!
 *  \enum t_type_var
 *  \author DURAND Nicolas Erich Pierre <nicolas.durand@cy-tech.fr>
 *  \version 1.0
 *  \date Tue 28 March 2023 - 15:03:34
 *  \brief contains the type of the variable that the union contain
 *  \param 
 */

typedef enum        s_type_var
{
    VAR_TYPE_FLOAT,
    VAR_TYPE_LONG_INT,
    VAR_TYPE_STRING         
}                   t_type_var;

/* -------------------------------------------------------------------------- */

/*!
 *  \struct t_table_value
 *  \author DURAND Nicolas Erich Pierre <nicolas.durand@cy-tech.fr>
 *  \version 1.0
 *  \date Tue 28 March 2023 - 14:43:31
 *  \brief Structure of the table of the variables than can be in the linear optimisation table
 *  \param str_var_name[4]  : Name of the variable
 *  \param flt_var_value    : Value of the variable (float)
 *  \param lng_var_value    : Value of the variable (long int)
 * 
 *  \details
 *   - All variables are coded in 4 octets
 *   - So there are less problems with the initialisation of the table
 */
typedef union       s_table_value
{
    char        str_value[4];
    float       flt_value;
    long int    lng_value;
}                   t_table_value;

/* -------------------------------------------------------------------------- */

/*!
 *  \struct t_data
 *  \author DURAND Nicolas Erich Pierre <nicolas.durand@cy-tech.fr>
 *  \version 1.0
 *  \date Tue 28 March 2023 - 15:04:45
 *  \brief 
 *  \param 
 */
typedef struct              s_data
{
    t_type_var          type_var;
    t_table_value*      table_var;
}                           t_data;

/* ********************************   MACROS   ******************************** */


/* ******************************** STRUCTURES ******************************** */


/* ******************************* PROTOTYPES  ******************************* */


t_data** init_table(size_t n);

static void swap_value(t_data* ptr_a, t_data* ptr_b);

static void find_entry_var(t_data** arr);



#endif