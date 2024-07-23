
#pragma once

#include <map>
#include <cstdlib>
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace AttemptAt3D
{
	class PtrForGlfw
	{
		/* Constructors */

	   public:
		PtrForGlfw(const PtrForGlfw&) = delete;
		PtrForGlfw& operator=(const PtrForGlfw&) = delete;

		PtrForGlfw();
		
		/* Fields */

	   private:
		std::map<std::size_t, void*> classMap;

		/* Methods */

	   public:
		void bindToGlfwWindow(GLFWwindow* windowForGlfw);

		template<class T>
		void add(T* tPtr)
		{ this->classMap[typeid(T).hash_code()] = tPtr; }

		template<class T>
		T* get()
		{ return (T*)(this->classMap[typeid(T).hash_code()]); }

		/* Functions */

	   public:
		static PtrForGlfw* Retrieve(GLFWwindow* windowForGlfw);
	};
}
