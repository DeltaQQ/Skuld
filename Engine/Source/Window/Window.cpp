#include "Window.h"

Window::Window()
	:
	m_window(nullptr)
{
}

void Window::create(int width, int height, const char* title)
{
	glfwInit();
	m_window = glfwCreateWindow(width, height, title, nullptr, nullptr);
	glfwWindowHint(GLFW_VISIBLE, GLFW_TRUE);
}

Window::operator bool() const
{
	glfwPollEvents();

	return !glfwWindowShouldClose(m_window);
}

Window::~Window()
{
	glfwDestroyWindow(m_window);
	glfwTerminate();
}