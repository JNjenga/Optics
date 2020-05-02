#include "vis_pch.hpp"

#include "visual_window.hpp"
#include "application.hpp"
#include "input.hpp"

void Vis::VisualWindow::init(int width, int height)
{
	if (!glfwInit())
	{
		LOG_FATAL("GLFW could not init");
	}

	m_Window = glfwCreateWindow(width, height, "Visual", NULL, NULL);

	if (!m_Window)
	{
		glfwTerminate();
		LOG_ERROR("GLFW window creation failed !");

	}

	glfwSetWindowSizeCallback(m_Window,
		[](GLFWwindow * window, int width, int height) {
			glViewport(0, 0, (GLsizei)width, (GLsizei)height);
			Vis::Application::WIDTH = width;
			Vis::Application::HEIGHT = height;
	}
	);

	glfwSetMouseButtonCallback(m_Window,
		[](GLFWwindow* window, int button, int action, int mods)
		{
			auto & m = Vis::Mouse::getMouse();
			if (button == GLFW_MOUSE_BUTTON_1)
				m.m_State = Vis::MouseEvents::LEFT_CLICK;
			else if(button == GLFW_MOUSE_BUTTON_2)
				m.m_State = Vis::MouseEvents::RIGHT_CLICK;

		}
	);

	glfwSetScrollCallback(m_Window,
		[](GLFWwindow* window, double xoffset, double yoffset)
		{
			// auto m = Vis::Mouse::getMouse();

		}
	);
	
	glfwSetCursorPosCallback(m_Window, 
		[](GLFWwindow* window, double xpos, double ypos)
		{
			auto & m = Vis::Mouse::getMouse();
			std::cout <<"B4 : "<< m.x << " " << m.y << "\n";

			m.x = (float)xpos;
			m.y = (float)ypos;
			std::cout << m.x << " " << m.y << "\n";
		}
	);

	glfwMakeContextCurrent(m_Window);
	
	glViewport(0, 0, (GLsizei)width, (GLsizei)height);

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
