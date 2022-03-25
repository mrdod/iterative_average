#include "stdlib.h"
#include "time.h"
#include "stdio.h"

/* Defines */
#define RAND_RANGE_MIN (-5000)
#define RAND_RANGE_MAX (5000)
#define INPUT_ARRAY_SIZE (10000)

/* Function Prototypes */
double iterative_average(double *input_value_array, long long unsigned int input_value_array_size);
double rand_range(double min, double max);

int main() {
    double array_of_doubles[INPUT_ARRAY_SIZE];
    double averaged_value;

    // Set seed for random function to be based on current time
    srand(time(NULL));

    // Create the array of random values
    for (long long unsigned int index = 0; index < INPUT_ARRAY_SIZE; index++) {
        double value = rand_range(RAND_RANGE_MIN, RAND_RANGE_MAX);
        array_of_doubles[index] = value;
    }

    // Run the iterative iterative_average function
    averaged_value = iterative_average(array_of_doubles, INPUT_ARRAY_SIZE);

    // Print result
    printf("%f", averaged_value);
}


/*
 * Iterative Average Function Definition
 *
 * Find the average of an array of double floating point inputs using an iterative approach
 *
 * Returns the calculated iterative average
 */
double iterative_average(double *input_value_array, long long unsigned int input_value_array_size) {
    double current_average = 0.0;

    for (long long unsigned int index = 0; index < input_value_array_size; index++) {
        // next_average = current_average + ((1 / (index           + 1)) * (input_value              - current_average))
        current_average = current_average + ((1 / (((double)index) + 1)) * (input_value_array[index] - current_average));
    }

    return current_average;
}


/*
 * Random Range Function Definition
 *
 * Outputs a random double value within the range provided
 */
double rand_range(double min, double max) {
    double random = ((double) rand()) / RAND_MAX;
    double range = (max - min) * random;
    double number = min + range;

    return number;
}
