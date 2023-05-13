/* To run: cc  ifs.c   -lm  -lX11 */

#include  "FPToolkit.c"
#include <stdio.h>
#include <math.h>
#include <string.h>

#define PI M_PI

//globals
double scale_x = 0.5;
double scale_y = 0.5;
double translate = 0.5;
double swidth = 400;
double sheight = 200;

void draw_line(){
//random number generator
    double n;
    double x, y;

    //start (x,y) at 0,0
    x = 0;
    y = 0;

    G_rgb(1,1,1);
    for (int i = 0; i<1000000; i++){
        //get a random number to choose between two rules
        n = drand48();
        //printf("%f ",n);

        if(n < 0.5){
            //Rule 1
            x = x * scale_x;
            y = y * scale_y;
            G_rgb(1,0,0);
            G_point(x*swidth, y*sheight);
        } else {
            //Rule 2
            G_rgb(0,1,0);
            x = x* scale_x;
            x = x+ translate;
            y = y* scale_y;
            y = y+ scale_y;
            G_point(x*swidth, y*sheight);

        }

    }
}

void fill_square(){
//random number generator
    double n;
    double x, y;

    //start (x,y) at 0,0
    x = 0;
    y = 0;

    G_rgb(1,1,1);
    for (int i = 0; i<1000000; i++){
        n = drand48();
        if(n < 0.25){
            //Rule 1: scale only
            //All other rules are in relation to this one (where we are after scaling)
            x = x*0.5;
            y = y*0.5;
            G_rgb(1,0,0);
            G_point(x*swidth, y*sheight);
        }
        else if(n < 0.5 && n >= 0.25){
            //Rule : scale, then translate y
            x = x*0.5;
            y = y*0.5;
            y = y + 0.5;
            G_rgb(1,0,0);
            G_point(x*swidth, y*sheight);

        }
        else if(n > 0.5 && n <= 0.75){
            //Rule 3: scale, then translate both x and y
            x = x*0.5;
            y = y*0.5;
            x = x + 0.5;
            y = y + 0.5;
            G_rgb(1,0,0);
            G_point(x*swidth, y*sheight);
        }
        else{
            //Rule 4: scacle, then translate just x
            x = x*0.5;
            y = y*0.5;
            x = x + 0.5;
            G_rgb(1,0,0);
            G_point(x*swidth, y*sheight);
        }
    }
}

void carpet(){
//random number generator
    double n;
    double x, y;

    //start (x,y) at 0,0
    x = 0;
    y = 0;

    double k = (1/9);
    printf("%f ", k);

    G_rgb(1,1,1);
    for (int i = 0; i<1000000; i++){
        n = drand48();
        if(n > 8* (1.0/9.0)){
            //Rule 1: scale only, by 0.3
            //All other rules are in relation to this one (where we are after scaling)
            x = x * (1.0/3.0);
            y = y* (1.0/3.0);
            G_rgb(1,1,0);
            G_point(x*swidth, y*sheight);
        }
        else if(n > 7* (1.0/9.0)){
            //Rule 2: scale, then translate x only
            x = x* (1.0/3.0);
            y = y* (1.0/3.0);
            x = x + (1.0/3.0);
            G_rgb(1,0.75,0.25);
            G_point(x*swidth, y*sheight);

        }
        else if(n > 6* (1.0/9.0)){
            //Rule 3: scale, then translate both x only, by 2/3
            x = x* (1.0/3.0);
            y = y* (1.0/3.0);
            x = x + (2.0/3.0);

            G_rgb(1,0,.75);
            G_point(x*swidth, y*sheight);
        }
        else if (n > 5* (1.0/9.0)){
            //Rule 4: scacle, then translate just y
            x = x* (1.0/3.0);
            y = y* (1.0/3.0);
            y = y + (1.0/3.0);
            G_rgb(0,0.8,1);
            G_point(x*swidth, y*sheight);
        }
        else if (n > 4* (1.0/9.0)){
            //Rule 5: scacle, then translate x and
            /*
            x = x* (1.0/3.0);
            y = y* (1.0/3.0);
            x = x + (1.0/3.0);
            y = y + (1.0/3.0);
            G_rgb(1,0,0);
            G_point(x*swidth, y*sheight);
            */
            double nothing = 0;
        }
        else if (n > 3* (1.0/9.0)){
            //Rule 6: scacle, then translate x and y
            x = x* (1.0/3.0);
            y = y* (1.0/3.0);
            x = x + (2.0/3.0);
            y = y + (1.0/3.0);
            G_rgb(0,1,0);
            G_point(x*swidth, y*sheight);
        }
        else if (n > 2* (1.0/9.0)){
            //Rule 7: scale, then translate just y
            x = x* (1.0/3.0);
            y = y* (1.0/3.0);
            y = y + (2.0/3.0);
            G_rgb(0.6,0.6,0);
            G_point(x*swidth, y*sheight);
        }
        else if (n > 1* (1.0/9.0)){
            //Rule 8: scacle, then translate x and y
            x = x* (1.0/3.0);
            y = y* (1.0/3.0);
            x = x + (1.0/3.0);
            y = y + (2.0/3.0);
            G_rgb(1,0,0);
            G_point(x*swidth, y*sheight);
        }
        else{
            //Rule 9: scacle, then translate x and y
            x = x* (1.0/3.0);
            y = y* (1.0/3.0);
            x = x + (2.0/3.0);
            y = y + (2.0/3.0);
            G_rgb(0,0,1);
            G_point(x*swidth, y*sheight);
        }
    }
}

void initials(){
//random number generator
    double n;
    double x, y;

    double mama_w = 36.0;
    double mama_h = 16.0;

    //start (x,y) at 0,0
    x = 0.0;
    y = 0.0;

    int red = 0;
    int orange = 0;
    int yellow = 0;
    int green = 0;
    int cyan = 0;
    int spring = 0;
    int dodger = 0;
    int blue = 0;
    int violet = 0;
    int magenta = 0;
    int purple = 0;

    G_rgb(1,1,1);
    for (int i = 0; i<1000000; i++){
        n = drand48();
        if(n > 10.0* (1.0/11.0)){
            //Rule 1: scale, rotate by adding 90 degrees to current angle, translate over and up by 1/10 the height/width
            //Left vertical of K
            double scale_factor_x = 36.0/36.0; //full width ratio
            double scale_factor_y = 2.0/16.0;

            double theta_degrees = 90.0;
            double theta_radians = theta_degrees * (PI/180.0);

            //SCALE
            x = x* scale_factor_x;
            y = y* scale_factor_y;

            //ROTATE
            double temp = x*cos(theta_radians) - y*sin(theta_radians);
            y = x* sin(theta_radians) + y*cos(theta_radians);
            x = temp;

            //TRANSLATE
            double x_change = 2.0/36.0;
            double y_change = 0.0/16.0;
            x = x + x_change;
            y = y + y_change;
            red++;
            G_rgb(1,0,0); //RED
            G_point(x* swidth, y*sheight);
        }
        else if(n > 9.0* (1.0/11.0)){
            //Rule 2: scale, rotate by 45 degrees, translate by 15% of screen
            //Upper rotated bar on K
            double scale_factor_x = 9.0/36.0;
            double scale_factor_y = 2.0/16.0;

            double theta_degrees = 45.0;
            double theta_radians = theta_degrees * (PI/180.0);

            //SCALE
            x = x* scale_factor_x;
            y = y* scale_factor_y;

            //ROTATE
            double temp = x*cos(theta_radians) - y*sin(theta_radians);
            y = x* sin(theta_radians) + y*cos(theta_radians);
            x = temp;

            //TRANSLATE
            double x_change = 4.0/36.0;
            double y_change = 8.0/16.0;
            x = x + x_change;
            y = y + y_change;

            int g = 128/255;
            G_rgb(1,g,0); //Orange
            orange++;
            G_point(x*swidth, y*sheight);
        }

        else if (n > 8.0* (1.0/11.0)){
            //Rule 3: scale, rotate by subtracting 45 degrees to current angle, translate 10% over, 40% up
            //Bottom tilted bar on K
            double scale_factor_x = 9.0/36.0;
            double scale_factor_y = 2.0/16.0;

            double theta_degrees = -45.0;
            double theta_radians = theta_degrees * (PI/180.0);

            //SCALE
            x = x* scale_factor_x;
            y = y* scale_factor_y;

            //ROTATE
            double temp = x*cos(theta_radians) - y*sin(theta_radians);
            y = x* sin(theta_radians) + y*cos(theta_radians);
            x = temp;

            //TRANSLATE
            double x_change = 2.0/36.0;
            double y_change = 6.0/16.0;

            x = x + x_change;
            y = y + y_change;

            G_rgb(1,1,0); //Yellow
            yellow++;
            G_point(x *swidth, y*sheight);
        }
        else if (n > 7.0* (1.0/11.0)){
            //Rule 4: dot on I
            double scale_factor_x = 2.0/36.0;
            double scale_factor_y = 2.0/16.0;

            //SCALE
            x = x* scale_factor_x;
            y = y* scale_factor_y;

            //TRANSLATE
            double x_change = 12.0/36.0;
            double y_change = 12.0/16.0;

            x = x + x_change;
            y = y + y_change;

            G_rgb(128/255,1,0); //Green
            green++;
            G_point(x *swidth, y*sheight);


        }
        else if(n > 6.0* (1.0/11.0)){
            //Rule 5:
            //Bar on I
            double scale_factor_x = 10.0/36.0;
            double scale_factor_y = 2.0/16.0;

            double theta_degrees = 90.0;
            double theta_radians = theta_degrees * (PI/180.0);

            //SCALE
            x = x* scale_factor_x;
            y = y* scale_factor_y;

            //ROTATE
            double temp = x*cos(theta_radians) - y*sin(theta_radians);
            y = x* sin(theta_radians) + y*cos(theta_radians);
            x = temp;

            //TRANSLATE
            double x_change = 14.0/36.0;
            double y_change = 0.0/16.0;
            x = x + x_change;
            y = y + y_change;

            G_rgb(0,1,1); //CYAN
            cyan++;
            G_point(x*swidth, y*sheight);
        }
        else if(n > 5.0* (1.0/11.0)){
            //Rule 6:
            //UBar on R
            double scale_factor_x = 10.0/36.0;
            double scale_factor_y = 2.0/16.0;

            double theta_degrees = 90.0;
            double theta_radians = theta_degrees * (PI/180.0);

            //SCALE
            x = x* scale_factor_x;
            y = y* scale_factor_y;

            //ROTATE
            double temp = x*cos(theta_radians) - y*sin(theta_radians);
            y = x* sin(theta_radians) + y*cos(theta_radians);
            x = temp;

            //TRANSLATE
            double x_change = 18.0/36.0;
            double y_change = 0.0/16.0;
            x = x + x_change;
            y = y + y_change;

            G_rgb(0,1,128/255); //Spring Green
            spring++;
            G_point(x*swidth, y*sheight);
        }
        else if(n > 4.0* (1.0/11.0)){
            //Rule 7:
            //Upper bar on r
            double scale_factor_x = 3.0/36.0;
            double scale_factor_y = 2.0/16.0;


            //SCALE
            x = x* scale_factor_x;
            y = y* scale_factor_y;


            //TRANSLATE
            double x_change = 18.0/36.0;
            double y_change = 8.0/16.0;
            x = x + x_change;
            y = y + y_change;

            G_rgb(0,0,0); //dodger
            dodger++;
            G_point(x*swidth, y*sheight);
        }
        else if(n > 3.0* (1.0/11.0)){
            //Rule 8:
            //Left bar on a
            double scale_factor_x = 8.0/36.0;
            double scale_factor_y = 2.0/16.0;

            double theta_degrees = 90.0;
            double theta_radians = theta_degrees * (PI/180.0);

            //SCALE
            x = x* scale_factor_x;
            y = y* scale_factor_y;

            //ROTATE
            double temp = x*cos(theta_radians) - y*sin(theta_radians);
            y = x* sin(theta_radians) + y*cos(theta_radians);
            x = temp;

            //TRANSLATE
            double x_change = 25.0/36.0;
            double y_change = 2.0/16.0;
            x = x + x_change;
            y = y + y_change;

            G_rgb(0,0,1); //Blue
            blue++;
            G_point(x*swidth, y*sheight);
        }
        else if(n > 2.0* (1.0/11.0)){
            //Rule 9:
            //Upper bar on a
            double scale_factor_x = 5.0/36.0;
            double scale_factor_y = 2.0/16.0;

            //SCALE
            x = x* scale_factor_x;
            y = y* scale_factor_y;

            //TRANSLATE
            double x_change = 25.0/36.0;
            double y_change = 8.0/16.0;
            x = x + x_change;
            y = y + y_change;

            G_rgb(1,10,1); //Violet
            violet++;
            G_point(x*swidth, y*sheight);
        }
        else if(n > 1.0* (1.0/11.0)){
            //Rule 10:
            //Lower bar on a
            double scale_factor_x = 5.0/36.0;
            double scale_factor_y = 2.0/16.0;

            //SCALE
            x = x* scale_factor_x;
            y = y* scale_factor_y;

            //TRANSLATE
            double x_change = 25.0/36.0;
            double y_change = 2.0/16.0;
            x = x + x_change;
            y = y + y_change;

            G_rgb(1,0,128/255); //magenta
            magenta++;
            G_point(x*swidth, y*sheight);
        }
        else {
            //Rule 11:
            //Right bar on a
            double scale_factor_x = 9.0/36.0;
            double scale_factor_y = 2.0/16.0;

            double theta_degrees = 90.0;
            double theta_radians = theta_degrees * (PI/180.0);

            //SCALE
            x = x* scale_factor_x;
            y = y* scale_factor_y;

            //ROTATE
            double temp = x*cos(theta_radians) - y*sin(theta_radians);
            y = x* sin(theta_radians) + y*cos(theta_radians);
            x = temp;

            //TRANSLATE
            double x_change = 34.0/36.0;
            double y_change = 1.0/16.0;
            x = x + x_change;
            y = y + y_change;

            G_rgb(128/255,0,1); //purple
            purple++;
            G_point(x*swidth, y*sheight);
        }

}

    printf("Rule 1: %d, Rule 2: %d, Rule 3: %d, Rule 4: %d, Rule 5: %d, Rule 6: %d, Rule 7: %d, Rule 8: %d, Rule 9: %d, Rule 10: %d, Rule 11: %d", red, orange, yellow, green, cyan, spring, dodger, blue, violet, magenta, purple);

}

int main(){

    G_init_graphics (swidth,sheight) ;  // interactive graphics

    // clear the screen in a given color
    G_rgb (0.3, 0.3, 0.3) ; // dark gray
    G_clear () ;

    //draw_line();
    //fill_square();
    //carpet();
    initials();


    // BEGIN SETDOWN
     int key ;
     key =  G_wait_key() ; // pause so user can see results

     //   G_save_image_to_file("demo.xwd") ;
     G_save_to_bmp_file("trees.bmp") ;
    return 0;
}