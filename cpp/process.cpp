#include "process.h"

Process::Process(int ttc, int mwt, int color = RED, Process* left, Process* right, Process* parent)
	: ttc(ttc), mwt(mwt), et(0), color(color), left(left), right(right), parent(parent) {}

Process::~Process() {}

int Process::PID = 0;