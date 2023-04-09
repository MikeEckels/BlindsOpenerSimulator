#ifndef BUTTON_H
#define BUTTON_H

class Button {
private:
	bool state = false;

public:
	Button() = default;
	~Button() = default;

	void Press();

	bool ReadState();
	bool GetState() const;

};

#endif //BUTTON_H