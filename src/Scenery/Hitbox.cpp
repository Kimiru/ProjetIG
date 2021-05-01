#include <Scenery/Hitbox.hpp>

void Hitbox::Box::setPosition(Matrix::Vec<3> pos)
{
	switch (anchorX)
	{
	case Hitbox::Anchor::LEFT:
		pos.data[0] += size.data[0] / 2;
		break;
	case Hitbox::Anchor::RIGHT:
		pos.data[0] -= size.data[0] / 2;
		break;
	}

	switch (anchorY)
	{
	case Hitbox::Anchor::BOTTOM:
		pos.data[1] += size.data[1] / 2;
		break;
	case Hitbox::Anchor::TOP:
		pos.data[1] -= size.data[1] / 2;
		break;
	}

	switch (anchorZ)
	{
	case Hitbox::Anchor::BACK:
		pos.data[2] += size.data[2] / 2;
		break;
	case Hitbox::Anchor::FRONT:
		pos.data[2] -= size.data[2] / 2;
		break;
	}

	position = pos;
}

Matrix::Vec<3> Hitbox::Box::getPosition()
{

	Matrix::Vec<3> pos = position;

	switch (anchorX)
	{
	case Hitbox::Anchor::LEFT:
		pos.data[0] -= size.data[0] / 2;
		break;
	case Hitbox::Anchor::RIGHT:
		pos.data[0] += size.data[0] / 2;
		break;
	}

	switch (anchorY)
	{
	case Hitbox::Anchor::BOTTOM:
		pos.data[1] -= size.data[1] / 2;
		break;
	case Hitbox::Anchor::TOP:
		pos.data[1] += size.data[1] / 2;
		break;
	}

	switch (anchorZ)
	{
	case Hitbox::Anchor::BACK:
		pos.data[2] -= size.data[2] / 2;
		break;
	case Hitbox::Anchor::FRONT:
		pos.data[2] += size.data[2] / 2;
		break;
	}

	return pos;
}

bool Hitbox::Box::collide(Box c)
{
	Matrix::Vec<3> size_2 = size / 2;
	Matrix::Vec<3> csize_2 = c.size / 2;
	/** Right left up down front back**/

	float r1 = right();
	float r2 = c.right();

	float l1 = left();
	float l2 = c.left();

	float u1 = top();
	float u2 = c.top();

	float d1 = bottom();
	float d2 = c.bottom();

	float f1 = front();
	float f2 = c.front();

	float b1 = back();
	float b2 = c.back();

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

void Hitbox::Cylinder::setPosition(Matrix::Vec<3> pos)
{

	switch (anchorX)
	{
	case Hitbox::Anchor::LEFT:
		pos.data[0] += radius;
		break;
	case Hitbox::Anchor::RIGHT:
		pos.data[0] -= radius;
		break;
	}

	switch (anchorY)
	{
	case Hitbox::Anchor::BOTTOM:
		pos.data[1] += height / 2;
		break;
	case Hitbox::Anchor::TOP:
		pos.data[1] -= height / 2;
		break;
	}

	switch (anchorZ)
	{
	case Hitbox::Anchor::BACK:
		pos.data[2] += radius;
		break;
	case Hitbox::Anchor::FRONT:
		pos.data[2] -= radius;
		break;
	}

	position = pos;
}

Matrix::Vec<3> Hitbox::Cylinder::getPosition()
{

	Matrix::Vec<3> pos = position;

	switch (anchorX)
	{
	case Hitbox::Anchor::LEFT:
		pos.data[0] -= radius;
		break;
	case Hitbox::Anchor::RIGHT:
		pos.data[0] += radius;
		break;
	}

	switch (anchorY)
	{
	case Hitbox::Anchor::BOTTOM:
		pos.data[1] -= height / 2;
		break;
	case Hitbox::Anchor::TOP:
		pos.data[1] += height / 2;
		break;
	}

	switch (anchorZ)
	{
	case Hitbox::Anchor::BACK:
		pos.data[2] -= radius / 2;
		break;
	case Hitbox::Anchor::FRONT:
		pos.data[2] += radius / 2;
		break;
	}

	return pos;
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

void Hitbox::HitboxBundle::add(Cylinder* cylinder)
{
	cylinders.push_back(cylinder);
}

void Hitbox::HitboxBundle::add(Box* box)
{
	boxes.push_back(box);
}

bool Hitbox::HitboxBundle::collide(Box box)
{
	foundBox = NULL;
	foundCylinder = NULL;

	for (Box* b : boxes) {
		if (b->collide(box)) {
			foundBox = b;
			return true;
		}
	}

	for (Cylinder* c : cylinders) {
		if (c->collide(box)) {
			foundCylinder = c;
			return true;
		}
	}

	return false;
}

bool Hitbox::HitboxBundle::collide(Cylinder cylinder)
{
	foundBox = NULL;
	foundCylinder = NULL;

	for (Box* b : boxes) {
		if (b->collide(cylinder)) {
			foundBox = b;
			return true;
		}
	}

	for (Cylinder* c : cylinders) {
		if (c->collide(cylinder)) {
			foundCylinder = c;
			return true;
		}
	}

	return false;
}

void Hitbox::HitboxBundle::collide(Box hitbox, std::function<void(Box, Box)> funcBox)
{
	foundBox = NULL;
	foundCylinder = NULL;

	for (Box* b : boxes) {
		if (b->collide(hitbox)) {
			foundBox = b;
			funcBox(hitbox, *b);
		}
	}

	for (Cylinder* c : cylinders) {
		if (c->collide(hitbox)) {
			foundCylinder = c;
			funcBox(hitbox, (Hitbox::Box)*c);
		}
	}
}

void Hitbox::HitboxBundle::collide(Cylinder hitbox, std::function<void(Cylinder, Box)> funcBox, std::function<void(Cylinder, Cylinder)> funcCylinder)
{
	foundBox = NULL;
	foundCylinder = NULL;

	for (Box* b : boxes) {
		if (b->collide(hitbox)) {
			foundBox = b;
			funcBox(hitbox, *b);
		}
	}

	for (Cylinder* c : cylinders) {
		if (c->collide(hitbox)) {
			foundCylinder = c;
			funcCylinder(hitbox, *c);
		}
	}
}


