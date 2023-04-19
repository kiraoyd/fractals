/* To run: cc  p_tree.c   -lm  -lX11 */



#include  "FPToolkit.c"
//#include <stdio.h>
#include <math.h>

#define PI 3.14159265

struct Point {
    double x, y;
};

//assumes triangle P0, P1, P5 where P5 is the unknown 90 degree angle point, P0 is lower left, P1 is lower right
//distance is between P0 and P1, percent is how far from P0, pm is
struct Point calculate_point(struct Point p0, struct Point p1, double distance, double percent){
    //find change in x and y between P0 and P1
    double change_x = p1.x - p0.x;
    double change_y = p1.y - p0.y;

    //find the point, P2 perpendicular to P0 - P1, heading up off P1
    double x2 = p1.x - change_y;
    double y2 = p1.y + change_x;
    struct Point p2 = {x2, y2};


    //find the point, pm that lies between P0 and P1 exactly percent ways from P0, p4 and p5 will be along this line
    double xm = p0.x + (percent * change_x);
    double ym = p0.y + (percent * change_y);
    struct Point pm = {xm, ym};

    //find the point, P4, perpendicular to P2, heading off to the left stopping at distance - percent
    //use same technique as finding p2

    //find change in x and y between P0 and Pm
    double change_x_p0_pm = pm.x - p0.x;
    double change_y_p0_pm = pm.y - p0.y;
    //find the point, P4, perpendicular to P0 - Pm, heading up off Pm
    double x4 = pm.x - change_y_p0_pm;
    double y4 = pm.y + change_x_p0_pm;
    struct Point p4 = {x4, y4};

    //find distance from pm to p5, call it l
    //first find the distance between P1 and Pm
    double dis_p1_pm = ((pm.x - p1.x) * (pm.x - p1.x)) + ((pm.y - p1.y) * (pm.y - p1.y));
    //then find the distance between p0 and pm
    double dis_p0_pm = distance - dis_p1_pm;

    double l = sqrt(dis_p1_pm * dis_p0_pm);

    double scale_factor = l / distance;

    double x5 = scale_factor * pm.x;
    double y5 = scale_factor + pm.y;
    struct Point p5 = {x5, y5};

    return p5;

}

int main(){

    //Declare variables here
    //USE DOUBLES!!!!! NOT INTS, except for array accessors
    int swidth, sheight ;
    double x0, y0, x1, y1, x2, y2, length, adj, opp;

    swidth = 400 ;  sheight = 400 ;
    G_init_graphics (swidth,sheight) ;  // interactive graphics

    // clear the screen in a given color
    G_rgb (0.3, 0.3, 0.3) ; // dark gray
    G_clear () ;

    /* CODE HERE */

    //Create initial p0 and p1 points for the first triangle (also top of trunk square)
    struct Point p0 = {100, 100};
    struct Point p1 = {300, 100};
    double distance = ((p1.x - p0.x) * (p1.x - p0.x)) + ((p1.y - p0.y) * (p1.y - p0.y));
    //set how far from p0 we want the third point to lie
    double percent = 0.3;
    struct Point p3 = calculate_point(p0, p1, distance, percent);

    //TODO: test, draw the triangle
    /*
    G_rgb(1,0,0); //red
    G_line(p0.x, p0.y, p3.x, p3.y);
    */
    G_rgb(0,1,0); //green
    G_line(p3.x, p3.y, p1.x, p1.y);

    G_rgb(0,0,1); //blue
    G_line(p1.x, p1.y, p0.x, p0.y);



    /* BEGIN SETDOWN */
    int key ;
    key =  G_wait_key() ; // pause so user can see results

    //   G_save_image_to_file("demo.xwd") ;
    G_save_to_bmp_file("demo.bmp") ;
}


