char Fname[100];
int count;
for(count = 0; couont < 30; count++){
    //04d is number of decimal places
    //generate the image we want to save HERE
    sprintf(Fname, "img%04d.bmp", count);
    //each "frame" gets saved as it's own file
    G_save_to_bmp_file(Fname);
}

//img0000.bmp through img0029.gmp
//try linux"convert" to make it into an mpeg
//G_display_image <-- option to see without the waitkey, can use with usleep