#include "Window.h"

Window::Window(int width, int height, const char* title)
	:
	m_window(nullptr)
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