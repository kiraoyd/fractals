
//To run: cc  m_julias.c   -lm  -lX11
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <complex.h>
#include <ctype.h>
#include  "FPToolkit.c"
// for isspace


//TODO programming the julia set could be the 5th fractal???
//To zoom, you have to recalculate with finer iterations each frame

const double SAMPLEITER = 0.1;
const double WIDTH = 800;
const double HEIGHT = 800;

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


struct Converge_info{
    int converges;
    double iterations;
    double detail;
};

struct Converge_info converges (complex c){
    complex z = 0;
    double target = 100; //this adjusts the detail
    int converge = 1;
    double i = 0;
    while(i < target && converge == 1){
        //if the absolute value of the z value ever becomes greater than 2, than it is divergent
        if(cabs(z) > 2){
            converge = 0;
        }
        //prcmx("%20.16lf", z);
        //printf("\n");
        z = z*z + c;
        i++;

    }
    //printf("i: %f", i);
    struct Converge_info info = {converge, i, target};
    return info;
}

struct Converge_info converges_julia (complex z, complex julia){
    double target = 20; //this adjusts the detail
    int converge = 1;
    double i = 0;
    while(i < target && converge == 1){
        //if the absolute value of the z value ever becomes greater than 2, than it is divergent
        if(cabs(z) > 2){
            converge = 0;
        }
        //prcmx("%20.16lf", z);
        //printf("\n");
        z = z*z + julia;
        i++;

    }
    struct Converge_info info = {converge, i, target};
    return info;
}

//checks convergence for number num, given cs value
void plot_julia(complex num, complex c, double x, double y){
    struct Converge_info info = {1, 0, 0};
    //for each point, discover if it converges or not
    info = converges_julia(num, c);
    //if false and less stable

    if(info.converges == 0){
        //plot the color based on the number of iterations
        double gray = info.iterations/info.detail;
        //printf("Gray: %f", gray);
        G_rgb(gray, gray, gray);
    }    else {
             //if true, we plot black
             G_rgb(0,0,0);
         }

    G_point(x, y);
}

//julia set start z at some point on the virtual window, and c at some other point on the virtual window
//proceed as in the mandelbrot

void julia(complex c){
    double max_i = 2;
    double min_i = -2;
    double max_r = 2;
    double min_r = -2;

    double r_val = min_r;
    complex i_val = min_i*I;

    //calculate the iteration values so they will hit every point across both screens equally
    double iter_real_x =  (max_r - min_r) / WIDTH;
    complex iter_i_y = ((max_i - min_i) / HEIGHT) *I;

    double physical_x = 0;
    double physical_y = 0;

    complex num;
    //Iterate across the PHYSICAL window
    //Outer loop moves along the y-axis of the physical window
    while(physical_y < HEIGHT){
        //inner loop moves across the x-axis of the physical window
        physical_x = 0;
        r_val = min_r;
        while(physical_x < WIDTH){
            //the point at any give spot on the virtual window will be r_val + i_val*i
            //the point at any given iteration on the physical will just be (physical_x, physical_y)
            //Check each point to see if it converges
            num = r_val + i_val;
            plot_julia(num, c, physical_x, physical_y);
            physical_x++;
            r_val = r_val + iter_real_x;
        }
        physical_y++;
        i_val = i_val + iter_i_y;
    }
}


void m_julia(){
    //iterate across the board, exactly the width of the physical window
    //for each point, call plot(), pass it the point we are on
    double max_i = 2;
    double min_i = -2;
    double max_r = 2;
    double min_r = -2;

    double r_val = min_r;
    complex i_val = min_i*I;

    //calculate the iteration values so they will hit every point across both screens equally
    double iter_real_x =  ((max_r - min_r) / WIDTH) * 20;
    complex iter_i_y = (((max_i - min_i) / HEIGHT) *I)*20;

    double physical_x = 0;
    double physical_y = 0;

    complex num;
    //Iterate across the PHYSICAL window
    //Outer loop moves along the y-axis of the physical window
    while(physical_y < HEIGHT){
        //inner loop moves across the x-axis of the physical window
        physical_x = 0;
        r_val = min_r;
        while(physical_x < WIDTH){
            //the point at any give spot on the virtual window will be r_val + i_val*i
            //the point at any given iteration on the physical will just be (physical_x, physical_y)
            num = r_val + i_val;
             prcmx("%20.16lf", num);
            //for every complex number on the screen, if it diverges, plot the julia set for it
            struct Converge_info info = {1,0,0};
            info = converges(num);
            if(info.converges == 0){
                julia(num);
                G_wait_key();
            }
            physical_x++;
            r_val = r_val + iter_real_x;

        }
        physical_y++;
        i_val = i_val + iter_i_y;
    }
}



int main() {

    G_init_graphics (WIDTH,HEIGHT) ;  // interactive graphics

    // clear the screen in a given color
    G_rgb (0.3, 0.3, 0.3) ; // dark gray
    G_clear () ;

    /*
    double r;
    printf("Enter the value for r: ");
    scanf("%lf", &r);
    test_complex(r);
    */

    m_julia();

    // BEGIN SETDOWN
     int key ;
     key =  G_wait_key() ; // pause so user can see results

     //   G_save_image_to_file("demo.xwd") ;
     //G_save_to_bmp_file("trees.bmp") ;
    return 0;

}
