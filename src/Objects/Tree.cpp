#include "Objects/Tree.hpp"

#include <iostream>

Leaves::Leaves() {
	this->material = &mater;
	mater.diffuse(58.0f / 256.0f, 95.0f / 256.0f, 11.0f / 256.0f, 1.0f);
}

Trunk::Trunk() {
	material = &mater;
	mater.diffuse(0.519f, 0.367f, 0.257f, 1.0);
}

Tree::Tree()
{
	trunk.translation.data[1] = .75f;

	trunk.scale.data[0] = .5f;
	trunk.scale.data[1] = 1.5f;
	trunk.scale.data[2] = .5f;

	add(&trunk);

	leaves.translation.data[1] = 2.5f;

	leaves.scale[0] = 2;
	leaves.scale[1] = 2;
	leaves.scale[2] = 2;


	add(&leaves);
}

void Tree::draw()
{
	std::cout << "cc\n";
}

void Leaves::draw()
{
	glutSolidCube(1);
}


void Trunk::draw()
{
	glutSolidCube(1);
}