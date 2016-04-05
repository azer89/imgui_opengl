


#ifndef MY_TEXTURE_H
#define MY_TEXTURE_H

#include <GL/gl3w.h>

class MyTexture
{
public:
	MyTexture();
	~MyTexture();

private:
	GLuint LoadBMP(const char * file_path);
};

#endif