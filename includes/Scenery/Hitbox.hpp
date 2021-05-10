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
		Matrix::Vec<3> getPosition();


		/**
		 * Return the value depending on the axis and the side.
		 */
		float left() { return position.data[0] - size.data[0] / 2; }
		float right() { return position.data[0] + size.data[0] / 2; }
		float bottom() { return position.data[1] - size.data[1] / 2; }
		float top() { return position.data[1] + size.data[1] / 2; }
		float back() { return position.data[2] - size.data[2] / 2; }
		float front() { return position.data[2] + size.data[2] / 2; }

		void setLeft(float v) { position.data[0] = v + size.data[0] / 2; }
		void setRight(float v) { position.data[0] = v - size.data[0] / 2; }
		void setBottom(float v) { position.data[1] = v + size.data[1] / 2; }
		void setTop(float v) { position.data[1] = v - size.data[1] / 2; }
		void setBack(float v) { position.data[2] = v + size.data[2] / 2; }
		void setFront(float v) { position.data[2] = v - size.data[2] / 2; }

		/**
		 * Test a collision with a box
		 */
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
		Matrix::Vec<3> getPosition();

		float left() { return position.data[0] - radius; }
		float right() { return position.data[0] + radius; }
		float bottom() { return position.data[1] - height / 2; }
		float top() { return position.data[1] + height / 2; }
		float back() { return position.data[2] - radius; }
		float front() { return position.data[2] + radius; }

		void setLeft(float v) { position.data[0] = v + radius; }
		void setRight(float v) { position.data[0] = v - radius; }
		void setBottom(float v) { position.data[1] = v + height / 2; }
		void setTop(float v) { position.data[1] = v - height / 2; }
		void setBack(float v) { position.data[2] = v + radius; }
		void setFront(float v) { position.data[2] = v - radius; }

		/**
		 * Test a collision with a box (convert into a cube before testing)
		 */
		bool collide(Box b);

		/**
		 * Test a collision with a cylinder
		 */
		bool collide(Cylinder c);

		void draw();

	};

	class HitboxBundle {

	public:
		std::vector<Cylinder*> cylinders;
		std::vector<Box*> boxes;
		Cylinder* foundCylinder;
		Box* foundBox;

		HitboxBundle() {
			foundBox = NULL;
			foundCylinder = NULL;
		}

		/**
		 * Concatenate two bundles
		 */
		HitboxBundle operator+(HitboxBundle bundle) {
			HitboxBundle res;
			for (Box* b : boxes) res.add(b);
			for (Box* b : bundle.boxes) res.add(b);
			for (Cylinder* c : cylinders) res.add(c);
			for (Cylinder* c : bundle.cylinders) res.add(c);
			return res;
		}

		/**
		 * Concatenate two bundles
		 */
		HitboxBundle& operator+=(HitboxBundle bundle) {
			for (Box* b : bundle.boxes) add(b);
			for (Cylinder* c : bundle.cylinders) add(c);
			return *this;
		}

		/**
		 * Add a cylinder to the bundle
		 */
		void add(Cylinder* cylinder);

		/**
		 * Add a box to the bundle
		 */
		void add(Box* boxes);

		/**
		 * Test collisions with all the bundle content
		 */
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