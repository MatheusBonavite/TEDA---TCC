#include <stdlib.h>
#include <stdio.h>

struct Micro_Cluster
{
    int number_of_micro_clusters;
    int number_of_data_samples;
    double center;
    double variance;
    double eccentricity;
    double typicality;
    double density;
    double outlier_threshold;
};

struct Micro_Cluster *update_micro_cluster(
    struct Micro_Cluster *micro_clusters_arr,
    unsigned int k)
{
    if (k == 0)
    {
        struct Micro_Cluster *temp = (struct Micro_Cluster *)calloc(1, sizeof(struct Micro_Cluster));
        if (temp == NULL)
        {
            printf("Cannot allocate initial memory.\n");
            exit(1);
        }
        else
        {
            temp[0].number_of_micro_clusters = 1;
            temp[0].number_of_data_samples = 1;
            temp[0].center = 1.0;
            temp[0].variance = 0.0;
            return temp;
        }
    }
}