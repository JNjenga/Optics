#include "vis_pch.hpp"
#include <GL/gl.h>
#include "application.hpp"
#include "window.hpp"
#include <math.h>
#include <thread>
#include <chrono>
#include "input.hpp"
#include "ui.hpp"


uint32_t Vis::Application::HEIGHT;
uint32_t Vis::Application::WIDTH;
Vis::Application * Vis::Application::app;

void Vis::Application::init()
{
	WIDTH = 680;
	HEIGHT = 480;

	// Create and init window	
	m_Window_Object = new VisionWindow();
	m_Window_Object->init(WIDTH, HEIGHT);

	// Create and initialize renderer
	m_Renderer = new Renderer();
	m_Renderer->init();

}

void Vis::Application::update()
{
	 
	auto & m = Vis::Mouse::getMouse();
	auto & k = Vis::Keys::getKeys();

	/* Zooming : Left control and Scroll up/down */
	if (k.keys[GLFW_KEY_LEFT_CONTROL])
	{
		if (m.y_scroll > 0)
		{

			if (!(c->scale > 1.0f))
			{
				c->scale += 0.02f;
			}

		}
		else if (m.y_scroll < 0) {
			if (!(c->scale < 0.2f))
			{
				c->scale -= 0.02f;
			}
		}
		m.y_scroll = 0;
	}

	/* Panning : Center mouse button and move mouse */
	if (m.mouseCenterClick())
	{
		c->x_origin += m.dx;
		c->y_origin += m.dy;
	}

	/* Update type of mouse cursor when mouse enters the grid*/

	/*
	if ((m.x > c->x_origin && m.x < c->getWidthBounds()) 
			&& (m.y > c->y_origin && m.y < c->getHeightBounds()))
	{
		// TODO : Handle if the mouse enters the cartesian plane
	}
	else
	{
		// TODO : Handle if the mouse exits the cartesian plane
	}
	*/

}

void Vis::Application::run()
{
	init();
	
	auto & m = Vis::Mouse::getMouse();
	
	float width = static_cast<float>(WIDTH);
	float height = static_cast<float>(HEIGHT);

	/* Initialize the catesian plane */

	c = new Vis::CartesianPlane(0.0f, 0.0f, width, height, 40.0f, 40.0f, .5f);

	c->addShaded(7, 7);
	c->addShaded(7, 8);
	c->addShaded(7, 9);
	c->addShaded(8, 7);
	c->addShaded(8, 8);
	c->addShaded(8, 9);
	c->addShaded(9, 7);
	c->addShaded(9, 8);
	c->addShaded(9, 9);

	/* Initialize the nuklear */

	nuklearInit();

	/* Game loop */
	int counter = 0;
	while (!glfwWindowShouldClose(m_Window_Object->getWindow()))
	{
		if (counter > 10)
		{
			counter = 0;
		}
		if (counter < 10) {
			m_Renderer->clear();
			m_Renderer->drawCartesianPlane(c);
			drawUI(c);
			glfwSwapBuffers(m_Window_Object->m_Window);
		}

		glfwPollEvents();

		update();

		counter++;

		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}

	nk_glfw3_shutdown();
}


Vis::Application::~Application()
{
	delete m_Window_Object;
}

Vis::Application * Vis::Application::getApp()
{
		if (app == nullptr)
		{
			app = new Vis::Application();
		}
		return app;
}

/* API refrence
if (m.mouseLeftClick())
{
	m_Renderer->drawQuad({ 0.0f, 0.0f, 0.0f }, { m.x, m.y }, { 0.188f, 0.247f, 0.623f });
}

// Side nav
{
	m_Renderer->drawQuad({ 0.0f,  0.0f, 0.0f }, { WIDTH / 5, HEIGHT }, { 0.247f, 0.317f, 0.709f });

	// Control widgets
	m_Renderer->drawQuad({ 0.0f,  0.0f, 0.0f }, { WIDTH / 5 , 40.0f }, { 0.188f, 0.247f, 0.623f });
	m_Renderer->drawQuad({ 10.0f,  50.0f, 0.0f }, { WIDTH / 5 - 30.0f, 25.0f }, { 0.898f, 0.905f, 0.960f });
	m_Renderer->drawQuad({ 10.0f,  100.0f, 0.0f }, { WIDTH / 5 - 30.0f, 25.0f }, { 0.898f, 0.905f, 0.960f });
	m_Renderer->drawQuad({ 10.0f,  150.0f, 0.0f }, { WIDTH / 5 - 30.0f, 25.0f }, { 0.898f, 0.905f, 0.960f });

}
*/
