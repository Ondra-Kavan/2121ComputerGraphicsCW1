#pragma once

#pragma once
#include <glew/glew.h>


/**
 * \brief Draws a textured quad across the whole screen
 * \param texture the texture to draw
 */
inline void draw_textured_quad(GLuint texture)
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


/**
 * \brief Draws a textured quad at the specified coordinates
 * \param texture The texture to be drawn
 * \param tl_pos_x X coordinate of the top lef corner of the quad
 * \param tl_pos_y Y coordinate of the top lef corner of the quad
 * \param br_pos_x X coordinate of the bottom right of the quad
 * \param br_pos_y Y coordinate of the bottom right of the quad
 */
inline void draw_textured_quad(GLuint texture, GLfloat tl_pos_x, GLfloat tl_pos_y, GLfloat br_pos_x, GLfloat br_pos_y)
{

	glBindTexture(GL_TEXTURE_2D, texture);

	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

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
