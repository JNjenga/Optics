#ifndef VISION_UI_H
#define VISION_UI_H

#include "vis_pch.hpp"

struct Button
{
	const char * text;
	float text_size;
	float width, height;
	float x, y;
	float padding;
	glm::vec3 color;
};

void initUI();
void drawButton(Button *);

#endif
