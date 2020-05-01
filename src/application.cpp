#include "vis_pch.hpp"
#include <gl/GL.h>
#include "application.hpp"
#include "visual_window.hpp"

void Vis::Application::init()
{

	// Create and init window	
	m_Window_Object = new VisualWindow();
	m_Window_Object->init();

	/*
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		LOG_FATAL("Failed to load glad\n");
	}
	*/

}

void Vis::Application::update()
{

}

void Vis::Application::run()
{
	init();

	while (!glfwWindowShouldClose(m_Window_Object->getWindow()))
	{
		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(1.0f, 0.5f, 1.0f, 1.0f);


		glBegin(GL_TRIANGLES);//start drawing a line loop
		glVertex3f(-1.0f, 0.0f, 0.0f);//left of window
		glVertex3f(0.0f, -1.0f, 0.0f);//bottom of window
		glVertex3f(1.0f, 0.0f, 0.0f);//right of window
		glVertex3f(0.0f, 1.0f, 0.0f);//top of window
		glEnd();//end drawing of line loop

		m_Window_Object->update();

	}
}
Vis::Application::~Application()
{
	delete m_Window_Object;
}
