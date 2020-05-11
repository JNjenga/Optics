#ifndef VISUAL_APPLICATION_H
#define VISUAL_APPLICATION_H

#include "visual_window.hpp"
#include "renderer.hpp"

namespace Vis
{
	struct Application
	{
		static uint32_t WIDTH, HEIGHT;

		virtual void init() ;
		virtual void update() ;
		virtual void run();
		virtual ~Application();

		VisualWindow * m_Window_Object;
		Renderer * m_Renderer;
	};
}

#endif