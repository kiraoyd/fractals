/* To run: cc  turtle.c   -lm  -lX11 */

#include  "FPToolkit.c"
//#include <stdio.h>
#include <math.h>



struct Point {
    double x, y;
};



struct Point find_new_position (struct Point position, double radians_angle,  int step){
    struct Point new_position;
    //move from position, in the direction of angle, by step number of pixels
    new_position.x = step * cos(radians_angle) + position.x;
    new_position.y = step * sin(radians_angle) + position.y;
    return new_position;
}


void turtle (char instruction_string[]){
    int index = 0;
    double angle = 0; //angle to plot next point off
    double angle_change = 30*(M_PI/180); //amount angle changes each + or -
    int step = 1; //length of line between start point and new point
    struct Point move_to = {0,0}; //temp to hold new position of turtle
    struct Point position;
    position.x = 100;
    position.y = 10;

    //enum direction move = "right";
    while(index < strlen(instruction_string)){
        //set start point

        //traverse steps to process each one
        if (instruction_string[index] == 'f' || instruction_string[index] >= 'A' && instruction_string[index] <= 'Z'){

            move_to = find_new_position(position, angle, step);
            //draw line between start point and new point
            G_rgb(1,1,1); //white
            G_line(position.x, position.y, move_to.x, move_to.y);
            //reset start point to new point
            position.x = move_to.x;
            position.y = move_to.y;
        }
        else if (instruction_string[index] == '+'){
            //move counter clockwise
            angle += angle_change;
            angle = fmod(angle, (2*M_PI));
        }
        else if (instruction_string[index] == '-'){
            //move clockwise
            angle -= angle_change;
            angle = fmod(angle, (2*M_PI));
        }
        index++;
    }
}

int main(){
    int swidth, sheight ;

    swidth = 800 ;  sheight = 800 ;
    G_init_graphics (swidth,sheight) ;  // interactive graphics

    // clear the screen in a given color
    G_rgb (0.3, 0.3, 0.3) ; // dark gray
    G_clear () ;

    /* CODE HERE */

    char array[] = {'f', '+', 'f', '+', 'f', 'f', '-', 'f'};

    char davids_array [1000000];
    scanf("%s", davids_array);
    printf("string length = %ld\n", strlen(davids_array));
    //TODO test Davids
    turtle(davids_array);

    /* BEGIN SETDOWN */
    int key ;
    key =  G_wait_key() ; // pause so user can see results

    //   G_save_image_to_file("demo.xwd") ;
    G_save_to_bmp_file("trees.bmp") ;

}