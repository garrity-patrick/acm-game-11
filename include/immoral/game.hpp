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
#include "immoral/types.hpp"
#include "immoral/window_settings.hpp"
#include "immoral/glutility.hpp"

namespace immoral
{	
	/*!
	 * \class game
	 * 
	 * Main class of the immoral engine.
	 */
	class game
	{
	protected:
		/*!
		 * The settings of the window managed by GLFW.
		 */
		window_settings m_window;
		
		/*!
		 * Is this game currently running?
		 */
		bool m_running;
		
		/*!
		 * The elapsed time in terms of the update function.
		 */
		f32 m_elapsed_update;
		
		/*!
		 * The elapsed time between iterations of the game loop.
		 */
		f32 m_elapsed_draw;
	
	public:
		/*!
		 * Constructor.
		 */
		game(void);
		
		/*!
		 * Destructor.
		 */
		virtual ~game(void);
		
		/*!
		 * Set the window settings for this game.
		 * \param win The new window settings.
		 */
		void set_window_settings(window_settings win) { m_window = win; }
		
		/*!
		 * Get the window settings for this game.
		 * \return The window settings.
		 */
		window_settings get_window_settings(void) const { return m_window; }
		
		/*!
		 * Initialize class objects.
		 */
		virtual void initialize(void);
		
		/*!
		 * Load game content such as textures and levels.
		 */
		virtual void load_content(void);
		
		/*!
		 * Update the game.
		 * \param elapsed The time that has elapsed since the last call to this
		 * function.
		 */
		virtual void update(f32 elapsed);
		
		/*!
		 * Render the game to the screen.
		 * \param elapsed The time that has elapsed since the last call to this
		 * function.
		 */
		virtual void draw(f32 elapsed);
		
		/*!
		 * Run the game. This function provides a default game loop that updates
		 * at 100 FPS. This function calls initialize and load_content before
		 * starting the game loop.
		 * \return The return status of the game (0 = normal termination).
		 */
		int run(void);
	};
}

#endif
