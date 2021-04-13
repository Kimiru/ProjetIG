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

Island island = Island({ 0, 0, 0 }, { 5, 5 });

void update(float dt) {
	if (Window::getKey(0x1B)) {
		exit(0);
	}

	if (Window::getKey('a')) {
	}
	angle += dt * M_PI_2 / 2;

	l.position(cos(angle) * 10, 2, sin(angle) * 10);

	player.update(dt);
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

	island.render();
	player.render();

	player.groundHitbox.draw();
	island.baseBox.draw();

	glPopMatrix();
	glFlush();
	glutSwapBuffers();
	int err = glGetError();
	if (err != GL_NO_ERROR)
		std::cout << "An error occured " << err << std::endl;
}

int main(int argc, char** argv) {
	srand(time(NULL));

	player.islands = &islands;
	player.translation.data[1] = 1;
	islands.push_back(&island);
	l.diffuse(1.0f, 1.0f, 1.0f, 1.0f).position(-10.0f, .0f, 0.0f);
	l.specular(1.0f, 1.0f, 1.0f, 1.0f);

	Window::create(argc, argv, 900, 600, "Test");
	Window::drawFunc(draw);
	Window::updateFunc(update);
	l.turnOn();

	Window::launch();

	return 0;
}