#include "cfscheduler.h"
#include <iostream>

using std::cout;

Scheduler::Scheduler() {
	root = 0;
	NIL = new Process(-1,-1, BLACK);

	cout << "\n\n Scheduler started";
}

Process* Scheduler::getRoot() const {
	return root;
}

void Scheduler::leftRotate(Process* x) {

	Process* y = x->right;
	x->right = y->left;

	if (y->left != Scheduler::NIL)
		y->left->parent = x;

	if (x->parent == Scheduler::NIL)
		root = y;
	else if (x == x->parent->left)
		x->parent->left = y;
	else
		x->parent->right = y;

	y->parent = x->parent;
	x->parent = y;
	y->left = x;

	return;
}

void Scheduler::rightRotate(Process* x) {

	Process* y = x->left;
	x->left = y->right;

	if (y->right != Scheduler::NIL)
		y->right->parent = x;

	if (x->parent == Scheduler::NIL)
		root = y;
	else if (x == x->parent->left)
		x->parent->left = y;
	else
		x->parent->right = y;

	y->parent = x->parent;
	x->parent = y;
	y->right = x;

	return;
}

void Scheduler::insert(int ttc, int mwt) {

	Process* newProcess = new Process(ttc,mwt,RED, Scheduler::NIL, Scheduler::NIL, Scheduler::NIL);

	if (root) {
		Process* temp = root;
		Process* ptr = nullptr;

		while (temp != Scheduler::NIL) {
			ptr = temp;

			if (temp->ttc < ttc)
				temp = temp->right;
			else
				temp = temp->left;
		}

		if (ttc > ptr->ttc)
			ptr->right = newProcess;
		else
			ptr->left = newProcess;

		newProcess->parent = ptr;

		insertFixup(newProcess);
	}
	else {
		root = newProcess;
		root->color = BLACK;
	}

	return;
}

void Scheduler::insertFixup(Process* z) {


	while (z->parent->color == RED) {
		if (z->parent == z->parent->parent->left) {
			Process* y = z->parent->parent->right; 
			if (y->color == RED) {
				
				z->parent->color = BLACK;
				y->color = BLACK;
				z->parent->parent->color = RED;
				z = z->parent->parent;

			}
			else if (z == z->parent->right) {

				z = z->parent;
				leftRotate(z);

			}
			else {

				z->parent->color = BLACK;
				z->parent->parent->color = RED;
				rightRotate(z->parent->parent);

			}
		}
		else {
			Process* y = z->parent->parent->left; 

			if (y->color == RED) {

				z->parent->color = BLACK;
				y->color = BLACK;
				z->parent->parent->color = RED;
				z = z->parent->parent;
			}
			else if (z == z->parent->left) {
				
				z = z->parent;
				rightRotate(z);
			}
			else {

				z->parent->color = BLACK;
				z->parent->parent->color = RED;
				leftRotate(z->parent->parent);
			}
		}
	}

	root->color = BLACK;

	return;
}

Process* Scheduler::findProcess(int find) const {

	Process* temp = root;

	while (temp != Scheduler::NIL && temp->ttc != find){
		if (temp->ttc > find)
			temp = temp->left;
		else
			temp = temp->right;
	}

	return temp;
}

Process* Scheduler::getNextToExecute() {

	Process* temp = root;

	while (temp->left != Scheduler::NIL){
		temp = temp->left;
	}

	return deleteProcess(temp->ttc);
}

Process* Scheduler::successor(Process* z) const {

	if (z->right == Scheduler::NIL)
		return Scheduler::NIL;

	Process* temp = z->right;

	while (temp->left != Scheduler::NIL)
		temp = temp->left;

	return temp;
}

Process* Scheduler::deleteProcess(int data) {

	Process* z = findProcess(data);
	Process* nextToExecute = new Process(z->ttc, z->mwt, z->color);
	nextToExecute->pid = z->pid;

	if (z != Scheduler::NIL) {
		
		if (z == getRoot() && z->left == Scheduler::NIL && z->right == Scheduler::NIL) {
		
			root = nullptr;
			delete z;
			return nextToExecute;
		}


		Process *y, *x;

		if (z->left == Scheduler::NIL || z->right == Scheduler::NIL) {
			y = z;
		}
		else {
			y = successor(z);
		}

		if (y->left != Scheduler::NIL)
			x = y->left;
		else
			x = y->right;

		x->parent = y->parent;

		if (y->parent == Scheduler::NIL)
			root = x;
		else if (y == y->parent->left)
			y->parent->left = x;
		else
			y->parent->right = x;

		if (y != z)
			z->ttc = y->ttc;

		
		if (y->color == BLACK)
			deleteFixup(x);

		delete y; 
	}



	return nextToExecute;
}

void Scheduler::deleteFixup(Process* x) {

	while (x != root && x->color == BLACK) {
		if (x == x->parent->left) {
			Process* w = x->parent->right; 

			if (w->color == RED) {
				w->color = BLACK;
				x->parent->color = RED;
				leftRotate(x->parent);
				w = x->parent->right;
			}

			if (w->left->color == BLACK && w->right->color == BLACK) {
				w->color = RED;
				x = x->parent;
			}
			else if (w->right->color == BLACK) {
				w->left->color = BLACK;
				w->color = RED;
				rightRotate(w);
				w = x->parent->right;
			}
			else {
				w->color = x->parent->color;
				x->parent->color = BLACK;
				w->right->color = BLACK;
				leftRotate(x->parent);
				x = root;
			}
		}
		else {
			Process* w = x->parent->left; 

			if (w->color == RED) {
				w->color = BLACK;
				x->parent->color = RED;
				rightRotate(x->parent);
				w = x->parent->left;
			}

			if (w->right->color == BLACK && w->left->color == BLACK) { 
				w->color = RED;
				x = x->parent;
			}
			else if (w->left->color == BLACK) {
				w->right->color = BLACK;
				w->color = RED;
				leftRotate(w);
				w = x->parent->left;
			}
			else {
				w->color = x->parent->color;
				x->parent->color = BLACK;
				w->left->color = BLACK;
				rightRotate(x->parent);
				x = root;
			}
		}
	}

	x->color = BLACK;
}





bool Scheduler::search(int find) const {
	return findProcess(find) != Scheduler::NIL;
}

void Scheduler::processManager() const {
	if (getRoot() != nullptr)
		showActiveProcesses(getRoot());
	else cout << "Empty scheduler";
	return;
}

void Scheduler::showActiveProcesses(const Process* ptr, int space) const {

	if (!ptr)
		return;

	space++;

	showActiveProcesses(ptr->right, space);

	for (int i = 1; i < space; i++)
		std::cout << "	  ";

	if (ptr->color == RED)
		std::cout << "R " << ptr->ttc << "\n";
	else
		std::cout << "B " << ptr->ttc << "\n";

	showActiveProcesses(ptr->left, space);
}


void Scheduler::clear(Process* curr_ptr) {

	if (curr_ptr != Scheduler::NIL) {
		clear(curr_ptr->left);
		clear(curr_ptr->right);

		delete curr_ptr;
	}
	root = 0;
}

/* Not the most optimal version,
TODO : start executing next process when timeRemaining - TIME_SLICE < 0 
*/
void Scheduler::executeProcess() { 

	if (getRoot() != nullptr) {
		Process* leftmost = getNextToExecute();
		int timeRemaining = leftmost->ttc - TIME_SLICE;

		if (timeRemaining > 0) {
			insert(timeRemaining, leftmost->mwt);

		}
		else if (timeRemaining <= 0) {
			cout << "PID: " << leftmost->pid << " finished executing.";
		}
	}
	else cout << "Scheduler empty";

}

Scheduler::~Scheduler() {
	clear(getRoot());

	cout << "\n\n All processes have been terminated! ";
	cout << "\n\n Shutting scheduler down...";


}
