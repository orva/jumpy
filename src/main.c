#include "triangle.h"
#include "object.h"
#include "gpu_data_utils.h"

#include <GL/glew.h>
#include <GL/glfw.h>

#include <stdio.h>
#include <stdlib.h>
#include <math.h>


static int running = GL_TRUE;


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


static int moving = GL_FALSE;
static void GLFWCALL key_callback(int key, int action)
{
	switch(key) {
	case GLFW_KEY_ESC:
		if (action == GLFW_RELEASE)
			jpy_terminate();
		break;
	case GLFW_KEY_SPACE:
		if (action == GLFW_RELEASE)
			moving = moving ? GL_FALSE : GL_TRUE;
		break;
	}
}


static int GLFWCALL close_callback(void)
{
	jpy_terminate();
	return GL_TRUE;
}


static void main_loop(void)
{
	object *tri = create_triangle();

	while(running) {
		glClear(GL_COLOR_BUFFER_BIT);

		if (!moving)
			jpy_obj_draw(tri);
		else
			jpy_obj_invoke(tri, 0);

		glfwSwapBuffers();

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

	glClearColor(0.0234,0.5937,0.6015,0);

	glfwSetWindowSizeCallback(window_resize);
	glfwSetKeyCallback(key_callback);
	glfwSetWindowCloseCallback(close_callback);
}


int main(void)
{
	init();
	main_loop();

	perror("Reached end of main, this should not happen!\n");
	return EXIT_SUCCESS;
}

