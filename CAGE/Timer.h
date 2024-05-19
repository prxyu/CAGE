#ifndef _CAGE_TIMER_H_
#define _CAGE_TIMER_H_

#include <Windows.h>

class Timer {
private:
	LARGE_INTEGER start, end, freq;
	bool stopped;

public:
	Timer();

	void Start();
	void Stop();
	float Reset();
	float Elapsed();
	bool Elapsed(float secs);
};


inline bool Timer::Elapsed(float secs) {
	return (Elapsed() >= secs ? true : false);
}
#endif