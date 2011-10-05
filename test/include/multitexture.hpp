#include <GL/gl.h>
#include <GL/glu.h>
#include <immoral/types.hpp>

class multitexture
{
public:
	class texture_element
	{
	private:
		u32 m_x, m_y;
		u32 m_width, m_height;
	
	public:
		texture_element(void)
		{
			m_x = 0; m_y = 0;
			m_width = 0; m_height = 0;
		}
		
		texture_element(const texture_element & other)
		{
			m_x = other.m_x; m_y = other.m_y;
			m_width = other.m_width; m_height = other.m_height;
		}
		
		~texture_element(void)
		{
		}
		
		texture_element & operator=(const texture_element & other)
		{
			if (this != & other)
			{
				m_x = other.m_x; m_y = other.m_y;
				m_width = other.m_width; m_height = other.m_height;
			}
			
			return *this;
		}
		
		u32 x(void) const { return m_x; }
		u32 y(void) const { return m_y; }
		u32 width(void) const { return m_width; }
		u32 height(void) const { return m_height; }
		
		void set_x(u32 x) { m_x = x; }
		void set_y(u32 y) { m_y = y; }
		void set_width(u32 width) { m_width = width; }
		void set_height(u32 height) { m_height = height; }
		void set(u32 x, u32 y, u32 width, u32 height)
		{
			m_x = x; m_y = y; m_width = width; m_height = height;
		}
	};
	
private:
	u8 * m_data;
	u32 m_width;
	u32 m_height;
	u32 m_bytes;
	u32 m_size;
	texture_element * m_elements;
	GLuint m_glid;

public:
	multitexture(void);
	multitexture(const multitexture & other) { copy(other); }
	~multitexture(void);
	
	multitexture & operator=(const multitexture & other)
	{
		if (this != &other)
		{
			copy(other);
		}
		
		return *this;
	}
	
	const u8 * data(void) const { return m_data; }
	u32 bytes(void) const { return m_bytes; }
	u32 width(void) const { return m_width; }
	u32 height(void) const { return m_height; }
	u32 size(void) const { return m_size; }
	GLuint id(void) const { return m_glid; }
	
	void texture_coords(u32 element, float * s, float * t) const;
	void generate(u32 width, u32 height, u32 sz);
	void load(const u8 * data, u32 bytes, u32 width, u32 height, u32 sz);
	texture_element * get_element(u32 element);
	void make_texture(void);

private:
	void copy(const multitexture & other);
};
