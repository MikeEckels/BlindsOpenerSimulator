#ifndef STEPPER_DRIVER_H
#define STEPPER_DRIVER_H

#include <limits>
#include <functional>

enum MotorDirection {CCW, CW};
enum uSteps {EIGHT = 8, SIXTEEN = 16, THIRTY_TWO = 32, SIXTY_FOUR = 64};
typedef std::function<void()> Callback;

class StepperDriver {
private:
	bool enabled = false;
	MotorDirection direction = CW;
	uSteps microSteps = SIXTEEN;

	static void nullCallback() {};
	Callback stepCallback = nullCallback;

public:
	StepperDriver(uSteps microSteps);
	~StepperDriver() = default;

	void Step();
	void Enable();
	void Disable();
	void BindStepCallback(Callback callback);
	void UnbindStepCallback();

	void SetDirection(MotorDirection direction);

	MotorDirection GetDirection() const;
	uSteps GetMicroSteps() const;
	bool GetEnabledState() const;

};

#endif //STEPPER_DRIVER_H