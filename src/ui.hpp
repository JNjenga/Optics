#ifndef VISION_UI_H
#define VISION_UI_H

#define NK_INCLUDE_FIXED_TYPES
#define NK_INCLUDE_STANDARD_IO
#define NK_INCLUDE_STANDARD_VARARGS
#define NK_INCLUDE_DEFAULT_ALLOCATOR
#define NK_INCLUDE_VERTEX_BUFFER_OUTPUT
#define NK_INCLUDE_FONT_BAKING
#define NK_INCLUDE_DEFAULT_FONT
#define NK_IMPLEMENTATION
#define NK_GLFW_GL2_IMPLEMENTATION
#define NK_KEYSTATE_BASED_INPUT

#include "application.hpp"
#include "cartesian.hpp"

#include "nuklear/nuklear.h"
#include "nuklear/nuklear_glfw_gl2.h"

static struct nk_context * ctx;
enum theme { THEME_BLACK, THEME_WHITE, THEME_RED, THEME_BLUE, THEME_DARK };

static void
set_style(struct nk_context *ctx, enum theme theme)
{
	struct nk_color table[NK_COLOR_COUNT];
	if (theme == THEME_WHITE) {
		table[NK_COLOR_TEXT] = nk_rgba(70, 70, 70, 255);
		table[NK_COLOR_WINDOW] = nk_rgba(175, 175, 175, 255);
		table[NK_COLOR_HEADER] = nk_rgba(175, 175, 175, 255);
		table[NK_COLOR_BORDER] = nk_rgba(0, 0, 0, 255);
		table[NK_COLOR_BUTTON] = nk_rgba(185, 185, 185, 255);
		table[NK_COLOR_BUTTON_HOVER] = nk_rgba(170, 170, 170, 255);
		table[NK_COLOR_BUTTON_ACTIVE] = nk_rgba(160, 160, 160, 255);
		table[NK_COLOR_TOGGLE] = nk_rgba(150, 150, 150, 255);
		table[NK_COLOR_TOGGLE_HOVER] = nk_rgba(120, 120, 120, 255);
		table[NK_COLOR_TOGGLE_CURSOR] = nk_rgba(175, 175, 175, 255);
		table[NK_COLOR_SELECT] = nk_rgba(190, 190, 190, 255);
		table[NK_COLOR_SELECT_ACTIVE] = nk_rgba(175, 175, 175, 255);
		table[NK_COLOR_SLIDER] = nk_rgba(190, 190, 190, 255);
		table[NK_COLOR_SLIDER_CURSOR] = nk_rgba(80, 80, 80, 255);
		table[NK_COLOR_SLIDER_CURSOR_HOVER] = nk_rgba(70, 70, 70, 255);
		table[NK_COLOR_SLIDER_CURSOR_ACTIVE] = nk_rgba(60, 60, 60, 255);
		table[NK_COLOR_PROPERTY] = nk_rgba(175, 175, 175, 255);
		table[NK_COLOR_EDIT] = nk_rgba(150, 150, 150, 255);
		table[NK_COLOR_EDIT_CURSOR] = nk_rgba(0, 0, 0, 255);
		table[NK_COLOR_COMBO] = nk_rgba(175, 175, 175, 255);
		table[NK_COLOR_CHART] = nk_rgba(160, 160, 160, 255);
		table[NK_COLOR_CHART_COLOR] = nk_rgba(45, 45, 45, 255);
		table[NK_COLOR_CHART_COLOR_HIGHLIGHT] = nk_rgba(255, 0, 0, 255);
		table[NK_COLOR_SCROLLBAR] = nk_rgba(180, 180, 180, 255);
		table[NK_COLOR_SCROLLBAR_CURSOR] = nk_rgba(140, 140, 140, 255);
		table[NK_COLOR_SCROLLBAR_CURSOR_HOVER] = nk_rgba(150, 150, 150, 255);
		table[NK_COLOR_SCROLLBAR_CURSOR_ACTIVE] = nk_rgba(160, 160, 160, 255);
		table[NK_COLOR_TAB_HEADER] = nk_rgba(180, 180, 180, 255);
		nk_style_from_table(ctx, table);
	}
	else if (theme == THEME_RED) {
		table[NK_COLOR_TEXT] = nk_rgba(190, 190, 190, 255);
		table[NK_COLOR_WINDOW] = nk_rgba(30, 33, 40, 215);
		table[NK_COLOR_HEADER] = nk_rgba(181, 45, 69, 220);
		table[NK_COLOR_BORDER] = nk_rgba(51, 55, 67, 255);
		table[NK_COLOR_BUTTON] = nk_rgba(181, 45, 69, 255);
		table[NK_COLOR_BUTTON_HOVER] = nk_rgba(190, 50, 70, 255);
		table[NK_COLOR_BUTTON_ACTIVE] = nk_rgba(195, 55, 75, 255);
		table[NK_COLOR_TOGGLE] = nk_rgba(51, 55, 67, 255);
		table[NK_COLOR_TOGGLE_HOVER] = nk_rgba(45, 60, 60, 255);
		table[NK_COLOR_TOGGLE_CURSOR] = nk_rgba(181, 45, 69, 255);
		table[NK_COLOR_SELECT] = nk_rgba(51, 55, 67, 255);
		table[NK_COLOR_SELECT_ACTIVE] = nk_rgba(181, 45, 69, 255);
		table[NK_COLOR_SLIDER] = nk_rgba(51, 55, 67, 255);
		table[NK_COLOR_SLIDER_CURSOR] = nk_rgba(181, 45, 69, 255);
		table[NK_COLOR_SLIDER_CURSOR_HOVER] = nk_rgba(186, 50, 74, 255);
		table[NK_COLOR_SLIDER_CURSOR_ACTIVE] = nk_rgba(191, 55, 79, 255);
		table[NK_COLOR_PROPERTY] = nk_rgba(51, 55, 67, 255);
		table[NK_COLOR_EDIT] = nk_rgba(51, 55, 67, 225);
		table[NK_COLOR_EDIT_CURSOR] = nk_rgba(190, 190, 190, 255);
		table[NK_COLOR_COMBO] = nk_rgba(51, 55, 67, 255);
		table[NK_COLOR_CHART] = nk_rgba(51, 55, 67, 255);
		table[NK_COLOR_CHART_COLOR] = nk_rgba(170, 40, 60, 255);
		table[NK_COLOR_CHART_COLOR_HIGHLIGHT] = nk_rgba(255, 0, 0, 255);
		table[NK_COLOR_SCROLLBAR] = nk_rgba(30, 33, 40, 255);
		table[NK_COLOR_SCROLLBAR_CURSOR] = nk_rgba(64, 84, 95, 255);
		table[NK_COLOR_SCROLLBAR_CURSOR_HOVER] = nk_rgba(70, 90, 100, 255);
		table[NK_COLOR_SCROLLBAR_CURSOR_ACTIVE] = nk_rgba(75, 95, 105, 255);
		table[NK_COLOR_TAB_HEADER] = nk_rgba(181, 45, 69, 220);
		nk_style_from_table(ctx, table);
	}
	else if (theme == THEME_BLUE) {
		table[NK_COLOR_TEXT] = nk_rgba(20, 20, 20, 255);
		table[NK_COLOR_WINDOW] = nk_rgba(202, 212, 214, 255);
		table[NK_COLOR_HEADER] = nk_rgba(137, 182, 224, 255);
		table[NK_COLOR_BORDER] = nk_rgba(140, 159, 173, 255);
		table[NK_COLOR_BUTTON] = nk_rgba(137, 182, 224, 255);
		table[NK_COLOR_BUTTON_HOVER] = nk_rgba(142, 187, 229, 255);
		table[NK_COLOR_BUTTON_ACTIVE] = nk_rgba(147, 192, 234, 255);
		table[NK_COLOR_TOGGLE] = nk_rgba(177, 210, 210, 255);
		table[NK_COLOR_TOGGLE_HOVER] = nk_rgba(182, 215, 215, 255);
		table[NK_COLOR_TOGGLE_CURSOR] = nk_rgba(137, 182, 224, 255);
		table[NK_COLOR_SELECT] = nk_rgba(177, 210, 210, 255);
		table[NK_COLOR_SELECT_ACTIVE] = nk_rgba(137, 182, 224, 255);
		table[NK_COLOR_SLIDER] = nk_rgba(177, 210, 210, 255);
		table[NK_COLOR_SLIDER_CURSOR] = nk_rgba(137, 182, 224, 245);
		table[NK_COLOR_SLIDER_CURSOR_HOVER] = nk_rgba(142, 188, 229, 255);
		table[NK_COLOR_SLIDER_CURSOR_ACTIVE] = nk_rgba(147, 193, 234, 255);
		table[NK_COLOR_PROPERTY] = nk_rgba(210, 210, 210, 255);
		table[NK_COLOR_EDIT] = nk_rgba(210, 210, 210, 225);
		table[NK_COLOR_EDIT_CURSOR] = nk_rgba(20, 20, 20, 255);
		table[NK_COLOR_COMBO] = nk_rgba(210, 210, 210, 255);
		table[NK_COLOR_CHART] = nk_rgba(210, 210, 210, 255);
		table[NK_COLOR_CHART_COLOR] = nk_rgba(137, 182, 224, 255);
		table[NK_COLOR_CHART_COLOR_HIGHLIGHT] = nk_rgba(255, 0, 0, 255);
		table[NK_COLOR_SCROLLBAR] = nk_rgba(190, 200, 200, 255);
		table[NK_COLOR_SCROLLBAR_CURSOR] = nk_rgba(64, 84, 95, 255);
		table[NK_COLOR_SCROLLBAR_CURSOR_HOVER] = nk_rgba(70, 90, 100, 255);
		table[NK_COLOR_SCROLLBAR_CURSOR_ACTIVE] = nk_rgba(75, 95, 105, 255);
		table[NK_COLOR_TAB_HEADER] = nk_rgba(156, 193, 220, 255);
		nk_style_from_table(ctx, table);
	}
	else if (theme == THEME_DARK) {
		table[NK_COLOR_TEXT] = nk_rgba(210, 210, 210, 255);
		table[NK_COLOR_WINDOW] = nk_rgba(57, 67, 71, 255);
		table[NK_COLOR_HEADER] = nk_rgba(51, 51, 56, 255);
		table[NK_COLOR_BORDER] = nk_rgba(46, 46, 46, 255);
		table[NK_COLOR_BUTTON] = nk_rgba(48, 83, 111, 255);
		table[NK_COLOR_BUTTON_HOVER] = nk_rgba(58, 93, 121, 255);
		table[NK_COLOR_BUTTON_ACTIVE] = nk_rgba(63, 98, 126, 255);
		table[NK_COLOR_TOGGLE] = nk_rgba(50, 58, 61, 255);
		table[NK_COLOR_TOGGLE_HOVER] = nk_rgba(45, 53, 56, 255);
		table[NK_COLOR_TOGGLE_CURSOR] = nk_rgba(48, 83, 111, 255);
		table[NK_COLOR_SELECT] = nk_rgba(57, 67, 61, 255);
		table[NK_COLOR_SELECT_ACTIVE] = nk_rgba(48, 83, 111, 255);
		table[NK_COLOR_SLIDER] = nk_rgba(50, 58, 61, 255);
		table[NK_COLOR_SLIDER_CURSOR] = nk_rgba(48, 83, 111, 245);
		table[NK_COLOR_SLIDER_CURSOR_HOVER] = nk_rgba(53, 88, 116, 255);
		table[NK_COLOR_SLIDER_CURSOR_ACTIVE] = nk_rgba(58, 93, 121, 255);
		table[NK_COLOR_PROPERTY] = nk_rgba(50, 58, 61, 255);
		table[NK_COLOR_EDIT] = nk_rgba(50, 58, 61, 225);
		table[NK_COLOR_EDIT_CURSOR] = nk_rgba(210, 210, 210, 255);
		table[NK_COLOR_COMBO] = nk_rgba(50, 58, 61, 255);
		table[NK_COLOR_CHART] = nk_rgba(50, 58, 61, 255);
		table[NK_COLOR_CHART_COLOR] = nk_rgba(48, 83, 111, 255);
		table[NK_COLOR_CHART_COLOR_HIGHLIGHT] = nk_rgba(255, 0, 0, 255);
		table[NK_COLOR_SCROLLBAR] = nk_rgba(50, 58, 61, 255);
		table[NK_COLOR_SCROLLBAR_CURSOR] = nk_rgba(48, 83, 111, 255);
		table[NK_COLOR_SCROLLBAR_CURSOR_HOVER] = nk_rgba(53, 88, 116, 255);
		table[NK_COLOR_SCROLLBAR_CURSOR_ACTIVE] = nk_rgba(58, 93, 121, 255);
		table[NK_COLOR_TAB_HEADER] = nk_rgba(48, 83, 111, 255);
		nk_style_from_table(ctx, table);
	}
	else {
		nk_style_default(ctx);
	}
}

static void nuklearInit()
{
	ctx = nk_glfw3_init(Vis::Application::getApp()->m_Window_Object->m_Window, NK_GLFW3_DEFAULT);
	struct nk_font_atlas *atlas;
	nk_glfw3_font_stash_begin(&atlas);
	struct nk_font *droid = nk_font_atlas_add_from_file(atlas, "./res/droid/DroidSans.ttf", 14, 0);
	nk_glfw3_font_stash_end();
	nk_style_set_font(ctx, &droid->handle);
	// nk_style_load_all_cursors(ctx, atlas->cursors);

	set_style(ctx, theme::THEME_BLUE);

}

static void appMenu(nk_context *ctx)
{
	static int mcheck = nk_true;

	nk_layout_row_dynamic(ctx, 25, 1);
	nk_checkbox_label(ctx, "Enable A", &mcheck);
	nk_layout_row_dynamic(ctx, 25, 1);
	nk_checkbox_label(ctx, "Enable B", &mcheck);

	nk_layout_row_dynamic(ctx, 25, 1);
	nk_checkbox_label(ctx, "Enable C", &mcheck);
	nk_layout_row_dynamic(ctx, 25, 1);
	nk_checkbox_label(ctx, "Enable D", &mcheck);

}
static void cpSettings(nk_context *ctx, Vis::CartesianPlane *c)
{
	nk_layout_row_dynamic(ctx, 25, 1);

	if (nk_tree_push(ctx, NK_TREE_TAB, "Cartesian Plane", NK_MAXIMIZED))
	{
		nk_layout_row_dynamic(ctx, 25, 1);

		static int property = 20;
		nk_property_int(ctx, "Compression:", 0, &property, 100, 10, 1);

		nk_layout_row_dynamic(ctx, 25, 1);
		nk_property_float(ctx, "Line weight:", 0.5f, &c->line_weight, 5.0f, 0.1f, 0.1f);
		nk_property_float(ctx, "Scale:", 0.3f, &c->scale, 2.0f, 0.1f, 0.1f);
		nk_layout_row_dynamic(ctx, 25, 1);
		nk_property_float(ctx, "x:", -1000.0f, &c->x_origin, 1000.0f, 1.0f, 1.0f);
		nk_property_float(ctx, "y:", -1000.0f, &c->y_origin, 1000.0f, 1.0f, 1.0f);
		nk_property_float(ctx, "Width:", -1000.0f, &c->width, 1000.0f, 1.0f, 1.0f);
		nk_property_float(ctx, "Height:", -1000.0f, &c->height, 1000.0f, 1.0f, 1.0f);
		

		nk_tree_pop(ctx);
	}
}
static void drawUI(Vis::CartesianPlane * c)
{
	nk_glfw3_new_frame();
	static float scale = 1.0f;

	if (nk_begin(ctx, "Vision Controls", nk_rect(0.0f, 0.0f, static_cast<float>(Vis::Application::getApp()->WIDTH) / 5.0f, static_cast<float>(Vis::Application::getApp()->HEIGHT)),
		NK_WINDOW_BORDER | NK_WINDOW_SCALABLE | NK_WINDOW_MOVABLE |
		NK_WINDOW_MINIMIZABLE | NK_WINDOW_TITLE))
	{

		appMenu(ctx);
		cpSettings(ctx, c);
	}

	nk_end(ctx);
	
	nk_glfw3_render(NK_ANTI_ALIASING_ON);
}

static void nuklearShutdown()
{
	nk_glfw3_shutdown();
}


#endif
