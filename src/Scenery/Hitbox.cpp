#include <Scenery/Hitbox.hpp>

bool Hitbox::Box::collide(Box c)
{
	Matrix::Vec<3> size_2 = size / 2;
	Matrix::Vec<3> csize_2 = c.size / 2;
	/** Right left up down front back**/

	float r1 = position.data[0] + size_2.data[0];
	float r2 = c.position.data[0] + csize_2.data[0];

	float l1 = position.data[0] - size_2.data[0];
	float l2 = c.position.data[0] - csize_2.data[0];

	float u1 = position.data[1] + size_2.data[1];
	float u2 = c.position.data[1] + csize_2.data[1];

	float d1 = position.data[1] - csize_2.data[1];
	float d2 = c.position.data[1] - csize_2.data[1];

	float f1 = position.data[2] + size_2.data[2];
	float f2 = c.position.data[2] + csize_2.data[2];

	float b1 = position.data[2] - csize_2.data[2];
	float b2 = c.position.data[2] - csize_2.data[2];

	return
		r1 > l2 && r2 > l1 &&
		u1 > d2 && u2 > d1 &&
		f1 > b2 && f2 > b1;
}

void Hitbox::Box::draw()
{
	glPushMatrix();
	glTranslatef(position.data[0], position.data[1], position.data[2]);
	glScalef(size.data[0], size.data[1], size.data[2]);
	glutWireCube(1);
	glPopMatrix();
}

bool Hitbox::Cylinder::collide(Box b)
{
	return b.collide(*this);
}

bool Hitbox::Cylinder::collide(Cylinder c)
{
	float h1 = height / 2;
	float h2 = c.height / 2;
	return
		position.data[1] + h1 > c.position.data[1] - h2 &&
		c.position.data[1] + h2 > position.data[1] - h1 &&
		(position - c.position).length() < radius + c.radius;
}

void Hitbox::Cylinder::draw()
{
	glPushMatrix();
	glTranslatef(position.data[0], position.data[1] - height / 2, position.data[2]);
	glRotatef(-90, 1, 0, 0);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	gluCylinder(gluNewQuadric(), radius, radius, height, 8, 8);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glPopMatrix();
}