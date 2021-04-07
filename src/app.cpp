#include <iostream>

#define _USE_MATH_DEFINES
#include <math.h>

#include <Matrix/Mat.hpp>
#include <Scenery/Window.hpp>
#include <Scenery/Material.hpp>
#include <Scenery/Light.hpp>
#include <Scenery/Euler.hpp>
#include <memory>
#include <Objects/Player.hpp>
#include <Scenery/Hitbox.hpp>

using namespace Matrix;
using namespace Scenery;

static float angle = 0;
static Light l;


Animator a;
Player b;

Hitbox::Box box;
Hitbox::Cylinder c;

void update(float dt) {
	if (Window::getKey(0x1B)) {
		exit(0);
	}

	if (Window::getKey('a')) {
	}
	angle += dt * M_PI_2 / 2;

	l.position(cos(angle) * 10, .05f, sin(angle) * 10);

	b.update(dt);
	a.update(dt);
	glutPostRedisplay();
}

void draw() {
	glClearColor(0.5F, 0.5F, 0.5F, 0.5F);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPushMatrix();

	gluLookAt(
		b.camera.data[0], b.camera.data[1], b.camera.data[2],
		b.translation.data[0], b.translation.data[1] + .5, b.translation.data[2],
		.0f, 1.0f, .0f);

	l.use();

	glPushMatrix();
	glTranslatef(b.leader[0], b.leader[1], b.leader[2]);
	glutSolidSphere(.1, 4, 4);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, -.1, 0);
	glScalef(10, .2, 10);
	glutSolidCube(1);
	glPopMatrix();

	/*Euler e;
	e.z(angle * M_PI / 180);
	auto rm = e.getMatrix();


	glMultMatrixf((const float*)rm.data);*/
	//auto mat = Mat<4>::rotZ(angle * M_PI / 180);

	//glMultMatrixf((const float*)mat.data);


	//p1.get()->render();

	//t.translation[1] = -1;
	//t.render();

	b.render();

	box.draw();
	c.draw();

	glPopMatrix();
	glFlush();
	glutSwapBuffers();
	int err = glGetError();
	if (err != GL_NO_ERROR)
		std::cout << "An error occured " << err << std::endl;
}

int main(int argc, char** argv) {

	box.size[0] = 1;
	box.size[1] = 2;
	box.size[2] = .5;

	c.radius = .5;
	c.height = 1;

	a.addKey(0, 0, bezier(-2, 2));
	a.end = 2;
	a.loop = true;
	a.pingpong = true;
	a.ref = &c.position[0];
	a.byReference();

	box.collide(c);
	c.collide(box);

	l.diffuse(1.0f, 1.0f, 1.0f, 1.0f).position(-10.0f, .0f, 0.0f);
	l.specular(1.0f, 1.0f, 1.0f, 1.0f);

	Window::create(argc, argv, 900, 600, "Test");
	Window::drawFunc(draw);
	Window::updateFunc(update);
	l.turnOn();

	Window::launch();



	return 0;
}