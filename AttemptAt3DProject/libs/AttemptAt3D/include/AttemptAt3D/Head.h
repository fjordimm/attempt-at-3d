
#pragma once

namespace AttemptAt3D
{
	class Head
	{
	public:
		Head();
		~Head();
		Head(const Head&) = delete;
		Head& operator=(const Head&) = delete;

		void go();
	
	private:
		void mainLoop();
	};
}
