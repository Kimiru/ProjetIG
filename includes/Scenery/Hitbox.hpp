#pragma once

#include <stdlib.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <vector>

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

	class HitboxBundle {

	public:
		std::vector<Cylinder*> cylinders;
		std::vector<Box*> boxes;
		Cylinder* foundCylinder;
		Box* foundBox;

		void add(Cylinder* cylinder);
		void add(Box* boxes);
		bool collide(Box box);
		bool collide(Cylinder cylinder);

		/**
		 * Test for collision between the hitbox and all boxes and cylinders
		 * in case of collision, call funcBox
		 */
		void collide(Box hitbox,
			std::function<void(Cylinder, Box)> funcBox);
		/**
		 * Test for collision between the hitbox and all boxes and cylinders
		 * in case of collision with a Box, call funcBox
		 * in case of collision with a Cylinder, call funcCylinder
		 */
		void collide(Cylinder hitbox,
			std::function<void(Cylinder, Box)> funcBox,
			std::function<void(Cylinder, Cylinder)> funcCylinder);

	};

}