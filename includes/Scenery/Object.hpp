#pragma once

#include <vector>
#include <string>

#include <Matrix/Mat.hpp>
using namespace Matrix;

#include <Scenery/Euler.hpp>
#include <Scenery/Material.hpp>
#include <Scenery/BuildOrder.hpp>

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
		BuildOrder buildOrder = BuildOrder::GL;

		Object();

		void add(Object* child);
		void remove(int index);
		void remove(std::string name);

		virtual void build();
		Vec<4> applyTransformation(Vec<4> v);

		void render();
		virtual void draw();
		virtual void update(float dt);
		void setBuildOrder(BuildOrder order) { buildOrder = order; rotation.buildOrder = order; }
	};

}