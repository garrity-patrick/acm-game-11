#ifndef _IMMORAL_GAME_HPP_
#define _IMMORAL_GAME_HPP_

/*!
 * \file game.hpp
 * \author Patrick Garrity
 * 
 * Contains the definition of the game class. This class is intended to be the
 * starting-point for games built using this engine. It provides an interface
 * for game functions, provides access to resources (etc.), and provides a
 * default game loop.
 */

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
	
	/*!
	 * \class game
	 * 
	 * Main class of the immoral engine.
	 */
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
		window_settings get_window(void) const { return m_window; }
		
		virtual void initialize(void);
		virtual void load_content(void);
		virtual void update(float elapsed);
		virtual void draw(float elapsed);
		
		int run(void);
	};
}

#endif
