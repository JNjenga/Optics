#ifndef VISUAL_CARTESIAN_H
#define VISUAL_CARTESIAN_H

#include "vis_pch.hpp"
#include <glm/glm.hpp>

namespace Vis {
	struct Cartesian
	{
		float origin_x;
		float origin_y;

		float end_x;
		float end_y;


		float cell_width;
		float cell_height;

		float scale;


		std::vector<glm::vec2> shaded;

		Cartesian(float o_x, float o_y, float e_x, float e_y, float c_w, float c_h, float s_l)
			: origin_x(o_x), origin_y(o_y), end_x(e_x),end_y(e_y),
			cell_width(c_w), cell_height(c_h), scale(s_l)
		{
		}

		void shadeCell(float x, float y)
		{
			shaded.push_back({x,y});
			shaded.erase(std::unique(shaded.begin(), shaded.end()), shaded.end());
		}

		void log() const
		{
			std::cout<<"X "<<origin_x<<" Y "<<origin_y<<"End X "<< end_x<< " End Y " << end_y<<" Cell Width "<< cell_width<<" Cell height "<< cell_height<<"\n";
		}

		const float getCellWidth() const
		{
			return scale * cell_width;
		}

		const float getCellHeight() const
		{
			return scale * cell_height;
		}
	};
}

#endif
