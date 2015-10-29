#include "Timer.h"

class Timer {
private:
	std::chrono::high_resolution_clock::time_point startTime;
	std::chrono::high_resolution_clock::time_point deltaStartTime;
	std::chrono::nanoseconds deltaTime;

public:
	Timer() {
		startTime = std::chrono::high_resolution_clock::now();
		deltaStartTime = startTime;
	}

	long long getElapsedTime() {
		std::chrono::high_resolution_clock::time_point now = std::chrono::high_resolution_clock::now();
		std::chrono::nanoseconds ns = std::chrono::duration_cast<std::chrono::nanoseconds>(now - startTime);
		return ns.count();
	}

	long long getDeltaTime() {
		return deltaTime.count();
	}

	void startDeltaChrono() {
		deltaStartTime = std::chrono::high_resolution_clock::now();
	}

	void stopDeltaChrono() {
		std::chrono::high_resolution_clock::time_point now = std::chrono::high_resolution_clock::now();
		deltaTime = std::chrono::duration_cast<std::chrono::nanoseconds>(now - deltaStartTime);
	}
};