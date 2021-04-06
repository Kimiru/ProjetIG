#pragma once

#include <Scenery/SkinnedMesh.hpp>
#include <Scenery/Animator.hpp>

#include <Scenery/Window.hpp>
#define _USE_MATH_DEFINES
#include <math.h>

using namespace Scenery;

class Player : public SkinnedMesh {

public:

	Material eyeMater;

	AnimatorBundle idle;
	Animator idleAnimators[4];

	Vec<3> camera = Vec<3>({ 0, 1, 1 });
	Vec<3> leader = Vec<3>({ 0, 0, 0.001 });

	const float speed = 2;

	Player();
	~Player() { delete material; }

	void update(float dt);
private:
	void checkInput(float dt);
	void updatePos(float dt);
	void updateCam(float dt);
};