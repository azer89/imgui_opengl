

#ifndef AWESOME_WINDOW_H
#define AWESOME_WINDOW_H

/**
* This code is heavily inspired by the skeleton code given in CS488 Winter 2016 at U Waterloo
*
* Reza Adhitya Saputra
* reza.adhitya.saputra@gmail.com
*/

#include <imgui.h>
#include "imgui_impl_glfw_gl3.h"
#include <GL/gl3w.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <memory>
//#include <stdio.h>

// forward declaration
class MyShader;

class AwesomeWindow
{
private:
	AwesomeWindow();

public:	
	~AwesomeWindow();

	void InitializeGL();	
	void ShowWindow();

public:
	static std::shared_ptr<AwesomeWindow> GetInstance();

private:
	void BuildStuff();

private:
	void cursorEnterWindowEvent(int entered);
	void mouseMoveEvent(double xPos, double yPos);
	void mouseButtonInputEvent(int button, int actions, int mods);
	void mouseScrollEvent(double xOffSet, double yOffSet);
	void windowResizeEvent(int width, int height);
	void keyInputEvent(int key, int action, int mods);

	static void error_callback(int error, const char* description);

	// Documentation: http://www.glfw.org/docs/latest/group__input.html
	static void cursor_enters_window_callBack(GLFWwindow *window, int entered);
	static void mouse_move_callBack(          GLFWwindow *window, double xPos, double yPos);
	static void mouse_button_callBack(        GLFWwindow *window, int button, int actions, int mods);
	static void mouse_scroll_callBack(        GLFWwindow *window, double xOffSet, double yOffSet);
	static void window_resize_callBack(       GLFWwindow *window, int width, int height);
	static void key_input_callBack(           GLFWwindow *window, int key, int scancode, int action, int mods);

private:
	GLFWwindow* _window;
	
	// Why do we have a static instance?
	// Becaus ethe callback functions (mouse events, key press events, and whatnot) are static !!!
	static std::shared_ptr<AwesomeWindow> _static_instance;

	MyShader* _myShader;
	GLuint _vbo;
	GLuint _vao;

	// Locations
	GLuint _mvpMatrixLocation;
	GLuint _colorLocation;
	GLuint _vertexLocation;
	GLuint _use_color_location;

};

#endif