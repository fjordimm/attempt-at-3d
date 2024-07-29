
#pragma once

#include "AttemptAt3D/(Drawing)/(Shaders)/ShaderProgram.hpp"

namespace AttemptAt3D::ShaderPrograms
{
	class InSpace : public ShaderProgram
	{
		/* Constructors */

	   public:
		InSpace(const InSpace&) = delete;
		InSpace& operator=(const InSpace&) = delete;
		
		InSpace();
		
		/* Fields */

	   private:
		GLint attribPosition;
		GLint attribColor;

		GLint uniView;
		GLint uniProj;
		GLint uniSunRot;

		/* Getters & Setters */

	   public:
		void setUniView(const glm::mat4& val);
		void setUniProj(const glm::mat4& val);
		void setUniSunRot(const glm::mat4& val);

		/* Methods */

	   public:
		void enableAttribsForMesh() final;
	   protected:
		virtual void enableAttribsForMesh_() {}

	   protected:
		void setupUniforms() final;
		virtual void setupUniforms_() {}

		void setupAttributes() final;
		virtual void setupAttributes_() {}

		void updateUniformsFromTran(Tran& tran) const final;
		virtual void updateUniformsFromTran_(Tran& tran) const {}
	};
}
