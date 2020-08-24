#include "vis_pch.hpp"

#include "ui.hpp"
#include "renderer.hpp"

void initUI()
{
	
}

void drawButton(Button * b)
{
	drawQuad({ b->x, b->y }, 0.0f, { b->width, b->height }, b->color);
	drawText(
		b->text,
		{ b->x , b->y },
		{ b->text_size , b->text_size },
		{1.0f, 1.0f, 1.0f}
	);
}