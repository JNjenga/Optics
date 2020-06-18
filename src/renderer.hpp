#ifndef VISION_RENDERER_H
#define VISION_RENDERER_H

#include <glm/glm.hpp>
#include "cartesian.hpp"

namespace Vis
{

	struct Renderer
	{
		virtual void init() ;
		
		virtual void drawPoint(
			glm::vec3 position, glm::vec3 color = glm::vec3(1.0f, 0.0f, 0.0f),
			float p_size = 10.0f) const;

		virtual void drawQuad(
			const glm::vec2 position,
			const glm::vec2 size,
			const glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f)) const;
		virtual void drawLine(const glm::vec2 start, const glm::vec2 end,
				const::glm::vec3 color = glm::vec3(1.0f,0.0f, 0.0f) ,
				float width = 1.0f) const;

		virtual void drawCartesianPlane(float x, float y,float x_end, float y_end,
				float cellWidth, float cellHeight) const ;

		void drawCartesianPlane(CartesianPlane *c) const;
		
		virtual void clear(glm::vec3 color = glm::vec3(0.92f, 0.92f, 0.92f), float alpha = 1.0f) const;

		virtual ~Renderer();

	};
}

#endif
