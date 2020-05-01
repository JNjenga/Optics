#include "vis_pch.hpp"

#include "visual_window.hpp"

void Vis::VisualWindow::init()
{
	if (!glfwInit())
	{
		LOG_FATAL("GLFW could not init");
	}

	m_Window = glfwCreateWindow(720, 680, "Visual", NULL, NULL);

	if (!m_Window)
	{
		glfwTerminate();
		LOG_ERROR("GLFW window creation failed !");

	}

	glfwMakeContextCurrent(m_Window);


}

void Vis::VisualWindow::update()
{
	glfwPollEvents();
	glfwSwapBuffers(m_Window);
}

GLFWwindow * Vis::VisualWindow::getWindow() const
{
	return m_Window;
}
Vis::VisualWindow::~VisualWindow()
{
	glfwTerminate();
}
