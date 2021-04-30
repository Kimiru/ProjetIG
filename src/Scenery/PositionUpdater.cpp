#include <Scenery/PositionUpdater.hpp>

/**
* Compute the relative movement function of
* the velocity, the acceleration, the drag and the deltaTime
* delta = vel*dt + acc*dt + min(vel*mindrag, mindrag)*dt
*/
void Scenery::PositionUpdater::computeDelta(float dt) {
	delta = vel * dt + acc * (1 / 2 * dt * dt);

	Matrix::Vec<3> absVel = vel.abs();
	Matrix::Vec<3> min = (absVel.multiply(drag) < minDrag) < absVel;
	Matrix::Vec<3> resDrag = min.multiply(-vel.sign()) * dt;

	vel += acc * dt + resDrag;
}

/**
 * Apply the delta to the position
 * Saving the last position
 */
void Scenery::PositionUpdater::applyDelta() {
	// save the last position
	lastPos = *pos;
	*pos += delta;
}

/**
 * Reverse position to the last position
 */
void Scenery::PositionUpdater::reverseDelta() {
	*pos = lastPos;
	*pos -= delta;
	delta += delta;
}

/**
 * Reapply the x member of the delta
 */
void Scenery::PositionUpdater::redoX() {
	pos->data[0] += delta.data[0];
}

/**
 * Reapply the y member of the delta
 */

void Scenery::PositionUpdater::redoY() {
	pos->data[1] += delta.data[1];
}

/**
 * Reapply the z member of the delta
 */
void Scenery::PositionUpdater::redoZ() {
	pos->data[2] += delta.data[2];
}

/**
 * Update the position
 * Calculate the delta and apply it
 */
void Scenery::PositionUpdater::update(float dt) {
	computeDelta(dt);
	applyDelta();
}