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

void Vis::Renderer::drawQuad(const glm::vec3 position,const glm::vec2 size, const glm::vec3 color) const
{
	glColor3fv(&color[0]);

	glBegin(GL_POLYGON);//begin drawing of polygon
	glVertex3f(position.x, position.y, position.z); // Left Top 
	glVertex3f(position.x + size.x, position.y, position.z); // Right Top 
	glVertex3f(position.x + size.x, position.y + size.y, position.z); // Right Bottom
	glVertex3f(position.x , position.y + size.y, position.z); // Left Bottom
	
	glEnd();//end drawing of polygon
}
void Vis::Renderer::drawLine(const glm::vec2 start, const glm::vec2 end, const::glm::vec3 color ,
		float width ) const
{
	glColor3fv(&color[0]);
	glLineWidth(width);
	glBegin(GL_LINES);
	glVertex3f(start.x, start.y, 1.0f);
	glVertex3f(end.x, end.y, 1.0f);
	glEnd();

}

void Vis::Renderer::drawCartesianPlane(float x, float y, float x_end, float y_end, float cellWidth, float cellHeight) const
{

	float h_span = y_end/cellHeight;
	float v_span = x_end/cellWidth;

	// Vertical
	float j = x;
	for(float i = 0.0f; i< v_span; i++)
	{
		drawLine({j,y}, {j, y_end}, {}, 2.0f );
		// std::cout<<"first ("<<j<<","<<y<<"),("<<j<<","<<y_end<<")\n";
		j+=cellWidth;
	}
	j = 0.0f;
	for(float i = 0.0f; i< h_span; i++)
	{
		drawLine({x,j }, {x_end, j}, {}, 2.0f );
		// printf("(%d , %d ),(%d , %d)\n", x, j,x_end, j);
		j+=cellHeight;
	}


}

void Vis::Renderer::drawCartesianPlane(Vis::Cartesian * c) const
{
	// Draw shaded
	for (auto & v2 : c->shaded)
	{
		drawQuad({ c->getCellWidth() * v2.x + c->origin_x, c->getCellHeight() * v2.y + c->origin_y, 0.0f },
			{ c->getCellWidth(), c->getCellHeight() },
			{ 0.219f, 0.219f, 0.219f });
	}

	float h_span = c->end_y/c->getCellHeight();
	float v_span = c->end_x/c->getCellWidth();

	// std::cout<<"H : "<< h_span<<" V : " << v_span<<"\n";
	// c->log();
	// Vertical
	float j = c->origin_x;
	for(float i = 0.0f; i< v_span; i++)
	{
		drawLine({j,c->origin_y}, {j, c->end_y }, { 0.133f, 0.568f, 0.521f }, 1.0f );
		// std::cout<<"("<<j<<","<<c->origin_y<<"),("<<j<<","<<c->end_y<<")\n";
		j+=c->getCellWidth();
	}
	// Horizontal
	j = 0.0f;
	for(float i = 0.0f; i< h_span; i++)
	{
		drawLine({c->origin_x,j }, {c->end_x, j}, { 0.133f, 0.568f, 0.364f }, 1.0f );
		// printf("(%d , %d ),(%d , %d)\n", c->origin_x, j,c->end_x, j);
		j+=c->getCellHeight();
	}
}

void Vis::Renderer::drawCartesianPlane(Vis::CartesianPlane * c) const
{
	int v_lines = (int)(c->width / c->getCellWidth()) + 1;
	int h_lines = (int)(c->height / c->getCellHeight()) + 1;
	
	// Draw vertical lines
	
	for(int i = 0; i < v_lines; i++){
		float origin_offest = c->x_origin + (c->getCellWidth()* i);
		float end_offset = c->y_origin + c->height;
		
		if(i == v_lines/2 ){
			drawLine({ origin_offest, c->y_origin }, { origin_offest , end_offset }, {1.0f, 0.0f, 1.0f}, c->line_weight);
			continue;
		}
		drawLine({ origin_offest, c->y_origin }, { origin_offest , end_offset }, {}, c->line_weight);
	}

	
	for(int i = 0; i < h_lines; i++){
		float origin_offest = c->y_origin + (c->getCellHeight()* i);
		float end_offset = c->x_origin + c->width;

		if(i == h_lines/2 ){
			drawLine({  c->x_origin, origin_offest }, { end_offset, origin_offest  }, {0.2f, 0.6f, 0.6f}, c->line_weight);
			continue;
		}
		drawLine({  c->x_origin, origin_offest }, { end_offset, origin_offest  }, {}, c->line_weight);
	}
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
