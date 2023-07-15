
//to run: cc  mandelbrot.c   -lm  -lX11
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <complex.h>
#include <ctype.h>
#include  "FPToolkit.c"


//To zoom, you have to recalculate with finer iterations each frame
const double SAMPLEITER = 0.1;
const double WIDTH = 800;
const double HEIGHT = 800;


//Example use: prcmx("%20.16lf", z);
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

//Example use:
//    double r;
//    printf("Enter the value for r: ");
//    scanf("%lf", &r);
//    test_complex(r);
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

//Holds information about discovering convergence for a complex number
struct Converge_info{
    int converges;
    double iterations;
    double detail;
};

//Note you can use how many iterations you get before discovering it diverges, to control what color to make it
//More iterations to hit divergence, the more stable it is
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
        z = z*z + c;
        i++;
    }
    struct Converge_info info = {converge, i, target};
    return info;
}

//Plot the corresponding point on the physical window
void plot(complex num, double x, double y){
    //converges, iterations, detail
    struct Converge_info info = {1, 0, 0};
    //for each point, discover if it converges or not
    info = converges(num);
    //if divergent and less stable, color in grayscale
    if(info.converges == 0){
        //plot the color based on the number of iterations
        double gray = info.iterations/info.detail;
        //printf("Gray: %f", gray);
        G_rgb(gray, gray, gray);
    }    else {
    //if convergent, we plot black
             G_rgb(0,0,0);
         }

    //draw the point on the physical window
    G_point(x, y);
}

//Loop through the complex numbers represented by the virtual window
//Determine convergence/divergence, and plot on the physical window accordingly
void mandelbrot(){
    //iterate across the board, exactly the width of the physical window
    //for each point, call plot(), pass it the point we are on
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
            num = r_val + i_val;
            plot(num, physical_x, physical_y);
            physical_x++;
            r_val = r_val + iter_real_x;
        }
        physical_y++;
        i_val = i_val + iter_i_y;
    }
}


//Convergence evaluator for a julia set, where z is the current location on the virtual window
struct Converge_info converges_julia (complex z, complex julia){
    double target = 100; //this adjusts the detail
    int converge = 1;
    double i = 0;
    while(i < target && converge == 1){
        //if the absolute value of the z value ever becomes greater than 2, than it is divergent
        if(cabs(z) > 2){
            converge = 0;
        }
        z = z*z + julia;
        i++;

    }
    struct Converge_info info = {converge, i, target};
    return info;
}

//plots actual pixel on the physical window for a julia set
void plot_julia(complex num, double x, double y){
    struct Converge_info info = {1, 0, 0};
    complex julia = 0.28 + 0.008*I; //change this and get a different julia set
    //complex julia = -0.79 + 0.15*I;
    //complex julia = -1.476 + 0*I;
    //complex julia = -0.12 - 0.77*I;

    //for each point, discover if it converges or not
    info = converges_julia(num, julia);
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
    //draw the point
    G_point(x, y);
}

//julia set start z at some point on the virtual window, and c at some other point on the virtual window
//proceed as in the mandelbrot
void julia(){
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
            num = r_val + i_val;
            plot_julia(num, physical_x, physical_y);
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

    mandelbrot();
     //G_save_to_bmp_file("mandelbrot.bmp") ;
    G_wait_key();
    julia();
    //G_save_to_bmp_file("julia.bmp") ;

    // BEGIN SETDOWN
     int key ;
     key =  G_wait_key() ; // pause so user can see results
     // G_save_image_to_file("demo.xwd") ;
    return 0;

}
