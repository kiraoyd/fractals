/* To run: cc  triangle.c   -lm  -lX11 */

#include  "FPToolkit.c"
#include <stdio.h>
#include <math.h>

#define PI 3.14159265

int main(){

    //Declare variables here
    //USE DOUBLES!!!!! NOT INTS, except for array accessors
    int swidth, sheight ;
    double x0, y0, x1, y1, x2, y2, length, adj, opp;

    swidth = 400 ;  sheight = 600 ;
    G_init_graphics (swidth,sheight) ;  // interactive graphics

    // clear the screen in a given color
    G_rgb (0.3, 0.3, 0.3) ; // dark gray
    G_clear () ;

    /* CODE HERE */

    //Set known values
    //P0 unknown
    //P1 (100, 200)
    //P2 (300, 200)
    length = 200; //same as hyp
    adj = length /2; //add to x1 to get missing points x-val
    x1 = 100;
    y1 = 100;
    x2 = 300;
    y2 = 100;


    //angle of each corner will always be 60 in equilateral triangle
    double angle = 60;
    double radians = angle * (PI/180);
    opp = length * sin(radians); //opp is the +y to unknown P1
    x0 = x1 + adj;
    y0 = y1 + opp;

    //now we have all three points, draw lines between them
    G_rgb(0,0,0); //black
    G_line(x0, y0, x1, y1);
    G_line(x0, y0, x2, y2);
    G_line(x1,y1, x2, y2);


    /* BEGIN SETDOWN */
    int key ;
    key =  G_wait_key() ; // pause so user can see results

    //   G_save_image_to_file("demo.xwd") ;
    G_save_to_bmp_file("demo.bmp") ;
}