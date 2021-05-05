#pragma once

#include "Scenery/Object.hpp"
#include "Scenery/Material.hpp"
#include "Scenery/Light.hpp"
#define _USE_MATH_DEFINES
#include <math.h>

class Crystal : public Scenery::Object {

public:

	Scenery::Material m;
	Scenery::Light l;

	Crystal() {
		material = &m;
		m.emission(0.5, 0.5, 0.0, 1.0);
		scale.set({ .1, .1, .1 });
		rotation.x(M_PI / 4);
		rotation.y(M_PI / 4);
		rotation.z(M_PI / 4);
		l.ambiant(0.1, 0.1, 0.2, 0.1).diffuse(25, 15, 0, .6).position(0, 0, 0).quadraticAttenuation(3);
		l.turnOn();
	}
	~Crystal() {
		l.turnOff();
	}

	void draw();

};