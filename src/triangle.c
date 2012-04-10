#include "triangle.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>


static void compute_offsets(float *fXOffset, float *fYOffset)
{
    const float fLoopDuration = 5.0f;
    const float fScale = 3.14159f * 2.0f / fLoopDuration;
    
    double fElapsedTime = glfwGetTime();
    
    float fCurrTimeThroughLoop = fmodf(fElapsedTime, fLoopDuration);
    
    *fXOffset = cosf(fCurrTimeThroughLoop * fScale) * 0.5f;
    *fYOffset = sinf(fCurrTimeThroughLoop * fScale) * 0.5f;
}


static void draw(object *obj)
{
	jpy_prog program = jpy_obj_get_program(obj, 0);
	if (!program)
		return;

	glUseProgram(program);

	jpy_vbo vbo = jpy_obj_get_vbo(obj);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
	glDrawArrays(GL_TRIANGLES, 0, 3);

	glDisableVertexAttribArray(0);
	glUseProgram(0);
}


static void move(object *obj)
{
	jpy_prog program = jpy_obj_get_program(obj, 1);
	if (!program)
		return;

	float x_off = 0.0, y_off = 0.0;
	compute_offsets(&x_off, &y_off);

	glUseProgram(program);

	GLuint uni_loc = glGetUniformLocation(program, "offset");
	glUniform2f(uni_loc, x_off, y_off);

	jpy_vbo vbo = jpy_obj_get_vbo(obj);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
	glDrawArrays(GL_TRIANGLES, 0, 3);

	glDisableVertexAttribArray(0);
	glUseProgram(0);

}


object *create_triangle(void)
{
	const float p[] = {
	0.75f, 0.75f, 0.0f, 1.0f,
	0.75f, -0.75f, 0.0f, 1.0f,
	-0.75f, -0.75f, 0.0f, 1.0f,
	};


	jpy_vbo vbo = jpy_create_vbo(p, 12, GL_STREAM_DRAW);
	jpy_prog programs[2];

	jpy_shader shaders[2];
	shaders[0] = jpy_read_shader(GL_VERTEX_SHADER, "data/triangle_static.vert");
	shaders[1] = jpy_read_shader(GL_FRAGMENT_SHADER, "data/triangle.frag");
	programs[0] = jpy_create_program(shaders);

	shaders[0] = jpy_read_shader(GL_VERTEX_SHADER, "data/triangle_moving.vert");
	shaders[1] = jpy_read_shader(GL_FRAGMENT_SHADER, "data/triangle.frag");
	programs[1] = jpy_create_program(shaders);


	draw_func funcs[] = {move};
	object *o = jpy_obj_create(vbo, programs, funcs, draw);
	if (!o) {
		perror("Creating triangle failed!");
		exit(EXIT_FAILURE);
	}
	return o;
}

