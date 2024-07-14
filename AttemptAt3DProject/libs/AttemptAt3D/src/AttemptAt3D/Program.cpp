
#include <iostream>
#include "AttemptAt3D/WindowHandling/Window.h"

using AttemptAt3D::WindowHandling::Window;

int main(void)
{
	Window win;

	bool running = true;
	while (running)
	{
		if (!win.ProcessMessages())
		{
			running = false;
		}

		// render stuff

		Sleep(10);
	}

	return 0;
}
