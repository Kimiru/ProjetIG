#pragma once

#include <Matrix/Vec.hpp>
#include <Scenery/Object.hpp>

class Island : public Scenery::Object {
public:
	Matrix::Vec<2> size;

	Island(Matrix::Vec<3> position, Matrix::Vec<2> dimension) {
		size = dimension;
		translation = ((Matrix::Vec<4>) position) << 1;

	}

	void draw();


};
