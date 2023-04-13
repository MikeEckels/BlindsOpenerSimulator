#include <conio.h>
#include <iostream>

#include "Blinds.h"

Button button = Button();
Blinds blinds = Blinds();

int main() {
	blinds.SetVelocityTarget(SLIDER, LINEAR_MM_SEC, 200.0f);
	blinds.SetVelocityTarget(ROTATOR, ANGULAR_RPM, 10.0f);
	char key = ' ';

	while (key != 'e') {
		key = _getch();

		switch (key) {
		case 'w':
			blinds.Open();
			std::cout << "SliderPositionMM: " << blinds.GetDistanceMM() << std::endl << std::endl;
			break;
		case 's':
			blinds.Close();
			std::cout << "SliderPositionMM: " << blinds.GetDistanceMM() << std::endl << std::endl;
			break;
		case 'd':
			blinds.OpenShades();
			std::cout << std::endl;
			break;
		case 'a':
			blinds.CloseShades();
			std::cout << std::endl;
			break;
		case 'b':
			button.Press();
			break;
		case 'l':
			blinds.TurnEncoderLeft(1);
			break;
		case 'r':
			blinds.TurnEncoderRight(1);
			break;
		default:
			std::cout << "[!] Unrecognized command" << std::endl;
		}

		if (button.ReadState()) {
			blinds.GetState() ? blinds.Close() : blinds.Open();
			std::cout << "SliderPositionMM: " << blinds.GetDistanceMM() << std::endl << std::endl;
		}
	}
}