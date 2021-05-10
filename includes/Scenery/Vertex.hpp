#pragma once

#include <GL/gl.h>
#include <Matrix/Vec.hpp>
using namespace Matrix;

namespace Scenery {

	class Vertex {

	public:

		Vec<3> position;
		Vec<3> normal;
		bool useTexture = false;
		Vec<2> texturePosition;

		/**
		 * Compute vector going from this vertex to v vertex
		 */
		Vec<3> operator>>(Vertex v);

		Vertex();
		Vertex(float x, float y, float z);
		Vertex(std::initializer_list<float> list);


		/**
		 * In case of using texture, defines the position on the texture
		 */
		void setTexPos(float x, float y);

		/**
		 * Uses gl functions to define Vertex /!\ Must be used between glStart(...) and glEnd()
		 */
		void use();

		/**
		 * Compute nomal from vectors v1->v2 and v1->v3
		 */
		static Vec<3> getNormal(Vertex v1, Vertex v2, Vertex v3);

	};

}

