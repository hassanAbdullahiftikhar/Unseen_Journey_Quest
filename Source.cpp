#include<iostream>
#include "Header.h"
#include<curses.h>
using namespace std;

int main() {
    initscr();         
    start_color();      
    init_pair(1, COLOR_GREEN, COLOR_BLACK);
    keypad(stdscr, TRUE);
    srand(time(0));
    game g1;            //game object
    g1.game_setup(15);  //initialize grid and other objects and start the game

    return 0;
}
