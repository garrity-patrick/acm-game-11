#ifndef _IMMORAL_GAME_HPP_
#define _IMMORAL_GAME_HPP_

#include <GL/glfw.h>
#include "window_settings.hpp"

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
	
	class game
	{
	protected:
		window_settings m_window;
		bool m_running;
		float m_elapsed_update;
		float m_elapsed_draw;
	
	public:
		game(void);
		virtual ~game(void);
		
		void set_window(window_settings win);
		
		virtual void initialize(void);
		virtual void load_content(void);
		virtual void update(float elapsed);
		virtual void draw(float elapsed);
		
		int run(void);
	};
}

#endif
