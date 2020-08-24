#include "vis_pch.hpp"

#include "vision.hpp"
#include "renderer.hpp"
#include "ui.hpp"

#include <thread>

#include <iostream>
int main()
{
    initWindow();

	initRenderer();

	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	Button * b = new Button();
	b->x = 100.0f;
	b->y = 100.0f;
	b->width = 90.0f, b->height = 30.0f;
	b->color = glm::vec3(1.0f, 0.0f, 1.0f);
	b->text = "Play Game";
	b->text_size = 10.0f;
	b->padding = 0.0f;
	

	while (!glfwWindowShouldClose(window))
    {
		glClear(GL_COLOR_BUFFER_BIT);

		// drawQuad("res/consolas.bmp", { 340.0f, 354.0f }, 0.0f, { 200.0f, 200.0f }, {});
		// drawText("THE QUICK BROWN FOX JUMPS OVER THE LAZY DOG", { 0.0f, 100.0f }, { 20.0f, 15.f }, { 20.0f, 20.0f });
		drawButton(b);
		/* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();

    }

    destroyWindow();

    return 0;
}
