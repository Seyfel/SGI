#pragma once

#include <ctime>

class Timer {
private:
	clock_t startTime;
	clock_t deltaStartTime;
	double deltaTime;
public:
	Timer();
	double getElapsedTime();
	double getDeltaTime();
	void startDeltaChrono();
	void stopDeltaChrono();
};