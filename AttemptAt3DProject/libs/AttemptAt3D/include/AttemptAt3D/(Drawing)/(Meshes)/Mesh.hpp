
#pragma once

#include <memory>
#include <cstdlib>
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "AttemptAt3D/(Drawing)/(Meshes)/MeshData.hpp"
#include "AttemptAt3D/(Util)/(Tran)/Tran.hpp"

namespace AttemptAt3D
{
	// Forward declarations
	class ShaderProgram;

	class Mesh
	{
		/* Constructors */

	   private:
		Mesh() = delete;
		Mesh(const Mesh&) = delete;
		Mesh& operator=(const Mesh&) = delete;
		
		Mesh(ShaderProgram* shaderProgram, std::unique_ptr<MeshData> meshData); // Only to be used by MeshManager
		
		/* Fields */

	   private:
		ShaderProgram* shaderProgram;
		std::unique_ptr<MeshData> meshData;

		GLuint vao;
		GLuint vbo;
		GLuint ebo;

		/* Getters and Setters */

	   public:
		inline ShaderProgram* getShaderProgram() { return this->shaderProgram; }
		inline std::size_t getVerticesLen() { return this->meshData->verticesLen; }
		inline const float* getVertices() { return this->meshData->vertices.get(); }
		inline std::size_t getElementsLen() { return this->meshData->elementsLen; }
		inline const GLuint* getElements() { return this->meshData->elements.get(); }

		/* Methods */

	   private:
		void generateGlVaoAndBuffers(); // Only to be used by MeshManager
		void cleanupForGl(); // Only to be used by MeshManager

	   public:
		void updateGlBufferData();
		GLuint getVaoForDrawing();

		/* Friends */

		friend class MeshManager;
		friend std::unique_ptr<Mesh> std::make_unique<Mesh>(AttemptAt3D::ShaderProgram*&, std::unique_ptr<AttemptAt3D::MeshData>&&);

		// TODO: cleanupForGl
	};
}
