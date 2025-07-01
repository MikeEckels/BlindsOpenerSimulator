#include "GUI.h"
#include "Platforms.h"

GUI gui = GUI(1280, 720, "Blinds Simulator", Theme::DARK);

int main() {
	gui.Init();

	while (gui.Update()) {}
	return 0;
}