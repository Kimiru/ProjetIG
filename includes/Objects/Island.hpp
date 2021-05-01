#pragma once

#include "Matrix/Vec.hpp"
#include "Scenery/Object.hpp"
#include "Scenery/Hitbox.hpp"
#include "Objects/Tree.hpp"
#include <vector>

class Island : public Scenery::Object {
public:
	Matrix::Vec<2> size;
	Hitbox::HitboxBundle bundle;
	Hitbox::Box baseBox;
	Hitbox::Box enterBox;
	bool enteredBox = false;
	Tree* trees = NULL;
	bool spawning = true;
	float spawstate = 0.00001;
	std::vector<Island*>* otherIslands = NULL;
	bool toFree = false;
	Island* prev = NULL, * next = NULL;

	static int index;

	Island(Matrix::Vec<3> position, Matrix::Vec<2> dimension) {

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

	Island(Matrix::Vec<3> position, Matrix::Vec<2> dimension, std::vector<Island*>* others) : Island(position, dimension) {
		otherIslands = others;
	}

	~Island() {
		if (trees != NULL) {
			delete[] trees;
		}
	}

	void kill();

	void draw();
	void update(float dt);

};
