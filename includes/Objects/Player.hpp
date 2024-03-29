#pragma once

#include "Scenery/SkinnedMesh.hpp"
#include "Scenery/Animator.hpp"

#include "Scenery/Window.hpp"
#define _USE_MATH_DEFINES
#include <math.h>
#include "Objects/Island.hpp"
#include "Scenery/PositionUpdater.hpp"
#include "Scenery/Hitbox.hpp"

using namespace Scenery;

class Player : public SkinnedMesh {

public:

	Material eyeMater;

	AnimatorBundle idle;
	Animator idleAnimators[4];
	AnimatorBundle walk;
	Animator walkAnimators[8];
	AnimatorBundle jump;
	Animator jumpAnimators[8];
	AnimatorBundle fall;
	Animator fallAnimators[8];
	AnimatorBundle jumpfall;
	Animator jumpfallAnimators[8];

	AnimationSelector animations;



	std::vector<Island*>* islands = NULL;
	PositionUpdater positionUpdater;
	Hitbox::Cylinder hitbox, groundHitbox;
	int canJump = 2;
	Hitbox::HitboxBundle* bundle = NULL;
	Hitbox::HitboxBundle* groundbundle = NULL;



	Vec<3> camera = Vec<3>({ 0, 1, 1 });
	Vec<3> leader = Vec<3>({ 0, 0, 0.001 });

	const float speed = 4;

	/**
	 * Create the player, its hitbox, its mesh and its animations
	 */
	Player();
	~Player() { delete material; }

	void update(float dt);

private:
	/**
	 * Check the input and update the player 
	 */
	void checkInput(float dt);
	/**
	 * Update the position depending on velocity and acceleration
	 */
	void updatePos(float dt);
	/**
	 * Update the camera position
	 */
	void updateCam(float dt);
};