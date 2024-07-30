
#pragma once

#include "AttemptAt3D/(Drawing)/(Shaders)/ShaderPrograms/(Abstract)/InSpace.hpp"

namespace AttemptAt3D::ShaderPrograms
{
	class ThreeDShape : public ShaderPrograms::InSpace
	{
		/* Constructors */

	   public:
		ThreeDShape(const ThreeDShape&) = delete;
		ThreeDShape& operator=(const ThreeDShape&) = delete;
		
		ThreeDShape();
		
		/* Fields */

	   private:
		GLint uniTransScale;
		GLint uniTransRot;
		GLint uniTransPos;

		/* Getters & Setters */

	   public:
		void setUniTransScale(const glm::mat4& val) const;
		void setUniTransRot(const glm::mat4& val) const;
		void setUniTransPos(const glm::mat4& val) const;

		/* Methods */

	   protected:
		MeshSamples::MeshSample::MeshVertAttribs attribFlagsForMeshSamples_() const final;
		void enableAttribsForMesh_() final;
	   	std::size_t getStride_() final;
		void setupUniforms_() final;
		void setupAttributes_() final;
		void updateUniformsFromTran_(Tran& tran) const final;

	   protected:
		virtual MeshSamples::MeshSample::MeshVertAttribs attribFlagsForMeshSamples__() const { return MeshSamples::MeshSample::MeshVertAttribs::None; };
		virtual void enableAttribsForMesh__() {}
		virtual std::size_t getStride__() { return 0; }
		virtual void setupUniforms__() {}
		virtual void setupAttributes__() {}
		virtual void updateUniformsFromTran__(Tran& tran) const {}
	};
}
