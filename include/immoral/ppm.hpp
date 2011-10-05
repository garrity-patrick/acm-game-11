#ifndef _IMMORAL_PPM_HPP_
#define _IMMORAL_PPM_HPP_

#include "immoral/types.hpp"

namespace immoral
{
	class ppm
	{
	private:
		u8 * m_data;
		u32 m_width;
		u32 m_height;
		u8 m_depth;
	
	public:
		ppm(void);
		ppm(const ppm & other);
		ppm(u32 width, u32 height);
		~ppm(void);
		
		ppm & operator=(const ppm & other);
		
		void clear(void);
		const u8 * data(void) const { return m_data; }
		u32 width(void) const { return m_width; }
		u32 height(void) const { return m_height; }
		u8 depth(void) const { return m_depth; }
		
		void load(const char * filename);
		void save(const char * filename);
		void save(const char * filename, bool binary);
	};
}

#endif
