
// #include "AttemptAt3D/Head.h"

// #include <cstdio>
// #include <list>

#include "AttemptAt3D/BodyManager/BodyManager.h"

// void printList(std::list<int>& l)
// {
// 	std::printf("List:\n");
// 	for (int elem : l)
// 	{
// 		std::printf("  %i\n", elem);
// 	}
// }

int main(void)
{
	// AttemptAt3D::Head head;
	// head.go();

	// std::list<int> loi;
	// loi.push_back(10);
	// loi.push_back(20);
	// loi.push_back(30);
	// loi.push_back(40);
	// loi.push_back(50);

	// loi.push_back(10010);
	// std::list<int>::iterator it1 = loi.end();
	// it1--;

	// loi.push_back(10020);
	// std::list<int>::iterator it2 = loi.end();
	// it2--;

	// printList(loi);
	// std::printf("one: %i\n", *it1);
	// std::printf("two: %i\n", *it2);

	// std::list<int>::iterator it1c = it1;
	// std::printf("SIZE: %zi\n", sizeof(it1c));
	// loi.erase(it1c);

	// printList(loi);
	// std::printf("one: %i\n", *it1);
	// std::printf("two: %i\n", *it2);

	AttemptAt3D::BodyManager bm;

	const std::size_t vertsLen1 = 4;
	std::unique_ptr<float[]> verts1(new float[vertsLen1] {1.0f, 2.0f, 3.0f, 4.0f});
	const std::size_t elemsLen1 = 3;
	std::unique_ptr<GLuint[]> elems1(new GLuint[elemsLen1] {0, 3, 2});
	auto bodyref1 = bm.makeNewBody(vertsLen1, std::move(verts1), elemsLen1, std::move(elems1));
	
	const std::size_t vertsLen2 = 5;
	std::unique_ptr<float[]> verts2(new float[vertsLen2] {1.5f, 2.5f, 3.5f, 4.5f, 5.5f});
	const std::size_t elemsLen2 = 11;
	std::unique_ptr<GLuint[]> elems2(new GLuint[elemsLen2] {0, 3, 2, 1, 3, 2, 2, 1, 0, 2, 1});
	auto bodyref2 = bm.makeNewBody(vertsLen2, std::move(verts2), elemsLen2, std::move(elems2));

	bm.drawAllBodies();

	return 0;
}
