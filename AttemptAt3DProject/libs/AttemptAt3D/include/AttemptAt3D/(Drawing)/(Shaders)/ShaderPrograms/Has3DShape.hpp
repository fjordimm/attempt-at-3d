
#pragma once

#include "AttemptAt3D/(Drawing)/(Shaders)/ShaderPrograms/InSpace.hpp"

namespace AttemptAt3D::ShaderPrograms
{
	class Has3DShape : public ShaderPrograms::InSpace
	{
		/* Constructors */

	   public:
		Has3DShape(const Has3DShape&) = delete;
		Has3DShape& operator=(const Has3DShape&) = delete;
		
		Has3DShape();
		
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
		void setupUniforms_() final;
		virtual void setupUniforms__() {}

		void setupAttributes_() final;
		virtual void setupAttributes__() {}

		void updateUniformsFromTran_(Tran& tran) const final;
		virtual void updateUniformsFromTran__(Tran& tran) const {}
	};
}
