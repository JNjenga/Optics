#ifndef VISION_H
#define VISION_H

#include "vis_pch.hpp"

GLFWwindow * window;
static int width = 680, height = 720;

void initWindow()
{
    if(!glfwInit()) {
		printf("Error : Glfw Init ");
    }


    window = glfwCreateWindow(width, height, "Vision", NULL, NULL);

    if(window == NULL)
    {
        glfwTerminate();
        printf("Error : Create window");
    }

    glfwMakeContextCurrent(window);   

	if (glewInit()) {
		printf("Error : Glew Init ");
	}
	glfwSetWindowSizeCallback(window, [](GLFWwindow* window, int w, int h) {
		height = h;
		width = w;
		glViewport(0, 0, w, h);
	});

	glViewport(0,0, height, height);
}

void destroyWindow()
{
    glfwTerminate();
}

#endif
