#include<iostream>
#include "Header.h"
#include<curses.h>
using namespace std;

int main() {
    int mode;
    cout << "1.Easy(10*10 grid)\n";
    cout << "2.Medium(15*15 grid)\n";
    cout << "3.Hard(20*20 grid)\n";
    cin >> mode;
    if (mode == 1) {
        mode = 10;
    }
    else if (mode == 2) {
        mode = 15;
    }
    else {
        mode = 20;
    }
    initscr();          // Start curses mode
    start_color();      // Start color functionality
    init_pair(1, COLOR_GREEN, COLOR_BLACK);
    init_pair(2, COLOR_YELLOW, COLOR_BLACK);
    init_pair(3, COLOR_RED, COLOR_BLACK);
    keypad(stdscr, TRUE); // Enable function keys and arrow keys
    srand(time(0));
    game g1;            //Game object
    g1.game_setup(mode);  //Initialize grid and other objects,start the game

    return 0;
}
