#include <iostream>

#define _USE_MATH_DEFINES
#include <math.h>

#include <Matrix/Mat.hpp>
#include <Scenery/Window.hpp>
#include <Scenery/Material.hpp>
#include <Scenery/Light.hpp>
#include <Scenery/Euler.hpp>
#include <Scenery/Object.hpp>
#include <Scenery/SkinnedMesh.hpp>
#include <memory>
#include <Objects/Tree.hpp>
#include <Scenery/Animator.hpp>s

using namespace Matrix;
using namespace Scenery;

static float angle = 0;
static Light l;

static Objects::Tree t;

static Material smat;
static SkinnedMesh sm;

Animator a;

void update(float dt) {
	if (Window::getKey(0x1B)) {
		exit(0);
	}

	if (Window::getKey('a')) {
		angle += dt * 90;
	}

	a.update(dt);
	sm[1].rotation.z(a.value);

	//sm[0].rotation.y(angle * M_PI / 180);
	//sm[1].rotation.z(cos(angle * M_PI / 180) / 3);
	//sm[2].rotation.y(M_PI_2);
	//sm[2].rotation.z(-cos(angle * M_PI / 180) / 3);
	sm.build();


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

	x = 0;//cos(angle * M_PI / 180) * 3;
	z = 3;//sin(angle * M_PI / 180) * 3;

	gluLookAt(x, 2.0f, z, .0f, 1.0f, .0f, .0f, 1.0f, .0f);

	/*Euler e;
	e.z(angle * M_PI / 180);
	auto rm = e.getMatrix();


	glMultMatrixf((const float*)rm.data);*/
	//auto mat = Mat<4>::rotZ(angle * M_PI / 180);

	//glMultMatrixf((const float*)mat.data);


	//p1.get()->render();

	//t.translation[1] = -1;
	//t.render();

	sm.render();


	glPopMatrix();
	glFlush();
	glutSwapBuffers();
	int err = glGetError();
	if (err != GL_NO_ERROR)
		std::cout << "An error occured " << err << std::endl;

}

int main(int argc, char** argv) {


	Vertex sauce[] = {
		Vertex(-.5, 0, .5),
		Vertex(.5, 0, .5),
		Vertex(.5, 0, -.5),
		Vertex(-.5, 0, -.5),
		Vertex(-.5, 1, .5),
		Vertex(.5, 1, .5),
		Vertex(.5, 1, -.5),
		Vertex(-.5, 1, -.5),
		Vertex(-.5, 2, .5),
		Vertex(.5, 2, .5),
		Vertex(.5, 2, -.5),
		Vertex(-.5, 2, -.5)
	};

	int weight[] = { 0, 0, 0, 0, 1, 1, 1, 1, 2, 2, 2, 2 };

	int tmap[] = {
		2, 1, 0,
		3, 2, 0,

		0, 1, 5,
		0, 5, 4,
		1, 2, 6,
		1, 6, 5,
		2, 3, 7,
		2, 7, 6,
		3, 0, 4,
		3, 4, 7,

		4, 5, 9,
		4, 9, 8,
		5, 6, 10,
		5, 10, 9,
		6, 7, 11,
		6, 11, 10,
		7, 4, 8,
		7, 8, 11,

		8, 9, 10,
		8, 10, 11
	};

	sm.material = &smat;

	sm.init(12, sauce, weight, 20, tmap, 3);
	sm[0].add(&sm[1]);
	sm[1].add(&sm[2]);

	sm[1].translation[1] = 1;
	sm[2].translation[1] = 1;

	sm.compileSkeleton();
	//sm[1].translation[1] = 2;
	//sm[1].rotation.z(M_PI_4);
	//sm[2].translation[0] = .5;
	//sm[1].rotation.order = Order::YXZ;

	sm.build();
	//sm.displayBones = true;

	a.ref = &sm[1].rotation.data[2];
	a.addKey(0, 0, bezier(-M_PI_4, M_PI_4));
	a.loop = true;
	a.pingpong = true;
	a.end = 2;

	smat.diffuse(.5, .0, .0, 1.0).ambiant(.5, .0, .0, 1.0);

	l.diffuse(1.0f, 1.0f, 1.0f, 1.0f).position(1.0f, 4.0f, 1.0f);
	l.specular(1.0f, 1.0f, 1.0f, 1.0f);

	Window::create(argc, argv, 900, 600, "Test");
	Window::drawFunc(draw);
	Window::updateFunc(update);
	l.turnOn();
	Window::launch();

	return 0;
}