/* To run: cc  ifs.c   -lm  -lX11 */

#include  "FPToolkit.c"
#include <stdio.h>
#include <math.h>
#include <string.h>

//globals
double scale_x = 0.5;
double scale_y = 0.5;
double translate = 0.5;
double swidth = 400;
double sheight = 400;

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
            //Rule 7: scacle, then translate just y
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

int main(){

    G_init_graphics (swidth,sheight) ;  // interactive graphics

    // clear the screen in a given color
    G_rgb (0.3, 0.3, 0.3) ; // dark gray
    G_clear () ;

    //draw_line();
    //fill_square();
    carpet();


    // BEGIN SETDOWN
     int key ;
     key =  G_wait_key() ; // pause so user can see results

     //   G_save_image_to_file("demo.xwd") ;
     G_save_to_bmp_file("trees.bmp") ;
    return 0;
}