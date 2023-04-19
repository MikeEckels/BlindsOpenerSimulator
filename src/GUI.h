#ifndef GUI_H
#define GUI_H

#include <glfw/glfw3.h>

#include "Blinds.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

namespace Theme {
	enum Colors { DARK, LIGHT, CLASSIC };
}

class GUI {
private:
	int dist = 0;
	int windowWidth = 0;
	int windowHeight = 0;
	bool useMaxscreen = false;
	Theme::Colors colors = Theme::DARK;
	const char* windowName = "Default Name";
	
	ImGuiIO* windowIO = nullptr;
	GLFWwindow* window = nullptr;
	const ImGuiViewport* viewport = nullptr;
	ImGuiWindowFlags windowFlags = ImGuiWindowFlags_NoMove |
								   ImGuiWindowFlags_NoDecoration |
								   ImGuiWindowFlags_NoSavedSettings;

	Blinds* blinds = nullptr;

	void InitGLFW(int major, int minor);
	void InitImGui(const char* OpenGLSLVersion);
	void SetMaxScreenSize();

public:
	GUI(const char* windowName, Theme::Colors colors);
	GUI(int windowWidth, int windowHeight, const char* windowName, Theme::Colors colors);
	~GUI() = default;

	void Init(Blinds* blinds);
	int Update();

};

#endif //GUI_H
