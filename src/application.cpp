#include "vis_pch.hpp"
#include <GL/gl.h>
#include "application.hpp"
#include "window.hpp"
#include <math.h>
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
	/* Panning 
	*Left control and mouse move
	*/
	auto & m = Vis::Mouse::getMouse();
	auto & k = Vis::Keys::getKeys();

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

	/* Panning
	*/
	if (m.mouseCenterClick())
	{
		c->x_origin += m.dx;
		c->y_origin += m.dy;
	}

	/* Update type of mouse */

	if ((m.x > c->x_origin && m.x < c->getWidthBounds()) 
			&& (m.y > c->y_origin && m.y < c->getHeightBounds()))
	{
		// TODO : Handle if the mouse enters the cartesian plane
	}
	else
	{
		// TODO : Handle if the mouse exits the cartesian plane
	}

}

void Vis::Application::run()
{
	init();
	
	auto & m = Vis::Mouse::getMouse();
	
	float width = static_cast<float>(WIDTH);
	float height = static_cast<float>(HEIGHT);

	c = new Vis::CartesianPlane(0.0f, 0.0f, width, height, 40.0f, 40.0f, .5f);

	c->shaded.push_back(glm::vec2());
	c->shaded.push_back(glm::vec2(2.0f, 2.0f));
	c->shaded.push_back(glm::vec2(3.0f, 5.0f));
	c->shaded.push_back(glm::vec2(32.0f, 2.0f));
	c->shaded.push_back(glm::vec2(2.0f, 23.0f));

	nuklearInit();

	while (!glfwWindowShouldClose(m_Window_Object->getWindow()))
	{
		
		width = static_cast<float>(WIDTH);
		height = static_cast<float>(HEIGHT);

		m_Renderer->clear();
		
		m_Renderer->drawCartesianPlane(c);
	

		// Handle mouse scroll

		drawUI(c);
		glfwSwapBuffers(m_Window_Object->m_Window);
		glfwPollEvents();

		update();
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

/* For reference puroposes
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
