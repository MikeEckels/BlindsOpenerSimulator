#include "Encoder.h"

void Encoder::TurnLeft(unsigned char numClicks) {
	this->direction = LEFT;
	this->position = ((this->position - (this->incrementAmount * numClicks)) <= (signed char)-128) ? (signed char)-128 : (this->position - (this->incrementAmount * numClicks));
}

void Encoder::TurnRight(unsigned char numClicks) {
	this->direction = RIGHT;
	this->position = ((this->position + (this->incrementAmount * numClicks)) >= (signed char)127) ? (signed char)127 : (this->position + (this->incrementAmount * numClicks));
}

void Encoder::PressButton() {
	this->encoderButton.Press();
}

void Encoder::Reset() {
	this->position = 0;
	this->direction = NONE;
}

signed char Encoder::GetPosition() const {
	return this->position;
}

EncoderDirection Encoder::GetDirection() const {
	return this->direction;
}

const char* Encoder::GetDirectionStr() const {
	switch (Encoder::GetDirection()) {
	case NONE:
		return "N/A";
	case LEFT:
		return "Left";
	case RIGHT:
		return "Right";
	default:
		return "Unknown Direction";
	}
}

bool Encoder::GetButtonState() const {
	return this->encoderButton.GetState();
}

bool Encoder::ReadButtonState() {
	return this->encoderButton.ReadState();
}

void Encoder::SetIncrement(signed char value) {
	this->incrementAmount = (value >= (signed char)127) ? (signed char)127 : value;
}

void Encoder::SetPosition(signed char position) {
	signed char oldPos = this->position;
	this->position = (position >= (signed char)127) ? (signed char)127 : position;
	this->position = (position <= (signed char)-128) ? (signed char)-128 : position;
	this->direction = (position > oldPos) ? RIGHT : this->direction;
	this->direction = (position < oldPos) ? LEFT : this->direction;
}