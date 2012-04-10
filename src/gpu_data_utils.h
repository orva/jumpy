#ifndef GPU_DATA_UTILS_H
#define GPU_DATA_UTILS_H

#include <GL/glew.h>
#include <GL/glfw.h>

typedef GLuint jpy_vbo;
typedef GLuint jpy_shader;
typedef GLuint jpy_prog;

jpy_prog jpy_create_program(const jpy_shader shaders[]);
jpy_shader jpy_create_shader(GLenum type, const char *source);
jpy_shader jpy_read_shader(GLenum type, const char *filename);
jpy_vbo jpy_create_vbo(const GLfloat vertices[], size_t count, GLenum type);

#endif

