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
		x = rand() % (s - 1);
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
	virtual void place_object(Node*& f) = 0;
	virtual ~object() {}
};
class player :public object {
	int score;
	stack h;
	bool key = false;
	bool t = false;
	int undo;
	int moves;
	int distance;
	bool left, right, up, down;
public:
	player(int s) :object(s) {
		score = 0;
		distance = 0;
		left = right = up = down = false;
	}
	bool& get_turn() {
		return t;
	}
	void set_undo(int i) {
		undo = i;
	}
	int& get_undo() {
		return undo;
	}
	void player_moves(int m) {
		moves = m;
	}
	int& get_moves() {
		return moves;
	}
	bool get_key() {
		return key;
	}
	void set_key_true() {
		key = true;
	}
	void set_d(int i) {
		distance = i;
	}
	int get_d() {
		return distance;
	}
	stack& get_Pstack() {
		return h;
	}
	int& get_score() {
		return score;
	}
	void place_object(Node*& f) {
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
struct bomb :public object {
	bomb* nextb;
public:
	bomb(int s) :object(s) {}
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
class key :public object {
public:
	key(int s) :object(s) {}
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
struct coin :public object {
	coin* nextc;
	void unique(key k, door d, player p,bomb b, Node*& f) {
		while ((k.get_x() == x && k.get_y() == y) || 
			(d.get_x() == x && d.get_y()==y) ||
			(p.get_x() == x && p.get_y()== y)||
			(b.get_x() == x && b.get_y() == y)) {
			x = rand() % (si - 1);
			y = rand() % (si - 1);
		}

	}
public:
	coin(int s, key k, door d, player p,bomb b, Node*& f) :object(s) {
		nextc = nullptr;
		unique(k, d, p, b,f);
	}
	void place_object(Node*& f) {
		Node* c = f;
		for (int i = 0; i < x; i++) {
			c = c->right;
		}
		for (int i = 0; i < y; i++) {
			c = c->down;
		}
		c->c = 'C';
	}
};
class Bmob_list {
	bomb* head;
	int c = 0;
	void initialize_list(int s,key k,player p) {
		srand(time(0));
		if (s == 10) {
			c = 3;
		}
		else if(s==15) {
			c = 4;
		}
		else {
			c = 5;
		}
		head = new bomb(s);
		while ((head->get_x() == k.get_x() && head->get_y() == k.get_y()) ||
			(head->get_x() == p.get_x() && head->get_y() == p.get_y())) {
			head->set_x(rand() % (s - 1));
			head->set_y(rand() % (s - 1));
		}

		bomb* cu = head;
		for (int i = 0; i < c-1; i++) {
			cu->nextb = new bomb(s);
			cu = cu->nextb;
			while ((cu->get_x() == k.get_x() && cu->get_y() == k.get_y()) ||
				(cu->get_x() == p.get_x() && cu->get_y() == p.get_y())) {
				cu->set_x(rand() % (s - 1));
				cu->set_y(rand() % (s - 1));
			}
		}
	}
public:
	Bmob_list(int s,key k,player p):head(nullptr){
		initialize_list(s,k,p);
	}
	void test() {
		mvprintw(19, 0,"%d",head->get_x( )>0? head->get_x() > 0:-999);
		mvprintw(19, 3, "%d", head->nextb->get_y() > 0 ? head->nextb->get_y() > 0:-999);
	}
	void populate(Node*&f) {
		bomb* cu = head;
		for (int i = 0; i < c; i++) {
			if (cu == nullptr) {
				break;
			}
			cu->place_object(f);
			cu = cu->nextb;
		}
	}
};
class coin_list {
	coin* h;
	int c = 0;
public:
	coin_list(int s, key k, door d, player p,bomb b, Node*& f) {
		if (s == 10) {
			c = 3;
		}
		else if (s == 15) {
			c = 5;
		}
		else if (s == 20) {
			c == 6;
		}
		h = new coin(s,k,d,p,b,f);
		coin* curr = h;
		for (int i = 1; i < c; i++) {
			curr->nextc = new coin(s, k, d, p,b, f);
			curr = curr->nextc;
		}
	}
	void rem_prev(Node*& f) {
		Node* g = f;
		Node* c = g;
		coin* cur = h;
		while (cur!=nullptr) {
			for (int i = 0; i < cur->get_x();i++) {
				c = c->right;
			}
			for (int i = 0; i < cur->get_y(); i++) {
				c = c->down;
			}
			c->c = '.';
			cur = cur->nextc;
		}
	}
	bool rem(int xp,int yp,Node*&f) {
		coin* cur = h;
		Node* g = f;
		while (cur != nullptr) {
			if (h->get_x() == xp && h->get_y() == yp) {
				for (int i = 0; i <= xp; i++) {
					g = g->right;
				}
				for (int i = 0; i <= yp; i++) {
					g = g->down;
				}
				g->c = '.';
				h = h->nextc;
				delete cur;
				return true;
			}
			else if (cur->nextc!=nullptr &&
				cur->nextc->get_x() == xp && cur->nextc->get_y() == yp) {
				coin* temp = cur->nextc;
				cur->nextc = cur->nextc->nextc;
				delete temp;
				return true;
			}
			cur = cur->nextc;
		}
		return false;
	}
	void update_c(int s,key k, door d, player p,bomb b, Node*& f) {
		coin* th = h;
		Node* cur = f;
		while (th != nullptr) {
			coin* temp = th;
			for (int i = 0; i < temp->get_x(); i++) {
				cur = cur->right;
			}
			for (int i = 0; i < temp->get_y(); i++) {
				cur = cur->down;
			}
			cur->c = '.';
			cur = f;
			th = th->nextc;
			delete temp;
		}
		h = new coin(s, k, d, p,b, f);
		coin* curr = h;
		for (int i = 1; i < c; i++) {
			curr->nextc = new coin(s, k, d, p, b,f);
			curr = curr->nextc;
		}
	}
	coin*& get_head() {
		return h;
	}
	void place_coins(Node*& f) {
		coin* cu = h;
		for (int i = 0; i < c; i++) {
			cu->place_object(f);
			cu = cu->nextc;
		}
	}
};
class Grid {
	Node* t_row = nullptr;
	int s;
	int pad;
	void initialize_grid() {
		//setting the first col. of each row
		Node* curr = t_row;
		for (int i = 0; i < s - 1; i++) {
			curr->down = new Node();
			curr->down->up = curr;
			curr = curr->down;
		}
		//setting rest of grid
		curr = t_row;
		Node* row = t_row;
		for (int i = 0; i < s; i++) {
			for (int j = 0; j < s - 1; j++) {
				curr->right = new Node();
				curr->right->left = curr;
				if (i != 0) {
					curr->right->up = curr->up->right;
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
	void update_grid(player k) {
		int x = k.get_x();
		int y = k.get_y();
		Node* curr = t_row;
		Node* r = t_row;
		for (int i = 0; i < s; i++) {
			for (int j = 0; j < s; j++) {
				if (curr->c == 'P') {
					curr->c = '.';
				}
				if (j == x && i == y) {
					curr->c = 'P';
				}
				curr = curr->right;
			}
			r = r->down;
			curr = r;
		}
		print_grid();
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
				if (col->c == 'C') {
					attron(COLOR_PAIR(2));
				}
				mvprintw(y, x, "%c", col->c); // Print the character
				attroff(COLOR_PAIR(2));
				clrtoeol();
				col = col->right;
				x += 2; // Increment the x-coordinate for the next character
			}
			y++; // Increment the y-coordinate for the next row
			row = row->down;
		}
		for (int i = 0; i < s + 2; i++) {
			for (int j = 0; j < 2 * s + 2; j++) {
				if (i == 0 || i == s + 1) {
					mvprintw(i, j, "#");
				}
				if (j == 0 || j == 2 * s + 1) {
					mvprintw(i, j, "#");
				}
			}
		}
		refresh();
	}
};
class game {
	Grid* h;
	player* p;
	key* k;
	bomb* b;
	door* d;
	coin_list* c;
	Bmob_list* bl;
	int pad = 0;
	bool hint = false, first_t = true;
	int t, ctime;
	int curr_d;
	int cal_d() {
		int e = 0, c = 0;
		e += k->get_x() - d->get_x();
		if (e < 0) {
			e *= -1;
		}
		c += k->get_y() - d->get_y();
		if (c < 0) {
			c *= -1;
		}
		int ex = 0;
		if (h->get_size() == 10) {
			ex = 6;
			p->set_undo(6);
		}
		else if (h->get_size() == 15) {
			ex = 2;
			p->set_undo(4);
		}
		else {
			p->set_undo(1);
		}
		return e + c + ex + 1;
	}
	void cal_manhattan() {//calculate manhattan distance between key or door
		int e = 0, c = 0;
		if (p->get_key() == false) {//calculate distance from key if not picked
			e += p->get_x() - k->get_x();
			if (e < 0) {
				e *= -1;
			}
			c += p->get_y() - k->get_y();
			if (c < 0) {
				c *= -1;
			}
			curr_d = c + e;
			if (p->get_d() == 0) {
				p->set_d(curr_d);
				p->player_moves(curr_d + cal_d());
			}
			if (curr_d <= p->get_d()) {
				hint = true;
				p->set_d(curr_d);
			}
			else {
				hint = false;
				p->set_d(curr_d);
			}
		}
		else {//calculate distance from door if key is picked
			e += p->get_x() - d->get_x();
			if (e < 0) {
				e *= -1;
			}
			c += p->get_y() - d->get_y();
			if (c < 0) {
				c *= -1;
			}
			curr_d = c + e;
			if (p->get_d() == 0) {
				p->set_d(curr_d);
			}
			if (curr_d <= p->get_d()) {
				hint = true;
				p->set_d(curr_d);
			}
			else {
				hint = false;
				p->set_d(curr_d);
			}
		}
	}
	void print_statements(Bmob_list *l) {
		mvprintw(h->get_size() + 2, 0 + pad, "Remaining moves:");
		mvprintw(h->get_size() + 2, 16 + pad, "%d", p->get_moves());
		mvprintw(h->get_size() + 2, 20 + pad, "Remaining undos:");
		mvprintw(h->get_size() + 2, 37 + pad, "%d", p->get_undo());
		mvprintw(h->get_size() + 2 + pad, 40, "Score:");
		mvprintw(h->get_size() + 2 + pad, 46, "%d", p->get_score());
		int counter = 20;
		location *g = p->get_Pstack().t();
		location* bn = g;
		coin* ct = c->get_head();
		while (ct != nullptr) {
			bl->test();
			mvprintw(counter, 0, "%d", ct->get_x());
			mvprintw(counter, 1, "%d", ct->get_y());
			ct = ct->nextc;
			counter++;
			//refresh();
		}
		if (p->get_key() == false) {
			mvprintw(h->get_size() + 3, 0 + pad, "Key Status: False");
		}
		else {
			mvprintw(h->get_size() + 3, 0 + pad, "Key Status: True");
		}
		if (first_t == false) {
			if (hint == true) {
				mvprintw(h->get_size() + 4, 1 + pad, "Hint:Getting closer");
			}
			else {
				mvprintw(h->get_size() + 4, 1 + pad, "Hint:Getting Farther");
			}
		}
	}
public:
	bool check_door() {//checking if player placement matches door placement, provided that key is picked
		if (p->get_key() == true) {
			int x1, x2, y1, y2;
			x1 = p->get_x(), y1 = p->get_y();
			x2 = d->get_x(), y2 = d->get_y();
			if (x1 == x2 && y1 == y2) {
				return true;
			}
			return false;
		}
		return false;
	}
	bool check_bomb() {//checking if player placement matches bomb placement
		int x1, x2, y1, y2;
		x1 = p->get_x(), y1 = p->get_y();
		x2 = b->get_x(), y2 = b->get_y();
		if (x1 == x2 && y1 == y2) {
			return true;
		}
		return false;
	}
	bool check_key() {//checking if player placement matches key placement
		int x1, x2, y1, y2;
		x1 = p->get_x(), y1 = p->get_y();
		x2 = k->get_x(), y2 = k->get_y();
		if (x1 == x2 && y1 == y2) {
			p->set_key_true();
			p->set_d(0);
			first_t = true;
			return true;
		}
		return false;
	}
public:
	void game_setup(int s) {
		h = new Grid(s);
		p = new player(s);
		k = new key(s);
		b = new bomb(s);
		d = new door(s);
		c = new coin_list(s,*k,*d,*p,*b,h->get_firstN());
		bl = new Bmob_list(s,*k,*p);
		t = 15;
		ctime = time(0);
		srand((time(0)));
		p->place_object(h->get_firstN());//placing player
		p->get_turn() = true;
		k->place_object(h->get_firstN());//placing key
		d->place_object(h->get_firstN());//placing door
		c->place_coins(h->get_firstN());
		bl->populate(h->get_firstN());
		h->print_grid();//printing grid on terminal
		print_statements(bl);
		while (true) { // Press 'q' to quit
			int ch = getch();
			if (time(0) - ctime >= t) {//reassign coins 
				ctime = time(0);
				refresh();
				c->update_c(s, *k, *d, *p, *b,h->get_firstN());
				c->place_coins(h->get_firstN());
			}
			h->update_grid(*p); // Update the grid based on the player's position
			switch (ch) {
			case KEY_UP:
				if (p->get_y() > 0) {
					int xp1 = -99, xp2 = -99;
					if (p->get_Pstack().t() != nullptr) {
						xp1 = p->get_Pstack().t()->x;
						xp2 = p->get_Pstack().t()->y;
					}
					if (!(xp1 == p->get_x() && xp2 == p->get_y() - 1)) {
						p->set_y(p->get_y() - 1); // Move up
						p->get_Pstack().insert(p->get_x(), p->get_y()+1);
						first_t = false;
						cal_manhattan();
						p->get_moves() -= 1;
					}
					break;
				}
				else {
					break;
				}
			case KEY_DOWN:
				if (p->get_y() < s - 1) {
					int xp1 = -99, xp2 = -99;
					if (p->get_Pstack().t() != nullptr) {
						xp1 = p->get_Pstack().t()->x;
						xp2 = p->get_Pstack().t()->y;
					}
					if (!(xp1 == p->get_x() && xp2 == p->get_y() + 1)) {
						p->set_y(p->get_y() + 1);// Move down
						p->get_Pstack().insert(p->get_x(), p->get_y()-1);
						first_t = false;
						cal_manhattan();
						p->get_moves() -= 1;
					}
					break;
				}
				else {
					break;
				}
			case KEY_LEFT:
				if (p->get_x() > 0) {
					int xp1 = -99, xp2 = -99;
					if (p->get_Pstack().t() != nullptr) {
						xp1 = p->get_Pstack().t()->x;
						xp2 = p->get_Pstack().t()->y;
					}
					if (!(xp1 == p->get_x() - 1 && xp2 == p->get_y())) {
						p->set_x(p->get_x() - 1); // Move left
						p->get_Pstack().insert(p->get_x()+1, p->get_y());
						first_t = false;
						cal_manhattan();
						p->get_moves() -= 1;
					}
					break;
				}
				else {
					break;
				}
			case KEY_RIGHT:
				if (p->get_x() < s - 1) {
					int xp1 = -99, xp2 = -99;
					if (p->get_Pstack().t() != nullptr) {
						xp1 = p->get_Pstack().t()->x;
						xp2 = p->get_Pstack().t()->y;
					}
					if (!(xp1 == p->get_x() + 1 && xp2 == p->get_y())) {
						p->set_x(p->get_x() + 1); // Move right
						p->get_Pstack().insert(p->get_x()-1, p->get_y());
						first_t = false;
						cal_manhattan();
						p->get_moves() -= 1;
					}
					break;
				}
				else {
					break;
				}
			case ' ':
				if (p->get_undo() > 0) {
					location* s = p->get_Pstack().t(); // Get the new top
					if (s != nullptr) { // undo move
						int nx = p->get_Pstack().t()->x;
						int ny = p->get_Pstack().t()->y;
						p->get_Pstack().pop(); // Remove the last position
						p->set_x(nx);
						p->set_y(ny);
						p->get_undo() -= 1;
						cal_manhattan();
					}
					break;
				}
			}
			/*if (p->get_moves() <= 0) {
				break;
			}*/
			if (check_bomb()) {
				break;
			}
			if (check_key()) {
				delete k;
				cout << "Key picked";
			}
			if (check_door()) {
				cout << "You won!!";
				break;
			}
			// Clear and redraw the grid with the updated player position
			clear();
			if (c->rem(p->get_x(), p->get_y(),h->get_firstN())==true) {
				p->get_undo() += 1;
			}
			h->update_grid(*p);
			h->print_grid();
			print_statements(bl);
		}

	}
};
