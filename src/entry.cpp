#include "vis_pch.hpp"
#include "application.hpp"


int main()
{
	Vis::Application * e = new Vis::Application();

	e->run();

	delete e;

	return 0;
}
