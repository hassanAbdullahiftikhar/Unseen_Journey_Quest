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
    Grid g(10);
    player p(10);
    key k(10);
    door d(10);
    p.place_object(g.get_firstN());
    k.place_object(g.get_firstN());
    d.place_object(g.get_firstN());
    g.print_grid();
    getch();

    endwin();           
    return 0;
}
