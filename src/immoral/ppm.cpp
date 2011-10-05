#include "immoral/ppm.hpp"
#include <string>
#include <sstream>
#include <fstream>

namespace immoral
{
	ppm::ppm()
	{
		m_data = 0;
		m_width = 0;
		m_height = 0;
		m_depth = 255;
	}
	
	ppm::ppm(const ppm & other)
	{
		m_width = other.m_width;
		m_height = other.m_height;
		m_data = 0;
		m_depth = other.m_depth;
		
		if (m_width > 0  && m_height > 0 && other.m_data != 0)
		{
			m_data = new u8[m_width * m_height * 3];
			for (u32 i = 0; i < (m_width * m_height * 3); ++i)
			{
				m_data[i] = other.m_data[i];
			}
		}
	}
	
	ppm::ppm(u32 width, u32 height)
	{
		m_width = width;
		m_height = height;
		m_data = 0;
		m_depth = 255;
		
		if (m_width > 0 && m_height > 0)
		{
			m_data = new u8[m_width * m_height];
		}
	}
	
	ppm::~ppm(void)
	{
		clear();
	}
		
	ppm & ppm::operator=(const ppm & other)
	{
		if (this != &other)
		{
			m_width = other.m_width;
			m_height = other.m_height;
			m_data = 0;
			m_depth = other.m_depth;
			
			if (m_width > 0  && m_height > 0 && other.m_data != 0)
			{
				m_data = new u8[m_width * m_height * 3];
				for (u32 i = 0; i < (m_width * m_height * 3); ++i)
				{
					m_data[i] = other.m_data[i];
				}
			}
		}
		
		return *this;
	}
	
	void ppm::clear(void)
	{
		if (m_data != 0) delete [] m_data;
		m_data = 0;
		m_width = 0;
		m_height = 0;
	}
	
	void ppm::load(const char * filename)
	{
		using std::ifstream;
		using std::string;
		using std::stringstream;
		
		ifstream stm(filename);
		
		if (stm.is_open())
		{
			char c = 'P';
			
			stm.get(c);
			if (c != 'P')
			{
				// Error: Bad PPM file header.
				return;
			}
			
			bool binary = true;
			
			stm.get(c);
			if (c == '3')
			{
				// ASCII mode
				binary = false;
			}
			else if (c == '6')
			{
				// BINARY mode
				binary = true;
			}
			else
			{
				// Error: Bad PPM file header.
				return;
			}
			
			string line;
			
			// Step 1: Finish reading header information.
			while (stm.good())
			{
				getline(stm, line);
				if (line.size() == 0) continue;
				bool comment = false;
				bool ws = true;
				for (u32 i = 0; i < line.size(); ++i)
				{
					// Blank lines
					if (line[i] != ' ' 
						&& line[i] != '\n' 
						&& line[i] != '\t') ws = false;
					// Comments
					if (line[i] == '#') { comment = true; break; }
				}
				
				if (!comment && !ws)
				{
					// First parse the columns and rows (width/height).
					stringstream ss1(line);
					ss1 >> m_width;
					ss1 >> m_height;
					
					// Read in the color depth.
					getline(stm, line);
					stringstream ss2(line);
					ss2 >> m_depth;
					break;
				}
			}
			
			if (m_data != 0) delete [] m_data; m_data = 0;
			
			// Create the image.
			if (m_width > 0 && m_height > 0)
			{
				m_data = new u8[m_width * m_height * 3];
			}
			else
			{
				// Error: Invalid width/height.
				return;
			}
			
			// Step 2: Read the stuff.
			if (!binary)
			{
				u32 counter = 0;
				while (stm.good())
				{
					getline(stm, line);
					if (line.size() == 0) continue;
					
					stringstream ss(line);
					for (u32 i = 0; i < (m_width * 3); ++i)
					{
						u8 color = 0;
						ss >> color;
						m_data[(m_width * counter) + i] = color;
					}
					
					++counter;
				}
			}
			else
			{
				std::streampos position = stm.tellg();
				stm.close();
				stm.open(filename, std::ios::binary);
				stm.seekg(position);
				stm.read(reinterpret_cast<char *>(m_data), m_width * m_height * 3);
			}
			
			// Close the file.
			stm.close();
		}
	}
	
	void ppm::save(const char * filename)
	{
	}
	
	void ppm::save(const char * filename, bool binary)
	{
	}
}
