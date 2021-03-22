#pragma once

#include <stdlib.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include <set>
#include <time.h>

namespace Scenery {

	class Window {
	private:
		static void storeKey(unsigned char key);
		static void removeKey(unsigned char key);
		static void keyDown(unsigned char key, int x, int y);
		static void keyUp(unsigned char key, int x, int y);
		static void storeSpecial(int key);
		static void removeSpecial(int key);
		static void specialDown(int key, int x, int y);
		static void specialUp(int key, int x, int y);

		static void(*update)(float);
		static void idle();

	public:

		static bool isOpened;
		static std::set<unsigned char> keys;
		static std::set<unsigned char> keysSingle;
		static std::set<unsigned char> specials;
		static std::set<unsigned char> specialsSingle;
		static clock_t lastTime;

		static void create(int argc, char** argv, int width, int height, const char* title);
		static void launch();
		static bool getKey(unsigned char key);
		static bool getKeySingle(unsigned char key);
		static bool getSpecial(unsigned char key);
		static bool getSpecialSingle(unsigned char key);
		static void drawFunc(void(*draw)(void));
		static void updateFunc(void(*update)(float));
	};

}