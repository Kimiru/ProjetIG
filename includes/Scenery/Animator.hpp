#pragma once

#include <vector>
#include <algorithm>
#include <map>
#include <functional>
#include <iostream>

namespace Scenery {

	std::function<float(float, float, float)> linear(float a, float b);

	std::function<float(float, float, float)> easeIn(float a, float b);

	std::function<float(float, float, float)> easeOut(float a, float b);

	std::function<float(float, float, float)> bezier(float a, float b);


	enum class UpdateMethode {
		REF, VALUE
	};

	class Animator {

	public:

		bool loop = false;
		bool pingpong = false;
		float* ref = NULL, time = 0, end = 0;
		float value = 0;

		UpdateMethode methode = UpdateMethode::VALUE;

		std::map<int, float> timekey;
		std::map <int, std::function<float(float, float, float)>> funcs;

		Animator() {}
		Animator(float* ref) : ref(ref) {}

		void addKey(int index, float time, std::function<float(float, float, float)> func);
		void update(float dt);
		int getCurrentTimeKey();
		float getNextTime(int currentKey);
		float getCurrentTime();
	};

}