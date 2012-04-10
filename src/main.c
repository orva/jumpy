#include "triangle.h"
#include "object.h"
#include "gpu_data_utils.h"

#include <GL/glew.h>
#include <GL/glfw.h>
#include <FTGL/ftgl.h>

#include <stdio.h>
#include <stdlib.h>
#include <math.h>



static FTGLfont *font;
static long last_frame;
static int frames,
	   fps;
static int running = GL_TRUE;
static int width = 800,
	   height = 600;

static int moving = GL_FALSE; // This should be in some object state thing..


void jpy_terminate(int exit_val)
{
	glfwTerminate();
	ftglDestroyFont(font);
	exit(exit_val);
}



static void GLFWCALL window_resize_callback(int x, int y)
{
	glfwSetWindowSize(x,y);
	glViewport(0, 0, (GLsizei) x, (GLsizei) y);
	width = x;
	height = y;
}


static void GLFWCALL key_callback(int key, int action)
{
	switch(key) {
	case GLFW_KEY_ESC:
		if (action == GLFW_RELEASE)
			jpy_terminate(EXIT_SUCCESS);
		break;
	case GLFW_KEY_SPACE:
		if (action == GLFW_RELEASE)
			moving = moving ? GL_FALSE : GL_TRUE;
		break;
	}
}


static int GLFWCALL close_callback(void)
{
	jpy_terminate(EXIT_SUCCESS);
	return GL_TRUE;
}


static void print(const char str[])
{
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(0.0,0.0 + width,0,0.0 + height,-1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glRasterPos2f(10.0f, 0.0f+height-20.0f);

	ftglRenderFont(font, str, FTGL_RENDER_ALL);

	glMatrixMode(GL_PROJECTION);
	glPopMatrix();   
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
}


static void calculate_fps(void)
{
	long cur = glfwGetTime();
	char buf[32]; // TODO make this safe.
	if (cur > last_frame) {
		fps = frames;
		frames = 0;
		last_frame = cur;
		sprintf(buf, "fps : %d", fps);
		print(buf);
	} else {
		frames += 1;
		sprintf(buf, "fps : %d", fps);
		print(buf);
	}
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


		calculate_fps();
		glfwSwapBuffers();

		if (!running)
			jpy_terminate(EXIT_SUCCESS);
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

	if (!glfwOpenWindow(width, height, 0,0,0,0, 0,0, GLFW_WINDOW)) {
		perror("Error while creating window!\n");
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	glfwSetWindowSizeCallback(window_resize_callback);
	glfwSetKeyCallback(key_callback);
	glfwSetWindowCloseCallback(close_callback);

	// Get all non-ancient gl* functions.
	if (glewInit() != GLEW_OK) {
		perror("Error while calling 'glewInit()'!\n");
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glClearColor(0.0234,0.5937,0.6015,0);

	font = ftglCreatePixmapFont("data/VeraMono.ttf");
	ftglSetFontFaceSize(font, 12, 12);

	// FPS counter variables.
	frames = 0;
	fps = 0;
	last_frame = glfwGetTime();
}


int main(void)
{
	init();
	main_loop();

	perror("Reached end of main, this should not happen!\n");
	return EXIT_FAILURE;
}

