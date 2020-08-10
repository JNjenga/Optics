#ifndef VISION_APPLICATION_H
#define VISION_APPLICATION_H

#include "window.hpp"
#include "renderer.hpp"

namespace Vis
{
	class Application
	{
	public:
		static uint32_t WIDTH, HEIGHT;

		void init() ;
		void update() ;
		void run();

		~Application();

		VisionWindow * m_Window_Object;
		Renderer * m_Renderer;
		Vis::CartesianPlane * c;

		static Vis::Application  * getApp();

	private:
		static Vis::Application * app;


	};
}


#endif
