#ifndef GPU_DATA_UTILS_H
#define GPU_DATA_UTILS_H

#include <GL/glew.h>
#include <GL/glfw.h>

typedef GLfloat jpy_vbo;
typedef GLfloat jpy_shader;

GLuint jpy_create_program(const jpy_shader shaders[]);
GLuint jpy_create_shader(GLenum type, const char *source);
GLuint jpy_read_shader(GLenum type, const char *filename);
GLuint jpy_create_vbo(const GLfloat vertices[], GLenum type);

GLuint stupid_test();

#endif

