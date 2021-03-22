#pragma once

#include "Scenery/Object.hpp";
#include "Scenery/Material.hpp"

namespace Objects {

	class Tree : public Scenery::Object {

		Object leaves, trunk;
		Scenery::Material leavesMater, trunkMater;

	public:

		Tree();

		void draw();

	};

}