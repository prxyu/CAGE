#include "Timer.h"
#include "Types.h"

Timer::Timer() {

	QueryPerformanceFrequency(&freq);

	ZeroMemory(&start, sizeof(start));
	ZeroMemory(&end, sizeof(end));

	stopped = false;
}

void Timer::Start() {

	if (stopped) {
	
		llong elapsed = end.QuadPart - start.QuadPart;

		QueryPerformanceCounter(&start);
		start.QuadPart -= elapsed;

		stopped = false;
	}
	else {
		QueryPerformanceCounter(&start);
	}
}

void Timer::Stop() {

	if (!stopped) {
		QueryPerformanceCounter(&end);
		stopped = true;
	}

}

float Timer::Reset() {
	
	llong elapsed;

	if (stopped) {
		elapsed = end.QuadPart - start.QuadPart;

		QueryPerformanceCounter(&start);

		stopped = false;
	}
	else {

		QueryPerformanceCounter(&end);

		elapsed = end.QuadPart - start.QuadPart;

		start = end;
	}

	return float(elapsed / double(freq.QuadPart));
}

float Timer::Elapsed() {

	llong elapsed;

	if (stopped) {
		elapsed = end.QuadPart - start.QuadPart;
	}
	else {
		QueryPerformanceCounter(&end);

		elapsed = end.QuadPart - start.QuadPart;
	}

	return float(elapsed / double(freq.QuadPart));
}