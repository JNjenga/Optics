#ifndef VISUAL_APPLICATION_H
#define VISUAL_APPLICATION_H

#include "visual_window.hpp"

namespace Vis
{
	struct Application
	{
		virtual void init() ;
		virtual void update() ;
		virtual void run();
		virtual ~Application();

		VisualWindow * m_Window_Object;
	};
}

#endif