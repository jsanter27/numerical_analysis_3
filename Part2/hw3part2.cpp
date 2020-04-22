// Justin Santer
// AMS 326 Homework 3 Part 2
// Professor Yuefan Deng
// April 24, 2020

#include <random>
#include <math.h>
#include <time.h>

double DIAMETER = .75;
double DISTANCE = 1.0;
int TOSSES = 1984444444;
int LINES = 10;

// Random double between A and B
double rand_double(double a, double b){
    double random = ((double) rand()) / (double) RAND_MAX;
    double difference = b - a;
    return random * difference + a;
}

// Rounds A to nearest B
double round_to_nearest(double a, double b){
    return round(a / b) * b;
}

// Find the interval range surrounding X
void set_interval(double *upper, double *lower, double x, double width){
    double bound = round_to_nearest(x, width);
    if (bound > x){
        *upper = bound;
        *lower = *upper - width;
    }
    else{
        *lower = bound;
        *upper = *lower + width;
    }
}

// Uses Monte Carlo method
double buffon_needle(int tosses, double diameter, double distance, int lines){
    int counter = 0;
    double radius = diameter / 2.0;
    double x, bound, upper, lower;
    for (int i = 0; i < tosses; i++){
        x = rand_double(distance, lines*distance);

        set_interval(&upper, &lower, x, distance);

        if (upper - x <= radius || x - lower <= radius){
            counter++;
        }
        //printf("X: %f, LOWER: %f, UPPER: %f, COUNTER: %d\n", x, lower, upper, counter);
    }
    return (double) counter /  (double) tosses;
}

int main(){

    srand(time(0));

    printf("\nGenerating %d tosses...\n", TOSSES);
    double start_time = time(0);
    double prob = buffon_needle(TOSSES, DIAMETER, DISTANCE, LINES);
    double end_time = time(0);
    printf("The probability of touching a line is %f percent\n", prob*100);
    
    double mins_taken = (end_time-start_time)/60.0;
    printf("Time Taken: %.2f minutes\n\n", mins_taken);

    return 0;
}