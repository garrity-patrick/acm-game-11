#ifndef _IMMORAL_WINDOW_SETTINGS_HPP_
#define _IMMORAL_WINDOW_SETTINGS_HPP_

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
