#include <Objects/Player.hpp>

Player::Player()
{
	bundle = NULL;
	positionUpdater.pos = &translation;
	hitbox.anchorY = Hitbox::Anchor::BOTTOM;
	hitbox.radius = .3;
	hitbox.height = 1.2;

	groundHitbox.anchorY = Hitbox::Anchor::TOP;
	groundHitbox.radius = .2;
	groundHitbox.height = .05;

	eyeMater.diffuse(0, 0, 0, 0).ambiant(0, 0, 0, 0).frontAndBack();

	int vamt = 86;

	Vertex vertices[] = {
		{-.25, 0, .1}, // 0 right leg
		{-.05, 0, .1},
		{-.05, 0, -.1},
		{-.25, 0, -.1},
		{-.25, .2, .1}, // 4
		{-.05, .2, .1},
		{-.05, .2, -.1},
		{-.25, .2, -.1},
		{-.25, .4, .1}, // 8
		{-.05, .4, .1}, // inside leg
		{-.05, .4, -.1},// inside leg
		{-.25, .4, -.1},

		{.25, 0, -.1}, // 12 left leg
		{.05, 0, -.1},
		{.05, 0, .1},
		{.25, 0, .1},
		{.25, .2, -.1}, // 16
		{.05, .2, -.1},
		{.05, .2, .1},
		{.25, .2, .1},
		{.25, .4, -.1}, // 20
		{.05, .4, -.1}, // inside leg
		{.05, .4, .1}, // inside leg
		{.25, .4, .1},

		{-.25, .6, .1}, // 24 trunk down
		{.25, .6, .1},
		{.25, .6, -.1},
		{-.25, .6, -.1},

		{-.25, .7, .1}, // 28 waist
		{.25, .7, .1},
		{.25, .7, -.1},
		{-.25, .7, -.1},

		{-.25, .9, .1}, // 32 trunk up
		{-.2, .9, .1},
		{.2, .9, .1},
		{.25, .9, .1},
		{.25, .9, -.1}, // 36
		{.2, .9, -.1},
		{-.2, .9, -.1},
		{-.25, .9, -.1},

		{-.45, .9, .1}, // 40 right arm
		{-.45, .9, -.1},
		{-.45, .7, -.1},
		{-.45, .7, .1},
		{-.65, .9, .1}, // 44
		{-.65, .9, -.1},
		{-.65, .7, -.1},
		{-.65, .7, .1},

		{.45, .9, -.1}, // 48 left arm
		{.45, .9, .1},
		{.45, .7, .1},
		{.45, .7, -.1},
		{.65, .9, -.1}, // 52
		{.65, .9, .1},
		{.65, .7, .1},
		{.65, .7, -.1},

		{-.125, .9, .125}, // 56
		{.125, .9, .125},
		{.125, .9, -.125},
		{-.125, .9, -.125},
		{-.125, 1.15, .125}, // 60
		{.125, 1.15, .125},
		{.125, 1.15, -.125},
		{-.125, 1.15, -.125},

		{-.1, 1.0, .130}, // 64 right eye
		{-.05, 1.0, .130},
		{-.05, 1.05, .130},
		{-.1, 1.05, .130},

		{.05, 1.0, .130}, // 68 left eye
		{.1, 1.0, .130},
		{.1, 1.05, .130},
		{.05, 1.05, .130},

		{-.125, 1.1, .05 }, // 72 right horn
		{-.125, 1.1, -.05 },
		{-.125, 1.05, 0 },
		{-.16, 1.1, .05 }, // 75
		{-.23, 1.1, 0 },
		{-.2, 1.05, 0.02 },
		{-.16, 1.25, .12}, // 78

		{.125, 1.1, .05 }, // 79 left horn
		{.125, 1.1, -.05 },
		{.125, 1.05, 0 },
		{.16, 1.1, .05 }, // 82
		{.23, 1.1, 0 },
		{.2, 1.05, 0.02 },
		{.16, 1.25, .12}, // 85

	};

	/*
		0 spine down
		1 spine up
		2 right leg up
		3 right leg down
		4 left leg up
		5 left leg down
		6 right arm up
		7 right arm down
		8 left arm up
		9 left arm down
		10 head
	*/

	int weights[] = {
		3, 3, 3, 3,
		3, 3, 3, 3, // right leg
		2, 2, 2, 2,

		5, 5, 5, 5,
		5, 5, 5, 5, // left leg
		4, 4, 4, 4,

		0, 0, 0, 0, // waist
		1, 1, 1, 1,

		6, 1, 1, 8, // shoulder
		8, 1, 1, 6,

		7, 7, 7, 7, // right arm
		7, 7, 7, 7,

		9, 9, 9, 9, // left arm
		9, 9, 9, 9,

		10, 10, 10, 10, // head
		10, 10, 10, 10,

		10, 10, 10, 10, // eyes
		10, 10, 10, 10,

		10, 10, 10, // right horn
		10, 10, 10,
		10,

		10, 10, 10, // left horn
		10, 10, 10,
		10,
	};

	init(vamt, vertices, weights, 11);

	/*
		0 spine down
		1 spine up
		2 right leg up
		3 right leg down
		4 left leg up
		5 left leg down
		6 right arm up
		7 right arm down
		8 left arm up
		9 left arm down
		10 head
	*/
	// bone conf
	{
		for (int i = 0; i < 11; i++) bones[i].setScale({ .05, .1, .05 });

		bones[0].add(&bones[1]);
		bones[0].add(&bones[2]);
		bones[2].add(&bones[3]);
		bones[0].add(&bones[4]);
		bones[4].add(&bones[5]);
		bones[1].add(&bones[6]);
		bones[6].add(&bones[7]);
		bones[1].add(&bones[8]);
		bones[8].add(&bones[9]);
		bones[1].add(&bones[10]);

		bones[0].translation[1] = .4;
		bones[0].rotation.order = Order::YXZ;

		bones[1].translation[1] = .25;

		bones[2].translation[0] = -.15;
		bones[2].rotation.order = Order::XZY;
		bones[2].rotation.setBase({ M_PI, 0, 0 });

		bones[3].translation[1] = .2;
		bones[3].rotation.order = Order::XZY;

		bones[4].translation[0] = .15;
		bones[4].rotation.order = Order::XZY;
		bones[4].rotation.setBase({ M_PI, 0, 0 });

		bones[5].translation[1] = .2;
		bones[5].rotation.order = Order::XZY;

		bones[6].translation[0] = -.25;
		bones[6].rotation.order = Order::ZXY;
		bones[6].rotation.setBase({ 0, 0, M_PI_2 });

		bones[7].translation[1] = .2;
		bones[7].rotation.order = Order::XZY;

		bones[8].translation[0] = .25;
		bones[8].rotation.order = Order::ZXY;
		bones[8].rotation.setBase({ 0, 0, -M_PI_2 });

		bones[9].translation[1] = .2;
		bones[9].rotation.order = Order::XZY;

		bones[10].translation[1] = .25;
	}

	// Mesh building
	{
		addQuadStrip(10, // right leg bottom
			{
				0, 4,
				1, 5,
				2, 6,
				3, 7,
				0, 4
			});
		addQuadStrip(10, // right leg top
			{
				4, 8,
				5, 9,
				6, 10,
				7, 11,
				4, 8
			});

		addQuadStrip(10, // left leg bottom
			{
				12, 16,
				13, 17,
				14, 18,
				15, 19,
				12, 16
			});

		addQuadStrip(10, // left leg top
			{
				16, 20,
				17, 21,
				18, 22,
				19, 23,
				16, 20
			});

		addQuadStrip(10, // waist
			{
				24, 28,
				25, 29,
				26, 30,
				27, 31,
				24, 28
			});

		addQuadStrip(8, // shoulder
			{
				32, 39,
				33, 38,
				34, 37,
				35, 36
			});

		addQuadStrip(10, // right arm up 
			{
				32, 40,
				39, 41,
				31, 42,
				28, 43,
				32, 40,
			});

		addQuadStrip(10, // right arm down
			{
				40, 44,
				41, 45,
				42, 46,
				43, 47,
				40, 44,
			});

		addQuadStrip(10, // left arm up
			{
				36, 48,
				35, 49,
				29, 50,
				30, 51,
				36, 48
			});

		addQuadStrip(10, // left arm down
			{
				48, 52,
				49, 53,
				50, 54,
				51, 55,
				48, 52
			});

		addQuadStrip(10, // head
			{
				56, 60,
				57, 61,
				58, 62,
				59, 63,
				56, 60,
			});

		addPolygon(4, 13,
			{
				3, 2, 1, 0, // right foot
				15,14,13,12, // left foor
				9, 10, 21, 22, // crotch
				11, 8, 24, 27, // right kidney
				23, 20, 26, 25, // left kidney
				9, 22, 25, 24, // belly
				21, 10, 27, 26, // booty
				28, 29, 34, 33, // chest
				30, 31, 38, 37, // back top
				44, 45, 46, 47, // right hand
				52, 53, 54, 55, // left hand
				59, 58, 57, 56, // head down
				60, 61, 62, 63, // head up
			});
		addPolygon(3, 8,
			{
				8, 9, 24, // right kidney
				10, 11, 27,
				22, 23, 25, // left kidney
				20, 21, 26,
				28, 33, 32, // shoulder
				29, 35, 34,
				30, 37, 36,
				31, 39, 38,
			});

		eyeMater.cullFront().cullNone();
		localMaterial = &eyeMater;
		addPolygon(4, 2, // eyes
			{
				64, 65, 66, 67,
				68, 69, 70, 71
			});

		addQuadStrip(8, //right horn
			{
				72, 75,
				73, 76,
				74, 77,
				72, 75,
			});

		addQuadStrip(8, //left horn
			{
				81, 84,
				80, 83,
				79, 82,
				81, 84,
			});

		addPolygon(3, 6, // horn point
			{
				75, 76, 78,
				76, 77, 78,
				77, 75, 78,
				84, 83, 85,
				83, 82, 85,
				82, 84, 85,
			});

		compileSkeleton();
		build();

		material = new Material();
		material->diffuse(.3, 0, 0, 1.0).ambiant(1, 0, 0, 1).front();
	}



	{ // idle animation

		idle.end = 1;
		idle.loop = true;
		idle.pingpong = true;
		for (int i = 0; i < 4; i++) {
			idle.addAnimator(&idleAnimators[i]);
			idleAnimators[i].end = 1;
			idleAnimators[i].loop = true;
			idleAnimators[i].pingpong = true;
		}

		// right arm
		idleAnimators[0].methode = UpdateMethode::REF;
		idleAnimators[0].ref = &bones[6].rotation.data[0];
		idleAnimators[0].addKey(0, 0, bezier(M_PI_4, -M_PI_4 / 2)); // X
		idleAnimators[1].methode = UpdateMethode::REF;
		idleAnimators[1].ref = &bones[6].rotation.data[2];
		idleAnimators[1].addKey(0, 0, linear(M_PI, M_PI)); // Z
		// left arm
		idleAnimators[2].methode = UpdateMethode::REF;
		idleAnimators[2].ref = &bones[8].rotation.data[0];
		idleAnimators[2].addKey(0, 0, bezier(M_PI_4, -M_PI_4 / 2)); // X
		idleAnimators[3].methode = UpdateMethode::REF;
		idleAnimators[3].ref = &bones[8].rotation.data[2];
		idleAnimators[3].addKey(0, 0, linear(-M_PI, -M_PI)); // Z

	}

	{// walk animation

		walk.end = 1;
		walk.loop = true;
		walk.pingpong = false;
		for (int i = 0; i < 8; i++) {
			walk.addAnimator(&walkAnimators[i]);
			walkAnimators[i].end = 1;
			walkAnimators[i].loop = true;
			walkAnimators[i].pingpong = false;
		}

		// RIGHT LEG
		walkAnimators[0].byReference();
		walkAnimators[0].ref = &bones[2].rotation.data[0];
		walkAnimators[0].addKey(0, 0, bezier(M_PI + M_PI_4, M_PI - M_PI / 3));
		walkAnimators[0].addKey(1, .5, bezier(M_PI - M_PI / 3, M_PI + M_PI_4));
		walkAnimators[1].byReference();
		walkAnimators[1].ref = &bones[3].rotation.data[0];
		walkAnimators[1].addKey(0, 0, linear(M_PI / 3, M_PI / 3));
		walkAnimators[1].addKey(1, .3, bezier(M_PI / 3, 0));
		walkAnimators[1].addKey(2, .6, linear(0, 0));
		walkAnimators[1].addKey(3, .7, bezier(0, M_PI / 3));

		// LEFT LEG
		walkAnimators[2].offset = .5;
		walkAnimators[2].byReference();
		walkAnimators[2].ref = &bones[4].rotation.data[0];
		walkAnimators[2].addKey(0, 0, bezier(M_PI + M_PI_4, M_PI - M_PI / 3));
		walkAnimators[2].addKey(1, .5, bezier(M_PI - M_PI / 3, M_PI + M_PI_4));
		walkAnimators[3].offset = .5;
		walkAnimators[3].byReference();
		walkAnimators[3].ref = &bones[5].rotation.data[0];
		walkAnimators[3].addKey(0, 0, linear(M_PI / 3, M_PI / 3));
		walkAnimators[3].addKey(1, .3, bezier(M_PI / 3, 0));
		walkAnimators[3].addKey(2, .6, linear(0, 0));
		walkAnimators[3].addKey(3, .7, bezier(0, M_PI / 3));

		// RIGHT ARM
		walkAnimators[4].methode = UpdateMethode::REF;
		walkAnimators[4].ref = &bones[6].rotation.data[0];
		walkAnimators[4].addKey(0, 0, bezier(M_PI_4, -M_PI_4 / 2)); // X
		walkAnimators[4].addKey(1, .5, bezier(-M_PI_4 / 2, M_PI_4)); // X
		walkAnimators[5].methode = UpdateMethode::REF;
		walkAnimators[5].ref = &bones[6].rotation.data[2];
		walkAnimators[5].addKey(0, 0, linear(M_PI, M_PI)); // Z

		// LEFT ARM
		walkAnimators[6].methode = UpdateMethode::REF;
		walkAnimators[6].ref = &bones[8].rotation.data[0];
		walkAnimators[6].addKey(0, 0, bezier(-M_PI_4 / 2, M_PI_4)); // X
		walkAnimators[6].addKey(1, .5, bezier(M_PI_4, -M_PI_4 / 2)); // X
		walkAnimators[7].methode = UpdateMethode::REF;
		walkAnimators[7].ref = &bones[8].rotation.data[2];
		walkAnimators[7].addKey(0, 0, linear(-M_PI, -M_PI)); // Z


	}

	{// jump

		jump.end = .3;
		jump.loop = false;
		jump.pingpong = false;
		for (int i = 0; i < 8; i++) {
			jump.addAnimator(&jumpAnimators[i]);
			jumpAnimators[i].end = .3;
			jumpAnimators[i].loop = false;
			jumpAnimators[i].pingpong = false;
		}

		// RIGHT LEG
		jumpAnimators[0].byReference();
		jumpAnimators[0].ref = &bones[2].rotation.data[0];
		jumpAnimators[0].addKey(0, 0, bezier(M_PI, M_PI - M_PI / 3));
		jumpAnimators[1].byReference();
		jumpAnimators[1].ref = &bones[3].rotation.data[0];
		jumpAnimators[1].addKey(0, 0, bezier(0, M_PI / 3));

		// LEFT LEG
		jumpAnimators[2].byReference();
		jumpAnimators[2].ref = &bones[4].rotation.data[0];
		jumpAnimators[2].addKey(0, 0, bezier(M_PI, M_PI + M_PI / 6));
		jumpAnimators[3].byReference();
		jumpAnimators[3].ref = &bones[5].rotation.data[0];
		jumpAnimators[3].addKey(0, 0, linear(0, 0));

		// RIGHT ARM
		jumpAnimators[4].methode = UpdateMethode::REF;
		jumpAnimators[4].ref = &bones[6].rotation.data[0];
		jumpAnimators[4].addKey(0, 0, bezier(0, M_PI_4)); // X
		jumpAnimators[5].methode = UpdateMethode::REF;
		jumpAnimators[5].ref = &bones[6].rotation.data[2];
		jumpAnimators[5].addKey(0, 0, bezier(M_PI, M_PI - M_PI / 6)); // Z

		// LEFT ARM
		jumpAnimators[6].methode = UpdateMethode::REF;
		jumpAnimators[6].ref = &bones[8].rotation.data[0];
		jumpAnimators[6].addKey(0, 0, bezier(0, M_PI_4)); // X
		jumpAnimators[7].methode = UpdateMethode::REF;
		jumpAnimators[7].ref = &bones[8].rotation.data[2];
		jumpAnimators[7].addKey(0, 0, linear(-M_PI, -M_PI + M_PI / 6)); // Z


	}

	{// fall

		fall.end = .3;
		fall.loop = false;
		fall.pingpong = false;
		for (int i = 0; i < 8; i++) {
			fall.addAnimator(&fallAnimators[i]);
			fallAnimators[i].end = .3;
			fallAnimators[i].loop = false;
			fallAnimators[i].pingpong = false;
		}

		// RIGHT LEG
		fallAnimators[0].byReference();
		fallAnimators[0].ref = &bones[2].rotation.data[0];
		fallAnimators[0].addKey(0, 0, bezier(M_PI, M_PI - M_PI_2));
		fallAnimators[1].byReference();
		fallAnimators[1].ref = &bones[3].rotation.data[0];
		fallAnimators[1].addKey(0, 0, bezier(0, M_PI / 3));

		// LEFT LEG
		fallAnimators[2].byReference();
		fallAnimators[2].ref = &bones[4].rotation.data[0];
		fallAnimators[2].addKey(0, 0, bezier(M_PI, M_PI - M_PI / 6));
		fallAnimators[3].byReference();
		fallAnimators[3].ref = &bones[5].rotation.data[0];
		fallAnimators[3].addKey(0, 0, linear(0, 0));

		// RIGHT ARM
		fallAnimators[4].methode = UpdateMethode::REF;
		fallAnimators[4].ref = &bones[6].rotation.data[0];
		fallAnimators[4].addKey(0, 0, bezier(0, M_PI_4)); // X
		fallAnimators[5].methode = UpdateMethode::REF;
		fallAnimators[5].ref = &bones[6].rotation.data[2];
		fallAnimators[5].addKey(0, 0, bezier(M_PI, M_PI_2)); // Z

		// LEFT ARM
		fallAnimators[6].methode = UpdateMethode::REF;
		fallAnimators[6].ref = &bones[8].rotation.data[0];
		fallAnimators[6].addKey(0, 0, bezier(0, M_PI_4)); // X
		fallAnimators[7].methode = UpdateMethode::REF;
		fallAnimators[7].ref = &bones[8].rotation.data[2];
		fallAnimators[7].addKey(0, 0, linear(-M_PI, -M_PI_2)); // Z


	}

	{// jumpfall

		jumpfall.end = .3;
		jumpfall.loop = false;
		jumpfall.pingpong = false;
		for (int i = 0; i < 8; i++) {
			jumpfall.addAnimator(&jumpfallAnimators[i]);
			jumpfallAnimators[i].end = .3;
			jumpfallAnimators[i].loop = false;
			jumpfallAnimators[i].pingpong = false;
		}

		// RIGHT LEG
		jumpfallAnimators[0].byReference();
		jumpfallAnimators[0].ref = &bones[2].rotation.data[0];
		jumpfallAnimators[0].addKey(0, 0, bezier(M_PI - M_PI / 3, M_PI - M_PI_2));
		jumpfallAnimators[1].byReference();
		jumpfallAnimators[1].ref = &bones[3].rotation.data[0];
		jumpfallAnimators[1].addKey(0, 0, bezier(M_PI / 3, M_PI / 3));

		// LEFT LEG
		jumpfallAnimators[2].byReference();
		jumpfallAnimators[2].ref = &bones[4].rotation.data[0];
		jumpfallAnimators[2].addKey(0, 0, linear(M_PI + M_PI / 6, M_PI - M_PI / 6));
		jumpfallAnimators[3].byReference();
		jumpfallAnimators[3].ref = &bones[5].rotation.data[0];
		jumpfallAnimators[3].addKey(0, 0, linear(0, 0));

		// RIGHT ARM
		jumpfallAnimators[4].methode = UpdateMethode::REF;
		jumpfallAnimators[4].ref = &bones[6].rotation.data[0];
		jumpfallAnimators[4].addKey(0, 0, linear(M_PI_4, M_PI_4)); // X
		jumpfallAnimators[5].methode = UpdateMethode::REF;
		jumpfallAnimators[5].ref = &bones[6].rotation.data[2];
		jumpfallAnimators[5].addKey(0, 0, linear(M_PI - M_PI / 6, M_PI - M_PI_2)); // Z

		// LEFT ARM
		jumpfallAnimators[6].methode = UpdateMethode::REF;
		jumpfallAnimators[6].ref = &bones[8].rotation.data[0];
		jumpfallAnimators[6].addKey(0, 0, bezier(M_PI_4, M_PI_4)); // X
		jumpfallAnimators[7].methode = UpdateMethode::REF;
		jumpfallAnimators[7].ref = &bones[8].rotation.data[2];
		jumpfallAnimators[7].addKey(0, 0, linear(-M_PI + M_PI / 6, -M_PI + M_PI_2)); // Z


	}

	animations.add(&idle);
	animations.add(&walk);
	animations.add(&jump);
	animations.add(&fall);
	animations.add(&jumpfall);

	animations.play(0);

	displayBones = false;

}

void Player::update(float dt)
{

	Hitbox::HitboxBundle bundle;
	Hitbox::HitboxBundle groundbundle;
	if (islands != NULL)
		for (Island* i : *islands) {
			bundle += i->bundle;
			groundbundle.add(&i->baseBox);
		}
	this->bundle = &bundle;
	this->groundbundle = &groundbundle;


	build();

	animations.update(dt);

	checkInput(dt);
	updatePos(dt);
	updateCam(dt);

	this->bundle = NULL;
	this->groundbundle = NULL;
}

void Player::checkInput(float dt)
{
	bool _z = Window::getKey('z');
	bool _q = Window::getKey('q');
	bool _s = Window::getKey('s');
	bool _d = Window::getKey('d');
	if (_z || _q || _s || _d) {
		if (!walk.run && abs(positionUpdater.vel.data[1]) < .5 && (*groundbundle).collide(groundHitbox)) {
			animations.play(1);
		}
		float angle = (camera - translation).angle(2, 0);
		Vec<3> move;

		if (_z) {
			float _cos = cos(angle + M_PI);
			float _sin = sin(angle + M_PI);
			move.data[0] += _sin;
			move.data[2] += _cos;
		}

		if (_q) {
			float _cos = cos(angle - M_PI_2);
			float _sin = sin(angle - M_PI_2);
			move.data[0] += _sin;
			move.data[2] += _cos;
		}

		if (_s) {
			float _cos = cos(angle);
			float _sin = sin(angle);
			move.data[0] += _sin;
			move.data[2] += _cos;
		}

		if (_d) {
			float _cos = cos(angle + M_PI_2);
			float _sin = sin(angle + M_PI_2);
			move.data[0] += _sin;
			move.data[2] += _cos;
		}

		if (move.length() != 0) {
			move.normalize();
			move *= speed;
			leader += move * dt;

		}
	}
	else if (!idle.run && abs(positionUpdater.vel.data[1]) < .5 && (*groundbundle).collide(groundHitbox)) {
		animations.stop();
		skeleton.reset();
		animations.play(0);
	}

	if (canJump && Window::getKeySingle(' ')) {
		positionUpdater.vel.data[1] = 4;
		canJump--;
		animations.stop();
		animations.play(2);
	}


	if (!fall.run && !jump.run && !jumpfall.run && positionUpdater.vel.data[1] < -.5) {
		animations.play(3);
	}

	if (jump.run && !jumpfall.run && jump.time >= .3 && positionUpdater.vel.data[1] < -.5) {
		animations.play(4);
	}


	if (Window::getSpecial(GLUT_KEY_LEFT)) {
		float camangle = (camera - translation).angle(2, 0);
		float _cos = cos(camangle + M_PI_2);
		float _sin = sin(camangle + M_PI_2);
		camera.data[0] += _sin * dt * 10;
		camera.data[2] += _cos * dt * 10;
	}
	if (Window::getSpecial(GLUT_KEY_RIGHT)) {
		float camangle = (camera - translation).angle(2, 0);
		float _cos = cos(camangle - M_PI_2);
		float _sin = sin(camangle - M_PI_2);
		camera.data[0] += _sin * dt * 10;
		camera.data[2] += _cos * dt * 10;
	}

	if (Window::getKey('r')) {
		float camangle = (camera - translation).angle(2, 0);
		float angle = (translation - leader).angle(2, 0) - camangle;
		angle = fmod(angle + M_PI, 2 * M_PI) - M_PI;
		if (abs(angle) > .005) {
			if (angle < 0) {
				float _cos = cos(camangle - M_PI_2);
				float _sin = sin(camangle - M_PI_2);
				camera.data[0] += _sin * dt * 10;
				camera.data[2] += _cos * dt * 10;
			}

			if (angle > 0) {
				float _cos = cos(camangle + M_PI_2);
				float _sin = sin(camangle + M_PI_2);
				camera.data[0] += _sin * dt * 10;
				camera.data[2] += _cos * dt * 10;
			}
		}
	}
}

void Player::updatePos(float dt)
{
	const float tolerence = .1;

	positionUpdater.vel.set({ 0, positionUpdater.vel.data[1], 0 });
	positionUpdater.acc.data[1] = -10;
	Vec<3> dir = leader - translation;
	dir.data[1] = 0;

	if (dir.length() > tolerence) {
		dir.normalize();
		dir *= speed;
		positionUpdater.vel += dir;
		rotation.y(-dir.angle(2, 0));
	}

	positionUpdater.update(dt);
	positionUpdater.collide(hitbox, *groundbundle, { 1, 1, 1 });
	positionUpdater.collide(hitbox, *bundle, { 1, 1, 1 });
	hitbox.setPosition(translation);
	groundHitbox.setPosition(translation);
	if (positionUpdater.vel.data[1] <= 0 && (*groundbundle).collide(groundHitbox)) {
		canJump = 2;
	}


	dir = translation - leader;
	dir.data[1] = 0;
	if (dir.length() > .1 * speed) {
		dir *= 0.5;
		leader += dir;
	}

}

void Player::updateCam(float dt)
{
	const float minSpeed = .5;
	const float percentSpeed = .7;
	const float tolerence = .005;

	Vec<3> dir = camera - translation;
	float ydif = dir.data[1] - 1.5;

	if (abs(ydif) > tolerence) {
		if (ydif > 0) {
			camera.data[1] -= max(percentSpeed * ydif, minSpeed) * dt;
		}
		else {
			camera.data[1] -= min(percentSpeed * ydif, -minSpeed) * dt;

		}
	}

	const float optimalDist = 3;

	Vec<2> hdif = Vec<2>({ dir.data[0], dir.data[2] });
	float dist = hdif.length();

	if (abs(dist - optimalDist) > tolerence) {

		if (dist > optimalDist) {
			hdif *= (percentSpeed);
			if (hdif.length() < minSpeed) {
				hdif.normalize();
				hdif *= minSpeed;
			}
			hdif *= dt;
			camera -= Vec<3>({ hdif.data[0], 0, hdif.data[1] });
		}
		else {
			hdif *= percentSpeed;
			if (hdif.length() < minSpeed) {
				hdif.normalize();
				hdif *= minSpeed;
			}
			hdif *= dt;
			camera += Vec<3>({ hdif.data[0], 0, hdif.data[1] });
		}
	}
}
