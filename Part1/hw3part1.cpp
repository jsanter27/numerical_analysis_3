// Justin Santer
// AMS 326 Homework 3 Part 1
// Professor Yuefan Deng
// April 24, 2020

#include <math.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <time.h>

using namespace std;

double RIVER_WIDTH = 7777.0;
double INITIAL_SPEED = 14.0;
double BOAT_SPEEDS[3] = {7.0, 14.0, 21.0};
double STEP_SIZE = 1.0;
int SAMPLE_SIZE = (RIVER_WIDTH+1)/STEP_SIZE;
char *PATH = "./data.csv";

// FUNCTION FOR WATER FLOW
double flow_function(double x){
    double a = RIVER_WIDTH;
    double v0 = INITIAL_SPEED;
    return 4 * v0 * ( ( x / a ) - ( pow(x, 2) / pow(a , 2) ) );
}

// HELPER FUNCTION FOR EULER METHOD
double func(double x, double y, double vB){
    double denom = vB * ( x / ( sqrt( pow(x, 2) + pow(y, 2) ) ) );
    return ( y / x ) - ( flow_function(x) / denom );
}

// BACKWARD EULER METHOD
void backward_euler(double *x_vals, double *y_vals, int size, double h, double speed){
    double x1, y1;
    for(int i = size-2; i >= 0; i--){
        x1 = x_vals[i+1];
        y1 = y_vals[i+1];
        x_vals[i] = x1 - h;
        y_vals[i] = y1 - h * func(x1, y1, speed);
    }
}

// OUTPUT DATA TO FILE
void data_to_csv(char filepath[], double *x_list[], double *y_list[], int size){
    ofstream CSV;
    CSV.open(filepath);
    CSV << "Speed: " << BOAT_SPEEDS[0] << ", , ,Speed: " << BOAT_SPEEDS[1] << 
           ", , ,Speed: " << BOAT_SPEEDS[2] << endl;

    for (int i = 0; i < size; i++){
        CSV << x_list[0][i] << "," << y_list[0][i] << ", ," <<
               x_list[1][i] << "," << y_list[1][i] << ", ," <<
               x_list[2][i] << "," << y_list[2][i] << endl;
    }

    CSV.close();
}

int main(){
    // DECLARE ARRAYS FOR DATAPOINTS
    double *x_vals1 = new double[SAMPLE_SIZE];
    double *y_vals1 = new double[SAMPLE_SIZE];
    double *x_vals2 = new double[SAMPLE_SIZE];
    double *y_vals2 = new double[SAMPLE_SIZE];
    double *x_vals3 = new double[SAMPLE_SIZE];
    double *y_vals3 = new double[SAMPLE_SIZE];

    // PUT ARRAYS INTO GREATER LIST
    double *x_list[3] = {x_vals1, x_vals2, x_vals3};
    double *y_list[3] = {y_vals1, y_vals2, y_vals3};

    // INITIALIZE DATAPOINTS
    x_vals1[SAMPLE_SIZE-1] = RIVER_WIDTH;
    y_vals1[SAMPLE_SIZE-1] = 0.0;
    x_vals2[SAMPLE_SIZE-1] = RIVER_WIDTH;
    y_vals2[SAMPLE_SIZE-1] = 0.0;
    x_vals3[SAMPLE_SIZE-1] = RIVER_WIDTH;
    y_vals3[SAMPLE_SIZE-1] = 0.0;

    // PERFORM BACKWARD EULER FOR THE THREE SPEEDS
    printf("\n");
    for (int i = 0; i < 3; i++){
        printf("\nPeforming Backward Euler Method (Speed = %.1f)...\n", BOAT_SPEEDS[i]);
        backward_euler(x_list[i], y_list[i], SAMPLE_SIZE, STEP_SIZE, BOAT_SPEEDS[i]);
    }

    // OUTPUT DATA TO CSV FILE
    printf("\nOutputting Results to CSV file...\n");
    data_to_csv(PATH, x_list, y_list, SAMPLE_SIZE);
    printf("\nDone!\n");

    // DELETE ARRAYS FROM MEMORY
    delete x_vals1;
    delete y_vals1;
    delete x_vals2;
    delete y_vals2;
    delete x_vals3;
    delete y_vals3;
    return 0;
}