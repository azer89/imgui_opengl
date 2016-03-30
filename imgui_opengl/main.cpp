// ImGui - standalone example application for Glfw + OpenGL 3, using programmable pipeline
// If you are new to ImGui, see examples/README.txt and documentation at the top of imgui.cpp.

/*
#include <imgui.h>
#include "imgui_impl_glfw_gl3.h"
#include <stdio.h>
#include <GL/gl3w.h>
#include <GLFW/glfw3.h>
*/

/*
static void error_callback(int error, const char* description)
{
    fprintf(stderr, "Error %d: %s\n", error, description);
}
*/

#include "AwesomeWindow.h"

int main(int, char**)
{
	AwesomeWindow* window = new AwesomeWindow();

	window->ShowWindow();

	delete window;

    return 0;
}
