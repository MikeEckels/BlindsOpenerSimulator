#ifndef HAL_H
#define HAL_H

class HAL {
public:
	HAL() = default;
	virtual ~HAL() = default;

	virtual int main() = 0;
	virtual void setup() = 0;
	virtual void yield() = 0;

	virtual void delaySec(float seconds) = 0;
	virtual void delayMicros(float micros) = 0;
	virtual void delayMillis(float millis) = 0;

	virtual unsigned char digitalRead(unsigned char pin) const = 0;
	virtual void digitalWrite(unsigned char pin, unsigned char value) = 0;
	
};

#endif //HAL_H
