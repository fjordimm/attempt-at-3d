
#include "AttemptAt3D/(PtrForGlfw)/PtrForGlfw.hpp"

namespace AttemptAt3D
{
	/* Constructors */

	PtrForGlfw::PtrForGlfw() :
		classMap()
	{}

	/* Methods */

	void PtrForGlfw::bindToGlfwWindow(GLFWwindow* windowForGlfw)
	{
		glfwSetWindowUserPointer(windowForGlfw, this);
	}
	
	/* Functions */
	
	PtrForGlfw* PtrForGlfw::Retrieve(GLFWwindow* windowForGlfw)
	{
		return (PtrForGlfw*)glfwGetWindowUserPointer(windowForGlfw);
	}
}
