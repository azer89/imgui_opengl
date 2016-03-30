

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

	void InitializeGL();
	
	void ShowWindow();

private:

	static void error_callback(int error, const char* description);
	static void cursor_enters_window_callBack(GLFWwindow *window, int entered);
	static void mouse_move_callBack(GLFWwindow *window, double xPos, double yPos);
	static void mouse_button_callBack(GLFWwindow * window, int button, int actions, int mods);
	static void mouse_scroll_callBack(GLFWwindow * window, double xOffSet, double yOffSet);
	static void window_resize_callBack(GLFWwindow * window, int width, int height);
	static void key_input_callBack(GLFWwindow* window, int key, int scancode, int action, int mods);

private:
	GLFWwindow* _window;
};

#endif