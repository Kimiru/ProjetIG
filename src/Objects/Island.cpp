#include <Objects\Island.hpp>

int Island::index = 0;

void Island::draw()
{
	glPushMatrix();
	glTranslatef(0, -0.5, 0);

	Matrix::Vec<2> dim = size;
	bool firstLayer = true;

	while (dim[0] >= 1 && dim[1] >= 1) {
		glPushMatrix();
		glScalef(dim[0], 1.0, dim[1]);
		glutSolidCube(1);
		glPopMatrix();
		glTranslatef(0, -1.0, 0);
		firstLayer = false;
		dim[0] -= 2;
		dim[1] -= 1;
	}

	glPopMatrix();
}
