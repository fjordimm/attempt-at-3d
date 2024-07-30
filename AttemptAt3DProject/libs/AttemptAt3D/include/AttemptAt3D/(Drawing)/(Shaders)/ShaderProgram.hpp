
#pragma once

#include <list>
#include <tuple>
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "AttemptAt3D/(Tran)/Tran.hpp"
#include "AttemptAt3D/(Drawing)/(Meshes)/Mesh.hpp"

namespace AttemptAt3D
{
	class ShaderProgram
	{
		/* Constructors */

	   public:
		ShaderProgram(const ShaderProgram&) = delete;
		ShaderProgram& operator=(const ShaderProgram&) = delete;
		
		ShaderProgram();
		
		/* Fields */

	   private:
		GLuint vertexShader;
		GLuint geometryShader;
		GLuint fragmentShader;

		std::list<std::tuple<Mesh*, Tran*>> trans;

	   protected:
		GLuint program;

		/* Methods */

	   public:
		void compileAndActivate();
		void use() const;

		std::list<std::tuple<Mesh*, Tran*>>::const_iterator addForm(Mesh* mesh, Tran* tran);
		void removeForm(const std::list<std::tuple<Mesh*, Tran*>>::const_iterator& iter);
		void drawAllTrans() const;

		virtual void enableAttribsForMesh() = 0;

	   protected:
		virtual const char* getVertexShaderSourcePath() const = 0;
		virtual const char* getGeometryShaderSourcePath() const = 0;
		virtual const char* getFragmentShaderSourcePath() const = 0;

		virtual GLsizei getStride() = 0;
		
		virtual void setupUniforms() = 0;
		virtual void setupAttributes() = 0;
		virtual void updateUniformsFromTran(Tran& tran) const = 0;

	   private:
		void checkShaderCompilation(GLuint shader) const;
	};

	// TODO: cleanup gl shaders and shader programs
}
