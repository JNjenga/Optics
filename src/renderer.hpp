#ifndef VISUAL_RENDERER_H
#define VISUAL_RENDERER_H

#include <glm/glm.hpp>

namespace Vis
{
	struct Renderer
	{
		virtual void init() ;
		
		virtual void drawPoint(
			glm::vec3 position, glm::vec3 color = glm::vec3(1.0f, 0.0f, 0.0f),
			float p_size = 10.0f) const;

		virtual void drawQuad(
			glm::vec3 position,
			glm::vec2 size,
			glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f)) const;
		virtual void drawLine() const;

		virtual void clear(glm::vec3 color = glm::vec3(0.9f, 0.9f, 0.9f), float alpha = 1.0f) const;

		virtual ~Renderer();

	};
}

#endif