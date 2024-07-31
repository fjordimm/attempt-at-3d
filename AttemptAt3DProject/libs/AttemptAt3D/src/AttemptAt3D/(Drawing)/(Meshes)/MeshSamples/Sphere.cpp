
#include "AttemptAt3D/(Drawing)/(Meshes)/MeshSamples/Sphere.hpp"

#include <vector>
#include <cmath>
#include "AttemptAt3D/(Util)/(Tran)/Vec.hpp"
#include "AttemptAt3D/(Debug)/Debug.hpp"
#include "AttemptAt3D/(Util)/(Math)/Math.hpp"

namespace AttemptAt3D::MeshSamples
{
	template <std::size_t Size>
	std::unique_ptr<std::vector<Vec>> Sphere<Size>::vertPositions3D() const
	{
		if (Size < 2)
		{ Debug::LogFatalError("Sphere size must be at least 2."); }

		const int numLayers = Size;
		const int numVertsPerLayer = Size * 2 + 2;

		std::unique_ptr<std::vector<Vec>> ret = std::make_unique<std::vector<Vec>>();

		// bottom vert
		ret->push_back(Vec(0.0f, 0.0f, -1.0f));

		// middle verts
		for (int i = 0; i < numLayers; i++)
		{
			float fractionOfVerticalSemicircle = (float)(i + 1) / (float)(numLayers + 1);
			float z = std::sin(Math::Pi * fractionOfVerticalSemicircle - Math::PiOver2);
			float r = std::cos(Math::Pi * fractionOfVerticalSemicircle - Math::PiOver2);

			for (int j = 0; j < numVertsPerLayer; j++)
			{
				float fractionOfHorizontalCircle = (float)j / (float)numVertsPerLayer;
				float x = r * std::cos(Math::TwoPi * fractionOfHorizontalCircle);
				float y = r * std::sin(Math::TwoPi * fractionOfHorizontalCircle);

				ret->push_back(Vec(x, y, z));
			}
		}

		// top vert
		ret->push_back(Vec(0.0f, 0.0f, +1.0f));
		
		return ret;
	}

	template <std::size_t Size>
	std::unique_ptr<std::vector<Vec>> Sphere<Size>::vertNormals3D() const
	{
		std::unique_ptr<std::vector<Vec>> ret = this->vertPositions3D();

		for (std::size_t i = 0; i < ret->size(); i++)
		{
			ret->at(i) = glm::normalize(ret->at(i));
		}

		return std::move(ret);
	}

	template <std::size_t Size>
	std::unique_ptr<std::vector<std::tuple<GLuint, GLuint, GLuint>>> Sphere<Size>::triangles() const
	{
		const int numLayers = Size;
		const int numVertsPerLayer = Size * 2 + 2;
		const int numVerts = 1 + numLayers * numVertsPerLayer + 1;
		const int numTriangles = numVertsPerLayer * (1 + 2 * (numLayers - 1) + 1);

		int bottomVert_i = 0;
		int topVert_i = numVerts - 1;

		std::unique_ptr<std::vector<std::tuple<GLuint, GLuint, GLuint>>> ret = std::make_unique<std::vector<std::tuple<GLuint, GLuint, GLuint>>>();

		// bottom cap
		for (int j = 0; j < numVertsPerLayer; j++)
		{
			GLuint vertBottom = bottomVert_i;
			GLuint vertTopLeft = 1 + j + 0;
			GLuint vertTopRight = (j == numVertsPerLayer - 1) ?
				1 + 0 :
				1 + j + 1;

			ret->push_back(std::make_tuple(vertBottom, vertTopRight, vertTopLeft));
		}

		// middle squares
		for (int i = 0; i < numLayers - 1; i++)
		{
			for (int j = 0; j < numVertsPerLayer; j++)
			{
				GLuint vertBottomLeft = (1 + (numVertsPerLayer * (i + 0))) + j + 0;
				GLuint vertBottomRight = (j == numVertsPerLayer - 1) ?
					(1 + (numVertsPerLayer * (i + 0))) + 0 :
					(1 + (numVertsPerLayer * (i + 0))) + j + 1;
				GLuint vertTopLeft = (1 + (numVertsPerLayer * (i + 1))) + j + 0;
				GLuint vertTopRight = (j == numVertsPerLayer - 1) ?
					(1 + (numVertsPerLayer * (i + 1))) + 0 :
					(1 + (numVertsPerLayer * (i + 1))) + j + 1;
				
				ret->push_back(std::make_tuple(vertTopRight, vertTopLeft, vertBottomLeft));
				ret->push_back(std::make_tuple(vertTopRight, vertBottomLeft, vertBottomRight));
			}
		}

		// top cap
		for (int j = 0; j < numVertsPerLayer; j++)
		{
			GLuint vertTop = topVert_i;
			GLuint vertBottomLeft = (1 + (numVertsPerLayer * (numLayers - 1))) + j + 0;
			GLuint vertBottomRight = (j == numVertsPerLayer - 1) ?
				(1 + (numVertsPerLayer * (numLayers - 1))) + 0 :
				(1 + (numVertsPerLayer * (numLayers - 1))) + j + 1;

			ret->push_back(std::make_tuple(vertTop, vertBottomLeft, vertBottomRight));
		}

		return ret;
	}

	// solves linker errors
	Sphere<2>   sphere2;
	Sphere<3>   sphere3;
	Sphere<4>   sphere4;
	Sphere<5>   sphere5;
	Sphere<6>   sphere6;
	Sphere<7>   sphere7;
	Sphere<8>   sphere8;
	Sphere<9>   sphere9;
	Sphere<10>  sphere10;
	Sphere<11>  sphere11;
	Sphere<12>  sphere12;
	Sphere<13>  sphere13;
	Sphere<14>  sphere14;
	Sphere<15>  sphere15;
	Sphere<16>  sphere16;
	Sphere<17>  sphere17;
	Sphere<18>  sphere18;
	Sphere<19>  sphere19;
	Sphere<20>  sphere20;
	Sphere<21>  sphere21;
}
