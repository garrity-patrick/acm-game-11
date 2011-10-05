#include <GL/gl.h>
#include <GL/glu.h>
#include <immoral/game.hpp>
#include <immoral/ppm.hpp>
#include <iostream>
#include "multitexture.hpp"

using std::cerr;
using std::endl;

const int TILE_SIZE=32;
const int SCX = 800;
const int SCY = 500;

class test : public immoral::game
{
private:
	immoral::ppm image;
	multitexture tex;
	GLuint texture;
	
public:
	test(void) { }
	virtual ~test(void)
	{
		glDeleteTextures(1, &texture);
	}
	
	void initialize(void)
	{
	}
	
	void load_content(void)
	{
		image.load("resources/grassdirt.ppm");
		tex.load(image.data(), image.width() * image.height() * 3,
				 image.width(), image.height(), 2);
		tex.make_texture();
		tex.get_element(0)->set(0, 0, 128, 128);
		tex.get_element(1)->set(128, 0, 128, 128);
		
		cerr << "width = " << tex.width() << endl;
		cerr << "height = " << tex.height() << endl;
		cerr << "bytes = " << tex.bytes() << endl;
		cerr << "size = " << tex.size() << endl;
		cerr << "GLid = " << tex.id() << endl;
		
		/*glEnable(GL_TEXTURE_2D);
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, 
			image.width(), image.height(), 0, GL_RGB,
			GL_UNSIGNED_BYTE, image.data());
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);*/
	}
	
	void update(float elapsed)
	{
		int esc = glfwGetKey(GLFW_KEY_ESC);
		if (esc == GLFW_PRESS) m_running = false;
	}
	
	void draw(float elapsed)
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glLoadIdentity();
		glColor3f(1.0f, 1.0f, 1.0f);
		
		int columns = (SCX / TILE_SIZE);
		int rows = (SCY / TILE_SIZE) + 1;
		
		for (int i = 0; i < columns; ++i)
		{
			for (int j = 0; j < rows; ++j)
			{
				glPushMatrix();
				glTranslatef(i * TILE_SIZE, j * TILE_SIZE, 0.0f);
				glBegin(GL_QUADS);
				glColor3f(0, 
					((float)(i * TILE_SIZE) / (float)SCX) / 1.0f, 
					((float)(j * TILE_SIZE) / (float)SCY) / 1.0f);
				glVertex2i(0, 0);
				glVertex2i(TILE_SIZE, 0);
				glVertex2i(TILE_SIZE, TILE_SIZE);
				glVertex2i(0, TILE_SIZE);
				glEnd();
				glPopMatrix();
			}
		}
		
		glLoadIdentity();
		glColor3f(1.0f, 1.0f, 1.0f);
		
		/*glPushMatrix();
		glBindTexture(GL_TEXTURE_2D, texture);
		glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f); glVertex2i(256 + 0, 256 + 0);
		glTexCoord2f(0.5f, 0.0f); glVertex2i(256 + 128, 256 + 0);
		glTexCoord2f(0.5f, 1.0f); glVertex2i(256 + 128, 256 + 128);
		glTexCoord2f(0.0f, 1.0f); glVertex2i(256 + 0, 256 + 128);
		
		glTexCoord2f(0.5f, 0.0f); glVertex2i(256 + 128, 256 + 0);
		glTexCoord2f(1.0f, 0.0f); glVertex2i(256 + 256, 256 + 0);
		glTexCoord2f(1.0f, 1.0f); glVertex2i(256 + 256, 256 + 128);
		glTexCoord2f(0.5f, 1.0f); glVertex2i(256 + 128, 256 + 128);
		glEnd();
		glPopMatrix();*/
		
		glPushMatrix();
		glBindTexture(GL_TEXTURE_2D, tex.id());
		glBegin(GL_QUADS);
		float s[2] = { 0.0f, 0.0f };
		float t[2] = { 0.0f, 0.0f };
		
		for (u32 i = 0; i < tex.size(); ++i)
		{
			tex.texture_coords(i, s, t);
			u32 w = tex.get_element(i)->width();
			u32 h = tex.get_element(i)->height();
			glTexCoord2f(s[0], t[0]); glVertex2i(i * w, i * h);
			glTexCoord2f(s[1], t[0]); glVertex2i(i * w + w, i * h);
			glTexCoord2f(s[1], t[1]); glVertex2i(i * w + w, i * h + h);
			glTexCoord2f(s[0], t[1]); glVertex2i(i * w, i * h + h);
		}
		
		glEnd();
		glPopMatrix();
	}
};

int main(int argc, char ** argv)
{
	test * t = 0;
	t = new test();
	if (t == 0) return 0;
	
	immoral::window_settings win;
	win.width = SCX;
	win.height = SCY;
	win.redbits = 0;
	win.greenbits = 0;
	win.bluebits = 0;
	win.alphabits = 0;
	win.depthbits = 0;
	win.stencilbits = 0;
	win.fullscreen = false;
	t->set_window_settings(win);
	
	int result = t->run();
	delete t;
	return result;
}
