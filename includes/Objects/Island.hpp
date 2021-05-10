#pragma once

#include "Matrix/Vec.hpp"
#include "Scenery/Object.hpp"
#include "Scenery/Hitbox.hpp"
#include "Objects/Tree.hpp"
#include <vector>
#include <Scenery\Vertex.hpp>
#include <Scenery\SkinnedMesh.hpp>
#include <Scenery\Triangle.hpp>
#include <Objects/Crystal.hpp>

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
	Scenery::SkinnedMesh mesh;
	Scenery::Material meshMat;
	Crystal crystal;

	static int index;
	static unsigned int textureID;

	/**
	 * Island constructor, create the island, hitbox and trees
	 */
	Island(Matrix::Vec<3> position, Matrix::Vec<2> dimension);

	Island(Matrix::Vec<3> position, Matrix::Vec<2> dimension, std::vector<Island*>* others) : Island(position, dimension) {
		otherIslands = others;
	}

	~Island() {
		if (trees != NULL) {
			delete[] trees;
		}
	}

	/**
	 * Remove the island from the islands list
	 */
	void kill();

	void draw();
	void update(float dt);

};
