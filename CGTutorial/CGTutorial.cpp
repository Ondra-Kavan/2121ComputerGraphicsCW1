// CGTutorial.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <FreeImage/FreeImagePlus.h>
#include <wincodec.h>
#include <glew/glew.h>
#include <freeglut/freeglut.h>
#include <CoreStructures/CoreStructures.h>
#include <iostream>

using namespace std;
using namespace CoreStructures;


// Function prototypes
void init(int argc, char* argv[]);
void display(void);
void drawTriangle(void);


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

	glutInitWindowSize(800, 800);
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
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
}


void display(void) {

	//clear the buffers to the following preset values
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//call our function to render our shape
	drawTriangle();

	//instructs the rendering that you are done with the current frame and buffers should be swapped to work on the next one.
	glutSwapBuffers();
}


// Draw a Triangle
void drawTriangle(void)
{
	glBegin(GL_LINE_LOOP);
	glVertex2f(0.0, 0.25f);
	glVertex2f(0.25, 0.25f);
	glVertex2f(0.25, 0.0f);
	glEnd();
}

//#include <iostream>
//
//int main()
//{
//    std::cout << "Hello World!\n";
//}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
