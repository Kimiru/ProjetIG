#include <Collisions/CylinderCollider.hpp>

bool Colliders::Cylinder::collide(Cylinder c)
{
	float size_2 = height/2;

	float u1 = position.data(1) + size_2;
	float u2 = c.position.data(1) + size_2;

	float d1 = c.position.data(1) - size_2;
	float d2 = c.position.data(1) - size_2;

	Vec<3> dir = c.position - position;
	dir.data(1) = 0;
	float dist = dir.length;
	return u1 > d2 && u2 > d1 && dist < radius + c.radius;
}

bool Colliders::Cylinder::collide(Cube c)
{
	return collide(*this);
}

void Colliders::Cylinder::draw()
{
	glPushMatrix();
	glTranslatef(position.data[0], position.data[1], position.data[2]);
	gluCylinder(gluNewQuadric(), radius, radius, height, 8, 8);
	glPopMatrix();
}
