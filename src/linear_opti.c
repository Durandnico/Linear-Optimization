/* **************************************************************************** */
/*                                                                              */
/*                                                       ::::::::  :::   :::    */
/*   Linear Optimisation                                :+:    :+: :+:   :+:    */
/*                                                    +:+         +:+ +:+       */
/*   By: Durandnico <durandnico@cy-tech.fr>          +#+          +#++:         */
/*                                                 +#+           +#+            */
/*   Created: 28/03/2023 15:33:26 by Durandnico   #+#    #+#    #+#             */
/*                                                ########     ###              */
/*                                                                              */
/* **************************************************************************** */

/*! 
 *  \file linear_opti.c
 *  \author DURAND Nicolas Erich Pierre <nicolas.durand@cy-tech.fr>
 *  \version 1.0
 *  \date Tue 28 March 2023 - 15:33:26
 *
 *  \brief 
 *
 *
 */

//librairies
#include "../inc/linear_opti.h"

/*!
 *  \fn static t_opti_table** init_table()
 *  \author DURAND Nicolas Erich Pierre <nicolas.durand@cy-tech.fr>
 *  \version 1.0
 *  \date Tue 28 March 2023 - 15:33:56
 *  \brief  initialize the table 
 *  \return the optimization table
 */
t_data** init_table(size_t n)
{
    t_data** arr;
    n = 5;
    arr = malloc(n * sizeof(*arr));

    // alloc memory and set all to 0
    for(int i = 0; i < n; i++){
        arr[i] = calloc(n + 1, sizeof(*arr[i]));

}


/* ------------------------------------------------------------------------ */