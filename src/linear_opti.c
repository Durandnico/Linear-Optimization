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

t_opti_table init_table(int int_nb_arg)//, float* X1, float* X2, float* Y)
{

    float X1[4] = {39,2.5,0.125,17.5};
    float X2[4] = {69, 7.5, 0.125, 10}; 
    float ugo[4] = {0,240,5,595};

    t_opti_table res;
    res.int_arg = int_nb_arg;
    int n = int_nb_arg;
    res.data_arr = malloc((n + 2) * sizeof(*res.data_arr));

    /* alloc memory and set all to 0 */
    for(int i = 0; i < n + 2; i++)
        res.data_arr[i] = calloc((n + 4) , sizeof(*res.data_arr[i]));

    /* set static part of the table*/
    res.data_arr[0][0].type_var = VAR_TYPE_STRING;  //left top corner
    res.data_arr[0][n + 3].type_var = VAR_TYPE_STRING;  //right top corner
    res.data_arr[1][0].type_var = VAR_TYPE_STRING;  //2nd row left corner (useless)
    strcpy(res.data_arr[0][0].table_var.str_value, "var");
    strcpy(res.data_arr[0][n + 3].table_var.str_value, "res");


    /* set all column title */
    for(int i = 1; i < n + 3; ++i){
        res.data_arr[0][i].type_var = VAR_TYPE_STRING;
        sprintf(res.data_arr[0][i].table_var.str_value, "%c%d", (i < 3) ? 'X' : 'Y', (i < 3) ? i  : i - 2 );
    }

    /* set all row title */
    for(int i = n + 1; i > 1; --i){
        res.data_arr[i][0].type_var = VAR_TYPE_STRING;
        sprintf(res.data_arr[i][0].table_var.str_value, "Y%d", i-1);
    }


    /* set value for X0 */
    for(int j = 1; j < n + 2; ++j){
        res.data_arr[j][1].type_var = VAR_TYPE_FLOAT;
        res.data_arr[j][1].table_var.flt_value = X1[j-1];
    }

    /* set value for X1 */
    for(int j = 1; j < n + 2; ++j){
        res.data_arr[j][2].type_var = VAR_TYPE_FLOAT;
        res.data_arr[j][2].table_var.flt_value = X2[j-1];
    }

    
    /* set value for Y0/1/../n */
    for(int i = 3; i < n + 3; ++i){
        res.data_arr[i-1][i].type_var = VAR_TYPE_FLOAT;
        res.data_arr[i-1][i].table_var.flt_value = 1;
    }

    /* set value for res */
    for(int i = 1; i < n+2; ++i){
        res.data_arr[i][n + 3].type_var = VAR_TYPE_FLOAT;
        res.data_arr[i][n + 3].table_var.flt_value = ugo[i - 1];
    }
    res.data_arr[1][n + 3].table_var.flt_value = 0;

    return (res);
}


/* ------------------------------------------------------------------------ */

void show_table(t_opti_table tbl)
{
    int n = tbl.int_arg;
    for(int i = 0; i < n + 2 ; ++i){
        for(int j = 0; j < n + 4; ++j){
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
        if( tbl.data_arr[1][i].type_var == VAR_TYPE_FLOAT && tbl.data_arr[1][i].table_var.flt_value > 0 )
            if( res == NULL || tbl.data_arr[1][*res].table_var.flt_value < tbl.data_arr[1][i].table_var.flt_value)
            {
                if(res == NULL)
                    res = malloc(sizeof(int));
                
                fprintf(stderr, "find entry: i = %d, old = %d\n", i, *res ? *res : 0);
                *res = i;
            } 
    }

    return (res);
}


/* ------------------------------------------------------------------------ */


static int* find_exit(t_opti_table tbl, int int_entry)
{
    ABORT_IF( int_entry < 1 || int_entry > tbl.int_arg + 2, "find_exit : int_entry is out of range");

    int* res = NULL;        //res var
    int n = tbl.int_arg;    //number of 

    fprintf(stderr, "find exit : int_entry = %d\n", int_entry);
    /* find the biggest value in the first column */
    for(int i = 2; i < n + 2; ++i){
        if( tbl.data_arr[i][int_entry].type_var == VAR_TYPE_FLOAT && tbl.data_arr[i][int_entry].table_var.flt_value > 0 )
            if( res == NULL || (tbl.data_arr[*res][n+3].table_var.flt_value / tbl.data_arr[*res][int_entry].table_var.flt_value ) > ( (float) tbl.data_arr[i][n + 3].table_var.flt_value / (float) tbl.data_arr[i][int_entry].table_var.flt_value))
            {
                if(res == NULL)
                    res = malloc(sizeof(int));
                
                fprintf(stderr, "find exit : i = %d, int_entry = %d, value = %f\n", i, int_entry, (float) tbl.data_arr[i][n + 3].table_var.flt_value / tbl.data_arr[i][int_entry].table_var.flt_value);
                *res = i;
            } 
    }

    return (res);
}


/* ------------------------------------------------------------------------ */

static void divide_line(t_opti_table tbl, int int_entry, int int_exit)
{
    int n = tbl.int_arg;
    float div = tbl.data_arr[int_exit][int_entry].table_var.flt_value;

    ABORT_IF( div == 0, "divide_line : div is 0");
    fprintf(stderr, "div = %f, entry = %d, exit  = %d, \n", div, int_entry, int_exit);

    for(int i = 1; i < n + 4; ++i)
    {
        tbl.data_arr[int_exit][i].table_var.flt_value /= (float) div;
        fprintf(stderr, "new value at %d, %d = %f\n", int_exit, i, tbl.data_arr[int_exit][i].table_var.flt_value);
    }
}


/* ------------------------------------------------------------------------ */


static void substract_nlinetoline(t_opti_table tbl, float flt_value, int int_index_source, int int_index_dest)
{
    ABORT_IF(int_index_source < 1 || int_index_source > tbl.int_arg + 2, "substract_nlinetoline : source index is out of range");
    ABORT_IF(int_index_dest < 1 || int_index_dest > tbl.int_arg + 2, "substract_nlinetoline : dest index is out of range");

    int n = tbl.int_arg;
    for(int i = 1; i < n + 4; ++i)
                tbl.data_arr[int_index_dest][i].table_var.flt_value -= tbl.data_arr[int_index_source][i].table_var.flt_value * flt_value;
    
}


/* ------------------------------------------------------------------------ */

/*!
 *  \fn void optimisation(t_opti_table tbl)
 *  \author DURAND Nicolas Erich Pierre <nicolas.durand@cy-tech.fr>
 *  \version 1.0
 *  \date Fri 31 March 2023 - 12:23:37
 *  \brief 
 *  \param 
 *  \return 
 */
void optimisation(t_opti_table tbl)
{
    //ABORT_IF(check_table(tbl) == -1, "optimisation : table is not valid");
    int cpt = 3;

    int* pint_entry = find_entry(tbl);
    ABORT_IF(pint_entry == NULL, "optimisation : no entry found");

    int* pint_exit = find_exit(tbl, *pint_entry);
    ABORT_IF(pint_exit == NULL, "optimisation : no exit found");

    fprintf(stderr, "entry : %d, exit : %d", *pint_entry, *pint_exit);
    while(pint_entry != NULL && pint_exit != NULL && cpt)
    {
        ABORT_IF(tbl.data_arr[0][*pint_entry].type_var != VAR_TYPE_STRING, "optimisation : entry is not a string");
        ABORT_IF(tbl.data_arr[*pint_exit][0].type_var != VAR_TYPE_STRING, "optimisation : exit is not a string");

        /* show table*/
        show_table(tbl);
        fprintf(stdout,"\n\t----------------------------------------\n\n");
        // set the new exit value (name)
        strcpy(tbl.data_arr[*pint_exit][0].table_var.str_value, tbl.data_arr[0][*pint_entry].table_var.str_value);
        
        /* divide all the line by the value of (entry, exit)*/
        divide_line(tbl, *pint_entry, *pint_exit);

        /* substract all line by n times (exit line) to make the entry row full of 0 (except for the exit line)*/
        for(int i = 1; i < tbl.int_arg + 2; ++i)
            if(i != *pint_exit)
                substract_nlinetoline(tbl, tbl.data_arr[i][*pint_entry].table_var.flt_value, *pint_exit, i);

        /* free momory */
        free(pint_entry);
        free(pint_exit);
        
        /* find new entry and exit */
        pint_entry = find_entry(tbl);
        if (pint_entry)
            pint_exit = find_exit(tbl, *pint_entry);
    }

    show_table(tbl);
}



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

    t_opti_table res = init_table(3);

    optimisation(res);

    return 0;
}