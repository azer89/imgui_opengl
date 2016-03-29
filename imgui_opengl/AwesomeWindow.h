

#ifndef AWESOME_WINDOW_H
#define AWESOME_WINDOW_H

#include <imgui.h>
#include "imgui_impl_glfw_gl3.h"
#include <stdio.h>
#include <GL/gl3w.h>
#include <GLFW/glfw3.h>

class AwesomeWindow
{
public:
	AwesomeWindow();
	~AwesomeWindow();

	void Show();

private:
	GLFWwindow* _window;
};

#endif