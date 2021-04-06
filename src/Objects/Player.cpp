#include <Objects/Player.hpp>

Player::Player()
{
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


	// idle animation
	{
		idle.end = true;
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
		idleAnimators[0].addKey(0, 0, bezier(M_PI_4, -M_PI_4)); // X
		idleAnimators[1].methode = UpdateMethode::REF;
		idleAnimators[1].ref = &bones[6].rotation.data[2];
		idleAnimators[1].addKey(0, 0, linear(M_PI, M_PI)); // Z
		// left arm
		idleAnimators[2].methode = UpdateMethode::REF;
		idleAnimators[2].ref = &bones[8].rotation.data[0];
		idleAnimators[2].addKey(0, 0, bezier(M_PI_4, -M_PI_4)); // X
		idleAnimators[3].methode = UpdateMethode::REF;
		idleAnimators[3].ref = &bones[8].rotation.data[2];
		idleAnimators[3].addKey(0, 0, linear(-M_PI, -M_PI)); // Z

	}

	idle.play();

	displayBones = false;

}

void Player::update(float dt)
{
	idle.update(dt);

	build();

	checkInput(dt);
	updatePos(dt);
	updateCam(dt);
}

void Player::checkInput(float dt)
{
	bool _z = Window::getKey('z');
	bool _q = Window::getKey('q');
	bool _s = Window::getKey('s');
	bool _d = Window::getKey('d');
	if (_z || _q || _s || _d) {
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

	if (Window::getKey('r')) {
		float angle = (leader - translation).angle(2, 0) - (camera - translation).angle(2, 0) + M_PI;
		std::cout << "angle:" << angle;
	}
}

void Player::updatePos(float dt)
{
	const float tolerence = .1;

	Vec<3> dir = leader - translation;
	dir.data[1] = 0;

	if (dir.length() > tolerence) {
		dir.normalize();
		dir *= speed * dt;
		translation += dir;
		rotation.y(-dir.angle(2, 0));
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

	if (Window::getKey(' ')) {
		camera.data[0] = 10;
		camera.data[1] = 10;
		camera.data[2] = 10;
	}
	if (Window::getKey('a')) {
		camera.data[0] = 0.5;
		camera.data[1] = -10;
		camera.data[2] = 0;
	}
}
