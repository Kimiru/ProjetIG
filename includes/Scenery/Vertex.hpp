#pragma once
#include <GL/gl.h>
#include <Matrix/Vec.hpp>
using namespace Matrix;

namespace Scenery {

	class Vertex {

	public:

		Vec<3> position;
		Vec<3> normal;
		bool useTexture;
		Vec<2> texturePosition;

		Vec<3> operator>>(Vertex v); // Compute vector going from this vertex to v vertex

		Vertex();

		void setTexPos(float x, float y);
		void use(); // Uses gl functions to define Vertex /!\ Must be used between glStart(...) and glEnd()

		static Vec<3> getNormal(Vertex v1, Vertex v2, Vertex v3); // Compute nomal from vectors v1->v2 and v1->v3

	};

}