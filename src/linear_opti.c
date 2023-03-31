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

t_opti_table init_table(int int_nb_arg)
{
    t_opti_table res;
    res.int_arg = int_nb_arg;
    int n = 8;
    res.data_arr = malloc(n++ * sizeof(*res.data_arr));

    /* alloc memory and set all to 0 */
    for(int i = 0; i < n - 1; i++)
        res.data_arr[i] = calloc(n+1 , sizeof(*res.data_arr[i]));

    /* set static part of the table*/
    res.data_arr[0][0].type_var = VAR_TYPE_STRING;  //left top corner
    res.data_arr[0][n].type_var = VAR_TYPE_STRING;  //right top corner
    res.data_arr[1][0].type_var = VAR_TYPE_STRING;  //2nd row left corner (useless)
    strcpy(res.data_arr[0][0].table_var.str_value, "var");
    strcpy(res.data_arr[0][n].table_var.str_value, "res");


    /* set all column title */
    for(int i = 1; i < n; ++i){
        res.data_arr[0][i].type_var = VAR_TYPE_STRING;
        sprintf(res.data_arr[0][i].table_var.str_value, "%c%d", (i < 3) ? 'X' : 'Y', (i < 3) ? i  : i - 2 );
    }

    /* set all row title */
    for(int i = n-2; i > 1; --i){
        res.data_arr[i][0].type_var = VAR_TYPE_STRING;
        sprintf(res.data_arr[i][0].table_var.str_value, "Y%d", i-1);
    }


    /* set value for X0/X1 */
    for(int i = 1; i < 1; ++i);

    /* set value for Y0/1/../n */
    for(int i = 3; i < n ; ++i){
        res.data_arr[i-1][i].type_var = VAR_TYPE_FLOAT;
        res.data_arr[i-1][i].table_var.flt_value = 1;
    }

    return (res);
}


/* ------------------------------------------------------------------------ */

void show_table(t_opti_table tbl)
{
    int n = tbl.int_arg;
    for(int i = 0; i < n ; ++i){
        for(int j = 0; j < n + 2; ++j){
            switch (tbl.data_arr[i][j].type_var)
            {
            case VAR_TYPE_STRING:
                printf("%s", tbl.data_arr[i][j].table_var.str_value);
                break;
            
            case VAR_TYPE_FLOAT:

                if( (int) tbl.data_arr[i][j].table_var.flt_value == tbl.data_arr[i][j].table_var.flt_value )
                    printf("%d", (int) tbl.data_arr[i][j].table_var.flt_value);

                else
                    printf("%.3f", tbl.data_arr[i][j].table_var.flt_value);
                break;

            default:
                printf("NTS");
                break;
            }
            putchar('\t');
        }
        putchar('\n');
    }
}


/* ------------------------------------------------------------------------ */

static void swap_value(t_data* ptr_a, t_data* ptr_b )
{
    t_data tmp = *ptr_a;
    *ptr_a = *ptr_b;
    *ptr_b = tmp;
}


/* ------------------------------------------------------------------------ */


void free_table(t_opti_table tbl)
{
    ABORT_IF( tbl.data_arr == NULL, "free_table : table is already free");
    int n = tbl.int_arg;

    for(int i = 0; i < n ; ++i)
        free(tbl.data_arr[i]);
    free(tbl.data_arr);

    tbl.data_arr = NULL;
}


/* ------------------------------------------------------------------------ */

static int* find_entry(t_opti_table tbl)
{
    int* res = NULL;        //res var
    int n = tbl.int_arg;    //number of 

    /* find the biggest value in the first row */
    for(int i = 1; i < n + 2; ++i){
        if( tbl.data_arr[0][i].type_var == VAR_TYPE_FLOAT && tbl.data_arr[0][i].table_var.flt_value > 0 )
            if( res == NULL || *res < tbl.data_arr[1][i].table_var.flt_value)
            {
                if(res == NULL)
                    res = malloc(sizeof(int));
                
                *res = tbl.data_arr[1][i].table_var.flt_value;
            } 
    }

    return (res);
}


/* ------------------------------------------------------------------------ */


static int* find_exit(t_opti_table tbl)
{
    int* res = NULL;        //res var
    int n = tbl.int_arg;    //number of 

    /* find the biggest value in the first column */
    for(int i = 2; i < n + 2; ++i){
        if( tbl.data_arr[i][1].type_var == VAR_TYPE_FLOAT && tbl.data_arr[i][1].table_var.flt_value < 0 )
            if( res == NULL || *res > tbl.data_arr[i][1].table_var.flt_value)
            {
                if(res == NULL)
                    res = malloc(sizeof(int));
                
                *res = tbl.data_arr[i][1].table_var.flt_value;
            } 
    }

    return (res);
}


/* ------------------------------------------------------------------------ */



/*!
 *  \fn int main (int argc, char** argv)
 *  \author DURAND Nicolas Erich Pierre <nicolas.durand@cy-tech.fr>
 *  \version 1.0
 *  \date Wed 29 March 2023 - 10:35:13
 *  \brief Main program
 *  \param argc : number of parameters
 *  \param argv : Values of the parameters 
 *  \return 0 if no error, -1 otherwise
 */
int main (int argc, char** argv) {
    (void)(argc);
    (void)(argv);

    t_opti_table res = init_table(8);

    show_table(res);
    return 0;
}