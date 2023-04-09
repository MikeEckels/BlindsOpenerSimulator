#include "Button.h"

void Button::Press() {
	this->state = true;
}

bool Button::ReadState() {
	bool _state = Button::GetState();
	this->state = false;
	return _state;
}

bool Button::GetState() const {
	return this->state;
}