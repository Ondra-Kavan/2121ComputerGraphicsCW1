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

using namespace std;
using namespace CoreStructures;


void init(int argc, char* argv[]);
void display(void);


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
	glutCreateWindow("Draw a Triangle!");

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
}


void display(void) {

	//clear the buffers to the following preset values
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	/*
	 * DRAW
	 */



	//instructs the rendering that you are done with the current frame and buffers should be swapped to work on the next one.
	glutSwapBuffers();
}
