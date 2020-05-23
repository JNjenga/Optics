#include "vis_pch.hpp"
#include "application.hpp"


int main()
{
	Vis::Application * application = Vis::Application::getApp();

	application->run();

	delete application;

	return 0;
}
