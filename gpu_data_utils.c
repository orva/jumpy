#include "gpu_data_utils.h"

#include <GL/glew.h>
#include <GL/glfw.h>

#include <stdlib.h>
#include <stdio.h>




GLuint jpy_create_shader(GLenum type, const char* source)
{
	GLuint shader = glCreateShader(type);

	glShaderSource(shader, 1, &source, NULL);
	glCompileShader(shader);

	GLint status;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
	if (status == GL_FALSE) {
		GLint log_len;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &log_len);

		GLchar* log = malloc(sizeof(GLchar)*(log_len+1));
		glGetShaderInfoLog(shader, log_len, NULL, log);

		const char* shader_type = NULL;
		switch(type) {
		case GL_VERTEX_SHADER: shader_type = "vertex"; break;
		case GL_GEOMETRY_SHADER: shader_type = "geometry"; break;
		case GL_FRAGMENT_SHADER: shader_type = "fragment"; break;
		}

		fprintf(stderr, "Compile failure in %s shader:\n%s\n",
			shader_type, log); 
		free(log);
	}

	return shader;
}


GLuint jpy_create_vbo(const int len, const GLfloat* vertices, GLenum type)
{
	GLuint vbo;

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, len*sizeof(GLfloat), vertices, type);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	return vbo;
}
