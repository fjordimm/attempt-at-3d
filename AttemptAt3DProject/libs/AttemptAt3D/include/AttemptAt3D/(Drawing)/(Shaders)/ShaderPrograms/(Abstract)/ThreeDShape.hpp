
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

	   public:
		void enableAttribsForMesh_() final;
	   protected:
		virtual void enableAttribsForMesh__() {}

	   protected:
		GLsizei getStride_() final;
		virtual GLsizei getStride__() { return 0; }

		void setupUniforms_() final;
		virtual void setupUniforms__() {}

		void setupAttributes_() final;
		virtual void setupAttributes__() {}

		void updateUniformsFromTran_(Tran& tran) const final;
		virtual void updateUniformsFromTran__(Tran& tran) const {}
	};
}
