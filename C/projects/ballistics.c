/**
  */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/** 180 degree angle. */
#define ANGLE 180
/** Gravity constant. */
#define GRAVITY 9.81
/** Length of columns in the middle. */
#define MIDDLE_COLUMN_LENGTH 12
/** Length of columns on the front and back. */
#define END_COLUMN_LENGTH 11
/**
  * Calculates the time it takes for a thrown object to hit the ground with a given 
  * angle and initial velocity.
  * @param angle angle of object being thrown
  * @param v0 initial velocity of the object
  * @return time double value of the time it takes for thrown object to hit the ground
  */
double flightTime( int angle, double v0 )
{
    double time;
    double degrees;
    degrees = sin(angle * M_PI / ANGLE);
    time = (2 * v0 * degrees) / GRAVITY;
    return time;
}

/**
  * Calculates the distance of the thrown object given the angle, velocity, and time, 
  * and prints out the data formatted by column.
  * @param angle angle of object being thrown
  * @param v0 initital velocity of object
  * @param t time it takes for the object to hit the ground
  */
void tableRow( int angle, double v0, double t )
{
    double distance;
    distance = v0 * t * cos(angle * M_PI / ANGLE);
    printf("%10d%c%c%c%10.3lf%c%c%c%10.3lf%c%c%c%10.3lf\n", angle, ' ', '|', ' ', v0, ' ', '|', ' ', t, ' ', '|', ' ', distance);
}
/**
  * Program starting point. Draws the title boxes and a line separating it from the data,
  * and calls uses a for loop to increment angle and calculate based on each angle.
  * @return 0 to terminate function call.
  */
int main()
{
    double v0;
    printf("V0: ");
    scanf("%lf", &v0);
    
    printf("\n%10s%c%c%c%10s%c%c%c%10s%c%c%c%10s\n", "angle", ' ', '|', 
        ' ', "v0", ' ', '|', ' ', "time", ' ', '|', ' ', "distance");
    for (int i = END_COLUMN_LENGTH; i > 0; i--) {
        printf("-");
    }
    printf("+");
    for (int i = MIDDLE_COLUMN_LENGTH; i > 0; i--) {
        printf("-");
    }
    printf("+");
    for (int i = MIDDLE_COLUMN_LENGTH; i > 0; i--) {
        printf("-");
    }
    printf("+");
    for (int i = END_COLUMN_LENGTH; i > 0; i--) {
        printf("-");
    }
    printf("\n");
    for (int i = 0; i <= 90; i = i + 5) {
        double time = flightTime(i, v0);
        tableRow(i, v0, time);
    }

    return 0;
}
