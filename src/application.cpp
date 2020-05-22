#include "vis_pch.hpp"
#include <GL/gl.h>
#include "application.hpp"
#include "visual_window.hpp"
#include <math.h>
#include "input.hpp"

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

#include "nuklear/nuklear.h"
#include "nuklear/nuklear_glfw_gl2.h"


uint32_t Vis::Application::HEIGHT;
uint32_t Vis::Application::WIDTH;
struct nk_context * ctx;


void Vis::Application::init()
{
	WIDTH = 680;
	HEIGHT = 480;

	// Create and init window	
	m_Window_Object = new VisualWindow();
	m_Window_Object->init(WIDTH, HEIGHT);

	/*
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		LOG_FATAL("Failed to load glad\n");
	}
	*/

	// Create and initialize renderer
	m_Renderer = new Renderer();
	m_Renderer->init();

	ctx = nk_glfw3_init(m_Window_Object->m_Window,NK_GLFW3_INSTALL_CALLBACKS);
	struct nk_font_atlas *atlas;
	nk_glfw3_font_stash_begin(&atlas);
	struct nk_font *droid = nk_font_atlas_add_from_file(atlas, "./res/comic.ttf", 14, 0);
	/*struct nk_font *roboto = nk_font_atlas_add_from_file(atlas, "../../../extra_font/Roboto-Regular.ttf", 14, 0);*/
	/*struct nk_font *future = nk_font_atlas_add_from_file(atlas, "../../../extra_font/kenvector_future_thin.ttf", 13, 0);*/
	/*struct nk_font *clean = nk_font_atlas_add_from_file(atlas, "../../../extra_font/ProggyClean.ttf", 12, 0);*/
	/*struct nk_font *tiny = nk_font_atlas_add_from_file(atlas, "../../../extra_font/ProggyTiny.ttf", 10, 0);*/
	/*struct nk_font *cousine = nk_font_atlas_add_from_file(atlas, "../../../extra_font/Cousine-Regular.ttf", 13, 0);*/
	nk_glfw3_font_stash_end();
	nk_style_set_font(ctx, &droid->handle);
	// nk_style_load_all_cursors(ctx, atlas->cursors);

}

void Vis::Application::update()
{

}

void Vis::Application::run()
{
	init();
	struct nk_colorf bg;
	bg.r = 0.10f, bg.g = 0.18f, bg.b = 0.24f, bg.a = 1.0f;

	auto & m = Vis::Mouse::getMouse();
	
	float width = static_cast<float>(WIDTH);
	float height = static_cast<float>(HEIGHT);

	Vis::Cartesian * c = new Vis::Cartesian(0.0f, 0.0f, width, height, 40.0f, 40.0f, 0.1f);

	// J
	c->shadeCell(3,3);
	c->shadeCell(4,3);
	c->shadeCell(5,3);
	c->shadeCell(6,3);
	c->shadeCell(6,4);
	c->shadeCell(6,5);
	c->shadeCell(6,6);
	c->shadeCell(6,7);
	c->shadeCell(5,7);
	c->shadeCell(4,7);
	c->shadeCell(3,7);
	c->shadeCell(3,6);


	while (!glfwWindowShouldClose(m_Window_Object->getWindow()))
	{
		glfwPollEvents();
		nk_glfw3_new_frame();
		static float scale = 1.0f;

		if (nk_begin(ctx, "Demo", nk_rect(0.0f, 0.0f, static_cast<float>(WIDTH) /5.0f, static_cast<float>(HEIGHT)),
			NK_WINDOW_BORDER |  NK_WINDOW_SCALABLE |
			NK_WINDOW_MINIMIZABLE | NK_WINDOW_TITLE))
		{
			enum { EASY, HARD };
			static int op = EASY;
			static int property = 20;
			nk_layout_row_static(ctx, 30, 80, 1);
			if (nk_button_label(ctx, "button"))
				fprintf(stdout, "button pressed\n");

			nk_layout_row_dynamic(ctx, 30, 2);
			if (nk_option_label(ctx, "easy", op == EASY)) op = EASY;
			if (nk_option_label(ctx, "hard", op == HARD)) op = HARD;

			nk_layout_row_dynamic(ctx, 25, 1);
			// nk_property_int(ctx, "Compression:", 0, &property, 100, 10, 1);
			nk_property_float(ctx, "Compression:", 0.05f, &scale, 2.0f, 0.1f, 0.01f);

			nk_layout_row_dynamic(ctx, 20, 1);
			nk_label(ctx, "background:", NK_TEXT_LEFT);
			nk_layout_row_dynamic(ctx, 25, 1);
			if (nk_combo_begin_color(ctx, nk_rgb_cf(bg), nk_vec2(nk_widget_width(ctx), 400))) {
				nk_layout_row_dynamic(ctx, 120, 1);
				bg = nk_color_picker(ctx, bg, NK_RGBA);
				nk_layout_row_dynamic(ctx, 25, 1);
				bg.r = nk_propertyf(ctx, "#R:", 0, bg.r, 1.0f, 0.01f, 0.005f);
				bg.g = nk_propertyf(ctx, "#G:", 0, bg.g, 1.0f, 0.01f, 0.005f);
				bg.b = nk_propertyf(ctx, "#B:", 0, bg.b, 1.0f, 0.01f, 0.005f);
				bg.a = nk_propertyf(ctx, "#A:", 0, bg.a, 1.0f, 0.01f, 0.005f);
				nk_combo_end(ctx);
			}
		}
		nk_end(ctx);

		width = static_cast<float>(WIDTH);
		height = static_cast<float>(HEIGHT);

		m_Renderer->clear({ bg.r, bg.g, bg.b });
		


		m_Renderer->drawCartesianPlane(c);
		// Update cartesian
		c->scale = scale;
		if(c->end_x != width)
		{
			c->origin_x = 0.0f;
			c->end_x = width;
			c->end_y = height;
		}
		
		// Snapping of pointer to cell corners
		if(m.x > c->origin_x){
			float p_x = 0.0f;
			float p_y = 0.0f;

			p_x = m.x - c->origin_x ;
			p_x = p_x / c->getCellWidth();
			float offset = fmodf(p_x,1.0f);
			p_x = ((offset > 0.5f) ? ceilf(p_x) : floorf(p_x))  * c->getCellWidth() + c->origin_x;
			
			p_y = m.y - c->origin_y;
			p_y = p_y / c->getCellHeight();
			offset = fmodf(p_y, 1.0f);

			p_y = ((offset > 0.5f) ? ceilf(p_y) : floorf(p_y))  * c->getCellHeight() + c->origin_y;
			
			// m_Renderer->drawPoint({ p_x , p_y, 0.0f }, { 0.560f, 0.f, 0.188f });
			m_Renderer->drawQuad({ p_x , p_y, 0.0f }, { c->getCellWidth(), c->getCellHeight() }, { 0.560f, 0.f, 0.188f });


		}
		nk_glfw3_render(NK_ANTI_ALIASING_ON);
		glfwSwapBuffers(m_Window_Object->m_Window);
		
		
	}

	nk_glfw3_shutdown();
}
Vis::Application::~Application()
{
	delete m_Window_Object;
}

/* For reference puroposes
if (m.mouseLeftClick())
{
	m_Renderer->drawQuad({ 0.0f, 0.0f, 0.0f }, { m.x, m.y }, { 0.188f, 0.247f, 0.623f });
}

// Side nav
{
	m_Renderer->drawQuad({ 0.0f,  0.0f, 0.0f }, { WIDTH / 5, HEIGHT }, { 0.247f, 0.317f, 0.709f });

	// Control widgets
	m_Renderer->drawQuad({ 0.0f,  0.0f, 0.0f }, { WIDTH / 5 , 40.0f }, { 0.188f, 0.247f, 0.623f });
	m_Renderer->drawQuad({ 10.0f,  50.0f, 0.0f }, { WIDTH / 5 - 30.0f, 25.0f }, { 0.898f, 0.905f, 0.960f });
	m_Renderer->drawQuad({ 10.0f,  100.0f, 0.0f }, { WIDTH / 5 - 30.0f, 25.0f }, { 0.898f, 0.905f, 0.960f });
	m_Renderer->drawQuad({ 10.0f,  150.0f, 0.0f }, { WIDTH / 5 - 30.0f, 25.0f }, { 0.898f, 0.905f, 0.960f });

}
*/
