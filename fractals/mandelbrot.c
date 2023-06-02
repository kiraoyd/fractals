//cc  mandelbrot.c   -lm  -lX11
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <complex.h>
#include <ctype.h>
// for isspace

const SAMPLEITER = 0.1;
const WIDTH = 800;
const HEIGHT = 800;

//TODO copy this into mandelbrot for use
void prcmx (char *control, complex c)
//print complex number
{
    double a,b ;
    a = creal(c) ; //extract the real portion
    b = cimag(c) ; //extract the imaginary portion
    printf(control,a) ;
    if (b >= 0) {
        printf("+") ;
    } else {
        printf("-") ;
    }
    printf(control,fabs(b)) ;
    printf("I") ;
}

//TODO copy into mandelbrot to use
complex sccmx ()
//scan complex number
{
    double rp,ip ;
    complex c ;
    scanf("%lf %lf",&rp, &ip) ;
    c = rp + ip*I ;
    return c ;
}

void text_complex (double r){
    complex z = 0;
    double target = 10;
    for (int i = 0; i < target; i++){
        prcmx("%20.16lf", z);
        printf("\n");
        z = z*z + r;
    }
}

bool converges (complex c){
    complex z = 0;
    double target = 10;
    bool converge = true;
    for (int i = 0; i < target; i++){
        if(cabs(z) > 2){
            converge = false;
        }
        prcmx("%20.16lf", z);
        printf("\n");
        z = z*z + c;
    }
    //if the absolute value of the z value ever becomes greater than 2, than it is divergent
    return converge;
}


void sample_space(){
    //iterate across the board
    //for each point, call plot(), pass it the point we are on
    double max_i = 2;
    double min_i = -2;
    double max_r = 2;
    double min_r = -2;

    double r_val = min_r;
    double i_val = min_i;

    complex point;
    //iterate across the x-axis for every value along the y
    //outer loop moves the y from min_y to max_y
    while(i_val < max_y){
        //inner loop moves across the x-axis of real numbers
        while(r_val < max_x){
            //the point at any give spot will be r_val + i_val*i
            point = r_val + i_val*I;
            plot(point);
            r_val += SAMPLEITER;
        }
        i_val += SAMPLEITER;
    }
}

struct Point {
    double x, y;
};

struct Point transform(complex virtual_p){
    struct Point point = {0,0};
    //Take the virtual point x (real), y (complex)
    double x = creal(virtual_p);
    double y = cimag(virtual_p);

    //scale it

    //translate it

    //fill struct
    point.x = x;
    point.y = y;

    return point;
}

void plot(complex point){
    bool converge = true;
    struct Point plot_point;
    //for each point, discover if it converges or not
    converge = converges(point)
    //if true, we plot pink
    if (converge){
        G_rgb(1,0,0); //red
    } else {
        //if false, we plot black
        G_rgb(0,0,0); //black
    }
    //scale and translate the point to the real window
    plot_point = transform(point);
    //draw the point
    G_point(plot_point.x, plot_point.y);
}

int main() {
    /*
    double r;
    printf("Enter the value for r: ");
    scanf("%lf", &r);
    test_complex(r);
    */

    sample_space();
    return 0;

}
