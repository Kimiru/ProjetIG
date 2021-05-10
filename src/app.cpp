#include <iostream>

#define _USE_MATH_DEFINES
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include <Matrix/Mat.hpp>
#include <Scenery/Window.hpp>
#include <Scenery/Material.hpp>
#include <Scenery/Light.hpp>
#include <Scenery/Euler.hpp>
#include <Objects/Player.hpp>
#include <Scenery/Hitbox.hpp>
#include <Objects/Island.hpp>
#include <Scenery/Textures.hpp>



/* Variables et constantes globales             */

static const float blanc[] = { 1.0F,1.0F,1.0F,1.0F };
static const float noir[] = { 0.0F,0.0F,0.0F,1.0F };

static int illumination = 1;
static int deuxFaces = 1;
static int anim = 0;
static int question = 0;
static int texture = 1;
static float rx = 0.0F;
static float ry = 0.0F;
static float rz = 0.0F;

//////////////////////////////////////////////////

static unsigned int textureID = 0;


using namespace Matrix;
using namespace Scenery;

static float angle = 0;

std::vector<Island*> islands;

Player player;

Island* island = NULL;



unsigned char* grass_image() {
	int nc = 32;
	int nl = 32;

	srand(0);

	unsigned char* img = (unsigned char*)calloc(3 * nc * nl, sizeof(unsigned char));
	if (!img)
		return NULL;
	unsigned char* p = img;
	for (int l = 0; l < nl; l++)
		for (int c = 0; c < nc; c++) {
			unsigned int rng = rand() % 100;
			rng = rng * 1 + 92;
			p[0] = 0;
			p[1] = rng;
			p[2] = 0;

			p += 3;
		}
	return img;
}



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
	if (Window::getKey(0x1B))
		exit(0);

	angle += dt * M_PI_2 / 2;


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
	float per = .3;
	glClearColor((75.0F / 255.0f) * per, 0, (130.0F / 255.0f) * per, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPushMatrix();

	gluLookAt( // define cam to play cam lookat play belly
		player.camera.data[0], player.camera.data[1], player.camera.data[2],
		player.translation.data[0], player.translation.data[1] + .5, player.translation.data[2],
		.0f, 1.0f, .0f);


	auto it = islands.begin();
	while (it != islands.end()) {
		(*it++)->render();
	}
	player.render();

	glPopMatrix();
	glFlush();
	glutSwapBuffers();
	int err = glGetError();
	if (err != GL_NO_ERROR)
		std::cout << "An error occured " << err << std::endl;
}

int main(int argc, char** argv) {

	srand(time(NULL));


	atexit(_delete);

	Window::create(argc, argv, 900, 600, "Island Jumper");
	Window::drawFunc(draw);
	Window::updateFunc(update);

	init();
	player.islands = &islands;
	Island::textureID = Textures::initTexture(grass_image(), 32, 32);

	Window::launch();

	return 0;
}