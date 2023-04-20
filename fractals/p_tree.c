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

    //find the point, pm that lies between P0 and P1 exactly percent ways from P0, p4 and p5 will be along this line
    double xm = p0.x + (percent * change_x);
    double ym = p0.y + (percent * change_y);
    struct Point pm = {xm, ym};

    //TODO: test we found Pm correctly, we did!
    G_rgb(1,1,1); //white
    G_line(pm.x, pm.y, p1.x, p1.y);

    //find the point, P3, directly above pm
    //It will be back from pm by change_y, and up by change_x
    double x3 = pm.x - change_y;
    double y3 = pm.y + change_x;
    struct Point p3 = {x3, y3};

    //first find the distance between P1 and Pm
    double dis_p1_pm = sqrt((p1.x - pm.x) * (p1.x - pm.x) + (p1.y - pm.y) * (p1.y - pm.y));
    //then find the distance between p0 and pm
    double dis_p0_pm = distance - dis_p1_pm;

    double l = sqrt(dis_p1_pm * dis_p0_pm);

    double scale_factor = l / distance;

    //move from p3 over by change in y times scale factor...
    //...and from p3 down by the change in x times the scale factor
    double x_90 = p3.x + scale_factor * change_y;
    double y_90 = p3.y - scale_factor * change_x;
    struct Point p_90 = {x_90, y_90};

    //TODO: test we found P_90 correctly, we did!
    G_rgb(0,0,1); //blue
    G_line(p_90.x, p_90.y, p1.x, p1.y);

    return p_90;

}

struct Point find_point(struct Point p0, struct Point p1){
    double change_x = p1.x - p0.x;
    double change_y = p1.y - p0.y;

    double p2x = p1.x - change_y;
    double p2y = p1.y + change_x;
    struct Point p_off_p1 = {p2x, p2y};

    return p_off_p1;
}

void tree (struct Point p0, struct Point p1, double distance, double percent, double depth){
    if (depth == 0){
         return;
    }

    //get the third point
    struct Point p2 = calculate_point(p0, p1, distance, percent);

    //TODO: test, draw the triangle
    G_rgb(1,0,0); //red
    G_line(p0.x, p0.y, p2.x, p2.y);
    G_rgb(0,1,0); //green
    G_line(p2.x, p2.y, p1.x, p1.y);
    G_rgb(1,0,1); //purple
    G_line(p1.x, p1.y, p0.x, p0.y);

    //draw squares off each edge: p0-p2, p2-p1
    double change_x = p2.x - p0.x;
    double change_y = p2.y - p0.y;

    //point off p2
    double p4x = p2.x - change_y;
    double p4y = p2.y + change_x;
    struct Point p4 = {p4x, p4y};

    //point off p0
    double p3x = p0.x - change_y;
    double p3y = p0.y + change_x;
    struct Point p3 = {p3x, p3y};
    //Draw square off p0-p2
    G_rgb(0,0,0);
    G_line(p2.x, p2.y, p4.x, p4.y);
    G_line(p0.x, p0.y, p3.x, p3.y);
    G_line(p3.x, p3.y, p4.x, p4.y);

    change_x = p1.x - p2.x;
    change_y = p1.y - p2.y;

    //point off p2
    double p5x = p2.x - change_y;
    double p5y = p2.y + change_x;
    struct Point p5 = {p5x, p5y};

    //point off p1
    double p6x = p1.x - change_y;
    double p6y = p1.y + change_x;
    struct Point p6 = {p6x, p6y};

    //draw square off p2-p1
    G_rgb(0,0,0);
    G_line(p1.x, p1.y, p6.x, p6.y);
    G_line(p2.x, p2.y, p5.x, p5.y);
    G_line(p5.x, p5.y, p6.x, p6.y);


    change_x = p0.x - p1.x;
    change_y = p0.y - p1.y;

    //point off p0
    double p7x = p0.x - change_y;
    double p7y = p0.y + change_x;
    struct Point p7 = {p7x, p7y};

    //point off p1
    double p8x = p1.x - change_y;
    double p8y = p1.y + change_x;
    struct Point p8 = {p8x, p8y};

    //Draw square off p0-p1
    G_rgb(0,0,0);
    G_line(p0.x, p0.y, p7.x, p7.y);
    G_line(p1.x, p1.y, p8.x, p8.y);
    G_line(p7.x, p7.y, p8.x, p8.y);


    if(depth == 1){

        G_rgb(1,0,1);
        G_fill_circle(p3.x, p3.y, 5);
        G_fill_circle(p4.x, p4.y, 5);
        G_fill_circle(p5.x, p5.y, 5);
        G_fill_circle(p6.x, p6.y, 5);

    }

    depth -= 1;


    //call children with p3-p4 and p5-p6
    tree(p3,p4, distance, percent, depth);
    tree(p5, p6, distance, percent, depth);



}

int main(){

    //Declare variables here
    //USE DOUBLES!!!!! NOT INTS, except for array accessors
    int swidth, sheight ;
    double x0, y0, x1, y1, x2, y2, length, adj, opp;

    swidth = 1000 ;  sheight = 1000 ;
    G_init_graphics (swidth,sheight) ;  // interactive graphics

    // clear the screen in a given color
    G_rgb (0.3, 0.3, 0.3) ; // dark gray
    G_clear () ;

    /* CODE HERE */

    //Create initial p0 and p1 points for the first triangle (also top of trunk square)
    struct Point p0 = {450, 100};
    struct Point p1 = {550, 100};
    double distance = sqrt((p1.x - p0.x) * (p1.x - p0.x) + (p1.y - p0.y) * (p1.y - p0.y));
    //set how far from p0 we want the third point to lie
    double percent = 0.4;
    double depth = 8;


    struct Point p2 = {200, 500};
    struct Point p3 = {250, 500};
    double distance2 = sqrt((p3.x - p2.x) * (p3.x - p2.x) + (p3.y - p2.y) * (p3.y - p2.y));
    double percent2 = 0.7;
    double depth2 = 7;

    tree(p2,p3, distance2, percent2, depth2);
    //pass two points of a line to a function that calculates the missing third point, and draws a square off each edge
    //of the resulting triangle
    tree(p0, p1, distance, percent, depth);



    /* BEGIN SETDOWN */
    int key ;
    key =  G_wait_key() ; // pause so user can see results

    //   G_save_image_to_file("demo.xwd") ;
    G_save_to_bmp_file("demo.bmp") ;
}


