/* To run: cc  turtle.c   -lm  -lX11 */

#include  "FPToolkit.c"
#include <stdio.h>
#include <math.h>
#include <string.h>

const int RULE_MAX = 100;
const int RULE_NUM = 30; //up to 30 rules in any grammar
const int INSTRUCTIONS_MAX = 1000000;

struct Point {
    double x, y;
};

struct Rule {
    char var;
    char rule [100];
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


    //General Algorithm:
    //Write some rules
    //the initial array needs to hold the "axiom", so start by loading that in to the array
    //Now parse the array left to right
    //When we see the axiom, replace it with what that variable's rule goes too
    //Continue to do this, left to right parsing, until you reach some max depth
    //non-terminals get added back in without being changed
int builder(struct Grammar rules, int depth, char* instructions){
    //build the first string
    instructions[0] = '\0';
    char axiom[1];
    axiom[0] = rules.axiom;
    strcpy(instructions, axiom);

    //parse the string repeatedly
    int count = 0;
    //this loop controls how many times we replace instruction variables with rules
    while (count < depth){
        //start at the first index of the instructions
        //match the character found in each index, to a rule
        int length = strlen(instructions);
        int index = 0;
        //make temp to hold all strings that need to be concatenated
        //this is  a 2-d array, of rules (char arrays)
        char temp[strlen(instructions)][RULE_MAX];
        //for each index, find out what should go in that position, and add to the array of temp strings
        while (index < length){
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
                printf("Rule found to replace %c: %s\n ", instructions[index], replace);
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
        //length of instructions should be the same as length of temp now
        while (index < length){
            strcat(concatenated, temp[index]);
            index++;
        }
        //copy concatenated into instructions
        strcpy(instructions, concatenated);
        printf("At depth %d, instruc: %s\n", count, instructions);
        count++;
    }
    //if successful, return 0
    return 0;
}

//Test string builder
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

void test_turtle(){
    char array[] = {'f', '+', 'f', '+', 'f', 'f', '-', 'f'};
    double startx = 200;
    double starty = 200;
    double distance = 5;
    //test mine:
    turtle(array, startx, starty, distance);
}

void test_davids(){
        char davids_array [1000000];
        scanf("%s", davids_array);
        printf("string length = %ld\n", strlen(davids_array));
        double startx = 100;
        double starty = 10;
        double distance = 1;
        //TODO test Davids
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
                printf("%c", instructions[index]);
                index++;
            }
        }
        else{
            printf("Invalid input");
        }

        turtle(instructions, startx, starty, distance);
        free(instructions);

}

int main(){

    int swidth, sheight ;

    swidth = 800 ;  sheight = 800 ;
    G_init_graphics (swidth,sheight) ;  // interactive graphics

    // clear the screen in a given color
    G_rgb (0.3, 0.3, 0.3) ; // dark gray
    G_clear () ;

    /* CODE HERE */
    //test_turtle();
    //test_davids();
    //test_builder();
    draw_flower(200, 200, 10);
    draw_flower(400, 400, 20);

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

    // BEGIN SETDOWN
    int key ;
    key =  G_wait_key() ; // pause so user can see results

    //   G_save_image_to_file("demo.xwd") ;
    G_save_to_bmp_file("trees.bmp") ;

    return 0;
}