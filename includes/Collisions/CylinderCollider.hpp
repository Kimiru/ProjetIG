#pragma once

#include <Collisions/CubeCollider.hpp>

namespace Colliders {

	class Cylinder : public Cube {
	
	
	public : 
		Vec<3> size;
		float radius = 0.5f;
		float height = 1.0f;

		virtual bool collide(Cylinder c);

		bool collide(Cube c);

		virtual void draw();

		operator Cube() {
			Cube c;
			c.position = position;
			c.size.data(1) = height;
			c.size.data(0) = c.size.data(2) =  2 * radius;
			return c;
		}

	private: 
	
	};

}