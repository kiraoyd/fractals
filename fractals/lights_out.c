/* To run: cc  lights_out.c   -lm  -lX11 */

#include  "FPToolkit.c"
#include <stdio.h>
#include <math.h>
#include <string.h>

#define PI M_PI
#define FRAME_SAVE 100

//globals
double scale_x = 0.5;
double scale_y = 0.5;
double translate = 0.5;
double swidth = 1000;
double sheight = 1000;


void lights_out_rules(double gradiant, int section){

    double n;
    double x, y;

    //start (x,y) at 0,0
    x = 0;
    y = 0;

    //mod the frame count by 8 (number of rules) to switch between each rule each frame
    int marker = (section % 8) + 1;

        for (int i = 0; i<1000000; i++){
            n = drand48();
            if(n > 8* (1.0/9.0)){
                //Rule 1: scale only, by 0.3
                //All other rules are in relation to this one (where we are after scaling)
                x = x * (1.0/3.0);
                y = y* (1.0/3.0);
                if(marker == 1){
                    G_rgb(1,1,1);
                } else{
                    G_rgb(1*gradiant,1*gradiant,0*gradiant);
                }
                G_point(x*swidth, y*sheight);
            }
            else if(n > 7* (1.0/9.0)){
                //Rule 2: scale, then translate x only
                x = x* (1.0/3.0);
                y = y* (1.0/3.0);
                x = x + (1.0/3.0);
                if(marker == 2){
                    G_rgb(1,1,1);
                }else {
                    G_rgb(1*gradiant,0.75*gradiant,0.25*gradiant);
                }
                G_point(x*swidth, y*sheight);

            }
            else if(n > 6* (1.0/9.0)){
                //Rule 3: scale, then translate both x only, by 2/3
                x = x* (1.0/3.0);
                y = y* (1.0/3.0);
                x = x + (2.0/3.0);
                if(marker == 3){
                    G_rgb(1,1,1);
                } else{
                    G_rgb(1*gradiant,0*gradiant,.75*gradiant);
                }
                G_point(x*swidth, y*sheight);
            }
            else if (n > 5* (1.0/9.0)){
                //Rule 4: scacle, then translate just y
                x = x* (1.0/3.0);
                y = y* (1.0/3.0);
                y = y + (1.0/3.0);
                if(marker == 8){
                    G_rgb(1,1,1);
                } else{
                    G_rgb(0*gradiant,0.8*gradiant,1*gradiant);
                }
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
                if(marker == 4){
                    G_rgb(1,1,1);
                } else{
                    G_rgb(0*gradiant,1*gradiant,0*gradiant);
                }
                G_point(x*swidth, y*sheight);
            }
            else if (n > 2* (1.0/9.0)){
                //Rule 7: scale, then translate just y
                x = x* (1.0/3.0);
                y = y* (1.0/3.0);
                y = y + (2.0/3.0);
                if(marker == 7){
                    G_rgb(1,1,1);
                } else{
                    G_rgb(0.6*gradiant,0.6*gradiant,0*gradiant);
                }
                G_point(x*swidth, y*sheight);
            }
            else if (n > 1* (1.0/9.0)){
                //Rule 8: scacle, then translate x and y
                x = x* (1.0/3.0);
                y = y* (1.0/3.0);
                x = x + (1.0/3.0);
                y = y + (2.0/3.0);
                if(marker == 6){
                    G_rgb(1,1,1);
                } else{
                    G_rgb(1*gradiant,0*gradiant,0*gradiant);
                }
                G_point(x*swidth, y*sheight);
            }
            else{
                //Rule 9: scacle, then translate x and y
                x = x* (1.0/3.0);
                y = y* (1.0/3.0);
                x = x + (2.0/3.0);
                y = y + (2.0/3.0);
                if(marker == 5){
                    G_rgb(1,1,1);
                } else{
                    G_rgb(0*gradiant,0*gradiant,1*gradiant);
                }
                G_point(x*swidth, y*sheight);
            }
        }
}


void carpet_lights_out(){
    int count = 0;
    int frames = 50;
    double gradiant = 0.99; //slowly fades all colors to black each frame
    while(count < frames){
        gradiant = gradiant * 0.9;
        lights_out_rules(gradiant, count);
        count++;
        G_wait_key();
    }
}

void lights_out_frame_save(){
    char frame_name[FRAME_SAVE]; //holds the frame_name
    int frames = FRAME_SAVE;
    int count = 0;
    double gradiant = 0.99; //slowly fades all colors to black each frame
    while(count < frames){
        sprintf(frame_name, "img%04d.bmp", count); //create a sequential framing scheme for the mpeg

        //draw frame to save
        gradiant = gradiant * 0.9;
        lights_out_rules(gradiant, count);

        G_save_to_bmp_file(frame_name);
        count++;
    }

}

int main(){

    G_init_graphics (swidth,sheight) ;  // interactive graphics

    // clear the screen in a given color
    G_rgb (0.3, 0.3, 0.3) ; // dark gray
    G_clear () ;

    //carpet_lights_out();

    lights_out_frame_save();

    // BEGIN SETDOWN
     int key ;
     key =  G_wait_key() ; // pause so user can see results

     //   G_save_image_to_file("demo.xwd") ;
     G_save_to_bmp_file("trees.bmp") ;
    return 0;
}