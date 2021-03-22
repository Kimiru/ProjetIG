#pragma once

#include <vector>
#include <string>

#include <Matrix/Mat.hpp>
using namespace Matrix;

#include <Scenery/Euler.hpp>

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

		Mat<4> transformationMatrix;
		bool built = false;

		Object();

		void add(Object* child);
		void remove(int index);
		void remove(std::string name);

		void build();
		Vec<4> applyTransformation(Vec<4> v);

		void render();
		void draw();

	};

}