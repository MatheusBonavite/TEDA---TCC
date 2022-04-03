#include <math.h>
#include <stdio.h>
#include <stdlib.h>

double online_eccentricity(
    double **matrix,
    double *mi,
    double *x_inner_mean,
    double *sigma,
    unsigned int amount_of_columns,
    unsigned int k)
{
    /*
        amount_of_columns: represents dimension here!
    */
    double alpha_one = (double)(k / (k + 1.0));
    double alpha_two = (double)(1.0 / (k + 1.0));

    if (k > 0)
    {
        double *mi_aux = (double *)malloc(amount_of_columns * sizeof(double));
        for (int i = 0; i < amount_of_columns; i++)
        {
            mi_aux[i] = (alpha_one * mi[i]);
            mi_aux[i] += (matrix[k][i] * alpha_two);
            mi[i] = mi_aux[i];
        }

        double *x_inner_mean_aux = (double *)malloc(amount_of_columns * sizeof(double));
        for (int i = 0; i < amount_of_columns; i++)
        {
            x_inner_mean_aux[i] = (alpha_one * x_inner_mean[i]);
            x_inner_mean_aux[i] += ((matrix[k][i] * matrix[k][i]) * alpha_two);
            x_inner_mean[i] = x_inner_mean_aux[i];
        }

        double sigma_accum = 0.0;
        for (int i = 0; i < amount_of_columns; i++)
        {
            sigma_accum += (x_inner_mean[i] - (mi[i] * mi[i]));
        }
        *sigma = sigma_accum;

        free(mi_aux);
        free(x_inner_mean_aux);
    }
    else
    {
        for (int i = 0; i < amount_of_columns; i++)
        {
            mi[i] = matrix[k][i];
        }
        for (int i = 0; i < amount_of_columns; i++)
        {
            x_inner_mean[i] = (matrix[k][i] * matrix[k][i]);
        }
        *sigma = 0.0;
    }

    double eccentricity_accum = 0.0;
    if (*sigma > 0)
    {
        for (int i = 0; i < amount_of_columns; i++)
        {
            eccentricity_accum += ((mi[i] - matrix[k][i]) * (mi[i] - matrix[k][i]));
            eccentricity_accum *= (alpha_two / (*sigma));
            eccentricity_accum += alpha_two;
        }
    }
    return eccentricity_accum;
}

// double cached_under_k = (double)1.0 / (k + 1.0);     //pink
// double cached_k_minus_one = (double)(k / (k + 1.0)); //amarelo
// double chached_mod_x_mi = (double)0.0;
// double chached_mod_mi_x = (double)0.0;

// //Updating mi:
// double *mi_aux = (double *)malloc(amount_of_columns * sizeof(double));
// for (int i = 0; i < amount_of_columns; i++)
// {
//     mi_aux[i] = (cached_k_minus_one * mi[i]);
//     mi_aux[i] += (matrix[k][i] * cached_under_k);
//     mi[i] = mi_aux[i];
// }
// printf("\n Mi update (inside function): \n");
// for (int i = 0; i < amount_of_columns; i++)
// {
//     printf("\n m[%i] = %lf", i, mi[i]);
// }
// free(mi_aux);
// /***************************/

// if (k > 0)
// {
//     //Updating sigma:
//     for (int i = 0; i < amount_of_columns; i++)
//     {
//         chached_mod_x_mi += (fabs(matrix[k][i] - mi[i]) * fabs(matrix[k][i] - mi[i]));
//         chached_mod_mi_x += ((mi[i] - matrix[k][i]) * (mi[i] - matrix[k][i]));
//     }
//     *sigma = (cached_k_minus_one * (*sigma)) + (pow(((sqrt(chached_mod_x_mi) * 2.0) / amount_of_columns), 2.0) * (1.0 / k));
//     /***************************/
// }
// printf("\n Sigma update (inside function): ");
// printf("\n sigma = %lf", *sigma);
// if ((k + 1.0) <= 2)
// {
//     return 1.0;
// }

// return (cached_under_k + (chached_mod_mi_x / ((k + 1.0) * (*sigma))));