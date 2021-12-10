#pragma once
#include <glew\glew.h>
#include <freeglut\freeglut.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "texture_loader.h"
#include "shader_setup.h"
#include "texture_loader.h"

using namespace std;

class tardis
{
	GLuint tardis_texture;

	// Shader
	GLuint tardis_shader;

	// Uniform variable locations in tardis_shader
	GLuint locT;


public:
	tardis()
	{
		tardis_texture = wicLoadTexture(wstring(L"Resources\\Textures\\tardis.png"));

		tardis_shader = setupShaders(string("Shaders\\basic_vertex_shader.txt"), string("Shaders\\basic_fragment_shader.txt"));
		// Setup uniform locations
		locT = glGetUniformLocation(tardis_shader, "T");
	}

	void render(float x, float y, float scale, float orientation)
	{
		glUseProgram(tardis_shader);

		// Create matrices based on input parameters
		glm::mat4x4 transform = glm::translate(glm::mat4(1.0f), glm::vec3(x, y, 0.0f)) *
			glm::rotate(glm::mat4(1.0f), glm::radians(orientation), glm::vec3(0.0f, 0.0f, 1.0f)) *
			glm::scale(glm::mat4(1.0f), glm::vec3(scale, scale, 1.0f));
		
		//Give the tardis transform to the shader
		glUniformMatrix4fv(locT, 1, GL_FALSE, (GLfloat*)&transform);
		glActiveTexture(GL_TEXTURE0);
		glUniform1i(glGetUniformLocation(tardis_shader, "tardisTexture"), 0);

		/*
		 * Draw a textured quad with the tardis texture???????
		 */
		draw_textured_quad(tardis_texture, -0.5, 0.5, 0.5, -0.5);		// This draws a blue square ¯\_(ツ)_/¯
		//draw_textured_quad(tardis_texture);														// This just draws a black screen for some reason ¯\_(ツ)_/¯
	}
};

