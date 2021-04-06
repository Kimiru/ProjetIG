#pragma once

#include <Matrix/Vec.hpp>
#include <iostream>
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

namespace Colliders {

	class Cube {
	
	
	public : 
		Vec<3> position;
		Vec<3> size;

		virtual bool collide(Cube c);

		virtual void draw();


	private: 
		
	
	
	};

}