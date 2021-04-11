#pragma once

#include "Matrix/Vec.hpp"
#include "Scenery/Object.hpp"
#include "Scenery/Hitbox.hpp"

class Island : public Scenery::Object {
public:
	Matrix::Vec<2> size;
	Hitbox::HitboxBundle bundle;
	Hitbox::Box baseBox;

	Island(Matrix::Vec<3> position, Matrix::Vec<2> dimension) {
		size = dimension;
		translation = ((Matrix::Vec<4>) position) << 1;
		baseBox.size.set({ size[0], 1, size[1] });
		baseBox.anchorY = Hitbox::Anchor::TOP;
		baseBox.setPosition(position);
		bundle.add(&baseBox);
	}

	void draw();


};
