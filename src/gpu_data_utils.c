#include "gpu_data_utils.h"

#include <stdio.h>
#include <stdlib.h>



jpy_prog jpy_create_program(const jpy_shader shaders[])
{
	jpy_prog program = glCreateProgram();

	size_t size = sizeof shaders/sizeof *shaders;
	for(size_t i=0; i<size; i++) 
		glAttachShader(program, shaders[i]);

	glLinkProgram(program);

	GLint status;
	glGetProgramiv(program, GL_LINK_STATUS, &status);
	if (status == GL_FALSE) {
		GLint log_length;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &log_length);

		GLchar *log = malloc(sizeof(GLchar)*(log_length+1));
		glGetProgramInfoLog(program, log_length, NULL, log);
		fprintf(stderr, "Linker failure: %s\n", log);
		free(log);
	}

	for(size_t i=0; i<size; i++) 
		glDetachShader(program, shaders[i]);

	return program;
}


jpy_shader jpy_create_shader(GLenum type, const char *source)
{
	GLuint shader = glCreateShader(type);

	glShaderSource(shader, 1, &source, NULL);
	glCompileShader(shader);

	GLint status;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
	if (status == GL_FALSE) {
		GLint log_len;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &log_len);

		GLchar *log = malloc(sizeof(GLchar)*(log_len+1));
		glGetShaderInfoLog(shader, log_len, NULL, log);

		const char *shader_type = NULL;
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



jpy_shader jpy_read_shader(GLenum type, const char *filename)
{
	FILE *fp = fopen(filename, "r");
	if (!fp)
		return 0;

	fseek(fp, 0L, SEEK_END);
	long len = ftell(fp);
	fseek(fp, 0L, SEEK_SET);

	char *buf = calloc(len+1, sizeof(char));
	if (!buf)
		return 0;

	fread(buf, sizeof(char), len, fp);
	fclose(fp);
	GLuint shader = jpy_create_shader(type, buf);
	free(buf);

	return shader;
}


jpy_vbo jpy_create_vbo(const float vertices[], size_t count, GLenum type)
{
	jpy_vbo vbo;

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, count*sizeof vertices[0], vertices, type);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	return vbo;
}

