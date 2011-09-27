#include <immoral/game.hpp>

class test : public immoral::game
{
public:
	test(void) { }
	virtual ~test(void) { }
	
	void initialize(void)
	{
	}
	
	void load_content(void)
	{
	}
	
	void update(float elapsed)
	{
		int esc = glfwGetKey(GLFW_KEY_ESC);
		if (esc == GLFW_PRESS) m_running = false;
	}
	
	void draw(float elapsed)
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		glBegin(GL_TRIANGLES);
		glColor3ub(255, 0, 0); glVertex2d(0, 0);
		glColor3ub(0, 255, 0); glVertex2d(100, 0);
		glColor3ub(0, 0, 255); glVertex2d(50, 50);
		glEnd();
	}
};

int main(int argc, char ** argv)
{
	test * t = 0;
	t = new test();
	if (t == 0) return 0;
	
	immoral::window_settings win;
	win.width = 640;
	win.height = 480;
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
