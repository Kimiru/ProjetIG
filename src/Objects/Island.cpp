#include <Objects\Island.hpp>
#include "Scenery\Textures.hpp"

int Island::index = 0;
unsigned int Island::textureID = 0;



Island::Island(Matrix::Vec<3> position, Matrix::Vec<2> dimension)
{
	float dx = dimension[0] / 2;
	float dy = dimension[1] / 2;
	Scenery::Vertex vertex[] = {
		{-dx, -1, -dy}, // 0
		{dx, -1, -dy},
		{dx, -1, dy},
		{-dx, -1, dy},
		{-dx, 0, -dy}, // 4
		{dx, 0, -dy},
		{dx, 0, dy},
		{-dx, 0, dy},
		{-dx, -1, -dy}, // 8
		{dx, -1, -dy},
		{dx, -1, dy},
		{-dx, -1, dy},
		{-dx, 0, -dy}, // 12
		{dx, 0, -dy},
		{dx, 0, dy},
		{-dx, 0, dy},
	};

	int weights[] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };

	mesh.init(16, vertex, weights, 1);

	mesh.material = &meshMat;
	meshMat.diffuse(1, 1, 1, 1).ambiant(1, 1, 1, 1).cullBack();

	mesh.addQuadStrip(10, { 4, 0, 5, 1, 6, 2, 7, 3, 4, 0 });
	mesh.addPolygon(4, 2, { 8, 9, 10, 11, 15, 14, 13, 12 });

	mesh.compileSkeleton();
	mesh.build();

	dx = dimension[0];
	dy = dimension[1];

	mesh.altered[0].setTexPos(0, 0);
	mesh.altered[1].setTexPos(dx, 0);
	mesh.altered[2].setTexPos(0, 0);
	mesh.altered[3].setTexPos(dx, 0);
	mesh.altered[4].setTexPos(0, 1);
	mesh.altered[5].setTexPos(dx, 1);
	mesh.altered[6].setTexPos(0, 1);
	mesh.altered[7].setTexPos(dx, 1);
	mesh.altered[8].setTexPos(0, 0);
	mesh.altered[9].setTexPos(dx, 0);
	mesh.altered[10].setTexPos(dx, dy);
	mesh.altered[11].setTexPos(0, dy);
	mesh.altered[12].setTexPos(0, 0);
	mesh.altered[13].setTexPos(dx, 0);
	mesh.altered[14].setTexPos(dx, dy);
	mesh.altered[15].setTexPos(0, dy);



	int nbrTree = dimension[0] * dimension[1] / 6;
	if (!index)
		nbrTree = 0;
	index++;
	trees = new Tree[nbrTree];
	for (int i = 0; i < nbrTree; i++) {
		Tree& tree = trees[i];
		float ranX = (float)(rand() % 100) / 100 * dimension[0] - 0.5 * dimension[0];
		float ranZ = (float)(rand() % 100) / 100 * dimension[1] - 0.5 * dimension[1];
		tree.translation.set({ ranX,0, ranZ });
		tree.hitbox.anchorY = Hitbox::Anchor::BOTTOM;
		tree.hitbox.size.set({ 0.5, 1.5, 0.5 });
		tree.hitbox.setPosition(Matrix::Vec<3>({ position[0] + ranX, position[1], position[2] + ranZ }));
		bundle.add(&tree.hitbox);
		add(&trees[i]);
	}
	size = dimension;
	translation = ((Matrix::Vec<4>) position) << 1;
	baseBox.size.set({ size[0], 1, size[1] });
	baseBox.anchorY = Hitbox::Anchor::TOP;
	baseBox.setPosition(position);
	enterBox.size.set({ size[0], 1, size[1] });
	enterBox.anchorY = Hitbox::Anchor::BOTTOM;
	enterBox.setPosition(position);
}

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
