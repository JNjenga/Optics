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
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

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

	glfwSetErrorCallback(
		[](int error_code, const char* description){
			std::cout << "Glfw Error" << error_code <<" "<<description<<"\n";
	});

	glfwSetMouseButtonCallback(m_Window,
		[](GLFWwindow* window, int button, int action, int mods)
		{
			auto & m = Vis::Mouse::getMouse();

			if (action == GLFW_PRESS)
			{
				if (button == GLFW_MOUSE_BUTTON_1)
					m.m_State = Vis::MouseEvents::LEFT_CLICK;
				else if (button == GLFW_MOUSE_BUTTON_2)
					m.m_State = Vis::MouseEvents::RIGHT_CLICK;
			}
			else if(action == GLFW_RELEASE)
			{
				m.m_State = Vis::MouseEvents::RESET;
			}
			

		}
	);

	glfwSetScrollCallback(m_Window,
		[](GLFWwindow* window, double xoffset, double yoffset)
		{
			auto & m = Vis::Mouse::getMouse();
			m.y_scroll = yoffset;
			std::cout << "Xoffset : " << xoffset << " Yoffset : " << m.y_scroll << "\n";

		}
	);

	
	glfwSetCursorPosCallback(m_Window, 
		[](GLFWwindow* window, double xpos, double ypos)
		{
			auto & m = Vis::Mouse::getMouse();

			m.dx = (float)xpos - m.x;
			m.dy = (float)ypos - m.y;

			m.x = (float)xpos;
			m.y = (float)ypos;
		}
	);

	glfwSetKeyCallback(m_Window, 
		[](GLFWwindow* window, int key, int scancode, int action, int mods)
		{
			auto & k = Vis::Keys::getKeys();

			if (action == GLFW_PRESS)
			{
				k.keys[key] = key;
			}
			else if (action == GLFW_RELEASE)
			{
				k.keys[key] = 0;
			}
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
