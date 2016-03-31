
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
	{
		glDeleteShader(this->_vertexShader._shaderID);
	}

	if (this->_fragmentShader._shaderID != 0)
	{
		glDeleteShader(this->_fragmentShader._shaderID);
	}

	if (this->_programID != 0)
	{
		glDeleteProgram(this->_programID);
	}
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
}

std::string MyShader::ReadTextFile(std::string file_path)
{
	std::string shader_code;

	std::ifstream file;
	file.open(file_path.c_str());
	if (!file) { std::cout << "cannot find " << file_path << "\n"; }

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

	return shader_code;
}