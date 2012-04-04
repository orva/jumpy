#ifndef GPU_DATA_UTILS_H
#define GPU_DATA_UTILS_H

#include <GL/glew.h>
#include <GL/glfw.h>

GLuint jpy_create_program(const size_t count, const GLuint* shaders);
GLuint jpy_create_shader(GLenum type, const char* source);
GLuint jpy_create_vbo(const size_t len, const GLfloat* vertices, GLenum type);

#endif
