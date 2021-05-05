#pragma once

#include "Scenery/Object.hpp"
#include "Scenery/Material.hpp"
#include "Scenery/Hitbox.hpp"

class Leaves : public Scenery::Object {

private:

	Scenery::Material mater;

public:

	Leaves();

	void draw();

};

class Trunk : public Scenery::Object {

private:

	Scenery::Material mater;

public:

	Trunk();

	void draw();

};

class Tree : public Scenery::Object {

	Leaves leaves;
	Trunk trunk;

public:

	Hitbox::Box hitbox;

	Tree();

	void draw();




};