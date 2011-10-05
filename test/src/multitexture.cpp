#include "multitexture.hpp"

multitexture::multitexture(void)
{
	m_data = 0;
	m_bytes = 0;
	m_width = 0;
	m_height = 0;
	m_size = 0;
	m_elements = 0;
	m_glid = 0;
}

multitexture::~multitexture(void)
{
}

void multitexture::texture_coords(u32 element, float * s, float * t) const
{
	if (s == 0 || t == 0) return;
	if (element >= m_size) return;
	if (m_elements == 0) return;
	
	// s = x coordinates, t = y coordinates (for our purposes)
	// we need to figure out from [0,1] where our element is.
	texture_element * e = m_elements + element;
	s[0] = static_cast<float>(e->x()) / static_cast<float>(m_width);
	s[1] = static_cast<float>(e->x() + e->width()) / static_cast<float>(m_width);
	t[0] = static_cast<float>(e->y()) / static_cast<float>(m_height);
	t[1] = static_cast<float>(e->y() + e->height()) / static_cast<float>(m_height);
}

void multitexture::generate(u32 width, u32 height, u32 size)
{
}

multitexture::texture_element * multitexture::get_element(u32 element)
{
	if (element >= m_size) return 0;
	return m_elements + element;
}

void multitexture::load(const u8 * data, u32 bytes, u32 width, u32 height, u32 sz)
{
	if (m_data != 0) delete [] m_data; m_data = 0;
	m_bytes = bytes;
	m_data = new u8[m_bytes];
	m_width = width;
	m_height = height;
	m_size = sz;
	if (m_elements != 0) delete [] m_elements; m_elements = 0;
	m_elements = new texture_element[m_size];
	
	for (u32 i = 0; i < m_bytes; ++i) m_data[i] = data[i];
}

void multitexture::make_texture(void)
{
	//if (m_glid != 0) { glDeleteTextures(1, &m_glid); m_glid = 0; }
	glGenTextures(1, &m_glid);
	glBindTexture(GL_TEXTURE_2D, m_glid);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, 
		m_width, m_height, 0, GL_RGB,
		GL_UNSIGNED_BYTE, m_data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

void multitexture::copy(const multitexture & other)
{
	if (m_data != 0) delete [] m_data; m_data = 0;
	m_bytes = other.m_bytes;
	if (m_bytes > 0) m_data = new u8[m_bytes];
	m_width = other.m_width;
	m_height = other.m_height;
	m_size = other.m_size;
	m_elements = new texture_element[m_size];
	m_glid = 0;
	
	for (u32 i = 0; i < m_bytes; ++i)
	{
		m_data[i] = other.m_data[i];
	}
	
	for (u32 i = 0; i < m_size; ++i)
	{
		m_elements[i] = other.m_elements[i];
	}
}
