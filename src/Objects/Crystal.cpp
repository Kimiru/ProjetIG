#include "Objects/Crystal.hpp"

void Crystal::draw()
{
	glPushMatrix();
	glutSolidCube(1);
	glPopMatrix();
}
