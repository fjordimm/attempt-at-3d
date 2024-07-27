
#include "AttemptAt3D/(Drawing)/MeshSamples/Sphere.hpp"

#include <vector>
#include <cmath>
#include "AttemptAt3D/(Tran)/Vec.hpp"
#include "AttemptAt3D/(Debug)/Debug.hpp"
#include "AttemptAt3D/(Math)/Math.hpp"

namespace AttemptAt3D::MeshSamples
{
	// TODO: delete the arrays from memory after they are returned

	template <std::size_t Size>
	std::size_t Sphere<Size>::verticesSize() const
	{
		const int numLayers = Size;
		const int numVertsPerLayer = Size * 2 + 2;
		return sizeof(float) * 6 * (1 + numLayers * numVertsPerLayer + 1);
	}

	template <std::size_t Size>
	const float* Sphere<Size>::vertices() const
	{
		if (Size < 2)
		{ Debug::LogFatalError("Sphere size must be at least 2."); }

		Vec bottomVert = Vec(0.0f, 0.0f, -1.0f);
		Vec topVert = Vec(0.0f, 0.0f, +1.0f);

		const int numLayers = Size;
		const int numVertsPerLayer = Size * 2 + 2;

		std::vector<std::unique_ptr<std::vector<Vec>>> layers;
		for (int i = 0; i < numLayers; i++)
		{
			float fractionOfVerticalSemicircle = (float)(i + 1) / (float)(numLayers + 1);
			float z = std::sin(Math::Pi * fractionOfVerticalSemicircle - Math::PiOver2);

			layers.push_back(std::make_unique<std::vector<Vec>>());
			for (int j = 0; j < numVertsPerLayer; j++)
			{
				float fractionOfHorizontalCircle = (float)j / (float)numVertsPerLayer;
				float x = std::cos(Math::TwoPi * fractionOfHorizontalCircle);
				float y = std::sin(Math::TwoPi * fractionOfHorizontalCircle);

				layers[i]->push_back(Vec(x, y, z));
			}
		}

		// Debug::Log("start");
		// for (int i = 0; i < numLayers; i++)
		// {
		// 	Debug::Printf("  Layer\n");
		// 	for (int j = 0; j < numVertsPerLayer; j++)
		// 	{
		// 		Debug::Printf("    %s\n", Vecs::ToString(layers[i]->at(j)).c_str());
		// 	}
		// }
		// Debug::Log("end");

		/* Create final array */

		std::size_t finalArray_l = 6 * (1 + numLayers * numVertsPerLayer + 1);
		float* finalArray = new float[finalArray_l];

		// bottom vertex
		finalArray[0] = bottomVert.x;
		finalArray[1] = bottomVert.y;
		finalArray[2] = bottomVert.z;
		finalArray[3] = 1.0f;
		finalArray[4] = 1.0f;
		finalArray[5] = 1.0f;

		// middle verts
		for (int i = 0; i < numLayers; i++)
		{
			for (int j = 0; j < numVertsPerLayer; j++)
			{
				finalArray[6 * (1 + i * numVertsPerLayer + j) + 0] = layers[i]->at(j).x;
				finalArray[6 * (1 + i * numVertsPerLayer + j) + 1] = layers[i]->at(j).y;
				finalArray[6 * (1 + i * numVertsPerLayer + j) + 2] = layers[i]->at(j).z;
				finalArray[6 * (1 + i * numVertsPerLayer + j) + 3] = 1.0f;
				finalArray[6 * (1 + i * numVertsPerLayer + j) + 4] = 1.0f;
				finalArray[6 * (1 + i * numVertsPerLayer + j) + 5] = 1.0f;
			}
		}

		// top vert
		finalArray[finalArray_l - 6] = topVert.x;
		finalArray[finalArray_l - 5] = topVert.y;
		finalArray[finalArray_l - 4] = topVert.z;
		finalArray[finalArray_l - 3] = 1.0f;
		finalArray[finalArray_l - 2] = 1.0f;
		finalArray[finalArray_l - 1] = 1.0f;

		return finalArray;
	}

	template <std::size_t Size>
	std::size_t Sphere<Size>::elementsSize() const
	{
		const int numLayers = Size;
		const int numVertsPerLayer = Size * 2 + 2;
		const int numVerts = 1 + numLayers * numVertsPerLayer + 1;
		const int numTriangles = numVertsPerLayer * (1 + 2 * (numLayers - 1) + 1);

		return sizeof(GLuint) * 3 * numTriangles;
	}

	template <std::size_t Size>
	const GLuint* Sphere<Size>::elements() const
	{
		const int numLayers = Size;
		const int numVertsPerLayer = Size * 2 + 2;
		const int numVerts = 1 + numLayers * numVertsPerLayer + 1;
		const int numTriangles = numVertsPerLayer * (1 + 2 * (numLayers - 1) + 1);

		int bottomVert_i = 0;
		int topVert_i = numVerts - 1;

		/* Create final array */

		std::size_t finalArray_l = 3 * numTriangles;
		GLuint* finalArray = new GLuint[finalArray_l];

		// bottom cap
		for (int j = 0; j < numVertsPerLayer; j++)
		{
			int vertA = 3 * j + 0;
			int vertB = 3 * j + 1;
			int vertC = 3 * j + 2;

			finalArray[vertA] = bottomVert_i;

			if (j != numVertsPerLayer - 1)
			{ finalArray[vertB] = 1 + j + 1; }
			else
			{ finalArray[vertB] = 1 + 0; }

			finalArray[vertC] = 1 + j + 0;
		}

		// middle squares
		// for (int i = 0; i < numLayers; i++)
		// {
		// 	for (int j = 0; j < numVertsPerLayer; j++)
		// 	{
				
		// 	}
		// }
		for (int i = 3 * (numVertsPerLayer - 1) + 2 + 1; i < 3 * (numVertsPerLayer * (1 + 2 * (numLayers - 1)) + (numVertsPerLayer - 1)) + 0; i++)
		{
			finalArray[i] = topVert_i;
		}

		// top cap
		for (int j = 0; j < numVertsPerLayer; j++)
		{
			int vertA = 3 * (numVertsPerLayer * (1 + 2 * (numLayers - 1)) + j) + 0;
			int vertB = 3 * (numVertsPerLayer * (1 + 2 * (numLayers - 1)) + j) + 1;
			int vertC = 3 * (numVertsPerLayer * (1 + 2 * (numLayers - 1)) + j) + 2;

			finalArray[vertA] = topVert_i;

			finalArray[vertB] = (1 + (numVertsPerLayer * (numLayers - 1))) + j + 0;

			if (j != numVertsPerLayer - 1)
			{ finalArray[vertC] = (1 + (numVertsPerLayer * (numLayers - 1))) + j + 1; }
			else
			{ finalArray[vertC] = (1 + (numVertsPerLayer * (numLayers - 1))) + 0; }
		}

		return finalArray;
	}

	Sphere<2> sphere2; // solves linker error
}
