#include <GLFW/glfw3.h>

class Window
{
public:
	Window(int width, int height, const char* title);
	~Window();

	explicit operator bool() const;

private:
	GLFWwindow* m_window;
};