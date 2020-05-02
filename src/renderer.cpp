#include "vis_pch.hpp"

#include "renderer.hpp"
#include "application.hpp"

void Vis::Renderer::init()
{


}

void Vis::Renderer::drawPoint(glm::vec3 position, glm::vec3 color ,
	float p_size) const
{
	glPointSize(p_size);

	glColor3fv(&color[0]);
	glBegin(GL_POINTS);
		glVertex3fv(&position[0]);
	glEnd();
}

void Vis::Renderer::drawQuad(glm::vec3 position, glm::vec2 size, glm::vec3 color) const
{
	glColor3fv(&color[0]);

	glBegin(GL_POLYGON);//begin drawing of polygon
	glVertex3f(position.x, position.y, position.z); // Left Top 
	glVertex3f(position.x + size.x, position.y, position.z); // Right Top 
	glVertex3f(position.x + size.x, position.y + size.y, position.z); // Right Bottom
	glVertex3f(position.x , position.y + size.y, position.z); // Left Bottom
	
	glEnd();//end drawing of polygon
}

void Vis::Renderer::drawLine() const
{

}

void Vis::Renderer::clear(glm::vec3 color, float alpha) const
{
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(color.r, color.g, color.b, alpha);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0f, (GLfloat)Vis::Application::WIDTH, (GLfloat)Vis::Application::HEIGHT, 0.f, 1.f, -1.f);
}
Vis::Renderer::~Renderer()
{

}
