
/**
* Reza Adhitya Saputra
* reza.adhitya.saputra@gmail.com
*/

#include "MyTexture.h"

#include <iostream>
#include <stdlib.h>
#include <string.h>

MyTexture::MyTexture()
{
}

MyTexture::MyTexture(const char * file_path)
{
	this->_textureID = LoadBMP(file_path);
}

MyTexture::~MyTexture()
{
}

// to do: remove example image
GLuint MyTexture::LoadBMP(const char * file_path)
{
	// Data read from the header of a BMP file
	unsigned char header[54];
	unsigned int  dataPos;
	unsigned int  imageSize;
	unsigned int  width;
	unsigned int  height;

	// RGB data
	unsigned char * image_data;

	FILE * file = fopen(file_path, "rb");
	if (!file)							    
	{
		std::cout << "cannot open file " << file_path << "\n";
		return 0;
	}

	// The header should be 54 bytes
	if (fread(header, 1, 54, file) != 54) { std::cout << "Wrong BMP\n"; return 0; }

	// A BMP files always begins with "BM"
	if (header[0] != 'B' || header[1] != 'M') { std::cout << "Wrong BMP\n"; return 0; }

	// Make sure this is a 24bpp file
	if (*(int*)&(header[0x1E]) != 0)  { std::cout << "Wrong BMP\n"; return 0;  }

	if (*(int*)&(header[0x1C]) != 24) { std::cout << "Wrong BMP\n"; return 0;  }

	// Read the information about the image
	dataPos   = *(int*)&(header[0x0A]);
	imageSize = *(int*)&(header[0x22]);
	width     = *(int*)&(header[0x12]);
	height    = *(int*)&(header[0x16]);

	// Some BMP files are misformatted, guess missing information
	if (imageSize == 0) { imageSize = width*height * 3; } // 3 : one byte for each Red, Green and Blue component
	if (dataPos == 0) { dataPos = 54; } // The BMP header is done that way
		
	image_data = new unsigned char[imageSize];	// Create a buffer
	fread(image_data, 1, imageSize, file);		// Read and put to the buffer
	fclose(file);							    // Close the image

	// Create a OpenGL texture
	GLuint textureID;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, image_data);

	delete[] image_data;

	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); 

	// nice trilinear filtering.	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glGenerateMipmap(GL_TEXTURE_2D);

	std::cout << "Image " << file_path << " is loaded\n";

	return textureID;
}