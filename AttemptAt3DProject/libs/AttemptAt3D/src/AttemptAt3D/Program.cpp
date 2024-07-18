
// #include "AttemptAt3D/Head.h"

#include <cstdio>
#include <list>

void printList(std::list<int>& l)
{
	std::printf("List:\n");
	for (int elem : l)
	{
		std::printf("  %i\n", elem);
	}
}

int main(void)
{
	// AttemptAt3D::Head head;
	// head.go();

	std::list<int> loi;
	loi.push_back(10);
	loi.push_back(20);
	loi.push_back(30);
	loi.push_back(40);
	loi.push_back(50);

	loi.push_back(10010);
	std::list<int>::iterator it1 = loi.end();
	it1--;

	loi.push_back(10020);
	std::list<int>::iterator it2 = loi.end();
	it2--;

	printList(loi);
	std::printf("one: %i\n", *it1);
	std::printf("two: %i\n", *it2);

	std::list<int>::iterator it1c = it1;
	std::printf("SIZE: %zi\n", sizeof(it1c));
	loi.erase(it1c);

	printList(loi);
	std::printf("one: %i\n", *it1);
	std::printf("two: %i\n", *it2);

	return 0;
}
