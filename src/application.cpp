#include "vis_pch.hpp"
#include <GL/gl.h>
#include "application.hpp"
#include "visual_window.hpp"
#include <math.h>
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
	
	float width = static_cast<float>(WIDTH);
	float height = static_cast<float>(HEIGHT);

	Vis::Cartesian * c = new Vis::Cartesian((width/5.0f), 0.0f, width, height, 40.0f, 40.0f, 0.1f);

	// J
	c->shadeCell(3,3);
	c->shadeCell(4,3);
	c->shadeCell(5,3);
	c->shadeCell(6,3);
	c->shadeCell(6,4);
	c->shadeCell(6,5);
	c->shadeCell(6,6);
	c->shadeCell(6,7);
	c->shadeCell(5,7);
	c->shadeCell(4,7);
	c->shadeCell(3,7);
	c->shadeCell(3,6);


	while (!glfwWindowShouldClose(m_Window_Object->getWindow()))
	{
		
		width = static_cast<float>(WIDTH);
		height = static_cast<float>(HEIGHT);

		m_Renderer->clear();
		
		// Side nav
		{
			m_Renderer->drawQuad({ 0.0f,  0.0f, 0.0f }, { WIDTH / 5, HEIGHT }, { 0.247f, 0.317f, 0.709f });

			// Control widgets
			m_Renderer->drawQuad({ 0.0f,  0.0f, 0.0f }, { WIDTH / 5 , 40.0f }, { 0.188f, 0.247f, 0.623f });
			m_Renderer->drawQuad({ 10.0f,  50.0f, 0.0f }, { WIDTH / 5 - 30.0f, 25.0f }, { 0.898f, 0.905f, 0.960f });
			m_Renderer->drawQuad({ 10.0f,  100.0f, 0.0f }, { WIDTH / 5 - 30.0f, 25.0f }, { 0.898f, 0.905f, 0.960f });
			m_Renderer->drawQuad({ 10.0f,  150.0f, 0.0f }, { WIDTH / 5 - 30.0f, 25.0f }, { 0.898f, 0.905f, 0.960f });

		}

		m_Renderer->drawCartesianPlane(c);
		// Update cartesian
		if(c->end_x != width)
		{
			c->origin_x = width/5;
			c->end_x = width;
			c->end_y = height;
		}
		
		// Snapping of pointer to cell corners
		if(m.x > c->origin_x){
			float p_x = 0.0f;
			float p_y = 0.0f;

			p_x = m.x - c->origin_x ;
			p_x = p_x / c->getCellWidth();
			float offset = fmodf(p_x,1.0f);
			p_x = ((offset > 0.5f) ? ceilf(p_x) : floorf(p_x))  * c->getCellWidth() + c->origin_x;
			
			p_y = m.y - c->origin_y;
			p_y = p_y / c->getCellHeight();
			offset = fmodf(p_y, 1.0f);

			p_y = ((offset > 0.5f) ? ceilf(p_y) : floorf(p_y))  * c->getCellHeight() + c->origin_y;

			// m_Renderer->drawPoint({ p_x , p_y, 0.0f }, { 0.560f, 0.f, 0.188f });
			m_Renderer->drawQuad({ p_x , p_y, 0.0f }, { c->getCellWidth(), c->getCellHeight() }, { 0.560f, 0.f, 0.188f });

		}

		m_Window_Object->update();

	}
}
Vis::Application::~Application()
{
	delete m_Window_Object;
}

/* For reference puroposes
if (m.mouseLeftClick())
{
	m_Renderer->drawQuad({ 0.0f, 0.0f, 0.0f }, { m.x, m.y }, { 0.188f, 0.247f, 0.623f });
}
*/
