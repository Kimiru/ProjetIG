#pragma once

#include <stdlib.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <vector>

#include <Matrix/Vec.hpp>
#include <functional>

namespace Hitbox {

	enum class Anchor {
		LEFT, RIGHT, TOP, BOTTOM, FRONT, BACK, CENTER
	};

	class Box {

	public:
		Matrix::Vec<3> position;
		Matrix::Vec<3> size;
		Anchor anchorX = Anchor::CENTER, anchorY = Anchor::CENTER, anchorZ = Anchor::CENTER;

		void setPosition(Matrix::Vec<3> pos);

		float left() { return position.data[0] - size.data[0] / 2; }
		float right() { return position.data[0] + size.data[0] / 2; }
		float bottom() { return position.data[1] - size.data[1] / 2; }
		float top() { return position.data[1] + size.data[1] / 2; }
		float back() { return position.data[2] - size.data[2] / 2; }
		float front() { return position.data[2] + size.data[2] / 2; }

		bool collide(Box c);

		void draw();

	};

	class Cylinder {

	public:

		Matrix::Vec<3> position;
		float height = 0, radius = 0;
		Anchor anchorX = Anchor::CENTER, anchorY = Anchor::CENTER, anchorZ = Anchor::CENTER;

		operator Box() {
			Box b;
			b.position = position;
			b.size.data[0] = b.size.data[2] = radius * 2;
			b.size.data[1] = height;
			return b;
		}
		void setPosition(Matrix::Vec<3> pos);

		float left() { return position.data[0] - radius; }
		float right() { return position.data[0] + radius; }
		float bottom() { return position.data[1] - height / 2; }
		float top() { return position.data[1] + height / 2; }
		float back() { return position.data[2] - radius; }
		float front() { return position.data[2] + radius; }

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

		HitboxBundle operator+(HitboxBundle bundle) {
			HitboxBundle res;
			for (Box* b : boxes) res.add(b);
			for (Box* b : bundle.boxes) res.add(b);
			for (Cylinder* c : cylinders) res.add(c);
			for (Cylinder* c : bundle.cylinders) res.add(c);
			return res;
		}

		HitboxBundle& operator+=(HitboxBundle bundle) {
			for (Box* b : bundle.boxes) add(b);
			for (Cylinder* c : bundle.cylinders) add(c);
			return *this;
		}

		void add(Cylinder* cylinder);
		void add(Box* boxes);
		bool collide(Box box);
		bool collide(Cylinder cylinder);

		/**
		 * Test for collision between the hitbox and all boxes and cylinders
		 * in case of collision, call funcBox
		 */
		void collide(Box hitbox,
			std::function<void(Box, Box)> funcBox);
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