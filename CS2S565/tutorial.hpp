#pragma once
#include <glm/mat4x4.hpp>


void drawTriangle(void);
void drawTexturedQuad(void);
void drawStarPackedArray(void);
void drawStarIndexArray(void);
void drawStarInterleavedArray(void);
void drawTexturedQuadArray(void);
void drawStar_VBO(void);
void drawQuad_VBO(void);
void setupStarVBO(void);
void setupQuadVBO(void);
void setupStarVAO(void);
void drawStar_VAO(void);
void drawHierarchy(glm::mat4x4& R);

using namespace std;




// Globals
//
// Snowman variables
//
Snowman* mySnowman = nullptr;

float snowmanX = 0.0f;
float snowmanY = 0.0f;
float snowmanOrientation = 0.0f;
//
// Demo model
//
float theta0 = 0.0f;
float theta1 = 0.1f;
float theta2 = 0.0f;
float theta1b = glm::radians(45.0f);

const float quadLength = 0.4f;

GLuint rustTexture;

// Matrix stack
stack<glm::mat4x4> matrixStack;


// Mouse input (rotation) example
void mouseButtonDown(int button_id, int state, int x, int y);
void mouseMove(int x, int y);
void keyDown(unsigned char key, int x, int y);


// Variable we'll use to animate (rotate) our star object
float theta = 0.0f;

// Variables needed to track where the mouse pointer is so we can determine which direction it's moving in
int mouse_x, mouse_y;
bool mDown = false;
glm::mat4 model_view = glm::mat4(1);
GLuint myTexture;

// Shader program object
GLuint myShaderProgram;
GLuint locT; // Location of "T" uniform variable

// Vertex Buffer Object IDs for the star object
GLuint starPosVBO, starColourVBO, starTexCoordVBO, starIndicesVBO;
GLuint quadPosVBO, quadColourVBO, quadTexCoordVBO, quadIndicesVBO;
// New ID - store the Vertex ARRAY Object for the star
GLuint starVAO;

static GLfloat boxVertices[] = {

	-0.4f, -0.7f,
	-0.4f, 0.7f,
	0.4f, -0.7f,
	0.4f, 0.7f

};
static GLubyte boxColors[] = {

	255, 0, 0,
	255, 255, 0,
	0, 255, 0,
	0, 255, 255
};

static GLfloat boxTextureCoords[] = {

0.0f, 1.0f,
0.0f, 0.0f,
1.0f, 1.0f,
1.0f, 0.0f
};

static GLubyte boxIndices[] = { 0,1,2,3 };
// Packed vertex arrays for the star object

// 1) Position Array - Store vertices as (x,y) pairs
static GLfloat starVertices[] = {

	0.0, 0.25f,
	0.1f, 0.1f,
	0.25f, 0.08f,
	0.15f, -0.05f,
	0.25f, -0.25f,
	0.0, -0.125f,
	-0.25f, -0.25f,
	-0.15f, -0.05f,
	-0.25f, 0.08f,
	-0.1f, 0.1f
};

// 2) Colour Array - Store RGB values as unsigned bytes
static GLubyte starColors[] = {

	255, 0, 0,
	255, 255, 0,
	0, 255, 0,
	0, 255, 255,
	0, 0, 255,
	128, 45, 200,
	0, 255, 0,
	255, 0, 255,
	255, 128, 255,
	255, 128, 128
};

// 3) Texture coordinate array (store uv coordinates as floating point values)
static float starTextureCoords[] = {

	0.5f, 1.0f,
	0.6f, 0.7f,
	1.0f, 0.7f,
	0.8f, 0.4f,
	0.95f, 0.0f,
	0.0f, 0.3f,
	-0.95f, 0.0f,
	-0.8f, 0.4f,
	-1.0f, 0.7f,
	-0.6f, 0.7f
};

struct VertexStruct
{
	GLfloat x, y;
	GLubyte r, g, b;
	GLfloat u, v;
};

static VertexStruct interleavedStarArray[] = {
	{0.0, 0.25f, 255, 0, 0,  0.5f, 1.0f},
	{0.1f, 0.1f, 255, 255, 0,  0.6f, 0.7f},
	{ 0.25f, 0.08f,		0, 255, 0,		1.0f, 0.7f },
	{ 0.15f, -0.05f,	0, 255, 255,	0.8f, 0.4f },
	{ 0.25f, -0.25f,	0, 0, 255,		0.95f, 0.0f },
	{ 0.0, -0.125f,		128, 45, 200,	0.0f, 0.3f },
	{ -0.25f, -0.25f,	0, 255, 0,		-0.95f, 0.0f },
	{ -0.15f, -0.05f,	255, 0, 255,	-0.8f, 0.4f },
	{ -0.25f, 0.08f,	255, 128, 255,	-1.0f, 0.7f },
	{ -0.1f, 0.1f,		255, 128, 128,	-0.6f, 0.7f }
};


// 4) Index Array - Store indices to star vertices - this determines the order the vertices are to be processed
static GLubyte StarIndices[] = { 0,1,2,3,4,5,6,7,8,9,10 };

// Draw example hierarchical object - pass in the current transform matrix so we can 'append' new transforms to this.
void drawHierarchy(glm::mat4x4& R) {



	matrixStack.push(R);

	// Draw base base of arm


	R = R * glm::rotate(glm::mat4(1.0f), theta0, glm::vec3(0.0f, 0.0f, 1.0f));
	glLoadMatrixf((GLfloat*)&R);

	drawTexturedQuad();


	matrixStack.push(R);

	// Draw first segment


	R = R * glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, quadLength, 0.0f)) * glm::rotate(glm::mat4(1.0f), theta1, glm::vec3(0.0f, 0.0f, 1.0f));


	glLoadMatrixf((GLfloat*)&R);

	drawTexturedQuad();


	matrixStack.push(R);

	// Draw first branch

	R = R * glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, quadLength, 0.0f)) * glm::rotate(glm::mat4(1.0f), theta2, glm::vec3(0.0f, 0.0f, 1.0f));

	glLoadMatrixf((GLfloat*)&R);

	drawTexturedQuad();

	R = matrixStack.top();
	matrixStack.pop();


	matrixStack.push(R);

	// Draw second branch


	R = R * glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, quadLength, 0.0f)) * glm::rotate(glm::mat4(1.0f), theta1b, glm::vec3(0.0f, 0.0f, 1.0f));
	glLoadMatrixf((GLfloat*)&R);

	drawTexturedQuad();

	R = matrixStack.top();
	matrixStack.pop();


	R = matrixStack.top();
	matrixStack.pop();


	R = matrixStack.top();
	matrixStack.pop();
}
void setupStarVBO(void) {

	// setup VBO for the star object position data
	glGenBuffers(1, &starPosVBO);
	glBindBuffer(GL_ARRAY_BUFFER, starPosVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(starVertices), starVertices, GL_STATIC_DRAW);

	// setup VBO for the star object colour data
	glGenBuffers(1, &starColourVBO);
	glBindBuffer(GL_ARRAY_BUFFER, starColourVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(starColors), starColors, GL_STATIC_DRAW);

	// setup VBO for the star object texture coord data
	glGenBuffers(1, &starTexCoordVBO);
	glBindBuffer(GL_ARRAY_BUFFER, starTexCoordVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(starTextureCoords), starTextureCoords, GL_STATIC_DRAW);

	// setup star vertex index array
	glGenBuffers(1, &starIndicesVBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, starIndicesVBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(StarIndices), StarIndices, GL_STATIC_DRAW);
}


void setupQuadVBO(void) {

	// setup VBO for the star object position data
	glGenBuffers(1, &quadPosVBO);
	glBindBuffer(GL_ARRAY_BUFFER, quadPosVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(boxVertices), boxVertices, GL_STATIC_DRAW);

	// setup VBO for the star object colour data
	glGenBuffers(1, &quadColourVBO);
	glBindBuffer(GL_ARRAY_BUFFER, quadColourVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(boxColors), boxColors, GL_STATIC_DRAW);

	// setup VBO for the star object texture coord data
	glGenBuffers(1, &quadTexCoordVBO);
	glBindBuffer(GL_ARRAY_BUFFER, quadTexCoordVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(boxTextureCoords), boxTextureCoords, GL_STATIC_DRAW);

	// setup star vertex index array
	glGenBuffers(1, &quadIndicesVBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, quadIndicesVBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(boxIndices), boxIndices, GL_STATIC_DRAW);
}
void drawStar_VBO(void) {

	// Bind each vertex buffer and enable
	// The data is still stored in the GPU but we need to set it up (which also includes validation of the VBOs behind-the-scenes)
	glBindBuffer(GL_ARRAY_BUFFER, starPosVBO);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (const GLvoid*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, starColourVBO);
	glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, 0, (const GLvoid*)0);
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, starTexCoordVBO);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, (const GLvoid*)0);
	glEnableVertexAttribArray(2);


	// Bind the index buffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, starIndicesVBO);


	// "Plug in" our shader into the GPU pipeline - we're now in the driving seat!!!!!  Our shaders now intercept and process our vertices as part of the GPU rendering pipeline!
	glUseProgram(myShaderProgram);


	// Draw the object - same function call as used for vertex arrays but the last parameter is interpreted as an offset into the currently bound index buffer (set to 0 so we start drawing from the beginning of the buffer).
	glDrawElements(GL_LINE_LOOP, 10, GL_UNSIGNED_BYTE, (GLvoid*)0);
}

void drawQuad_VBO(void) {


	// Bind Texture
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, myTexture);
	glUniform1i(glGetUniformLocation(myShaderProgram, "beeTexture"), 0);
	glEnable(GL_TEXTURE_2D);

	// Bind each vertex buffer and enable
	// The data is still stored in the GPU but we need to set it up (which also includes validation of the VBOs behind-the-scenes)
	glBindBuffer(GL_ARRAY_BUFFER, quadPosVBO);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (const GLvoid*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, quadColourVBO);
	glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, 0, (const GLvoid*)0);
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, quadTexCoordVBO);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, (const GLvoid*)0);
	glEnableVertexAttribArray(2);

	// Bind the index buffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, quadIndicesVBO);



	// "Plug in" our shader into the GPU pipeline - we're now in the driving seat!!!!!  Our shaders now intercept and process our vertices as part of the GPU rendering pipeline!
	glUseProgram(myShaderProgram);


	// Draw the object - same function call as used for vertex arrays but the last parameter is interpreted as an offset into the currently bound index buffer (set to 0 so we start drawing from the beginning of the buffer).
	glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_BYTE, (GLvoid*)0);
}
void setupStarVAO(void) {

	// Create and bind the vertex array object.  This remembers the vertex buffer object bindings below so we don't have to specify them at render time.
	glGenVertexArrays(1, &starVAO);
	glBindVertexArray(starVAO);


	// Setup the star position VBO
	glGenBuffers(1, &starPosVBO);
	glBindBuffer(GL_ARRAY_BUFFER, starPosVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(starVertices), starVertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (const GLvoid*)0);
	glEnableVertexAttribArray(0);

	// Setup the star colour VBO
	glGenBuffers(1, &starColourVBO);
	glBindBuffer(GL_ARRAY_BUFFER, starColourVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(starColors), starColors, GL_STATIC_DRAW);
	glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, 0, (const GLvoid*)0);
	glEnableVertexAttribArray(1);

	// setup the star texture coordinate VBO
	glGenBuffers(1, &starTexCoordVBO);
	glBindBuffer(GL_ARRAY_BUFFER, starTexCoordVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(starTextureCoords), starTextureCoords, GL_STATIC_DRAW);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, (const GLvoid*)0);
	glEnableVertexAttribArray(2);

	// setup star vertex index array
	glGenBuffers(1, &starIndicesVBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, starIndicesVBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(StarIndices), StarIndices, GL_STATIC_DRAW);

	glBindVertexArray(0);
}


void drawStar_VAO(void) {

	// "Plug in" our shader into the GPU pipeline - we're now in the driving seat!!!!!  Our shaders now intercept and process our vertices as part of the GPU rendering pipeline!
	glUseProgram(myShaderProgram);

	// Bind star VAO and draw
	glBindVertexArray(starVAO);
	glDrawElements(GL_LINE_LOOP, 10, GL_UNSIGNED_BYTE, (GLvoid*)0);
}



void drawTexturedQuadArray(void) {
	glBindTexture(GL_TEXTURE_2D, myTexture);
	glEnable(GL_TEXTURE_2D);
	glVertexPointer(2, GL_FLOAT, 0, boxVertices);
	//glColorPointer(3, GL_UNSIGNED_BYTE, 0, starColors);
	glTexCoordPointer(2, GL_FLOAT, 0, starTextureCoords);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}
// Draw a 5-pointed star using vertex arrays
void drawStarPackedArray(void) {

	glVertexPointer(2, GL_FLOAT, 0, starVertices);
	glColorPointer(3, GL_UNSIGNED_BYTE, 0, starColors);
	glTexCoordPointer(2, GL_FLOAT, 0, starTextureCoords);

	glDrawArrays(GL_LINE_LOOP, 0, 10);
}
void drawStarInterleavedArray(void)
{
	glVertexPointer(2, GL_FLOAT, sizeof(VertexStruct), interleavedStarArray);
	glColorPointer(3, GL_UNSIGNED_BYTE, sizeof(VertexStruct), &(interleavedStarArray[0].r));
	glTexCoordPointer(2, GL_FLOAT, sizeof(VertexStruct), &(interleavedStarArray[0].u));
	glDrawArrays(GL_LINE_LOOP, 0, 10);
}

// Draw a 5-pointed star using vertex arrays
void drawStarIndexArray(void) {

	glVertexPointer(2, GL_FLOAT, 0, starVertices);
	glColorPointer(3, GL_UNSIGNED_BYTE, 0, starColors);
	glTexCoordPointer(2, GL_FLOAT, 0, starTextureCoords);


	glDrawElements(GL_LINE_LOOP, 10, GL_UNSIGNED_BYTE, StarIndices);
}

void drawTexturedQuad(void) {
	//glBindTexture(GL_TEXTURE_2D, myTexture);
	glEnable(GL_TEXTURE_2D);
	//glBegin(GL_TRIANGLE_STRIP);
	//glTexCoord2f(0.0f, 1.0f);
	//glVertex2f(-0.4f, -0.7f);
	//
	//glTexCoord2f(0.0f, 0.0f);
	//glVertex2f(-0.4f, 0.7f);

	//glTexCoord2f(1.0f, 1.0f);
	//glVertex2f(0.4f, -0.7f);

	//glTexCoord2f(1.0f, 0.0f);
	//glVertex2f(0.4f, 0.7f);
	//glEnd();

	glBindTexture(GL_TEXTURE_2D, rustTexture);

	glBegin(GL_TRIANGLE_STRIP);

	glColor3ub(255, 255, 255);

	glTexCoord2f(0.4f, 1.0f);
	glVertex2f(-0.05f, 0.0f);

	glTexCoord2f(0.4f, 0.0f);
	glVertex2f(-0.05f, quadLength);

	glTexCoord2f(0.6f, 1.0f);
	glVertex2f(0.05f, 0.0f);

	glTexCoord2f(0.6f, 0.0f);
	glVertex2f(0.05f, quadLength);

	glEnd();
}


// DrawTriangle
void drawTriangle(void)
{
	//hint: use 
	glBegin(GL_LINE_LOOP);

	//e.g. 
	glVertex2f(0.0, 0.25f);
	glVertex2f(0.25, 0.25f);
	glVertex2f(0.25, 0.0f);
	glEnd();
}


#pragma region Event handling functions

void mouseButtonDown(int button_id, int state, int x, int y) {

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
void mouseMove(int x, int y) {

	if (mDown) {

		int dx = x - mouse_x;
		int dy = y - mouse_y;

		// Ctrl click to rotate, click on its own to move...
		if (glutGetModifiers() == GLUT_ACTIVE_CTRL) {


			theta1 += float(dy) * 0.01;
			theta1b += float(dy) * 0.01;
			theta2 += float(dy) * 0.01;

			snowmanOrientation += float(dy);
		}
		else {

			snowmanX += float(dx) * 0.0025f;
			snowmanY -= float(dy) * 0.0025f;
		}


		mouse_x = x;
		mouse_y = y;

		glutPostRedisplay();
	}
}


void keyDown(unsigned char key, int x, int y) {

	if (key == 'r') {

		snowmanX = 0.0f;
		snowmanY = 0.0f;
		snowmanOrientation = 0.0f;

		glutPostRedisplay();
	}
}


void tutorial_diplay()
{
	glm::mat4 R = glm::rotate(glm::mat4(1), theta, glm::vec3(0.0f, 0.0f, 1.0f));
	glm::mat4  T = glm::translate(glm::mat4(1), glm::vec3(-0.8f, -0.25f, 0.0f));
	R = T * R;
	glLoadMatrixf(glm::value_ptr(R));

	glUseProgram(0);
	drawHierarchy(R);
	T = glm::translate(glm::mat4(1), glm::vec3(0.3f, 0.0f, 0.0f));
	for (int i = 0; i < 5; i++)
	{
		R = T * R;
		drawHierarchy(R);
	}

	mySnowman->renderSnowman(snowmanX, snowmanY, 0.25f, snowmanOrientation);
}