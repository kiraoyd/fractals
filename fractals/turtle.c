/* To run: cc  turtle.c   -lm  -lX11 */

#include  "FPToolkit.c"
#include <stdio.h>
#include <math.h>
#include <string.h>

const int RULE_MAX = 100; //up to 100 characters in any rule
const int RULE_NUM = 30; //up to 30 rules in any grammar
const int INSTRUCTIONS_MAX = 1000000; //max characters in one instruction string
const double swidth = 400.0;
const double sheight = 400.0;

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
            G_rgb(255.0/255.0,182.0/255.0,193.0/255.0); //pink
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
    double distance;
};

//Simuates the draw, and finds the min and max of x and y coords, and returns a new startx, starty, and distance
void auto_placer (char instruction_string[], struct Turtle_info *turtle){
    int index = 0;
    double angle = 0.0; //angle to plot next point off
    double angle_change = 30.0*(M_PI/180.0); //amount angle changes each + or -
    double step = turtle -> distance; //length of line between start point and new point
    struct Point move_to = {0.0,0.0}; //temp to hold new position of turtle
    struct Point position;
    position.x = turtle -> startx;
    position.y = turtle -> starty;

    //the min/max X and min/max Y will begin as the initial point we start at
    double x_max = turtle -> startx;
    double x_min = turtle-> startx;
    double y_max = turtle -> starty;
    double y_min = turtle->starty;

    //simulate turtle
    while(index < strlen(instruction_string)){
        //traverse steps to process each one
        if (instruction_string[index] == 'f' || instruction_string[index] >= 'A' && instruction_string[index] <= 'Z'){
            move_to = find_new_position(position, angle, step);
            G_rgb(1,0,0); //white

            //Instead of drawing, we need to keep track of the max and min values:
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
            angle = fmod(angle, (2.0*M_PI));
        }
        else if (instruction_string[index] == '-'){
            //move clockwise
            angle -= angle_change;
            angle = fmod(angle, (2.0*M_PI));
        }
        index++;
    }

    printf("xmax = %f, ymax %f", x_max, y_max);
    char axis = 'x';
    double largest_overshoot = x_max - x_min; //assume diff between x is largest
    double y_dis = y_max - y_min;
    if(y_dis > largest_overshoot){
        largest_overshoot = y_dis;
        axis = 'y';
    }

    printf("largest = %f", largest_overshoot);

    //scale factor will be the max / width or height of the screen
    double scale_factor;
    if(axis == 'x'){
        scale_factor = swidth / largest_overshoot;
    }
    else if (axis == 'y'){
        scale_factor = sheight / largest_overshoot;
    }
    scale_factor = scale_factor*0.9;
    printf("scale = %f", scale_factor);
    //Update the turtle
    //Distance is 1.0, so this is basically just passing the scale_factor as the step!
    turtle->distance = turtle->distance * scale_factor;

    //The center of the figure will be the midpoint of the max/min values
    //Will be used in the translation step
    double mid_x = (x_max + x_min) / 2.0;
    double mid_y = (y_max + y_min) / 2.0;

    //need this to move the start point to the origin
    double change_x = 0.0 - mid_x;
    double change_y = 0.0 - mid_y;
    //this is the center of the screen
    double s_center_x = swidth / 2.0;
    double s_center_y = sheight/ 2.0;


    //calculate new start point, bring the start point down to the origin
    //Then scale by your scale_factor
    //Then translate back to the center of the screen
    double new_start_x = scale_factor* (turtle->startx + change_x) + s_center_x;
    double new_start_y = scale_factor* (turtle->starty + change_y) + s_center_y;

    //Update the turtle struct with the recalculated values for startx, starty
    turtle->startx = new_start_x;
    turtle->starty = new_start_y;

    //TODO test new start point
    G_rgb(1,1,1);
    G_fill_circle(new_start_x, new_start_y, 5);
    G_wait_key();
}

void test_turtle(){
    char array[] = {'f', '+', 'f', '+', 'f', 'f', '-', 'f'};
    double startx = 50;
    double starty = 50;
    double distance = 20;
    //test mine:
    struct Turtle_info info;
    info.startx = startx;
    info.starty = starty;
    info.distance = distance;
    auto_placer(array, &info);
    turtle(array, info.startx, info.starty, info.distance);
}

void test_davids(){
        char davids_array [1000000];
        scanf("%s", davids_array);
        printf("string length = %ld\n", strlen(davids_array));
        double startx = 100.0;
        double starty = 10.0;
        double distance = 1.0;
        //TODO test Davids
        struct Turtle_info adjusted;
        adjusted.startx = startx;
        adjusted.starty = starty;
        adjusted.distance = distance;
        auto_placer(davids_array, &adjusted);
        turtle(davids_array, adjusted.startx, adjusted.starty, distance);
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
        //make a new turtle struct that will get adjusted by auto placer
        struct Turtle_info adjusted;
        adjusted.startx = startx;
        adjusted.starty = starty;
        adjusted.distance = distance;
        //TODO test old start point
        G_rgb(1,0,0);
        G_fill_circle(adjusted.startx, adjusted.starty, 5);
        G_wait_key();

        auto_placer(instructions, &adjusted);
        //pass the values from the adjusted struct to the draw turtle

        turtle(instructions, adjusted.startx, adjusted.starty, adjusted.distance);
        free(instructions);

}

int main(){

    G_init_graphics (swidth,sheight) ;  // interactive graphics

    // clear the screen in a given color
    G_rgb (0.3, 0.3, 0.3) ; // dark gray
    G_clear () ;

    /* CODE HERE */
    //test_turtle();
    //test_davids();
    //test_builder();

    //TOOD make a nice background for the flower here, maybe a gradiant?
    draw_flower(400.0, 200.0, 1.0);


    // BEGIN SETDOWN
    int key ;
    key =  G_wait_key() ; // pause so user can see results

    //   G_save_image_to_file("demo.xwd") ;
    G_save_to_bmp_file("trees.bmp") ;

    return 0;
}