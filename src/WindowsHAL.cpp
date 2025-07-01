#include "WindowsHAL.h"

int WindowsHAL::main() {
	return 0;
}

void WindowsHAL::setup() {

}

void WindowsHAL::yield() {
	//Do nothing
}

void WindowsHAL::delaySec(float seconds) {
	Delay::delaySec(seconds);
}

void WindowsHAL::delayMicros(float micros) {
	Delay::delayMicros(micros);
}

void WindowsHAL::delayMillis(float millis) {
	Delay::delayMillis(millis);
}

unsigned char WindowsHAL::digitalRead(unsigned char pin) const {
	return 0;
}

void WindowsHAL::digitalWrite(unsigned char pin, unsigned char value) {

}