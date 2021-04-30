#include <Objects\Island.hpp>
#include "Scenery\Textures.hpp"

int Island::index = 0;
unsigned int Island::textureID = 0;



void Island::kill()
{
	if (otherIslands != NULL) {
		auto it = otherIslands->begin();
		while (it != otherIslands->end())
			if (*it == this)
				break;
			else
				it++;
		otherIslands->erase(it);
	}
	delete this;
}

void Island::draw()
{
	if (toFree) return;
	glPushMatrix();

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, Island::textureID);
	mesh.render();
	glDisable(GL_TEXTURE_2D);

	glTranslatef(0, -1.5, 0);

	Matrix::Vec<2> dim = size;
	dim[0] -= 2;
	dim[1] -= 2;
	bool firstLayer = true;

	while (dim[0] >= 1 && dim[1] >= 1) {
		glPushMatrix();
		glScalef(dim[0], 1.0, dim[1]);
		glutSolidCube(1);
		glPopMatrix();
		glTranslatef(0, -1.0, 0);
		firstLayer = false;
		dim[0] -= 2;
		dim[1] -= 2;
	}

	glPopMatrix();
}

void Island::update(float dt)
{
	if (!toFree) {
		if (spawning) {
			if (spawstate < 1) {

				spawstate += dt;

				if (spawstate > 1)
					spawstate = 1;
			}
		}
		else {
			spawstate -= dt;
			if (spawstate <= 0)
				toFree = true;
		}

		if (spawstate < 1 && spawstate > 0) {
			scale.set({ spawstate, spawstate , spawstate });
		}
	}

}
