#include <iostream>

#define _USE_MATH_DEFINES
#include <math.h>
#include <time.h>

#include <Matrix/Mat.hpp>
#include <Scenery/Window.hpp>
#include <Scenery/Material.hpp>
#include <Scenery/Light.hpp>
#include <Scenery/Euler.hpp>
#include <Objects/Player.hpp>
#include <Scenery/Hitbox.hpp>
#include <Objects/Island.hpp>

using namespace Matrix;
using namespace Scenery;

static float angle = 0;
static Light l;


std::vector<Island*> islands;


Player player;

Island* island = NULL;

void init() {
	Island::index = 0;
	player.translation.set({ 0, 1, 0 });
	player.positionUpdater.vel.set({ 0, 0, 0 });
	player.positionUpdater.acc.set({ 0, 0, 0 });
	player.camera.set({ 0, 5, 5 });
	island = new  Island({ 0, 0, 0 }, { 5, 5 }, &islands);
	islands.push_back(island);
}

void _delete() {
	while (islands.size())
		(*islands.begin())->kill();
}

float rng() {
	return (float)(rand() % 100) / 100;
}

void update(float dt) {
	if (Window::getKey(0x1B)) {

		exit(0);
	}

	if (Window::getKey('a')) {
	}
	angle += dt * M_PI_2 / 2;

	l.position(cos(angle) * 10, 2, sin(angle) * 10);

	auto it = islands.begin();
	while (it != islands.end()) {
		(*it)->update(dt);

		if ((*it)->spawning && (*it)->spawstate == 1 && !(*it)->enteredBox && player.hitbox.collide((*it)->enterBox)) {
			(*it)->enteredBox = true;
			if ((*it)->prev != NULL)
				(*it)->prev->spawning = false;
			Matrix::Vec<2> size = Matrix::Vec<2>({ rng() * 4 + 3 , rng() * 4 + 3 });
			float angle = rng() * M_PI * 2;
			float len = (size / 2).length() + ((*it)->size / 2).length();
			float x = sin(angle) * len;
			float z = cos(angle) * len;
			Matrix::Vec<3> pos = Matrix::Vec<3>({ (*it)->translation[0] + x, (*it)->translation[1] + rng() * 2 - 1,(*it)->translation[2] + z });

			Island* i = new Island(pos, size, &islands);
			(*it)->next = i;
			i->prev = (*it);
			islands.push_back(i);
			break;
		}
		it++;
	}

	it = islands.begin();
	while (it != islands.end())
		if ((*it)->toFree) {
			(*it)->kill();

			break;
		}
		else it++;

	player.update(dt);

	if (player.positionUpdater.vel.data[1] < -20) {
		_delete();
		init();
	}

	glutPostRedisplay();
}

void draw() {
	glClearColor(0.5F, 0.5F, 0.5F, 0.5F);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPushMatrix();

	gluLookAt( // define cam to play cam lookat play belly
		player.camera.data[0], player.camera.data[1], player.camera.data[2],
		player.translation.data[0], player.translation.data[1] + .5, player.translation.data[2],
		.0f, 1.0f, .0f);

	l.use(); // use light


	auto it = islands.begin();
	while (it != islands.end()) {
		(*it)->enterBox.draw();
		(*it++)->render();
	}
	player.render();

	player.groundHitbox.draw();

	glPopMatrix();
	glFlush();
	glutSwapBuffers();
	int err = glGetError();
	if (err != GL_NO_ERROR)
		std::cout << "An error occured " << err << std::endl;
}

int main(int argc, char** argv) {
	srand(time(NULL));

	init();

	player.islands = &islands;


	l.diffuse(1.0f, 1.0f, 1.0f, 1.0f).position(-10.0f, .0f, 0.0f);
	l.specular(1.0f, 1.0f, 1.0f, 1.0f);

	Window::create(argc, argv, 900, 600, "Test");
	Window::drawFunc(draw);
	Window::updateFunc(update);
	l.turnOn();

	Window::launch();

	return 0;
}