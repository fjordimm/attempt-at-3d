
#include <iostream>
#include "AttemptAt3D/WindowHandling/Window.h"

using AttemptAt3D::WindowHandling::Window;

int main(void)
{
	std::cout << "haha window" << std::endl;

	Window* pWindow = new Window();

	bool running = true;
	while (running)
	{
		if (!pWindow->ProcessMessages())
		{
			std::cout << "window closin" << std::endl;
			running = false;
		}

		// render stuff

		Sleep(10);
	}

	delete pWindow;

	return 0;
}
