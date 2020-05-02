#include "vis_pch.hpp"
#include <gl/GL.h>
#include "application.hpp"
#include "visual_window.hpp"

#include "input.hpp"

uint32_t Vis::Application::HEIGHT;
uint32_t Vis::Application::WIDTH;


void Vis::Application::init()
{
	WIDTH = 680;
	HEIGHT = 480;

	// Create and init window	
	m_Window_Object = new VisualWindow();
	m_Window_Object->init(WIDTH, HEIGHT);

	/*
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		LOG_FATAL("Failed to load glad\n");
	}
	*/

	// Create and initialize renderer
	m_Renderer = new Renderer();
	m_Renderer->init();


}

void Vis::Application::update()
{

}

void Vis::Application::run()
{
	init();

	auto & m = Vis::Mouse::getMouse();
	

	while (!glfwWindowShouldClose(m_Window_Object->getWindow()))
	{
		
		m_Renderer->clear();
		
		m_Renderer->drawQuad({ 0.0f,  0.0f, 0.0f }, { WIDTH / 5, HEIGHT }, { 0.247f, 0.317f, 0.709f });
		m_Renderer->drawQuad({ 0.0f,  0.0f, 0.0f }, { WIDTH / 5 , 40.0f }, { 0.188f, 0.247f, 0.623f });
		m_Renderer->drawQuad({ 10.0f,  50.0f, 0.0f }, { WIDTH / 5 - 30.0f, 25.0f }, { 0.898f, 0.905f, 0.960f });
		m_Renderer->drawQuad({ 10.0f,  100.0f, 0.0f }, { WIDTH / 5 - 30.0f, 25.0f }, { 0.898f, 0.905f, 0.960f });
		m_Renderer->drawQuad({ 10.0f,  150.0f, 0.0f }, { WIDTH / 5 - 30.0f, 25.0f }, { 0.898f, 0.905f, 0.960f });
		m_Renderer->drawPoint({ m.x, m.y, 0.0f }, {1.0f, 0.0f, 1.0f}, 20.0f);
		if (m.mouseLeftClick())
		{
			m_Renderer->drawQuad({ 0.0f, 0.0f, 0.0f }, { m.x, m.y }, { 0.188f, 0.247f, 0.623f });
		}
		m_Window_Object->update();

	}
}
Vis::Application::~Application()
{
	delete m_Window_Object;
}
