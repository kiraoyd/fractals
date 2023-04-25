/* To run: cc  turtle.c   -lm  -lX11 */

#include  "FPToolkit.c"
//#include <stdio.h>
#include <math.h>

struct Point {
    int x, y;
}

struct Point step_f (struct Point position, double radians_angle,  int step){
    struct Point new_position;
    //move from position, in the direction of angle, by step number of pixels

    return new_position;

}

double step_plus (double radians_angle, double angle_change){
    double new_angle;
    //change the radians_angle by the angle_change, counter clockwise

    return new_angle;
}

double step_minus (double radians_angle, double angle_change){
    double new_angle;
    //change the radians_angle by the angle_change, clockwise

    return new_angle;
}

void turtle (char instruction_string[]){
    int length = strlen(instruction_string);
    int index = 0;
    double angle; //angle to plot next point off
    double angle_change; //amount angle changes each + or -
    int step; //length of line between start point and new point

    //enum direction move = "right";
    while(index < length){
        //set start point
        //traverse steps to process each one
        if (instruction_string[index] == 'f'){
            //call step_f
            //draw line between start point and new point
            //reset start point to new point
        }
        else if (instruction_string[index] == '+'){
            //call step_plus
        }
        else if (instruction_string[index] == '-'){
            //call step_minus
        }
        println("step")

        index++;
    }



}