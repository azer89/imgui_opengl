
/**
* Reza Adhitya Saputra
* reza.adhitya.saputra@gmail.com
*/

#ifndef MY_TEXTURE_H
#define MY_TEXTURE_H

#include <GL/gl3w.h>

class MyTexture
{
public:
	MyTexture();
	MyTexture(const char * file_path);
	~MyTexture();

public:
	GLuint _textureID;

private:
	GLuint LoadBMP(const char * file_path);
};

#endif