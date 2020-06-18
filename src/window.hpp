#ifndef VISION_GLFW_WINDOW_H
#define VISION_GLFW_WINDOW_H

namespace Vis
{
	struct VisionWindow
	{
		virtual void init(int width, int height) ;
		virtual void update() ;

		GLFWwindow * getWindow() const;

		~VisionWindow();
		
		GLFWwindow * m_Window;
	};
}

#endif