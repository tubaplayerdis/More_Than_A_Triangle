#include "VBO.h"

VBO::VBO(GLfloat* verticies, GLsizeiptr size) 
{
	glGenBuffers(1, &ID);
	glBindBuffer(GL_ARRAY_BUFFER, ID);
	//Acually store data, sizeof() function gets size of something in bytes 
	glBufferData(GL_ARRAY_BUFFER, size, verticies, GL_STATIC_DRAW);
}


void VBO::Bind() 
{
	glBindBuffer(GL_ARRAY_BUFFER, ID);
}

void VBO::Unbind()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VBO::Delete() 
{
	glDeleteBuffers(1, &ID);
}