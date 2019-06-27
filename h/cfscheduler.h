#pragma once
#ifndef CFSCHEDULER_H
#define CFSCHEDULER_H

#include "process.h"

/*
When the scheduler is invoked to run a new process, the operation of the scheduler is as follows:

The leftmost node of the scheduling tree is chosen (as it will have the lowest spent execution time), and sent for execution.
If the process simply completes execution, it is removed from the system and scheduling tree.
If the process reaches its maximum execution time or is otherwise stopped (voluntarily or via interrupt) 
it is reinserted into the scheduling tree based on its new spent execution time.
The new leftmost node will then be selected from the tree, repeating the iteration.

*/


//time quanta for each process to run before context-change
#define TIME_SLICE 5

class Scheduler {
private:
	
	Process* root;
	Process* NIL;

	Process* getRoot() const;
	void leftRotate(Process*);
	void rightRotate(Process*);
	Process* successor(Process*) const;
	Process* findProcess(int) const;
	Process* getNextToExecute();

public:
	
	Scheduler();

	void insert(int,int);
	void insertFixup(Process*);
	Process* deleteProcess(int);
	void deleteFixup(Process*);

	bool search(int) const;
	void processManager() const;
	void showActiveProcesses(const Process*, int space = 0) const;
	void clear(Process*);

	void executeProcess();

	~Scheduler();
};

#endif

