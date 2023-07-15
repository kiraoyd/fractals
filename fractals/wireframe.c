//To Run: cc wireframe.c -lm -lX11


#include "FPToolkit.c"

/*

       Y+
       |
       |    * (y,z)
       |
<------+--------Z+
   D   |
       |
       |


y'    y
- =  ---
D    D+z

H = D*tan(halfangle) ;

with the x-axis perpendicular to this plane.

*/

#define M 700000
double Wsize = 1000  ; // window size ... choose 600 for repl
double X[M],Y[M],Z[M] ;
//What's inside X, Y, and Z?
//They hold line segment information
//point 0 and point 1, in indicies 0 and 1, describe a line between point 0 and point 1
//indicies 2 and 3, hold a line between point 1 and point 2
//indicies 4 and 5 hold a line between point 2 and pont 3
double Xplot[M],Yplot[M] ;
int N = 0 ;


int translate(double dx, double dy, double dz)
{
  int i ;

  for (i = 0 ; i < N ; i++) {
    X[i] += dx ;
    Y[i] += dy ;
    Z[i] += dz ;
  }
}



int rotate_x(double degrees)
// Y[] and Z[] will change but X[] will be unchanged
{
  double radians,c,s,temp ;
  int i ;

  radians = degrees*M_PI/180 ;
  c = cos(radians) ;
  s = sin(radians) ;
  for (i = 0 ; i < N ; i++) {
    temp =  c*Y[i] - s*Z[i] ;
    Z[i] =  s*Y[i] + c*Z[i] ;
    Y[i] = temp ;
  }
}




int rotate_y(double degrees)
// X[] and Z[] will change but Y[] will be unchanged
{
  double radians,c,s,temp ;
  int i ;

  radians = degrees*M_PI/180 ;
  c = cos(radians) ;
  s = sin(radians) ;
  for (i = 0 ; i < N ; i++) {
    temp =  c*X[i] + s*Z[i] ;
    Z[i] = -s*X[i] + c*Z[i] ;
    X[i] = temp ;
  }
}



int rotate_z(double degrees)
// X[] and Y[] will change but Z[] will be unchanged
{
  double radians,c,s,temp ;
  int i ;

  radians = degrees*M_PI/180 ;
  c = cos(radians) ;
  s = sin(radians) ;
  for (i = 0 ; i < N ; i++) {
    temp =  c*X[i] - s*Y[i] ;
    Y[i] =  s*X[i] + c*Y[i] ;
    X[i] = temp ;
  }
}



int project(double observer_distance, double halfangle_degrees)
{

  // student work goes here
  double y_prime, x_prime, H;

  double ha_radians = halfangle_degrees * (M_PI/180);

  H = tan(ha_radians) * observer_distance;
  double scale = Wsize/H;
  double translate = Wsize / 2;

  //iterate over the lists of points
  for(int i = 0; i < M; i++){
      //calculate the projected point onto the virtual screen
     Yplot[i] = scale* (observer_distance * Y[i] / (observer_distance + Z[i])) + translate;
     Xplot[i] = scale* (observer_distance * X[i] / (observer_distance + Z[i])) + translate;
  }

}


int draw()
{
  int i ;
  for (i = 0 ; i < N ; i=i+2) {
    G_line(Xplot[i],Yplot[i],  Xplot[i+1],Yplot[i+1]) ;
  }

}


int print_object()
{
  int i ;
  for (i = 0 ; i < N ; i=i+2) {
    printf("(%lf, %lf, %lf)   (%lf, %lf, %lf)\n",
	   X[i],Y[i],Z[i],  X[i+1],Y[i+1],Z[i+1]) ;
  }

  printf("===============================\n") ;

  for (i = 0 ; i < N ; i=i+2) {
    printf("(%lf, %lf)   (%lf, %lf)\n",
	   Xplot[i],Yplot[i],  Xplot[i+1],Yplot[i+1]) ;
  }
}



int save_line(double xs, double ys, double zs,
	      double xe, double ye, double ze)
{
  // about to add items at slots N and N+1 :
  if (N+1 >= M) {
    printf("full\n") ;
    return 0 ;
  }

  X[N] = xs ; Y[N] = ys ; Z[N] = zs ; N++ ;
  X[N] = xe ; Y[N] = ye ; Z[N] = ze ; N++ ;

  return 1 ;
}


//a cube with a center at (0,0,0) will consist of 8 points, which will be all permutations of 1 and -1 as (x,y,z)
void build_cube()
{
    N = 0; //reset to the beginning of the global arrays

    //manually enter the 8 point based line segments to the x,y,z array
    //C to D, starting at C
    X[N] = -1; Y[N] = -1; Z[N] = -1; //C
    N++;
    X[N] = -1; Y[N] = 1; Z[N] = -1; //D
    N++;

    //D to E,  starting at D
    X[N] = -1; Y[N] = 1; Z[N] = -1;   //D
    N++;
    X[N] = -1; Y[N] = 1; Z[N] = 1;  //E
    N++;

    //E to F, starting at E
    X[N] = -1; Y[N] = 1; Z[N] = 1; //E
    N++;
    X[N] = 1; Y[N] = 1; Z[N] = 1;  //F
    N++;

    //F to A, starting at F
    X[N] = 1; Y[N] = 1; Z[N] = 1;  //F
    N++;
    X[N] = 1; Y[N] = 1; Z[N] = -1;  //A
    N++;


    //A to D, starting at A
    X[N] = 1; Y[N] = 1; Z[N] = -1;  //A
    N++;
    X[N] = -1; Y[N] = 1; Z[N] = -1;  //D
    N++;

    //A to B
    X[N] = 1; Y[N] = 1; Z[N] = -1;  //A
    N++;
    X[N] = 1; Y[N] = -1; Z[N] = -1; //B
    N++;

    //C to B
    X[N] = -1; Y[N] = -1; Z[N] = -1; //C
    N++;
    X[N] = 1; Y[N] = -1; Z[N] = -1;  //B
    N++;

    //B to G
    X[N] = 1; Y[N] = -1; Z[N] = -1;  //B
    N++;
    X[N] = 1; Y[N] = -1; Z[N] = 1; //G
    N++;

    //G to F
    X[N] = 1; Y[N] = -1; Z[N] = 1; //G
    N++;
    X[N] = 1; Y[N] = 1; Z[N] = 1; //F
    N++;

    //E to H
    X[N] = -1; Y[N] = 1; Z[N] = 1;  //E
    N++;
    X[N] = -1; Y[N] = -1; Z[N] = 1;  //H
    N++;

    //H to G
    X[N] = -1; Y[N] = -1; Z[N] = 1;  //H
    N++;
    X[N] = 1; Y[N] = -1; Z[N] = 1; //G
    N++;

    //H to C
    X[N] = -1; Y[N] = -1; Z[N] = 1;  //H
    N++;
    X[N] = -1; Y[N] = -1; Z[N] = -1; //C
    N++;

}

struct Point {
    double x, y;
};

struct Point get_carpet_point(){
//random number generator
    double n;

    //start (x,y) at 0,0
    struct Point point = {0,0};

    double k = (1/9);
    printf("%f ", k);

    G_rgb(1,1,1);
    for (int i = 0; i<1000000; i++){
        n = drand48();
        if(n > 8* (1.0/9.0)){
            //Rule 1: scale only, by 0.3
            //All other rules are in relation to this one (where we are after scaling)
            point.x = point.x * (1.0/3.0);
            point.y = point.y* (1.0/3.0);

        }
        else if(n > 7* (1.0/9.0)){
            //Rule 2: scale, then translate x only
            point.x = point.x* (1.0/3.0);
            point.y = point.y* (1.0/3.0);
            point.x = point.x + (1.0/3.0);
        }
        else if(n > 6* (1.0/9.0)){
            //Rule 3: scale, then translate both x only, by 2/3
            point.x = point.x* (1.0/3.0);
            point.y = point.y* (1.0/3.0);
            point.x = point.x + (2.0/3.0);
        }
        else if (n > 5* (1.0/9.0)){
            //Rule 4: scacle, then translate just y
            point.x = point.x* (1.0/3.0);
            point.y = point.y* (1.0/3.0);
            point.y = point.y + (1.0/3.0);
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
            point.x = point.x* (1.0/3.0);
            point.y = point.y* (1.0/3.0);
            point.x = point.x + (2.0/3.0);
            point.y = point.y + (1.0/3.0);
        }
        else if (n > 2* (1.0/9.0)){
            //Rule 7: scale, then translate just y
            point.x = point.x* (1.0/3.0);
            point.y = point.y* (1.0/3.0);
            point.y = point.y + (2.0/3.0);
        }
        else if (n > 1* (1.0/9.0)){
            //Rule 8: scacle, then translate x and y
            point.x = point.x* (1.0/3.0);
            point.y = point.y* (1.0/3.0);
            point.x = point.x + (1.0/3.0);
            point.y = point.y + (2.0/3.0);
        }
        else{
            //Rule 9: scacle, then translate x and y
            point.x = point.x* (1.0/3.0);
            point.y = point.y* (1.0/3.0);
            point.x = point.x + (2.0/3.0);
            point.y = point.y + (2.0/3.0);
        }
    }
    return point;
}

void buid_sponge()
{

    N = 0;
    //TODO how is this gonna work actually....
}


//this just creates the points x,y,z that make up the pyramid
int build_pyramid()
{
  int n,k ;
  double a,x[100],z[100],yv ;

  N = 0 ; // global

  n = 4 ;
  for (k = 0; k <= n ; k++) {
    a = k * 2*M_PI/n ;
    x[k] = cos(a) ;
    z[k] = sin(a) ;
  }

  yv = -1 ;
  for (k = 0; k < n ; k++) {
    save_line(0,2,0,  x[k],yv,z[k]) ;
    save_line(x[k],yv,z[k],    x[k+1],yv,z[k+1]) ;
  }

}

int test_pyramid()
{
  G_init_graphics(Wsize,Wsize) ;
  G_rgb(0,0,0) ;
  G_clear() ;
  G_rgb(0,1,0) ;

  build_pyramid() ;
  project(5,45) ;
  draw() ;
  print_object() ;

  G_wait_key() ;
}

void test_cube()
{
  G_init_graphics(Wsize,Wsize) ;
  G_rgb(0,0,0) ;
  G_clear() ;
  G_rgb(0,1,0) ;

  build_cube() ;
  project(5,45) ;
  draw() ;
  print_object() ;

  G_wait_key() ;
}


int test_cube_rotate()
{
  //  G_choose_repl_display() ; // not too bad as a repl movie
  G_init_graphics(Wsize,Wsize) ;

  build_cube() ;

  while (1) {
    G_rgb(0,0,0) ;
    G_clear() ;
    G_rgb(0,1,0) ;
    project(3,45) ;
    draw() ;
    rotate_y(3) ;
    if (G_wait_key() == 'q') { break ; }
  }

}


int test_pyramid_rotate()
{
  //  G_choose_repl_display() ; // not too bad as a repl movie
  G_init_graphics(Wsize,Wsize) ;

  build_pyramid() ;

  while (1) {
    G_rgb(0,0,0) ;
    G_clear() ;
    G_rgb(0,1,0) ;
    project(3,45) ;
    draw() ;
    rotate_y(2) ;
    if (G_wait_key() == 'q') { break ; }
  }

}




int main()
{
  //test_cube() ;
  //test_cube_rotate();
    test_pyramid_rotate() ;
}
