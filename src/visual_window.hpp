#ifndef VISUAL_GLFW_WINDOW_H
#define VISUAL_GLFW_WINDOW_H

namespace Vis
{
	struct VisualWindow
	{
		virtual void init() ;
		virtual void update() ;

		GLFWwindow * getWindow() const;

		virtual ~VisualWindow();
		
		GLFWwindow * m_Window;
	};
}

#endif