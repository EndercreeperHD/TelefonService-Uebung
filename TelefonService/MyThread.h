#pragma once
#include "Thread.h"
class MyThread : public Thread
{
public:
	void run() override {
		cout << "HS\n";
	};
};

