#ifndef VISION_CARTESIAN_H
#define VISION_CARTESIAN_H

#include "vis_pch.hpp"
#include <glm/glm.hpp>

namespace Vis {

	struct CartesianPlane {

		float x_origin = 0.0f;
		float y_origin = 0.0f;

		float width = 0.0f, height = 0.0f;

		float scale = 0.0f;
		float line_weight;

		float cell_width = 0.0f, cell_height = 0.0f;


		std::vector<glm::vec2> shaded;

		CartesianPlane(float x , float y,
			float w, float h, float c_w, float c_h, float s, float l_w = 3.0f)
			: x_origin{x}, y_origin{y}, width{w}, height{h}, scale{s},
			cell_width{c_w}, cell_height{c_h}, line_weight{l_w}
		{
		}

		const float getCellWidth() const
		{
			return scale * cell_width;
		}

		const float getCellHeight() const
		{
			return scale * cell_height;
		}
		const float getWidthBounds() const
		{
			return x_origin + width;
		}
		const float getHeightBounds() const
		{
			return y_origin + height;
		}

	};
}

#endif
