#ifndef DELAY_H
#define DELAY_H

#include <Windows.h>

class Delay final {
public:
	Delay() = delete;

	static void delaySec(float seconds);
	static void delayMillis(float millis);
	static void delayMicros(float micros);

};

#endif //DELAY_H