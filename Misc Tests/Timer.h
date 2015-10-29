#pragma once

#include <chrono>

class Timer {
	Timer();
	long long getElapsedTime();
	long long getDeltaTime();
	void startDeltaChrono();
	void stopDeltaChrono();
};