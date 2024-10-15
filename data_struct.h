#pragma once

struct location {
	int x, y;
	location* next;
	location(int c1, int c2) :x(c1), y(c2) {
		next = nullptr;
	}
};
class stack {
	location* top;
public:
	stack() {
		top = nullptr;
	}
	void insert(int x, int y) {
		if (top == nullptr) {
			top = new location(x, y);
		}
		else {
			location* curr = new location(x, y);
			curr->next = top;
			top = curr;
		}
	}
	bool is_empty() {
		return top == nullptr;
	}
	location*& t() {
		return top;
	}
	void pop() {
		if (top != nullptr) {
			if (top->next == nullptr) {
				location* curr = top;
				delete curr;
				top = nullptr;
			}
			else {
				location* curr = top;
				top = top->next;
				delete curr;
			}
		}
	}
};
class coin_queue {
	location* first=nullptr;
	location* tail = nullptr;
public:
	int nn = 0;
	coin_queue() {
		first = nullptr;
		tail = nullptr;
	}
	void enque(int x,int y) {
		if (first == nullptr) {
			first = new location(x, y);
			tail = first;
			first->next = nullptr;
		}
		else {
			location* cu = tail;
			location* n = new location(x, y);
			cu->next = n;
			tail = n;
		}
		nn++;
	}
	void print(int r) {
		location* cu = first;
		mvprintw(r+3,0,"Coins collected:");
		int row = r+4;
		for (int i = 0; i < nn; i++) {
			mvprintw(row+i, 0, "(");
			mvprintw(row+i, 1, "%d", cu->y);
			mvprintw(row+i, 3, "%d", cu->x);
			mvprintw(row+i, 5, ")");
			cu = cu->next;
		}
	}
};
