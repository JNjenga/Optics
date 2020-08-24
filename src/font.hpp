#ifndef VISION_FONT_H
#define VISION_FONT_H

#include "vis_pch.hpp"

struct BMFont
{
	int rows, cols;
	int width, height;
	
	int start_index;

	const char * texture_name;
};

#endif
