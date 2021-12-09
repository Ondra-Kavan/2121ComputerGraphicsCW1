/*
 *
 *	2D Scene Rendering in OpenGL
 *
 *	Ondrej Kavan
 *
 */


#include <FreeImage/FreeImagePlus.h>
#include <wincodec.h>
#include <glew/glew.h>
#include <freeglut/freeglut.h>
#include <CoreStructures/CoreStructures.h>
#include <iostream>

#include "texture_loader.h"
#include "texture_loader.hpp"

using namespace std;
//using namespace CoreStructures;

/*
 * Global variables
 */

GLuint bg_texture;
GLuint texture;


void init(int argc, char* argv[]);
void display(void);
void draw_textured_quad(GLuint texture);
void draw_textured_quad(GLuint texture, GLfloat tl_pos_x, GLfloat tl_pos_y, GLfloat br_pos_x, GLfloat br_pos_y);


int main(int argc, char* argv[]) {

	init(argc, argv);

	glutMainLoop();

	return 0;
}


void init(int argc, char* argv[]) {

	// 1. Initialise FreeGLUT
	glutInit(&argc, argv);

	glutInitContextVersion(4, 3);
	glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);

	glutInitWindowSize(800, 600);
	glutInitWindowPosition(64, 64);
	glutCreateWindow("AAAAAAAAAAA!!!!!!!");

	// Display callback
	glutDisplayFunc(display);


	// 2. Initialise GLEW library
	GLenum err = glewInit();

	// Ensure the GLEW library was initialised successfully before proceeding
	if (err == GLEW_OK) {

		cout << "GLEW initialised okay\n";
	}
	else {

		cout << "GLEW could not be initialised!\n";
		throw;
	}


	// 3. Initialise OpenGL settings and objects we'll use in our scene
	glClearColor(.0, .0, .0, .0);


	// Texture stuff

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	bg_texture = fiLoadTexture(R"(Textures\BG.jpg)");
	texture = fiLoadTexture(R"(..\..\Common\Resources\Textures\bumblebee.png)");
}


void display(void) {

	//clear the buffers to the following preset values
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	/*
	 * DRAW
	 */

	draw_textured_quad(bg_texture);
	draw_textured_quad(texture, -0.5,0.5,0.5,-0.5);

	 //instructs the rendering that you are done with the current frame and buffers should be swapped to work on the next one.
	glutSwapBuffers();
}


void draw_textured_quad(GLuint texture)
{
	glBindTexture(GL_TEXTURE_2D, texture);
	glEnable(GL_TEXTURE_2D);

	glBegin(GL_QUADS);

	glTexCoord2f(0, 0);
	glVertex2f(-1, 1.0f);

	glTexCoord2f(0, 1);
	glVertex2f(-1, -1);

	glTexCoord2f(1, 1);
	glVertex2f(1.0f, -1);

	glTexCoord2f(1, 0);
	glVertex2f(1.0f, 1.0f);

	glEnd();
	glDisable(GL_TEXTURE_2D);
}

void draw_textured_quad(GLuint texture, GLfloat tl_pos_x, GLfloat tl_pos_y, GLfloat br_pos_x, GLfloat br_pos_y)
{
	glBindTexture(GL_TEXTURE_2D, texture);
	glEnable(GL_TEXTURE_2D);

	glBegin(GL_QUADS);

	glTexCoord2f(0, 0);
	glVertex2f(tl_pos_x, tl_pos_y);

	glTexCoord2f(0, 1);
	glVertex2f(tl_pos_x, br_pos_y);

	glTexCoord2f(1, 1);
	glVertex2f(br_pos_x, br_pos_y);

	glTexCoord2f(1, 0);
	glVertex2f(br_pos_x, tl_pos_y);

	glEnd();
	glDisable(GL_TEXTURE_2D);
}
