#include "stdlib.h"
#include "time.h"
#include "stdio.h"
#include "float.h"

/* Defines */
#define RAND_RANGE_MIN (-500000)
#define RAND_RANGE_MAX (500000)
#define INPUT_ARRAY_SIZE (100000)

/* Function Prototypes */
double iterative_average(double *input_value_array, long long unsigned int input_value_array_size);
double rand_double_range(double min, double max);

int main() {
    FILE* fp;
    double array_of_doubles[INPUT_ARRAY_SIZE];
    double averaged_value;

    // Open input values file
    fp = fopen("input_values.txt","w+");

    // Set seed for random function to be based on current time
    srand(time(NULL));

    // Create the array of random values
    for (long long unsigned int index = 0; index < INPUT_ARRAY_SIZE; index++) {
        double value = rand_double_range(RAND_RANGE_MIN, RAND_RANGE_MAX);

        array_of_doubles[index] = value;
        fprintf(fp,"%f\n", value);
    }

    // Close input values file
    fclose(fp);

    // Run the iterative iterative_average function
    averaged_value = iterative_average(array_of_doubles, INPUT_ARRAY_SIZE);

    // Print result
    if(averaged_value == DBL_MAX){
        printf("Error occurred, please check configuration");
    } else {
        printf("The average value is: %f", averaged_value);
    }
}


/*
 * Iterative Average Function Definition
 *
 * Find the average of an array of double floating point inputs using an iterative approach. We need to use iterative
 * approach because the number of elements is arbitrary which could lead to overflow issues.
 *
 * https://www.heikohoffmann.de/htmlthesis/node134.html
 * next_average = current_average + ( (1 / (index + 1)) * (input_value - current_average) )
 *
 * Inputs:
 * input_value_array      --- an array of doubles of arbitrary size to be averaged
 * input_value_array_size --- size of array to be averaged, can be up to ULLONG_MAX
 *
 * Outputs:
 * Returns the calculated iterative average, DBL_MAX if there is an error
 */
double iterative_average(double *input_value_array, long long unsigned int input_value_array_size) {
    double current_average = 0.0;

    // Check inputs to ensure valid
    if(input_value_array == NULL || input_value_array_size == 0){
        return DBL_MAX;
    }

    // Iterate through list, calculating average as we go
    for (long long unsigned int index = 0; index < input_value_array_size; index++) {
        // next_average = current_average + ((1 / (index           + 1)) * (input_value              - current_average))
        current_average = current_average + ((1 / (((double)index) + 1)) * (input_value_array[index] - current_average));
    }

    // Return calculated average
    return current_average;
}


/*
 * Random Range Function Definition
 *
 * In order to get a good assortment of floating point values, we need
 * to specify a range and will use that to calculate a value.
 *
 * Output:
 * Random double value within the range provided. Will return DBL_MAX
 * if min config is less than max config.
 */
double rand_double_range(double min, double max) {

    // Ensure min is less than max
    if(min > max){
        return DBL_MAX;
    }

    double random = ((double) rand()) / RAND_MAX;
    double bottom = (max - min) * random;

    return(min + bottom);
}
