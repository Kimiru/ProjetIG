#pragma once

#include <vector>
#include <algorithm>
#include <map>
#include <functional>
#include <iostream>

namespace Scenery {

	/**
	 * Return a linear function depending on 3 parameters
	 */
	std::function<float(float, float, float)> linear(float a, float b);

	/**
	 * Return a function that takes time to get fast
	 */
	std::function<float(float, float, float)> easeIn(float a, float b);

	/**
	 * Return a function that takes time to get slow
	 */
	std::function<float(float, float, float)> easeOut(float a, float b);

	/**
	 * Return the bezier function
	 */
	std::function<float(float, float, float)> bezier(float a, float b);


	enum class UpdateMethode {
		REF, VALUE
	};

	class Animator {

	public:

		bool loop = false;
		bool pingpong = false;
		float* ref = NULL, time = 0, end = 1;
		float value = 0;
		float offset = 0;

		UpdateMethode methode = UpdateMethode::VALUE;

		std::map<int, float> timekey;
		std::map <int, std::function<float(float, float, float)>> funcs;

		/**
		 * Create an animator which can update a value or a reference
		 */
		Animator() {}
		Animator(float* ref) : ref(ref) {}

		/**
		 * Define the animation current and time by updating the value
		 */
		void setTime(float value);

		/**
		 * Add an animation key
		 */
		void addKey(int index, float time, std::function<float(float, float, float)> func);

		/**
		 * Make the animation progress of dt seconds
		 */
		void update(float dt);

		/**
		 * Reset the current time
		 */
		void reset();

		/**
		 * Return the index of the current key
		 */
		int getCurrentTimeKey();

		/**
		 * Return the next temporally after the current key
		 */
		float getNextTime(int currentKey);

		/**
		 * Return the current time
		 */
		float getCurrentTime();

		/**
		 * Define the animator in order to act by reference
		 */
		void byReference() { methode = UpdateMethode::REF; }
	};

	class AnimatorBundle {

	public:

		std::vector<Animator*> bundle;
		bool run = false;
		float end = 1, time = 0;
		bool loop = false;
		bool pingpong = false;

		/**
		 * Add an animator to the bundle
		 */
		void addAnimator(Animator* animator);

		/**
		 * Play the animation
		 */
		void play();
		
		/**
		 * Pause the animation
		 */
		void pause();
		
		/**
		 * Reset the animation
		 */
		void reset();
		
		/**
		 * Define the time of the bundle and all the animators
		 */
		void setTime(float value);
		
		/**
		 * Continue the animation of dt seconds
		 */
		void update(float dt);

	};

	class AnimationSelector {
	public:
		std::vector<AnimatorBundle*> bundles;
		int running = -1;

		/**
		 * Add the bundle to the selector, elements are inserted in the order
		 */
		void add(AnimatorBundle* bundle);
		
		/**
		 * Play the given animation, resets the last executing animation
		 * The argument needs to be a correct index
		 */
		void play(int animation);
		
		/**
		 * Pause the current animation
		 */
		void pause();
		
		/**
		 * Stop the current animation
		 */
		void stop();

		/**
		 * Update the executing animation of dt seconds
		 */
		void update(float dt);

	};

}