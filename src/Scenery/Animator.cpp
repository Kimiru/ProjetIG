#include <Scenery/Animator.hpp>

void Scenery::Animator::setTime(float newTime)
{
	time = newTime;
	if (loop && !pingpong && offset != 0) {
		time = fmod(time + offset, end);
	}

	int key = getCurrentTimeKey();
	float time = getCurrentTime();
	float left = timekey[key];
	float right = getNextTime(key);
	std::function<float(float, float, float)> func;

	if (funcs.find(key) == funcs.end()) {
		if (methode == UpdateMethode::VALUE)
			value = 0;
		else
			*ref = 0;
	}
	else {
		func = funcs[key];
		if (methode == UpdateMethode::VALUE)
			value = func(time, left, right);
		else
			*ref = func(time, left, right);
	}
}

void Scenery::Animator::addKey(int index, float time, std::function<float(float, float, float)> func)
{
	timekey[index] = time;
	funcs[index] = func;
}

void Scenery::Animator::update(float dt)
{
	float trueEnd = end * (pingpong ? 2 : 1);

	if (time < trueEnd || loop) {
		time += dt;
	}
	if (time > trueEnd && loop) {
		time -= trueEnd;
	}
	if (time > trueEnd && !loop) {
		time = trueEnd;
	}

	int key = getCurrentTimeKey();
	float time = getCurrentTime();
	float left = timekey[key];
	float right = getNextTime(key);

	std::function<float(float, float, float)> func;

	if (funcs.find(key) == funcs.end()) {
		if (methode == UpdateMethode::VALUE)
			value = 0;
		else
			*ref = 0;
	}
	else {
		func = funcs[key];
		if (methode == UpdateMethode::VALUE)
			value = func(time, left, right);
		else
			*ref = func(time, left, right);
	}
}

void Scenery::Animator::reset()
{
	setTime(0);
}

int Scenery::Animator::getCurrentTimeKey()
{
	int res = timekey.begin()->first;

	for (auto it : timekey)
		if (time >= it.second || time < timekey[res])
			res = it.first;

	return res;
}

float Scenery::Animator::getNextTime(int currentKey)
{
	float res = end;

	for (auto it : timekey)
		if (currentKey != it.first && timekey[currentKey] < it.second && it.second < res)
			res = it.second;

	return res;
}



float Scenery::Animator::getCurrentTime()
{
	if (pingpong)
		if (time < end)
			return time;
		else return 2 * end - time;
	else
		return time;
}

std::function<float(float, float, float)> Scenery::linear(float a, float b)
{
	return std::function<float(float, float, float)>([a, b](float time, float left, float right)
		{
			return (time - left) / (right - left) * (b - a) + a;
		});
}

std::function<float(float, float, float)> Scenery::easeIn(float a, float b)
{
	return std::function<float(float, float, float)>([a, b](float time, float left, float right)
		{
			float i = (time - left) / (right - left);
			if (time - left < (right - left) / 2)
				return 2 * i * i * (b - a) + a;
			else
				return i * (b - a) + a;
		});
}

std::function<float(float, float, float)> Scenery::easeOut(float a, float b)
{
	return std::function<float(float, float, float)>([a, b](float time, float left, float right)
		{
			float i = (time - left) / (right - left);
			if (time - left > (right - left) / 2)
				return (float)(2 * i * (1 - i) + 0.5) * (b - a) + a;
			else
				return i * (b - a) + a;
		});
}

std::function<float(float, float, float)> Scenery::bezier(float a, float b)
{
	return std::function<float(float, float, float)>([a, b](float time, float left, float right)
		{
			float i = (time - left) / (right - left);

			return (i * i * (3 - 2 * i)) * (b - a) + a;
		});
}

void Scenery::AnimatorBundle::addAnimator(Animator* animator)
{
	bundle.push_back(animator);
}

void Scenery::AnimatorBundle::play()
{
	run = true;
}

void Scenery::AnimatorBundle::pause()
{
	run = false;
}

void Scenery::AnimatorBundle::reset()
{
	for (Animator* a : bundle) a->reset();
}

void Scenery::AnimatorBundle::setTime(float value)
{
	for (Animator* a : bundle) a->setTime(value);
}

void Scenery::AnimatorBundle::update(float dt)
{
	if (!run) return;
	float trueEnd = end * (pingpong ? 2 : 1);

	if (time < trueEnd || loop) {
		time += dt;
	}
	if (time > trueEnd && loop) {
		time -= trueEnd;
	}
	if (time > trueEnd && !loop) {
		time = trueEnd;
	}

	setTime(time);

}
