
#include "AwesomeWindow.h"
#include <iostream>

#include <imgui.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/io.hpp>

#include "MyShader.h"

/**
 * This code is heavily inspired by the skeleton code given in CS488 Winter 2016 at U Waterloo
 *
 * Reza Adhitya Saputra
 * reza.adhitya.saputra@gmail.com
 */

std::shared_ptr<AwesomeWindow> AwesomeWindow::_static_instance = nullptr;


AwesomeWindow::AwesomeWindow() : _myShader(0)
{
}

AwesomeWindow::~AwesomeWindow()
{
	//if (_window) { delete _window; }
	if (_myShader) { delete _myShader; }
}

std::shared_ptr<AwesomeWindow> AwesomeWindow::GetInstance()
{
	if (_static_instance == nullptr)
		{ _static_instance = std::shared_ptr<AwesomeWindow>(new AwesomeWindow()); }
	return _static_instance;
}

void AwesomeWindow::InitializeGL()
{
	std::cout << "InitializeGL\n";

	/* Stuff I forget what their purposes are */
	//glShadeModel(GL_SMOOTH); // error ?
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glEnable(GL_DEPTH_TEST);

	ImVec4 clear_color = ImColor(114, 144, 154);
	glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);

	// shader-related
	_myShader = new MyShader();
	_myShader->Initialize("D:\\Code\\imgui_opengl\\imgui_opengl\\shader.vert", "D:\\Code\\imgui_opengl\\imgui_opengl\\shader.frag");
	_myShader->Link();
	_texCoordLocation   = _myShader->getAttribLocation("uv");
	_mvpMatrixLocation  = _myShader->getUniformLocation("mvpMatrix");
	_use_color_location = _myShader->getUniformLocation("use_color");
	_colorLocation      = _myShader->getAttribLocation("vertexColor");
	_vertexLocation     = _myShader->getAttribLocation("vert");	
}

void AwesomeWindow::BuildStuff()
{
	// http://www.opengl-tutorial.org/beginners-tutorials/tutorial-5-a-textured-cube/

	using namespace glm;

	vec3 vertices[] = {
		vec3(0.0,     0.0, 0.0),
		vec3(0.0,   250.0, 0.0),
		vec3(250.0, 250.0, 0.0),
		vec3(0.0,     0.0, 0.0),
		vec3(250.0, 250.0, 0.0),
		vec3(250.0,   0.0, 0.0)
	};

	vec2 uv_coords[] =
	{
		vec2(0, 1),
		vec2(0, 0),
		vec2(1, 0),
		vec2(0, 1),
		vec2(1, 0),
		vec2(1, 1)
	};

	vec3 colors[] =
	{
		vec3(1.0, 0.0, 0.0),
		vec3(0.0, 0.0, 1.0),
		vec3(0.0, 1.0, 0.0),
		vec3(1.0, 0.0, 0.0),
		vec3(0.0, 1.0, 0.0),
		vec3(0.0, 0.0, 1.0)
	};

	// create VAO
	glGenVertexArrays(1, &this->_vao);
	glBindVertexArray(this->_vao);

	//  create a VBO for position and uv
	glGenBuffers(1, &this->_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, this->_vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(this->_vertexLocation);
	glVertexAttribPointer(this->_vertexLocation, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
	std::cout << "vbo ID: " << _vbo << "\n";

	// create VBO for uv
	glGenBuffers(1, &this->_uvVbo);
	glBindBuffer(GL_ARRAY_BUFFER, this->_uvVbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(uv_coords), uv_coords, GL_STATIC_DRAW);
	glEnableVertexAttribArray(this->_texCoordLocation);
	glVertexAttribPointer(this->_texCoordLocation, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
	std::cout << "uvVbo ID: " << _uvVbo << "\n";

	// create VBO for color
	glGenBuffers(1, &this->_colVbo);
	glBindBuffer(GL_ARRAY_BUFFER, this->_colVbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);
	glEnableVertexAttribArray(this->_colorLocation);
	glVertexAttribPointer(this->_colorLocation, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
	std::cout << "colVbo ID: " << _colVbo << "\n";

	// unbind vao and vbo
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	// texture!
	_texture = MyTexture("D:\\Code\\imgui_opengl\\laughing_man.bmp");
}

void AwesomeWindow::ShowWindow()
{
	using namespace glm;

	// prepare stuff
	glfwSetErrorCallback(error_callback);	
	if (!glfwInit()) { std::cout << "cannot init glfw\n"; return; }
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	_window = glfwCreateWindow(1280, 720, "Awesome Window", NULL, NULL);
	glfwMakeContextCurrent(_window);
	gl3wInit();

	// Register callbacks
	glfwSetKeyCallback(        _window, key_input_callBack);
	glfwSetWindowSizeCallback( _window, window_resize_callBack);
	glfwSetScrollCallback(     _window, mouse_scroll_callBack);
	glfwSetMouseButtonCallback(_window, mouse_button_callBack);
	glfwSetCursorPosCallback(  _window, mouse_move_callBack);
	glfwSetCursorEnterCallback(_window, cursor_enters_window_callBack);

	ImGui_ImplGlfwGL3_Init(_window, false);

	try 
	{
		// init your OpenGL
		this->InitializeGL();
		this->BuildStuff();

		while (!glfwWindowShouldClose(_window))
		{
			glfwPollEvents();
			ImGui_ImplGlfwGL3_NewFrame();

			// App Logic

			// GUI Logic

			// Rendering
			int display_w, display_h;
			glfwGetFramebufferSize(_window, &display_w, &display_h);

			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			glViewport(0, 0, display_w, display_h);

			this->_myShader->enable();
			
			// draw your shit
			mat4 orthoMatrix = glm::ortho(0.0f, (float)display_w, (float)display_h, 0.0f, -100.f, 100.0f);
			//mat4 transformMatrix;
			mat4 transformMatrix = glm::scale(
				glm::mat4(1.0f), // identity matrix, weird parameter, huh?
				glm::vec3(1.0));
			mat4 mpvMatrix = orthoMatrix * transformMatrix;
			glUniformMatrix4fv(this->_mvpMatrixLocation, 1, GL_FALSE, glm::value_ptr(mpvMatrix));
			
			glBindTexture(GL_TEXTURE_2D, this->_texture._textureID);
			glUniform1f(this->_use_color_location, (GLfloat)0.0);
			glBindVertexArray(this->_vao);
			glDrawArrays(GL_TRIANGLES, 0, 6);
			// unbind
			glBindTexture(GL_TEXTURE_2D, 0);
			glBindVertexArray(0);
			this->_myShader->disable();

			ImGui::Render();
			glfwSwapBuffers(_window);
		}

	}
	catch (const  std::exception & e) 
	{
		std::cerr << "Exception Thrown: ";
		std::cerr << e.what() << std::endl;
	}
	catch (...) 
	{
		std::cerr << "Uncaught exception thrown!  Terminating Program." << std::endl;
	}

	// Cleanup
	ImGui_ImplGlfwGL3_Shutdown();
	glfwTerminate();

	/*
	// Setup window
	glfwSetErrorCallback(error_callback);

	if (!glfwInit())
	{
		std::cout << "cannot init glfw\n";
		return;
		//return 1;
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#if __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
	_window = glfwCreateWindow(1280, 720, "ImGui OpenGL3 example", NULL, NULL);
	glfwMakeContextCurrent(_window);
	gl3wInit();

	// Setup ImGui binding
	ImGui_ImplGlfwGL3_Init(_window, true);

	// Load Fonts
	// (there is a default font, this is only if you want to change it. see extra_fonts/README.txt for more details)
	//ImGuiIO& io = ImGui::GetIO();
	//io.Fonts->AddFontDefault();
	//io.Fonts->AddFontFromFileTTF("../../extra_fonts/Cousine-Regular.ttf", 15.0f);
	//io.Fonts->AddFontFromFileTTF("../../extra_fonts/DroidSans.ttf", 16.0f);
	//io.Fonts->AddFontFromFileTTF("../../extra_fonts/ProggyClean.ttf", 13.0f);
	//io.Fonts->AddFontFromFileTTF("../../extra_fonts/ProggyTiny.ttf", 10.0f);
	//io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\ArialUni.ttf", 18.0f, NULL, io.Fonts->GetGlyphRangesJapanese());

	bool show_test_window = true;
	bool show_another_window = true;
	ImVec4 clear_color = ImColor(114, 144, 154);

	// Main loop
	while (!glfwWindowShouldClose(_window))
	{
		glfwPollEvents();
		ImGui_ImplGlfwGL3_NewFrame();

		// 1. Show a simple window
		// Tip: if we don't call ImGui::Begin()/ImGui::End() the widgets appears in a window automatically called "Debug"
		{
			static float f = 0.0f;
			ImGui::Text("Hello, world!");
			ImGui::SliderFloat("float", &f, 0.0f, 1.0f);
			ImGui::ColorEdit3("clear color", (float*)&clear_color);
			if (ImGui::Button("Test Window")) show_test_window ^= 1;
			if (ImGui::Button("Another Window")) show_another_window ^= 1;
			ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		}

		// 2. Show another simple window, this time using an explicit Begin/End pair
		if (show_another_window)
		{
			ImGui::SetNextWindowSize(ImVec2(200, 100), ImGuiSetCond_FirstUseEver);
			ImGui::Begin("Another Window", &show_another_window);
			ImGui::Text("Hello");
			ImGui::End();
		}

		// 3. Show the ImGui test window. Most of the sample code is in ImGui::ShowTestWindow()
		if (show_test_window)
		{
			ImGui::SetNextWindowPos(ImVec2(650, 20), ImGuiSetCond_FirstUseEver);
			ImGui::ShowTestWindow(&show_test_window);
		}

		// Rendering
		int display_w, display_h;
		glfwGetFramebufferSize(_window, &display_w, &display_h);
		glViewport(0, 0, display_w, display_h);
		glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
		glClear(GL_COLOR_BUFFER_BIT);
		ImGui::Render();
		glfwSwapBuffers(_window);
	}

	// Cleanup
	ImGui_ImplGlfwGL3_Shutdown();
	glfwTerminate();
	*/
}

void AwesomeWindow::error_callback(int error, const char* description)
{
	fprintf(stderr, "Error %d: %s\n", error, description);
}

void AwesomeWindow::cursor_enters_window_callBack(GLFWwindow *window, int entered)
{
	GetInstance()->cursorEnterWindowEvent(entered);
}

void AwesomeWindow::mouse_move_callBack(GLFWwindow *window, double xPos, double yPos)
{
	GetInstance()->mouseMoveEvent(xPos, yPos);
}

void AwesomeWindow::mouse_button_callBack(GLFWwindow * window, int button, int actions, int mods)
{
	GetInstance()->mouseButtonInputEvent(button, actions, mods);
}

void AwesomeWindow::mouse_scroll_callBack(GLFWwindow * window, double xOffSet, double yOffSet)
{
	GetInstance()->mouseScrollEvent(xOffSet, yOffSet);
}

void AwesomeWindow::window_resize_callBack(GLFWwindow * window, int width, int height)
{
	GetInstance()->windowResizeEvent(width, height);
}

void AwesomeWindow::key_input_callBack(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	GetInstance()->keyInputEvent(key, action, mods);
}

void AwesomeWindow::cursorEnterWindowEvent(int entered)
{
	//std::cout << "cursorEnterWindowEvent\n";
}

void AwesomeWindow::mouseMoveEvent(double xPos, double yPos)
{
	//std::cout << "mouseMoveEvent\n";
}

void AwesomeWindow::mouseButtonInputEvent(int button, int actions, int mods)
{
	//std::cout << "mouseButtonInputEvent\n";
}

void AwesomeWindow::mouseScrollEvent(double xOffSet, double yOffSet)
{
	//std::cout << "mouseScrollEvent\n";
}

void AwesomeWindow::windowResizeEvent(int width, int height)
{
	//std::cout << "windowResizeEvent\n";
}

void AwesomeWindow::keyInputEvent(int key, int action, int mods)
{
	//std::cout << "keyInputEvent\n";
}

