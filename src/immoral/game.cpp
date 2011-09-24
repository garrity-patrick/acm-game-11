#include "immoral/game.hpp"
#include <iostream>
#include <ctime>

namespace immoral
{
	game::game(void)
	{
		m_running = false;
		m_elapsed_update = 0.0f;
		m_elapsed_draw = 0.0f;
	}
	
	game::~game(void)
	{
	}
	
	void game::set_window(window_settings win)
	{
		m_window = win;
	}
	
	void game::initialize(void)
	{
	}
	
	void game::load_content(void)
	{
	}
	
	void game::update(float elapsed)
	{
	}
	
	void game::draw(float elapsed)
	{
	}
	
	int game::run(void)
	{
		m_running = true;
		
		if (!glfwInit())
		{
			std::cerr << "Could not initialize the GLFW." << std::endl;
			return 1;
		}
		
		// Setup options for the window.
		glfwOpenWindowHint(GLFW_WINDOW_NO_RESIZE, GL_TRUE);
		
		// Create a window with the set window parameters.
		int mode = GLFW_WINDOW;
		if (m_window.fullscreen) mode = GLFW_FULLSCREEN;
		
		if (!glfwOpenWindow(
			m_window.width, 
			m_window.height, 
			m_window.redbits,
			m_window.greenbits,
			m_window.bluebits,
			m_window.alphabits,
			m_window.depthbits,
			m_window.stencilbits,
			mode))
		{
			glfwTerminate();
			std::cerr << "Could not open the window." << std::endl;
			return 1;
		}
		
		// Set additional window information.
		glfwSetWindowTitle("IMM0RAL");
		
		this->initialize();
		this->load_content();
		
		// Enable 2D mode.
		gl_enable_2d();
		
		// Timing information
		// We want to update at 100 FPS, and let drawing be unrestricted.
		clock_t update_rate = CLOCKS_PER_SEC / 100;
		clock_t tick_count = clock();
		clock_t elapsed_time = update_rate;
		clock_t actual_elapsed_time = 0;
		
		while (m_running)
		{
			// Calculate the elapsed time.
			actual_elapsed_time = clock() - tick_count;
			elapsed_time += actual_elapsed_time;
			
			if (elapsed_time >= update_rate)
			{
				// Get the elapsed time (in seconds) to pass to update.
				m_elapsed_update = (float)elapsed_time / (float)CLOCKS_PER_SEC;
				
				// Update the game.
				this->update(m_elapsed_update);
				
				// Reset the elapsed time.
				elapsed_time = 0;
			}
			
			// Update the tick count, and calculate the elapsed time (in
			// seconds) since the last draw (every frame).
			tick_count = clock();
			m_elapsed_draw = (float)actual_elapsed_time / (float)CLOCKS_PER_SEC;
			
			// Draw the game.
			this->draw(m_elapsed_draw);
			
			// Swap the front and back buffers.
			glfwSwapBuffers();
		}
		
		glfwTerminate();
		return 0;
	}
}
