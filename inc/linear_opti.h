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
 *  \param VAR_TYPE_FLOAT   :   the variable is a float
 *  \param VAR_TYPE_STRING  :   the variable is a string
 */

typedef enum        s_type_var
{
    VAR_TYPE_FLOAT,
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
 *  \param flt_var_value    : Value of the variable
 * 
 *  \details
 *   - All variables are coded in 4 octets
 *   - So there are less problems with the initialisation of the table
 */
typedef union       s_table_value
{
    char        str_value[4];
    float       flt_value;
}                   t_table_value;


/* -------------------------------------------------------------------------- */


/*!
 *  \struct t_data
 *  \author DURAND Nicolas Erich Pierre <nicolas.durand@cy-tech.fr>
 *  \version 1.0
 *  \date Tue 28 March 2023 - 15:04:45
 *  \brief link a variable with its type
 *  \param type_var     : the type of the variable
 *  \param table_var    : the variable
 */
typedef struct              s_data
{
    t_type_var          type_var;
    t_table_value       table_var;
}                           t_data;

/* -------------------------------------------------------------------------- */


/*!
 *  \struct t_opti_table
 *  \author DURAND Nicolas Erich Pierre <nicolas.durand@cy-tech.fr>
 *  \version 1.0
 *  \date Wed 29 March 2023 - 12:21:05
 *  \brief the table for the linear optimization
 *  \param data_arr : the array of the data
 *  \param int_arg  : the number of arguments
 */

typedef struct          s_opti_table
{
    t_data**        data_arr;
    int             int_arg;
}                       t_opti_table;

/* ********************************   MACROS   ******************************** */

/*! 
 *  \def ABORT_IF(a, msg)
 *  \brief 
 */
#define ABORT_IF(a, msg) if(a) { fprintf(stderr,"%s\n",msg); exit(1); }


/* ******************************** STRUCTURES ******************************** */


/* ******************************* PROTOTYPES  ******************************* */


/*!
 *  \fn static void swap_value(t_data* ptr_a, t_data* ptr_b )
 *  \author DURAND Nicolas Erich Pierre <nicolas.durand@cy-tech.fr>
 *  \version 1.0
 *  \date Wed 29 March 2023 - 12:44:41
 *  \brief swap the value of two the table
 *  \param ptr_a : pointer to the first value
 *  \param ptr_b : pointer to the second value
 */
static void swap_value(t_data* ptr_a, t_data* ptr_b);


/*!
 *  \fn static int* find_entry(t_opti_table tbl)
 *  \author DURAND Nicolas Erich Pierre <nicolas.durand@cy-tech.fr>
 *  \version 1.0
 *  \date Wed 29 March 2023 - 12:53:09
 *  \brief find the entry var of the table
 *  \param tbl : the table to search
 *  \return pointer to the index of the entry or NULL if not found 
 */
static int* find_entry(t_opti_table tbl);


/*!
 *  \fn static int* find_exit(t_opti_table tbl, int int_entry)
 *  \author DURAND Nicolas Erich Pierre <nicolas.durand@cy-tech.fr>
 *  \version 1.0
 *  \date Fri 31 March 2023 - 11:41:08
 *  \brief find the exit var of the table
 *  \param tbl : the table to search
 *  \return pointer to the index of the exit or NULL if not found
 */
static int* find_exit(t_opti_table tbl, int int_entry);


/*!
 *  \fn static void divide_line(t_opti_table tbl, int int_entry, int int_exit)
 *  \author DURAND Nicolas Erich Pierre <nicolas.durand@cy-tech.fr>
 *  \version 1.0
 *  \date Fri 31 March 2023 - 11:48:57
 *  \brief divide the line of index int_exit by the value of the cell of index (int_entry, int_exit)
 *  \param tbl : the opti table 
 */
static void divide_line(t_opti_table tbl, int int_entry, int int_exit);


/*!
 *  \fn static void substract_nlinetoline(t_opti_table tbl, float flt_value, int int_index_source, int int_index_dest)
 *  \author DURAND Nicolas Erich Pierre <nicolas.durand@cy-tech.fr>
 *  \version 1.0
 *  \date Fri 31 March 2023 - 11:52:02
 *  \brief substract n time source line to the dest line
 *  \param tbl              : the opti table
 *  \param flt_value        : the number of time to substract the source line to the dest line
 *  \param int_index_source : the index of the source line
 *  \param int_index_dest   : the index of the dest line
 */
static void substract_nlinetoline(t_opti_table tbl, float flt_value, int int_index_source, int int_index_dest);




/*!
 *  \fn void show_table(t_data** arr)
 *  \author DURAND Nicolas Erich Pierre <nicolas.durand@cy-tech.fr>
 *  \version 1.0
 *  \date Wed 29 March 2023 - 10:52:26
 *  \brief 
 *  \param 
 *  \return 
 */
void show_table(t_opti_table arr);

/*!
 *  \fn void free_table(t_opti_table tbl)
 *  \author DURAND Nicolas Erich Pierre <nicolas.durand@cy-tech.fr>
 *  \version 1.0
 *  \date Wed 29 March 2023 - 12:47:17
 *  \brief free the table
 *  \param tbl : the table to free
 *  \return set the table to NULL
 */
void free_table(t_opti_table tbl);


/*!
 *  \fn static t_opti_table** init_table()
 *  \author DURAND Nicolas Erich Pierre <nicolas.durand@cy-tech.fr>
 *  \version 1.0
 *  \date Tue 28 March 2023 - 15:33:56
 *  \brief  initialize the table 
 *  \param int_nb_arg   :   number of argument
 *  \return the optimization table initialize
 */
t_opti_table init_table(int int_nb_arg);

#endif