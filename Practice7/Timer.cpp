#include "Timer.h"

	Timer::Timer() {
		startTime = clock();
		deltaStartTime = startTime;
		deltaTime = 0.0f;
	}
	double Timer::getElapsedTime() {
		clock_t now = clock();
		return double(now - startTime) / CLOCKS_PER_SEC;
	}
	double Timer::getDeltaTime() {
		return deltaTime;
	}
	void Timer::startDeltaChrono() {
		deltaStartTime = clock();
	}
	void Timer::stopDeltaChrono() {
		clock_t now = clock();
		deltaTime = float(now - deltaStartTime) / CLOCKS_PER_SEC;
	}
