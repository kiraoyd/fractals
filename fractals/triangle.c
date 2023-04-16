/* To run: cc  triangle.c   -lm  -lX11 */

#include  "FPToolkit.c"


int main(){

    //Declare variables here
    //USE DOUBLES!!!!! NOT INTS, except for array accessors
    int swidth, sheight ;
    double x1, y1, x2, y2, x3, y3;

    swidth = 400 ;  sheight = 600 ;
    G_init_graphics (swidth,sheight) ;  // interactive graphics

    // clear the screen in a given color
    G_rgb (0.3, 0.3, 0.3) ; // dark gray
    G_clear () ;

    /* CODE HERE */

    //TODO start top of triangle at (200, 300) for now
    x1 = 200;
    y1 = 300;

    //Lines must  all be the same length
    double length;
    length = 100;  //outer triangle

    G_rgb (1.0, 0.0, 0.0) ; // red
    int i = 0;
    while(i < length){
       G_point(x1, y1);

    }

   // draw a line
   G_rgb (0.0, 1.0, 0.0) ; // green
   G_line (0,0, swidth-1, sheight-1) ;


    /* BEGIN SETDOWN */
    int key ;
    key =  G_wait_key() ; // pause so user can see results

    //   G_save_image_to_file("demo.xwd") ;
    G_save_to_bmp_file("demo.bmp") ;
}