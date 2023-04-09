#ifndef ENCODER_H
#define ENCODER_H

#include "Button.h"

enum EncoderDirection { NONE, LEFT, RIGHT };

class Encoder {
private:
	signed char position = 0;
	EncoderDirection direction = NONE;
	signed char incrementAmount = 1;

	Button encoderButton = Button();

public:
	Encoder() = default;
	~Encoder() = default;

	void Reset();
	void PressButton();
	void TurnLeft(unsigned char numClicks);
	void TurnRight(unsigned char numClicks);

	signed char GetPosition() const;
	EncoderDirection GetDirection() const;
	const char* GetDirectionStr() const;
	bool GetButtonState() const;
	
	bool ReadButtonState();
	void SetIncrement(signed char value);
	void SetPosition(signed char position);

};

#endif //ENCODER_H
