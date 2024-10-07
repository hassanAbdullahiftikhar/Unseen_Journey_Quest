#pragma once
#include<iostream>
#include<ctime>
#include<curses.h>
#include "data_struct.h"
using namespace std;
struct Node {
	Node* up, * down, * left, * right;
	char c;
	Node() {
		up = down = left = right = nullptr;
		c = '.';
	}
};
class object {
protected:
	int x, y, si;
public:
	object(int s) {
		x = rand()%(s-1);
		y = rand() % (s - 1);
		si = s;
	}
	void set_x(int i) {
		x = i;
	}
	void set_y(int i) {
		y = i;
	}
	int get_x() {
		return x;
	}
	int get_y() {
		return y;
	}
	virtual void place_object(Node *&f)=0;
	virtual ~object() {}
};
class player :public object {
	int score;
	bool key = false;
	bool t = false;
public:
	player(int s):object(s) {
		score = 0;
	}
	bool get_key() {
		return key;
	}
	void set_key_true() {
		key = true;
	}
	int& get_score() {
		return score;
	}
	void place_object(Node *&f) {
		Node* c = f;
		for (int i = 0; i < x; i++) {
			c = c->right;
		}
		for (int i = 0; i < y; i++) {
			c = c->down;
		}
		c->c = 'P';
	}
};
class key:public object {
public:
	key(int s):object(s){}
	void place_object(Node*& f) {
		Node* c = f;
		for (int i = 0; i < x; i++) {
			c = c->right;
		}
		for (int i = 0; i < y; i++) {
			c = c->down;
		}
		c->c = 'K';
	}
};
class door :public object {
public:
	door(int s) :object(s) {}
	void place_object(Node*& f) {
		Node* c = f;
		for (int i = 0; i < x; i++) {
			c = c->right;
		}
		for (int i = 0; i < y; i++) {
			c = c->down;
		}
		c->c = 'D';
	}
};
class bomb :public object {
public:
	bomb(int s):object(s){}
	void place_object(Node*& f) {
		Node* c = f;
		for (int i = 0; i < x; i++) {
			c = c->right;
		}
		for (int i = 0; i < y; i++) {
			c = c->down;
		}
		c->c = 'B';
	}
};
class Grid {
	Node* t_row=nullptr;
	int s;
	void initialize_grid() {
		//setting the first col. of each row
		Node* curr = t_row;
		for (int i = 0; i < s-1; i++) {
			curr->down = new Node();
			curr->down->up = curr;
			curr = curr->down;
		}
		//setting rest of grid
		curr = t_row;
		Node* row = t_row;
		for (int i = 0; i < s; i++) {
			for (int j = 0; j < s-1; j++) {
				curr->right = new Node();
				curr->right->left = curr;
				if (i != 0) {
					curr->right->up= curr->up->right;
					curr->up->right->down = curr->right;
				}
				curr = curr->right;
			}
			row = row->down;
			curr = row;
		}
	}
public:
	Grid(int s) {
		t_row = new Node();
		this->s = s;
		initialize_grid();
	}
	int get_size() {
		return s;
	}
	Node*& get_firstN() {
		return t_row;
	}
	void print_grid() {
		Node* row = t_row;
		int y = 1;
		while (row != nullptr) {
			Node* col = row;
			int x = 1;
			while (col != nullptr) {
				attron(COLOR_PAIR(1));
				mvprintw(y, x,"%c", col->c); // Print the character
				clrtoeol();
				col = col->right;
				x += 2; // Increment the x-coordinate for the next character
			}
			y++; // Increment the y-coordinate for the next row
			row = row->down;
		}
		for (int i = 0; i <  15 + 2;i++) {
			for (int j = 0; j < 2*15 + 2;j++) {
				if (i == 0 || i ==  s+1) {
					mvprintw(i, j, "#");
					if (i == s + 1) {
						clrtoeol();
					}
				}
				if (j == 0 || j ==  2*s + 1) {
					mvprintw(i, j, "#");
				}
			}
		}
		for (int i = 0; i < s + 2; i++) {
			for (int j = 2 * s + 2; j < 5000; j++) {
				mvaddch(i, j, ' ');
			}
		}
		refresh();
	}
};