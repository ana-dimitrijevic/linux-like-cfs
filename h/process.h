#pragma once
#ifndef PROCESS_H
#define PROCESS_H

#define RED 1
#define BLACK 0

#include <string>

using std::string;
using std::to_string;

/*

The nodes are indexed by processor "execution time" in nanoseconds.

A "maximum execution time" is also calculated for each process. 
This time is based upon the idea that an "ideal processor" would equally share processing power amongst all processes. 
Thus, the maximum execution time is the time the process has been waiting to run, 
divided by the total number of processes, or in other words, 
the maximum execution time is the time the process would have expected to run on an "ideal processor".

*/

class Process
{

private:
	//time to complete
	int ttc;
	//maximum waiting time
	int mwt;
	//execution time
	int et;
	//unique process identificator
	int pid=PID++;
	static int PID;

	int color;
	Process *left, *right, *parent;

	friend class Scheduler;

public:
	Process(int, int, int,Process *left = 0, Process *right = 0, Process *parent = 0);
	~Process();
};

#endif

