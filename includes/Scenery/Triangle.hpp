#pragma once

#include <Scenery/Vertex.hpp>
#include <Scenery/Material.hpp>

#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

namespace Scenery {

	class Triangle {

	public:

		Vertex* _1, * _2, * _3;
		Material* localMaterial = NULL;


		Triangle();
		Triangle(Vertex* _1, Vertex* _2, Vertex* _3);

		/**
		 * Recompute the normal between _1, _2, _3
		 */
		void renormalize();

		/**
		 * glBegin(GL_TRIANGLES)
		 */
		static void start();
		
		/**
		 * glEnd(GL_TRIANGLES)
		 */
		static void end();

		/**
		 * Use the three vertices in order to render the triangle
		 * start() and end() have to be used explicitally
		 */
		void draw();

	};

}