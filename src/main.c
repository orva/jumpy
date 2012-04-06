#include "object.h"
#include "gpu_data_utils.h"

#include <GL/glew.h>
#include <GL/glfw.h>

#include <stdio.h>
#include <stdlib.h>
#include <math.h>


static int running = GL_TRUE;

const GLfloat vertexPositions[] = {
	0.35f, 0.35f, 0.0f, 1.0f,
	0.35f, -0.35f, 0.0f, 1.0f,
	-0.35f, -0.35f, 0.0f, 1.0f,
};

void jpy_terminate(void)
{
	glfwTerminate();
	exit(EXIT_SUCCESS);
}

static void GLFWCALL window_resize(int x, int y)
{
	glfwSetWindowSize(x,y);
	glViewport(0, 0, (GLsizei) x, (GLsizei) y);
}


void ComputePositionOffsets(float *fXOffset, float *fYOffset)
{
    const float fLoopDuration = 5.0f;
    const float fScale = 3.14159f * 2.0f / fLoopDuration;
    
    double fElapsedTime = glfwGetTime();
    
    float fCurrTimeThroughLoop = fmodf(fElapsedTime, fLoopDuration);
    
    *fXOffset = cosf(fCurrTimeThroughLoop * fScale) * 0.5f;
    *fYOffset = sinf(fCurrTimeThroughLoop * fScale) * 0.5f;
}


static GLuint program; 
static GLint uni_loc;

void draw(object *obj)
{
	float x_off = 0.0, y_off = 0.0;
	ComputePositionOffsets(&x_off, &y_off);
	uni_loc = glGetUniformLocation(program, "offset");
	glUniform2f(uni_loc, x_off, y_off);


	jpy_vbo vbo = jpy_obj_get_vbo(obj);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
	glDrawArrays(GL_TRIANGLES, 0, 3);

	glDisableVertexAttribArray(0);

}

static void main_loop(void)
{
	jpy_shader list[] = {0, 0};
	list[0] = jpy_read_shader(GL_VERTEX_SHADER, "triangle.vert");
	list[1] = jpy_read_shader(GL_FRAGMENT_SHADER, "triangle.frag");
	program = jpy_create_program(2, list);
	glDeleteShader(list[0]);
	glDeleteShader(list[1]);

	GLuint vbo = jpy_create_vbo(12, vertexPositions, GL_STATIC_DRAW);

	object ob = *jpy_create_object(vbo, 1, draw);

	while(running) {
		glClear(GL_COLOR_BUFFER_BIT);
		glUseProgram(program);

		jpy_obj_draw(&ob);

		glUseProgram(0);
		glfwSwapBuffers();

		running = !glfwGetKey(GLFW_KEY_ESC) 
			&& glfwGetWindowParam(GLFW_OPENED);

		if (!running)
			jpy_terminate();
	}
}


static void init(void)
{
	if (!glfwInit()) {
		perror("Error while calling 'glfwInit()'!\n");
		exit(EXIT_FAILURE);
	}

	glfwOpenWindowHint(GLFW_OPENGL_VERSION_MAJOR, 3); 
	glfwOpenWindowHint(GLFW_WINDOW_NO_RESIZE, GL_TRUE); 

	if (!glfwOpenWindow(800, 600, 0,0,0,0, 0,0, GLFW_WINDOW)) {
		perror("Error while creating window!\n");
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	// Get all non-ancient gl* functions.
	if (glewInit() != GLEW_OK) {
		perror("Error while calling 'glewInit()'!\n");
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwSetWindowSizeCallback(window_resize);
	glClearColor(0.0234,0.5937,0.6015,0);
}


int main(void)
{
	init();
	main_loop();

	perror("Reached end of main, this should not happen!\n");
	return EXIT_SUCCESS;
}

