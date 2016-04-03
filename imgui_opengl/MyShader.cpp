
/**
* This code is heavily inspired by the skeleton code given in CS488 Winter 2016 at U Waterloo
*
* Reza Adhitya Saputra
* reza.adhitya.saputra@gmail.com
*/

#include "MyShader.h"

#include <fstream> // for reading text files
#include <sstream> // for reading text files
#include <iostream>

MyShader::MyShader() : _programID(0)
{
}

MyShader::~MyShader()
{
	if (this->_vertexShader._shaderID != 0)
		{ glDeleteShader(this->_vertexShader._shaderID); }

	if (this->_fragmentShader._shaderID != 0)
		{ glDeleteShader(this->_fragmentShader._shaderID); }

	if (this->_programID != 0)
		{ glDeleteProgram(this->_programID); }
}

void MyShader::Initialize(std::string vs_path, std::string fs_path)
{
	this->_programID = glCreateProgram();

	this->_vertexShader._shaderID = glCreateShader(GL_VERTEX_SHADER);
	this->_vertexShader._filePath = vs_path;
	this->_vertexShader._shaderCode = this->ReadTextFile(vs_path);
	const char* vs_code_const = this->_vertexShader._shaderCode.c_str();
	glShaderSource(this->_vertexShader._shaderID, 1, (const GLchar **)&vs_code_const, NULL);
	glCompileShader(this->_vertexShader._shaderID);
	CheckCompilation(this->_vertexShader._shaderID);

	this->_fragmentShader._shaderID = glCreateShader(GL_FRAGMENT_SHADER);
	this->_fragmentShader._filePath = fs_path;
	this->_fragmentShader._shaderCode = this->ReadTextFile(fs_path);
	const char* fs_code_const = this->_fragmentShader._shaderCode.c_str();
	glShaderSource(this->_fragmentShader._shaderID, 1, (const GLchar **)&fs_code_const, NULL);
	glCompileShader(this->_fragmentShader._shaderID);
	CheckCompilation(this->_fragmentShader._shaderID);


}

void MyShader::enable()
{
	glUseProgram(this->_programID);
}

void MyShader::disable()
{
	glUseProgram((GLuint)NULL);
}

void MyShader::Link()
{
	glAttachShader(this->_programID, this->_vertexShader._shaderID);
	glAttachShader(this->_programID, this->_fragmentShader._shaderID);
	glLinkProgram(this->_programID);

	// check
	GLint linkStatus;
	glGetProgramiv(this->_programID, GL_LINK_STATUS, &linkStatus);
	if (linkStatus == GL_FALSE)
	{
		GLint errorMessageLength;
		// Get the length in chars of the link error message.
		glGetProgramiv(this->_programID, GL_INFO_LOG_LENGTH, &errorMessageLength);

		// Retrieve the link error message.
		GLchar* errorMessage = new GLchar[errorMessageLength];
		glGetProgramInfoLog(this->_programID, errorMessageLength, NULL, errorMessage);

		std::cout << "Linking shader error: " << errorMessage << "\n";
		//std::stringstream strStream;
		//strStream << "Error Linking Shaders: " << errorMessage << endl;

		delete[] errorMessage;
		//throw ShaderException(strStream.str());
	}
	else
	{
		std::cout << "Linking shader OK\n";
	}
}

GLint MyShader::getUniformLocation(const char * uniformName) const
{
	GLint result = glGetUniformLocation(this->_programID, (const GLchar *)uniformName);
	if (result == -1) { std::cout << "Error obtaining uniform location: " << uniformName << "\n"; }
	else { std::cout << "[uniform] " << uniformName << ": " << result << "\n"; }
	return result;
}

GLint MyShader::getAttribLocation(const char * attributeName) const
{
	GLint result = glGetAttribLocation(this->_programID, (const GLchar *)attributeName);
	if (result == -1)  { std::cout << "Error obtaining attribute location: " << attributeName << "\n"; }
	else { std::cout << "[attribute] " << attributeName << ": " << result << "\n"; }
	return result;
}

void MyShader::CheckCompilation(GLuint id)
{
	GLint flag;
	glGetShaderiv(id, GL_COMPILE_STATUS, &flag);
	if (flag == GL_FALSE)
	{
		GLint msg_length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &msg_length);
		GLchar* msg = new GLchar[msg_length + 1];
		glGetShaderInfoLog(id, msg_length, NULL, msg);
		std::cout << "Shader error: " << msg << "\n";
		delete[] msg;
	}
	else
	{
		std::cout << "Shader OK\n";
	}
}

std::string MyShader::ReadTextFile(std::string file_path)
{
	std::string shader_code;

	std::ifstream file;
	file.open(file_path.c_str());
	if (!file) { std::cout << "cannot find " << file_path << "\n"; }
	else { std::cout << file_path << " is found\n"; }

	std::stringstream sStream;	
	while (file.good())
	{
		std::string str;
		std::getline(file, str, '\r');
		sStream << str;
	}
	file.close();
	sStream << '\0';

	shader_code = sStream.str();

	//std::cout << "=========================\n";
	//std::cout << shader_code << "\n";
	//std::cout << "=========================\n";

	return shader_code;
}