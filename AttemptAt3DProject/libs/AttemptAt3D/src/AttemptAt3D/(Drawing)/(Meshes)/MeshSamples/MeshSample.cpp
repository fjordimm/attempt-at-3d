
#include "AttemptAt3D/(Drawing)/(Meshes)/MeshSamples/MeshSample.hpp"

#include <cstring>
#include "AttemptAt3D/(Debug)/Debug.hpp"

namespace AttemptAt3D::MeshSamples
{
	/* Constructors */

	MeshSample::MeshSample() {}

	/* Methods */

	std::unique_ptr<MeshData> MeshSample::make(MeshVertAttribs attribs) const
	{
		bool doPositions3D = (attribs & MeshVertAttribs::Positions3D) != MeshVertAttribs::None;
		bool doNormals3D = (attribs & MeshVertAttribs::Normals3D) != MeshVertAttribs::None;

		ATTEMPTAT3D_DEBUG_ASSERT(doPositions3D);

		/* Make verts */

		std::size_t vertsVertLen = -1;
		std::size_t vertsLen = -1;
		std::unique_ptr<float[]> verts = nullptr;
		{
			std::size_t numFloatsPerVertex = 0;

			std::unique_ptr<const std::vector<Vec>> vertPositions3D = nullptr;
			if (doPositions3D)
			{
				vertPositions3D = this->vertPositions3D();
				numFloatsPerVertex += 3;
			}

			std::unique_ptr<const std::vector<Vec>> vertNormals3D = nullptr;
			if (doNormals3D)
			{
				vertNormals3D = this->vertNormals3D();
				numFloatsPerVertex += 3;
			}

			if (doPositions3D && doNormals3D)
			{
				ATTEMPTAT3D_DEBUG_ASSERT(vertPositions3D->size() == vertNormals3D->size());
			}

			vertsVertLen = vertPositions3D->size();

			vertsLen = vertsVertLen * numFloatsPerVertex;

			std::unique_ptr<float[]> _verts(new float[vertsLen]);
			verts = std::move(_verts);

			for (int i = 0; i < vertsVertLen; i++)
			{
				std::size_t cumlOffset = 0;

				if (doPositions3D)
				{
					verts[i * numFloatsPerVertex + cumlOffset + 0] = vertPositions3D->at(i).x;
					verts[i * numFloatsPerVertex + cumlOffset + 1] = vertPositions3D->at(i).y;
					verts[i * numFloatsPerVertex + cumlOffset + 2] = vertPositions3D->at(i).z;

					cumlOffset += 3;
				}

				if (doNormals3D)
				{
					verts[i * numFloatsPerVertex + cumlOffset + 0] = vertNormals3D->at(i).x;
					verts[i * numFloatsPerVertex + cumlOffset + 1] = vertNormals3D->at(i).y;
					verts[i * numFloatsPerVertex + cumlOffset + 2] = vertNormals3D->at(i).z;

					cumlOffset += 3;
				}
			}
		}

		/* Make elems */

		std::size_t trianglesLen = -1;
		std::size_t elemsLen = -1;
		std::unique_ptr<GLuint[]> elems = nullptr;
		{
			std::unique_ptr<std::vector<std::tuple<GLuint, GLuint, GLuint>>> triangles = this->triangles();

			trianglesLen = triangles->size();

			elemsLen = trianglesLen * 3;

			std::unique_ptr<GLuint[]> _elems(new GLuint[elemsLen]);
			elems = std::move(_elems);

			for (int i = 0; i < trianglesLen; i++)
			{
				elems[i * 3 + 0] = std::get<0>(triangles->at(i));
				elems[i * 3 + 1] = std::get<1>(triangles->at(i));
				elems[i * 3 + 2] = std::get<2>(triangles->at(i));
			}
		}

		/* Finish */

		return std::make_unique<MeshData>(vertsLen, std::move(verts), elemsLen, std::move(elems));

		///////////////////////////////////

		// std::size_t vertsLen = this->verticesSize() / sizeof(float);

		// std::unique_ptr<float[]> verts(new float[vertsLen]);
		// std::memcpy(verts.get(), this->vertices(), this->verticesSize());

		// std::size_t elemsLen = this->elementsSize() / sizeof(GLuint);

		// std::unique_ptr<GLuint[]> elems(new GLuint[elemsLen]);
		// std::memcpy(elems.get(), this->elements(), this->elementsSize());

		// return std::make_unique<MeshData>(vertsLen, std::move(verts), elemsLen, std::move(elems));
	}

	/* Enum Operator Overloads */

	MeshSample::MeshVertAttribs operator|(MeshSample::MeshVertAttribs lhs, MeshSample::MeshSample::MeshVertAttribs rhs)
	{
		return static_cast<MeshSample::MeshVertAttribs>(
			static_cast<std::underlying_type_t<MeshSample::MeshVertAttribs>>(lhs) |
			static_cast<std::underlying_type_t<MeshSample::MeshVertAttribs>>(rhs)
		);
	}

	MeshSample::MeshSample::MeshVertAttribs operator&(MeshSample::MeshVertAttribs lhs, MeshSample::MeshVertAttribs rhs)
	{
		return static_cast<MeshSample::MeshVertAttribs>(
			static_cast<std::underlying_type_t<MeshSample::MeshVertAttribs>>(lhs) &
			static_cast<std::underlying_type_t<MeshSample::MeshVertAttribs>>(rhs)
		);
	}

	MeshSample::MeshSample::MeshVertAttribs operator^(MeshSample::MeshVertAttribs lhs, MeshSample::MeshVertAttribs rhs)
	{
		return static_cast<MeshSample::MeshVertAttribs>(
			static_cast<std::underlying_type_t<MeshSample::MeshVertAttribs>>(lhs) ^
			static_cast<std::underlying_type_t<MeshSample::MeshVertAttribs>>(rhs)
		);
	}

	MeshSample::MeshSample::MeshVertAttribs operator~(MeshSample::MeshVertAttribs the)
	{
		return static_cast<MeshSample::MeshVertAttribs>(
			~static_cast<std::underlying_type_t<MeshSample::MeshVertAttribs>>(the)
		);
	}

	bool operator==(MeshSample::MeshVertAttribs lhs, MeshSample::MeshVertAttribs rhs)
	{
		return
			static_cast<std::underlying_type_t<MeshSample::MeshVertAttribs>>(lhs) ==
			static_cast<std::underlying_type_t<MeshSample::MeshVertAttribs>>(rhs);
	}

	bool operator!=(MeshSample::MeshVertAttribs lhs, MeshSample::MeshVertAttribs rhs)
	{
		return
			static_cast<std::underlying_type_t<MeshSample::MeshVertAttribs>>(lhs) !=
			static_cast<std::underlying_type_t<MeshSample::MeshVertAttribs>>(rhs);
	}
}
