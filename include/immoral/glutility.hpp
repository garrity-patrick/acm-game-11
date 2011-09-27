#ifndef _IMMORAL_GLUTILITY_HPP_
#define _IMMORAL_GLUTILITY_HPP_

#include <GL/gl.h>
#include <GL/glu.h>

namespace immoral
{
	void gl_enable_2d(void)
	{
		int vport[4];
		glGetIntegerv(GL_VIEWPORT, vport);
		glMatrixMode(GL_PROJECTION);
		glPushMatrix();
		glLoadIdentity();
		glOrtho(0, vport[2], 0, vport[3], -1, 1);
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glLoadIdentity();
	}
	
	void gl_disable_2d(void)
	{
		glMatrixMode(GL_PROJECTION);
		glPopMatrix();
		glMatrixMode(GL_MODELVIEW);
		glPopMatrix();
	}
}

#endif
