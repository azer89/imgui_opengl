

#ifndef MY_SHADER_H
#define MY_SHADER_H

#include <GL/gl3w.h>
#include <string>

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