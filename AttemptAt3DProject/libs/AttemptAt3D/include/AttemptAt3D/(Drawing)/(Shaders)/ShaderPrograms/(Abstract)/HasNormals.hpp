
#pragma once

#include "AttemptAt3D/(Drawing)/(Shaders)/ShaderPrograms/(Abstract)/ThreeDShape.hpp"

namespace AttemptAt3D::ShaderPrograms
{
	class HasNormals : public ShaderPrograms::ThreeDShape
	{
		/* Constructors */

	   public:
		HasNormals(const HasNormals&) = delete;
		HasNormals& operator=(const HasNormals&) = delete;
		
		HasNormals();
		
		/* Fields */

	   private:
		GLint attribNormal;

		/* Methods */

	   public:
		void enableAttribsForMesh__() final;
	   protected:
		virtual void enableAttribsForMesh___() {}

	   protected:
		GLsizei getStride__() final;
		virtual GLsizei getStride___() { return 0; }
		
		void setupUniforms__() final;
		virtual void setupUniforms___() {}

		void setupAttributes__() final;
		virtual void setupAttributes___() {}

		void updateUniformsFromTran__(Tran& tran) const final;
		virtual void updateUniformsFromTran___(Tran& tran) const {}
	};
}
