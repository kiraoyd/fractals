/* To run: cc  turtle.c   -lm  -lX11 */

#include  "FPToolkit.c"
#include <stdio.h>
#include <math.h>
#include <string.h>

const int RULE_MAX = 100; //up to 100 characters in any rule
const int RULE_NUM = 30; //up to 30 rules in any grammar
const int INSTRUCTIONS_MAX = 1000000; //max characters in one instruction string
const int swidth = 200;
const int sheight = 200;

struct Point {
    double x, y;
};

struct Rule {
    char var;
    char rule [100]; //each rule limited to 100 char max
};

struct Grammar {
    char axiom;
    struct Rule rules [30]; //can have up to 30 rules, each with up to 100 characters
    //first index of each stored array is always the variable itself, the rule starts at rules[_][1]
};

//searches the Grammar for a match, grabs rule and copies into 'rule'
int find_rule(struct Grammar grammar, char match, char* rule){
    int length = RULE_NUM;
    int count = 0;
    int found = 0;
    //go through the array of rule structs, if a rules var matches 'match', copy and return the associated rule
    while (count < length){
        if(grammar.rules[count].var == match){
            strcpy(rule, grammar.rules[count].rule);
            found = 1;
        }
        count++;
    }
    return found;
}


int builder(struct Grammar rules, int depth, char* instructions){
    //build the first string
    instructions[0] = '\0';
    char axiom[1]; //make this a string for ease of strcpy
    axiom[0] = rules.axiom;
    strcpy(instructions, axiom); //first thing in instructions should be the axiom

    //parse the string repeatedly
    int count = 0;
    //this loop controls how many times we replace instruction variables with rules
    while (count < depth){
        //start at the first index of the instructions
        int length = strlen(instructions);
        int index = 0;
        //make temp to hold all strings that need to be concatenated
        //this is  a 2-d array, of rules (char arrays)
        char temp[strlen(instructions)][RULE_MAX];
        //for each index, find out what should go in that position, and add to the array of temp strings
        while (index < length){
            //match the character found in each index, to a rule
            if(instructions[index] >= 'A' && instructions[index] <= 'Z'){
                //find the string replacing this index
                char* replace = malloc(RULE_MAX * sizeof(char));
                int found = find_rule(rules, instructions[index], replace);
                if(found == 0){
                    //no matching rule found, terminate on bad input
                    free(replace);
                    printf("no rule found for %c\n", instructions[index]);
                    return -1;
                }
                //printf("Rule found to replace %c: %s\n ", instructions[index], replace);
                char replace_temp[RULE_MAX];
                strcpy(replace_temp, replace);
                strcpy(temp[index], replace_temp); //copy in the rule to the spot in the temp array
                free(replace);
            }
            else if(instructions[index] == '+'){
                strcpy(temp[index], "+"); //the string at this index in temp is just +
            }
            else if(instructions[index] == '-'){
                strcpy(temp[index], "-");  //the string at this index in temp is just -
            }
            else{
                temp[index][0] = '\0';
            }
            index++;
        }

        //once we have all rules in place of variables in temp, concatenate all those into a big char array
        char concatenated[INSTRUCTIONS_MAX];
        concatenated[0] = '\0';
        index = 0;
        //roll through the temp, and build one long string from what's stored in temp
        //length of instructions should be the same as length of temp, since we used instructions to build temp
        while (index < length){
            strcat(concatenated, temp[index]);
            index++;
        }
        //copy concatenated into instructions to overwrite instructions with new string
        strcpy(instructions, concatenated);
        //printf("At depth %d, instruc: %s\n", count, instructions);
        count++;
    }
    //if successful, return 0
    return 0;
}

//Test string builder on console output of instructions
void test_builder(){

    //make a test grammar
    struct Grammar my_rules;
    my_rules.rules[0].var = 'B';
    strcpy(my_rules.rules[0].rule, "A+A");
    my_rules.rules[1].var = 'A';
    strcpy(my_rules.rules[1].rule, "B-B");
    my_rules.axiom = 'B';

    int depth = 6;
    char* instructions = malloc(INSTRUCTIONS_MAX*sizeof(char));
    int success = builder(my_rules, depth, instructions);
    if(success >= 0){
        int index = 0;
        while (index < strlen(instructions)){
            printf("%c", instructions[index]);
            index++;
        }
    }
    else{
        printf("Invalid input");
    }

    free(instructions);

}

struct Point find_new_position (struct Point position, double radians_angle,  int step){
    struct Point new_position;
    //move from position, in the direction of angle, by step number of pixels
    new_position.x = step * cos(radians_angle) + position.x;
    new_position.y = step * sin(radians_angle) + position.y;
    return new_position;
}


void turtle (char instruction_string[], double startx, double starty, int distance){
    int index = 0;
    double angle = 0; //angle to plot next point off
    double angle_change = 30*(M_PI/180); //amount angle changes each + or -
    int step = distance; //length of line between start point and new point
    struct Point move_to = {0,0}; //temp to hold new position of turtle
    struct Point position;
    position.x = startx;
    position.y = starty;

    //enum direction move = "right";
    while(index < strlen(instruction_string)){
        //set start point
        //traverse steps to process each one
        if (instruction_string[index] == 'f' || instruction_string[index] >= 'A' && instruction_string[index] <= 'Z'){

            move_to = find_new_position(position, angle, step);
            //draw line between start point and new point
            G_rgb(1,1,1); //white
            G_line(position.x, position.y, move_to.x, move_to.y);
            //reset start point to new point
            position.x = move_to.x;
            position.y = move_to.y;
        }
        else if (instruction_string[index] == '+'){
            //move counter clockwise
            angle += angle_change;
            angle = fmod(angle, (2*M_PI));
        }
        else if (instruction_string[index] == '-'){
            //move clockwise
            angle -= angle_change;
            angle = fmod(angle, (2*M_PI));
        }
        index++;
    }
}

struct Turtle_info {
    double startx, starty;
    int distance;
};

//Simuates the draw, and finds the min and max of x and y coords, and returns a new startx, starty, and distance
void auto_placer (char instruction_string[], struct Turtle_info *turtle){
    int index = 0;
    double angle = 0; //angle to plot next point off
    double angle_change = 30*(M_PI/180); //amount angle changes each + or -
    int step = turtle -> distance; //length of line between start point and new point
    struct Point move_to = {0,0}; //temp to hold new position of turtle
    struct Point position;
    position.x = turtle -> startx;
    position.y = turtle -> starty;

    //the min/max X and min/max Y will begin as the initial point we start at
    double x_max = turtle -> startx;
    double x_min = turtle-> startx;
    double y_max = turtle -> starty;
    double y_min = turtle->starty;

    printf("starting xmax: %f, xmin %f, ymax %f, ymin %f", x_max, x_min, y_max, y_min);

    //enum direction move = "right";
    while(index < strlen(instruction_string)){

        //traverse steps to process each one
        if (instruction_string[index] == 'f' || instruction_string[index] >= 'A' && instruction_string[index] <= 'Z'){

            move_to = find_new_position(position, angle, step);
            //draw line between start point and new point
            G_rgb(1,0,0); //white
            //Instead of drawing, we need to keep track of the max and min values:
            G_line(position.x, position.y, move_to.x, move_to.y);
            //check to see if we have adjusted the x max/min
            if(move_to.x > x_max){
                x_max = move_to.x;
            }
            else if (move_to.x < x_min){
                x_min = move_to.x;
            }

            //check to see if we have adjusted the y max/min
            if(move_to.y > y_max){
                y_max = move_to.y;
            }
            else if(move_to.y < y_min){
                y_min = move_to.y;
            }
            //reset start point to new point
            position.x = move_to.x;
            position.y = move_to.y;
        }
        else if (instruction_string[index] == '+'){
            //move counter clockwise
            angle += angle_change;
            angle = fmod(angle, (2*M_PI));
        }
        else if (instruction_string[index] == '-'){
            //move clockwise
            angle -= angle_change;
            angle = fmod(angle, (2*M_PI));
        }
        index++;
    }

    printf("xmax: %f, xmin %f, ymax %f, ymin %f", x_max, x_min, y_max, y_min);
    char axis = 'x';
    double largest_overshoot = x_min;
    if (x_max > largest_overshoot){
        largest_overshoot = x_max;
        axis = 'x';
    }
    if(y_max > largest_overshoot){
        largest_overshoot = y_max;
        axis = 'y';
    }
    if(y_min > largest_overshoot){
        largest_overshoot = y_min;
        axis = 'y';
    }


    //scale factor will be the max / width or height of the screen
    double scale_factor = 1;
    if(axis == 'x'){
        if(largest_overshoot > swidth){
            scale_factor = swidth / largest_overshoot;
        }
    }
    else if (axis == 'y'){
        if(largest_overshoot > sheight){
            scale_factor = sheight / largest_overshoot;
        }
    }

    printf("Largest overshoot: %f", largest_overshoot);
    printf("Scale factor: %f", scale_factor);
    //scale the distance by the scale_factor, update turtle struct
    turtle->distance = turtle->distance * scale_factor;


    //The center of the figure will be the midpoint of the max/min values
    //Will be used in the translation step
    //TODO, translation not working for the flower
    double mid_x = (x_max + x_min) / 2;
    double mid_y = (y_max + y_min) / 2;
    G_rgb(1,0,0);
    G_fill_circle(mid_x, mid_y, 50);
    double s_center_x = (swidth+1) / 2;
    double s_center_y = (sheight+1)/ 2;
    G_rgb(0,0,0);
    G_fill_circle(s_center_x, s_center_y, 5);
    printf("midx = %f, midy = %f", mid_x, mid_y);

    double change_x = s_center_x - mid_x;
    double change_y = s_center_y - mid_y;
    printf("dx = %f, dy = %f", change_x, change_y);

    //calculate new start point, scale first!
    double new_start_x = (scale_factor* turtle->startx) + change_x;
    double new_start_y = (scale_factor* turtle->starty) + change_y;
    G_rgb(0,0,1);
    G_fill_circle(new_start_x, new_start_y, 10);

    //Update the turtle struct with the recalculated values for startx, starty
    turtle->startx = new_start_x;
    turtle->starty = new_start_y;

}

void test_turtle(){
    char array[] = {'f', '+', 'f', '+', 'f', 'f', '-', 'f'};
    double startx = 200;
    double starty = 200;
    double distance = 20;
    //test mine:
    struct Turtle_info info;
    info.startx = startx;
    info.starty = starty;
    info.distance = distance;
    auto_placer(array, &info);
    turtle(array, startx, starty, distance);
}

void test_davids(){
        char davids_array [1000000];
        scanf("%s", davids_array);
        printf("string length = %ld\n", strlen(davids_array));
        double startx = 100;
        double starty = 10;
        int distance = 1;
        //TODO test Davids
        struct Turtle_info adjusted;
        adjusted.startx = startx;
        adjusted.starty = starty;
        adjusted.distance = distance;
        auto_placer(davids_array, &adjusted);
        turtle(davids_array, startx, starty, distance);
}

void draw_flower(double startx, double starty, double distance){
        //make a test grammar, at a depth of 10 this one makes a flower
        struct Grammar my_rules;
        my_rules.rules[0].var = 'B';
        strcpy(my_rules.rules[0].rule, "A+A");
        my_rules.rules[1].var = 'A';
        strcpy(my_rules.rules[1].rule, "B-B");
        my_rules.axiom = 'B';

        int depth = 10;
        char* instructions = malloc(INSTRUCTIONS_MAX*sizeof(char));
        int success = builder(my_rules, depth, instructions);
        if(success >= 0){
            int index = 0;
            while (index < strlen(instructions)){
                //printf("%c", instructions[index]);
                index++;
            }
        }
        else{
            printf("Invalid input");
        }


        //auto placer needs to simulate turtle
        struct Turtle_info adjusted;
        adjusted.startx = startx;
        adjusted.starty = starty;
        adjusted.distance = distance;

        auto_placer(instructions, &adjusted);
        turtle(instructions, adjusted.startx, adjusted.starty, adjusted.distance);
        free(instructions);

}

int main(){

    G_init_graphics (swidth,sheight) ;  // interactive graphics

    // clear the screen in a given color
    G_rgb (0.3, 0.3, 0.3) ; // dark gray
    G_clear () ;

    /* CODE HERE */
    test_turtle();
    //test_davids();
    //test_builder();

    //draw_flower(200, 200, 10);
    //draw_flower(400, 400, 20);


    // BEGIN SETDOWN
    int key ;
    key =  G_wait_key() ; // pause so user can see results

    //   G_save_image_to_file("demo.xwd") ;
    G_save_to_bmp_file("trees.bmp") ;


/*
    //Some reference code below:
    char v[1000000];
    char u[1000000];
    u[0] = '\0'; v[0] = '\0'; //this makes u and v "empty" strings
    int length = strlen(u); //returns a long in, %ld
    strcpy(u, "dog"); //will overwrite what is there, and copy in "dog"
    strcpy(v, "pig");
    strcat(u,v);
    strcpy(v,u);
*/
    return 0;
}