#include<iostream>
#include "Header.h"
#include<curses.h>
using namespace std;

int main() {
    initscr();          // Start curses mode
    start_color();      // Start color functionality
    init_pair(1, COLOR_GREEN, COLOR_BLACK);
    keypad(stdscr, TRUE); // Enable function keys and arrow keys
    srand(time(0));
    Grid g(10);
    g.print_grid();
    endwin();
    return 0;
}
