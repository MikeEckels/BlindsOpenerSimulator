#ifndef WINDOWS_HAL_H
#define WINDOWS_HAL_H

#include "HAL.h"
#include "Delay.h"

class WindowsHAL : public HAL {
	int main() override;
	void setup() override;
	void yield() override;

	void delaySec(float seconds) override;;
	void delayMicros(float micros) override;
	void delayMillis(float millis) override;

	unsigned char digitalRead(unsigned char pin) const override;
	void digitalWrite(unsigned char pin, unsigned char value) override;
};

#endif //WINDOWS_HAL_H
