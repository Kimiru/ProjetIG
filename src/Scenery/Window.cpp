#include <Scenery/Window.hpp>
#include <iostream>

void(*Scenery::Window::update)(float);

bool Scenery::Window::isOpened;
std::set<unsigned char> Scenery::Window::keys;
std::set<unsigned char> Scenery::Window::keysSingle;
std::set<unsigned char> Scenery::Window::specials;
std::set<unsigned char> Scenery::Window::specialsSingle;
clock_t Scenery::Window::lastTime;

void resize(int x, int y) {
	glViewport(0, 0, x, y);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(70.0F, (float)x / y, 1.0, 40.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void Scenery::Window::create(int argc, char** argv, int width, int height, const char* title)
{
	if (Window::isOpened)
		return;
	Window::isOpened = true;

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
	glutInitWindowSize(width, height);
	glutInitWindowPosition(50, 50);
	glutCreateWindow(title);

	glEnable(GL_LIGHTING);
	glDepthFunc(GL_LESS);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);
	glEnable(GL_AUTO_NORMAL);

	glutReshapeFunc(resize);

	glutKeyboardFunc(keyDown);
	glutKeyboardUpFunc(keyUp);
	glutSpecialFunc(specialDown);
	glutSpecialUpFunc(specialUp);
	glutIdleFunc(idle);
	update = NULL;
	lastTime = clock();
}

void Scenery::Window::launch()
{
	glutMainLoop();
}

void Scenery::Window::keyDown(unsigned char key, int x, int y)
{
	storeKey(key);
}

void Scenery::Window::keyUp(unsigned char key, int x, int y)
{
	removeKey(key);
}

void Scenery::Window::storeSpecial(int key)
{
	specials.insert(key);
	specialsSingle.insert(key);
}

void Scenery::Window::removeSpecial(int key)
{
	specials.erase(key);
	specialsSingle.erase(key);
}

void Scenery::Window::specialDown(int key, int x, int y)
{
	storeSpecial(key);
}

void Scenery::Window::specialUp(int key, int x, int y)
{
	removeSpecial(key);
}

void Scenery::Window::idle()
{
	clock_t currentTime = clock();
	float dt = (currentTime - lastTime) / 1000.0f;
	lastTime = currentTime;

	if (update)
		update(dt);
}

void Scenery::Window::storeKey(unsigned char key)
{
	keys.insert(key);
	keysSingle.insert(key);
}

bool Scenery::Window::getKey(unsigned char key)
{
	return keys.find(key) != keys.end();
}

bool Scenery::Window::getKeySingle(unsigned char key)
{
	bool res = keysSingle.find(key) != keysSingle.end();
	if (res)
		keysSingle.erase(key);
	return res;
}

bool Scenery::Window::getSpecial(unsigned char key)
{
	return specials.find(key) != specials.end();
}

bool Scenery::Window::getSpecialSingle(unsigned char key)
{
	bool res = specialsSingle.find(key) != specialsSingle.end();
	if (res)
		specialsSingle.erase(key);
	return res;
}

void Scenery::Window::drawFunc(void(*draw)(void))
{
	glutDisplayFunc(draw);
}

void Scenery::Window::removeKey(unsigned char key)
{
	keys.erase(key);
	keysSingle.erase(key);
}

void Scenery::Window::updateFunc(void(*update)(float))
{
	Window::update = update;
}


