#pragma once

#include <Scenery/Vertex.hpp>

#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

namespace Scenery {

	class Triangle {

	public:

		Vertex& _1, _2, _3;

		Triangle(Vertex& _1, Vertex& _2, Vertex& _3);

		void draw();

	};

}