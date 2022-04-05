#include <GLFW/glfw3.h>

class Window
{
public:
	Window();
	~Window();

	void create(int width, int height, const char* title);

	explicit operator bool() const;

private:
	GLFWwindow* m_window;
};