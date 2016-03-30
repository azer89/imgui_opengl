
#include "AwesomeWindow.h"
#include <iostream>



AwesomeWindow::AwesomeWindow() : _window(0)
{
}

AwesomeWindow::~AwesomeWindow()
{
	//if (_window) { delete _window; }
}

void AwesomeWindow::InitializeGL()
{
	/* Stuff I forget what their purposes are */
	//glShadeModel(GL_SMOOTH); // error ?
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glEnable(GL_DEPTH_TEST);

	ImVec4 clear_color = ImColor(114, 144, 154);
	glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
}

void AwesomeWindow::ShowWindow()
{
	glfwSetErrorCallback(error_callback);	
	if (!glfwInit()) { std::cout << "cannot init glfw\n"; return; }
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	_window = glfwCreateWindow(1280, 720, "Awesome Window", NULL, NULL);
	glfwMakeContextCurrent(_window);
	gl3wInit();

	// Register callbacks

	ImGui_ImplGlfwGL3_Init(_window, true);

	try 
	{

		// init your OpenGL
		this->InitializeGL();

		while (!glfwWindowShouldClose(_window))
		{
			glfwPollEvents();
			ImGui_ImplGlfwGL3_NewFrame();

			// App Logic

			// GUI Logic

			// Rendering
			int display_w, display_h;
			glfwGetFramebufferSize(_window, &display_w, &display_h);
			glViewport(0, 0, display_w, display_h);
			
			// draw your shit

			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
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
}

void AwesomeWindow::mouse_move_callBack(GLFWwindow *window, double xPos, double yPos)
{
}

void AwesomeWindow::mouse_button_callBack(GLFWwindow * window, int button, int actions, int mods)
{
}

void AwesomeWindow::mouse_scroll_callBack(GLFWwindow * window, double xOffSet, double yOffSet)
{
}

void AwesomeWindow::window_resize_callBack(GLFWwindow * window, int width, int height)
{
}

void AwesomeWindow::key_input_callBack(GLFWwindow* window, int key, int scancode, int action, int mods)
{
}
