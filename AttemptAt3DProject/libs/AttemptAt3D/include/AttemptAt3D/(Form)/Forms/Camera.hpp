
#pragma once

#include "AttemptAt3D/(Form)/Form.hpp"

namespace AttemptAt3D::Forms
{
	class Camera : public Form
	{
		/* Constructors */

		using Form::Form;

	   public:
		template <class T = Camera, typename std::enable_if<std::is_base_of<Camera, T>::value>::type* = nullptr>
		static std::unique_ptr<T> New(WorldState& worldState)
		{
			return Form::New<T>(worldState, nullptr);
		}

		/* Methods */

	   public:
		void recalculateAndApplyViewMatrix(ShaderManager& shaderManager);

		/* Friends */

		friend std::unique_ptr<Camera> std::make_unique<Camera>(AttemptAt3D::WorldState&, std::unique_ptr<AttemptAt3D::Mesh>&&);
	};
}
