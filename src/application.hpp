#ifndef VISUAL_APPLICATION_H
#define VISUAL_APPLICATION_H

#include "visual_window.hpp"
#include "renderer.hpp"

namespace Vis
{
	struct Application
	{
		static uint32_t WIDTH, HEIGHT;

		void init() ;
		void update() ;
		void run();

		~Application();

		VisualWindow * m_Window_Object;
		Renderer * m_Renderer;
		Vis::Cartesian * c;

		static Vis::Application  * getApp();

	private:
		static Vis::Application * app;


	};
}


#endif