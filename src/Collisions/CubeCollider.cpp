#include <Collisions/CubeCollider.hpp>


bool Colliders::Cube::collide(Colliders::Cube c){
	Vec<3> size_2 = size / 2;
	Vec<3> csize_2 = c.size / 2 ;
	/** Right left up down front back**/

	float r1 = position.data(0) + size_2.position.data(0);
	float r2 = c.position.data(0) + csize_2.position.data(0);


	float l1 = position.data(0) - size_2.position.data(0);
	float l2 = c.position.data(0) - csize_2.position.data(0);
	
	float u1 = position.data(1) + size_2.position.data(1);
	float u2 = c.position.data(1) + csize_2.position.data(1);
	
	float d1 = c.position.data(1) - csize_2.position.data(1);
	float d2 = c.position.data(1) - csize_2.position.data(1);
	
	float f1 = position.data(2) + size_2.position.data(2);
	float f2 = c.position.data(2) + csize_2.position.data(2);

	float b1 = c.position.data(2) - csize_2.position.data(2);
	float b2 = c.position.data(2) - csize_2.position.data(2);

	return r1 > l2 && r2 > l1 && u1 > d2 && u2 > d1 && f1 > b2 && f2 > b1;
}

void Colliders::Cube::draw()
{
	glPushMatrix();
	glTranslatef(position.data[0], position.data[1], position.data[2]);
	glScalef(size.data[0], size.data[1], size.data[2]);
	glutSolidCube(1);
	glPopMatrix();
}
