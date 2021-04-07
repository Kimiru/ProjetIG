#pragma once

#include <stdlib.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include <Matrix/Vec.hpp>

namespace Hitbox {

	class Box {

	public:

		Matrix::Vec<3> position;
		Matrix::Vec<3> size;

		bool collide(Box c);

		void draw();

	};

	class Cylinder {

	public:

		Matrix::Vec<3> position;
		float height = 0, radius = 0;

		operator Box() {
			Box b;
			b.position = position;
			b.size.data[0] = b.size.data[2] = radius * 2;
			b.size.data[1] = height;
			return b;
		}

		bool collide(Box b);
		bool collide(Cylinder c);

		void draw();

	};

}