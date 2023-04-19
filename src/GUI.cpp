#include "GUI.h"

GUI::GUI(const char* windowName, Theme::Colors colors) {
	this->colors = colors;
	this->useMaxscreen = true;
	this->windowName = windowName;
}

GUI::GUI(int windowWidth, int windowHeight, const char* windowName, Theme::Colors colors) {
	this->colors = colors;
	this->windowName = windowName;
	this->windowWidth = windowWidth;
	this->windowHeight = windowHeight;
}

void GUI::InitGLFW(int major, int minor) {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, major);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minor);

	if (this->useMaxscreen) { GUI::SetMaxScreenSize(); }

	this->window = glfwCreateWindow(this->windowWidth, this->windowHeight, this->windowName, nullptr, nullptr);
	if (this->window == nullptr) { glfwTerminate(); }

	glfwMakeContextCurrent(this->window);
}

void GUI::SetMaxScreenSize() {
	const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
	this->windowWidth = mode->width - 1;
	this->windowHeight = mode->height - 1;
}

void GUI::InitImGui(const char* OpenGLSLVersion) {
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();

	this->windowIO = &ImGui::GetIO();
	this->windowIO->ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

	switch (this->colors) {
	case Theme::DARK:
		ImGui::StyleColorsDark();
		break;
	case Theme::LIGHT:
		ImGui::StyleColorsLight();
		break;
	case Theme::CLASSIC:
		ImGui::StyleColorsClassic();
		break;
	default:
		ImGui::StyleColorsDark();
	}
	
	ImGui_ImplOpenGL3_Init(OpenGLSLVersion);
	ImGui_ImplGlfw_InitForOpenGL(this->window, true);
	this->viewport = ImGui::GetMainViewport();
}

void GUI::Init(Blinds* blinds) {
	GUI::InitGLFW(3, 3);
	GUI::InitImGui("#version 330");
	this->blinds = blinds;
}

int GUI::Update() {
	if (!glfwWindowShouldClose(this->window)) {
		glfwPollEvents();

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
		ImGui::SetNextWindowPos(this->viewport->WorkPos);
		ImGui::SetNextWindowSize(this->viewport->WorkSize);

		ImGui::Begin(this->windowName, nullptr, this->windowFlags);
		if (ImGui::Button("Open Blinds")) { this->blinds->Open(); };
		ImGui::SameLine();
		if (ImGui::Button("Close Blidns")) { this->blinds->Close(); };
		ImGui::SameLine();
		ImGui::Button("Encoder Button");
		if (ImGui::Button("Open Shades")) { this->blinds->OpenShades(); };
		ImGui::SameLine();
		if (ImGui::Button("Close Shades")) { this->blinds->CloseShades(); };

		ImGui::SameLine();
		static int counter = 0;
		float spacing = ImGui::GetStyle().ItemInnerSpacing.x;
		ImGui::PushButtonRepeat(true);
		if (ImGui::ArrowButton("##left", ImGuiDir_Left)) { counter -= 25; }
		ImGui::SameLine(0.0f, spacing);
		if (ImGui::ArrowButton("##right", ImGuiDir_Right)) { counter += 25; }
		ImGui::PopButtonRepeat();
		ImGui::SameLine();
		ImGui::Text("%d", counter);
		
		ImGui::ShowDemoWindow();
		ImGui::NewLine();
		ImGui::Text("Blinds Position mm - %d", this->blinds->GetMaxDistanceMM());
		this->dist = this->blinds->GetDistanceMM();
		ImGui::SliderInt(" ", &this->dist, 0, this->blinds->GetMaxDistanceMM());
		ImGui::BeginDisabled();
		ImGui::Text("Shades Position deg");
		ImGui::SliderAngle(" ", (float*) & this->dist);
		ImGui::EndDisabled();
		ImGui::End();

		ImGui::Render();
		glViewport(0, 0, this->windowWidth, this->windowHeight);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		glfwSwapBuffers(this->window);
	}
	else {
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();

		glfwDestroyWindow(this->window);
		glfwTerminate();
		return 0;
	}

}