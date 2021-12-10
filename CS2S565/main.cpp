#include <FreeImage\FreeImagePlus.h>
#include <wincodec.h>
#include <glew\glew.h>
#include <freeglut\freeglut.h>
#include <iostream>

#include "texture_loader.h"
#include "shader_setup.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <stack>

#include "draw_functions.hpp"
#include "Snowman.h"
#include "tardis.hpp"

#include "tutorial.hpp"

GLuint bg_texture;
GLuint tardis_texture;

// Function prototypes
void init(int argc, char* argv[]);
void display(void);

void oks_keyDown(unsigned char key, int x, int y);
void oks_mouseButtonDown(int button_id, int state, int x, int y);
void oks_mouseMove(int x, int y);

/*
 * Global
 */

tardis* the_tardis = nullptr;

float tardis_x = .0f;
float tardis_y = .0f;
float tardis_orientation = .0f;

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

	//// Register keyboard and mouse callback functions
	//glutKeyboardFunc(keyDown);
	//glutMouseFunc(mouseButtonDown);
	//glutMotionFunc(mouseMove);

	glutKeyboardFunc(oks_keyDown);
	glutMouseFunc(oks_mouseButtonDown);
	glutMotionFunc(oks_mouseMove);

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



	// Example query OpenGL state (get version number)
	int majorVersion, minorVersion;

	glGetIntegerv(GL_MAJOR_VERSION, &majorVersion);
	glGetIntegerv(GL_MINOR_VERSION, &minorVersion);

	cout << "OpenGL version " << majorVersion << "." << minorVersion << "\n\n";


	// Report maximum number of vertex attributes
	GLint numAttributeSlots;
	glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &numAttributeSlots);
	cout << "GL_MAX_VERTEX_ATTRIBS = " << numAttributeSlots << endl;

	// 3. Initialise OpenGL settings and objects we'll use in our scene
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);



	// Shader setup - more on this next week!!!
	myShaderProgram = setupShaders(string("Shaders\\basic_vertex_shader.txt"), string("Shaders\\basic_fragment_shader.txt"));
	locT = glGetUniformLocation(myShaderProgram, "T");

	myTexture = fiLoadTexture(R"(..\..\Common\Resources\Textures\bumblebee.png)");
	rustTexture = wicLoadTexture(wstring(L"Resources\\Textures\\rust1.jpg"));

	bg_texture = fiLoadTexture(R"(Resources\Textures\BG.jpg)");
	tardis_texture = wicLoadTexture(wstring(L"Resources\\Textures\\tardis.png"));

	// Set Projection Matrix
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-1.0f, 1.0f, -1.0f, 1.0f);

	glMatrixMode(GL_MODELVIEW);
	glm::vec3 origin(0, 0, -0.5);
	glm::vec3 target(0, 0, 0);
	glm::vec3 up(0, 1, 0);
	model_view = glm::lookAt(origin, target, up);


	// Create new Snowman instance
	mySnowman = new Snowman();

	the_tardis = new tardis();
}



void display(void) {

	//clear the buffers to the following preset values
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glUseProgram(0);

	//tutorial_diplay();


	draw_textured_quad(bg_texture);

	draw_textured_quad(tardis_texture, -0.5, 0.5, 0.5, -0.5);
	the_tardis->render(tardis_x, tardis_y, 0.8f, tardis_orientation);

	//instructs the rendering that you are done with the current frame and buffers should be swapped to work on the next one.
	glutSwapBuffers();
}

/*
 * OKS is just a prefix I chose to differentiate my own function
 */

void oks_mouseButtonDown(int button_id, int state, int x, int y) {

	if (button_id == GLUT_LEFT_BUTTON) {

		if (state == GLUT_DOWN) {

			mouse_x = x;
			mouse_y = y;

			mDown = true;

		}
		else if (state == GLUT_UP) {

			mDown = false;
		}
	}
}
void oks_mouseMove(int x, int y) {

	if (mDown) {

		int dx = x - mouse_x;
		int dy = y - mouse_y;

		
		tardis_x += float(dx) * 0.0025f;
		tardis_y -= float(dy) * 0.0025f;

		
		mouse_x = x;
		mouse_y = y;

		glutPostRedisplay();
	}
}

void oks_keyDown(unsigned char key, int x, int y)
{
	// rotate what should be the tardis
	if (key == 'p')
	{
		tardis_orientation += 1.0f;

		glutPostRedisplay();
	}
	// reset orientation
	if (key == 'r')
	{
		tardis_orientation = .0f;
		glutPostRedisplay();
	}
}
