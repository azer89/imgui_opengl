

#ifndef MY_SHADER_H
#define MY_SHADER_H

#include <GL/gl3w.h>
#include <string>

/**
* This code is heavily inspired by the skeleton code given in CS488 Winter 2016 at U Waterloo
*
* Reza Adhitya Saputra
* reza.adhitya.saputra@gmail.com
*/

struct AShader
{
	GLuint		_shaderID;
	std::string _filePath;
	std::string _shaderCode;

	AShader()
	{
		this->_shaderID = 0;
		this->_filePath = "";
		this->_shaderCode = "";
	}
};

class MyShader
{
private:
	GLuint	_programID;

	AShader _vertexShader;
	AShader _fragmentShader;

public:
	MyShader();
	~MyShader();

private:
	void Initialize(std::string vs_path, std::string fs_path);
	std::string ReadTextFile(std::string file_path);
	void CheckCompilation(GLuint id);
};

#endif