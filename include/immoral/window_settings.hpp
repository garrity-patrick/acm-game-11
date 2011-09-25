#ifndef _IMMORAL_WINDOW_SETTINGS_HPP_
#define _IMMORAL_WINDOW_SETTINGS_HPP_

/*!
 * \file window_settings.hpp
 * \author Patrick Garrity
 * 
 * // Contains the window settings structure.
 */

namespace immoral
{
	class window_settings
	{
	public:
		int width;
		int height;
		int redbits;
		int greenbits;
		int bluebits;
		int alphabits;
		int depthbits;
		int stencilbits;
		bool fullscreen;
	};
}

#endif
