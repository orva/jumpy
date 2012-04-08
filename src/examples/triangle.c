#include "../object.h"
#include <math.h>

static const GLfloat vertices[] = {
	0.35f, 0.35f, 0.0f, 1.0f,
	0.35f, -0.35f, 0.0f, 1.0f,
	-0.35f, -0.35f, 0.0f, 1.0f,
};


static void compute_offsets(float *fXOffset, float *fYOffset)
{
    const float fLoopDuration = 5.0f;
    const float fScale = 3.14159f * 2.0f / fLoopDuration;
    
    double fElapsedTime = glfwGetTime();
    
    float fCurrTimeThroughLoop = fmodf(fElapsedTime, fLoopDuration);
    
    *fXOffset = cosf(fCurrTimeThroughLoop * fScale) * 0.5f;
    *fYOffset = sinf(fCurrTimeThroughLoop * fScale) * 0.5f;
}


void draw(object *obj)
{
	jpy_prog program = jpy_obj_get_program(obj, 0);
	float x_off = 0.0, y_off = 0.0;

	glUseProgram(program);

	compute_offsets(&x_off, &y_off);
	GLuint uni_loc = glGetUniformLocation(program, "offset");
	glUniform2f(uni_loc, x_off, y_off);


	jpy_vbo vbo = jpy_obj_get_vbo(obj);
	glBindBuffer(GL_ARRAY_BUFFER, jpy_obj_get_vbo(obj));
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
	glDrawArrays(GL_TRIANGLES, 0, 3);

	glDisableVertexAttribArray(0);
	glUseProgram(0);
}


object *create_triangle(void)
{
	jpy_vbo vbo = jpy_create_vbo(vertices, GL_STATIC_DRAW);
	jpy_prog programs[1];

	
	jpy_shader shaders[2] = {
		jpy_read_shader(GL_VERTEX_SHADER, "triangle.vert"),
		jpy_read_shader(GL_FRAGMENT_SHADER, "triangle.frag")
	};
	programs[0] = jpy_create_program(shaders);

	return jpy_obj_create(vbo, programs, NULL, draw);
}

