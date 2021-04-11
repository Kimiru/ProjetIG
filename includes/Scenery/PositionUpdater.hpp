#pragma once

#include <Matrix/Vec.hpp>
#include <Scenery/Hitbox.hpp>

namespace Scenery {

	class PositionUpdater {

	public:

		Matrix::Vec<3> vel, acc, drag, minDrag, delta, lastPos;
		Matrix::Vec<4>* pos;

		PositionUpdater() { pos = NULL; }
		PositionUpdater(Matrix::Vec<4>* pos) : pos(pos) {}

		/**
		 * Compute the relative movement function of
		 * the velocity, the acceleration, the drag and the deltaTime
		 * deleta = vel*dt + acc*dt + min(vel*mindrag, mindrag)*dt
		 */
		void computeDelta(float dt);

		/**
		 * Apply the delta to the position
		 * Saving the last position
		 */
		void applyDelta();
		/**
		 * Reverse position to the last position
		 */
		void reverseDelta();
		/**
		 * Reapply the x member of the delta
		 */
		void redoX();
		/**
		 * Reapply the y member of the delta
		 */
		void redoY();
		/**
		 * Reapply the z member of the delta
		 */
		void redoZ();

		/**
		 * Update the position
		 * Calculate the delta and apply it
		 */
		void update(float dt);

		/**
		 * Update the position
		 * Calculate the delta and apply it
		 * Check for collisions between
		 */
		template<typename T>
		void update(float dt, T hitbox, Hitbox::HitboxBundle bundle);
	};
