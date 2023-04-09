#include "Delay.h"

void Delay::delaySec(float seconds) {
	long long timeStart;
	long long timeDelta;
	long long timeEllapsed;

	QueryPerformanceFrequency((LARGE_INTEGER*)(&timeDelta));
	QueryPerformanceCounter((LARGE_INTEGER*)(&timeStart));
	long long timeToWait = (long long)((double)timeDelta * (double)seconds);
	timeEllapsed = timeStart;

	while ((timeEllapsed - timeStart) < timeToWait) {
		QueryPerformanceCounter((LARGE_INTEGER*)(&timeEllapsed));
	}
}

void Delay::delayMillis(float millis) {
	long long timeStart;
	long long timeDelta;
	long long timeEllapsed;

	QueryPerformanceFrequency((LARGE_INTEGER*)(&timeDelta));
	long long timeToWait = (long long)((double)timeDelta * (double)millis / 1000.0f);
	QueryPerformanceCounter((LARGE_INTEGER*)(&timeStart));
	timeEllapsed = timeStart;

	while ((timeEllapsed - timeStart) < timeToWait) {
		QueryPerformanceCounter((LARGE_INTEGER*)(&timeEllapsed));
	}
}

void Delay::delayMicros(float micros) {
	long long timeStart;
	long long timeDelta;
	long long timeEllapsed;

	QueryPerformanceFrequency((LARGE_INTEGER*)(&timeDelta));
	long long timeToWait = (long long)((double)timeDelta * (double)micros / 1000000.0f);
	QueryPerformanceCounter((LARGE_INTEGER*)(&timeStart));
	timeEllapsed = timeStart;

	while ((timeEllapsed - timeStart) < timeToWait) {
		QueryPerformanceCounter((LARGE_INTEGER*)(&timeEllapsed));
	}
}
