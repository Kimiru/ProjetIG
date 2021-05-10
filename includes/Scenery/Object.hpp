#pragma once

#include <vector>
#include <string>

#include <Matrix/Mat.hpp>
using namespace Matrix;

#include <Scenery/Euler.hpp>
#include <Scenery/Material.hpp>

#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
//using namespace Matrix;
namespace Scenery {

	class Object {

	public:
		std::vector<Object*> children;
		std::string name;

		Vec<3> translation;
		Euler rotation;
		Vec<3> scale;
		Material* material = NULL;

		Mat<4> transformationMatrix;
		bool built = false;

		Object();

		/**
		 * Manage children
		 */
		void add(Object* child);
		void remove(int index);
		void remove(std::string name);

		/**
		 * Build transformation matrix
		 */
		virtual void build();

		/**
		 * Apply the transformation matrix to the vector given in paramater
		 */
		Vec<4> applyTransformation(Vec<4> v);

		/**
		 * Apply materials, transformations, render the object and its children
		 */
		void render();

		/**
		 * Draw the object
		 */
		virtual void draw();

		/**
		 * Update the object
		 */
		virtual void update(float dt);
	};

}