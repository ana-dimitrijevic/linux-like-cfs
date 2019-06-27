#pragma once
#ifndef MENU_H
#define MENU_H

#include <iostream>
#include "cfscheduler.h"

using std::cin;
using std::cout;

int pid, ttc, mwt, data;
string props;

void menu(Scheduler& cfScheduler) {
	cout << "\n\n1.Create new process";
	cout << "\n2.Kill process";
	cout << "\n3.Execute process";
	cout << "\n4.Process manager";
	cout << "\n\nEnter your choice : ";
	int choice;
	std::cin >> choice;

	Process* new_tree_root;

	
	switch (choice) {
	case 1:
		cout << "\nEnter ttc : ";
		cin >> ttc;

		cout << "\nEnter mwt : ";
		cin >> mwt;

		cfScheduler.insert(ttc,mwt);
		cout << "New process successfully created!";

		break;

	case 2:
		cout << "\nEnter PID to be killed : ";
		cin >> pid;

		//cfScheduler.deleteProcessByPID(pid);
		cout << "Process successfully killed!";


		break;

	case 3:
		cfScheduler.executeProcess();
		break;

	case 4:
		cfScheduler.processManager();
		break;

	default:
		cout << "\nInvalid choice!";
		break;
	}

	return;
}

#endif
