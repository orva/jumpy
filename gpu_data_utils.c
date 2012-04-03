#include "gpu_data_utils.h"

#include <GL/glew.h>
#include <GL/glfw.h>

GLuint jpy_create_shader(GLenum type, const char* source)
{
	
}


GLuint jpy_create_vbo(const int len, const GLfloat* vertices, GLenum type)
{
	GLuint* vbo;

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, len*sizeof(GLfloat));
}
