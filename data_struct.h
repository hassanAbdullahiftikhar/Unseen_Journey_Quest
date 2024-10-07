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
