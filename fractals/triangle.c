Unable to connect to chat

1 of 7,805
messed up triangle
Inbox

Kira Klingenberg <kirak@pdx.edu>
Attachments
11:15 PM (1 minute ago)
to me


 One attachment
  •  Scanned by Gmail
/* To run: cc  triangle.c   -lm  -lX11 */

#include  "FPToolkit.c"
#include <stdio.h>
#include <math.h>

#define PI 3.14159265


void s_triangle(double x0, double y0, double x1, double y1, double x2, double y2, double length, double depth, double limit){

    //base case
    if(depth == limit){
       return;
    }
    //now we have all three points, draw lines between them
    G_rgb(0,0,0); //black
    G_line(x0, y0, x1, y1); //between P0 and P1
    G_line(x0, y0, x2, y2); //between P0 and P2
    G_line(x1,y1, x2, y2); //between P1 and P2

   //calculate the midpoints
   double split = 0.5;
   //between P0 and P1: P1 for first child, P0 for second child
   double p0_p1_midx = x0 + (split*(x1-x0));
   double p0_p1_midy = y0 + (split *(y1 - y0));
   //between P1 and P2: P2 for second child, P1 for third child
   double p1_p2_midx = x1 + (split*(x2-x1));
   double p1_p2_midy = y1 + (split *(y2 - y1));
   //between P0 and P2: P2 for first child, P0 for third child
   double p0_p2_midx = x0 + (split*(x2-x0));
   double p0_p2_midy = y0 + (split *(y2 - y0));

   double new_len = length /2;
   depth += 1;

   //call first child: p0 (x0, y0), P1 (p0_p1_midx, p0_p1_midy), P2 (p0_p2_midx, p0_p2_midy)
   s_triangle(x0, y0,p0_p1_midx, p0_p1_midy, p0_p2_midx, p0_p2_midy, new_len, depth, limit);
   //call second child: P0 (p0_p1_midx, p0_p1_midy), P1 (x1, y1), P2 (p1_p2_midx, p1_p2_midy)
   s_triangle(p0_p1_midx, p0_p1_midy,x1, y1, p1_p2_midx, p1_p2_midy, new_len, depth, limit);
   //call third child: P0 (p0_p2_midx, p0_p2_midy), P1 (p1_p2_midx,p1_p2_midy), P2 (x2, y2);
   s_traingle(p0_p2_midx, p0_p2_midy, p1_p2_midx,p1_p2_midy, x2, y2, new_len, depth, limit ) ;

}


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

    //now we have all three points, call the function
    double depth = 0;
    double limit = 5;
    s_triangle(x0, y0, x1, y1, x2, y2, length, depth, limit);


    /* BEGIN SETDOWN */
    int key ;
    key =  G_wait_key() ; // pause so user can see results

    //   G_save_image_to_file("demo.xwd") ;
    G_save_to_bmp_file("demo.bmp") ;
}