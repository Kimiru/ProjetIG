#include <iostream>

#define _USE_MATH_DEFINES
#include <math.h>

#include <Matrix/Mat.hpp>
#include <Scenery/Window.hpp>
#include <Scenery/Material.hpp>
#include <Scenery/Light.hpp>
#include <Scenery/Euler.hpp>
#include <Scenery/Object.hpp>
#include <memory>
#include <Objects/Tree.hpp>

using namespace Matrix;
using namespace Scenery;

static float angle = 0;
static Light l;

static std::unique_ptr<Object> p1(new Object());
static Object* o2 = new Object(), o3;

static Objects::Tree t;

void update(float dt) {
	if (Window::getKey(0x1B)) {
		delete o2;
		exit(0);
	}

	if (Window::getKey('a')) {
		angle += dt * 360;
	}

	p1.get()->rotation.order = Order::YXZ;
	p1.get()->rotation.y(angle);
	p1.get()->build();

	l.position(cos(angle * M_2_PI / 180) * 4, 1.0f, sin(angle * M_2_PI / 180) * 4);

	glutPostRedisplay();
}

void draw() {
	glClearColor(0.5F, 0.5F, 0.5F, 0.5F);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPushMatrix();

	l.use();

	float rada = angle * M_PI / 180;
	float x = cos(rada) * 5.0;
	float z = sin(rada) * 5.0;

	x = 0.0;
	z = 5.0;

	gluLookAt(x, 3.0f, z, .0f, 0.0f, .0f, .0f, 1.0f, .0f);

	/*Euler e;
	e.z(angle * M_PI / 180);
	auto rm = e.getMatrix();


	glMultMatrixf((const float*)rm.data);*/
	//auto mat = Mat<4>::rotZ(angle * M_PI / 180);

	//glMultMatrixf((const float*)mat.data);


	//p1.get()->render();

	//t.translation[1] = -1;
	t.render();


	glPopMatrix();
	glFlush();
	glutSwapBuffers();
	int err = glGetError();
	if (err != GL_NO_ERROR)
		std::cout << "An error occured " << err << std::endl;

}

int main(int argc, char** argv) {

	o2->translation[1] = 1.5;
	//o2->build();
	o3.translation[0] = 1.5;
	//o3.build();
	o2->add(&o3);
	p1.get()->add(o2);

	l.diffuse(1.0f, 1.0f, 1.0f, 1.0f).position(1.0f, 4.0f, 1.0f);
	l.specular(1.0f, 1.0f, 1.0f, 1.0f);

	Window::create(argc, argv, 900, 600, "Test");
	Window::drawFunc(draw);
	Window::updateFunc(update);
	l.turnOn();
	Window::launch();

	return 0;
}