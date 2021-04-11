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
		 * deleta = vel*dt + acc*dt + min(vel*drag, mindrag)*dt
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
		void update(float dt, T hitbox, Hitbox::HitboxBundle bundle) {
			update(dt);
			if constexpr (T == Hitbox::Box) {
				std::function<void(Box, Box)> func = [this, dt](Hitbox::Box b1, Hitbox::Box b2) {
					this->reverseDelta();

					// Gestion collision x
					this->redoX();
					b1.position = *this->pos;
					if (b1.collide(b2)) {
						// Collision d'un bloc venant de la gauche vers la droite
						if (delta.data[0] > 0) {
							float l = b2.position.data[0] - b2.size.data[0]/2;
							float r = b1.position.data[0] + b1.size.data[0]/2;
							float dist = r - l;
							this->position->data[0] -= dist;
							this->delta.data[0] -= dist;
						}
						// Collision d'un bloc venant de la droite vers la gauche
						if (delta.data[0] < 0) {
							float l = b1.position.data[0] - b1.size.data[0] / 2;
							float r = b2.position.data[0] + b2.size.data[0] / 2;
							float dist = l - r;
							this->position->data[0] -= dist;
							this->delta.data[0] -= dist;
						}
					}


					// Gestion collision y
					this->redoY();
					b1.position = *this->pos;
					if (b1.collide(b2)) {
						// Collision d'un bloc venant de la gauche vers la droite
						if (delta.data[1] > 0) {
							float l = b2.position.data[1] - b2.size.data[1] / 2;
							float r = b1.position.data[1] + b1.size.data[1] / 2;
							float dist = r - l;
							this->position->data[1] -= dist;
							this->delta.data[1] -= dist;
						}
						// Collision d'un bloc venant de la droite vers la gauche
						if (delta.data[1] < 0) {
							float l = b1.position.data[1] - b1.size.data[1] / 2;
							float r = b2.position.data[1] + b2.size.data[1] / 2;
							float dist = l - r;
							this->position->data[1] -= dist;
							this->delta.data[1] -= dist;
						}
					}

					// Gestion collision z
					this->redoZ();
					b1.position = *this->pos;
					if (b1.collide(b2)) {
						// Collision d'un bloc venant de la gauche vers la droite
						if (delta.data[2] > 0) {
							float l = b2.position.data[2] - b2.size.data[2] / 2;
							float r = b1.position.data[2] + b1.size.data[2] / 2;
							float dist = r - l;
							this->position->data[2] -= dist;
							this->delta.data[2] -= dist;
						}
						// Collision d'un bloc venant de la droite vers la gauche
						if (delta.data[2] < 0) {
							float l = b1.position.data[2] - b1.size.data[2] / 2;
							float r = b2.position.data[2] + b2.size.data[2] / 2;
							float dist = l - r;
							this->position->data[2] -= dist;
							this->delta.data[2] -= dist;
						}
					}
				};
				bundle.collide(hitbox, func);
			}

			// Gestion Cylindre

			if constexpr (T == Hitbox::Cylinder) {
				std::function<void(Cylinder, Box)> funcBox = [this, dt](Hitbox::Cylinder c, Hitbox::Box b) {
					this->reverseDelta();

					// Gestion collision x
					this->redoX();
					c.position = *this->pos;
					if (c.collide(b)) {
						// Collision d'un bloc venant de la gauche vers la droite
						if (delta.data[0] > 0) {
							float l = b.position.data[0] - b.size.data[0] / 2;
							float r = c.position.data[0] + radius;
							float dist = r - l;
							this->position->data[0] -= dist;
							this->delta.data[0] -= dist;
						}
						// Collision d'un bloc venant de la droite vers la gauche
						if (delta.data[0] < 0) {
							float l = c.position.data[0] - radius;
							float r = b.position.data[0] + b.size.data[0] / 2;
							float dist = l - r;
							this->position->data[0] -= dist;
							this->delta.data[0] -= dist;
						}
					}


					// Gestion collision y
					this->redoY();
					c.position = *this->pos;
					if (c.collide(b)) {
						// Collision d'un bloc venant de la gauche vers la droite
						if (delta.data[1] > 0) {
							float l = b.position.data[1] - b.size.data[1] / 2;
							float r = c.position.data[1] + height/2;
							float dist = r - l;
							this->position->data[1] -= dist;
							this->delta.data[1] -= dist;
						}
						// Collision d'un bloc venant de la droite vers la gauche
						if (delta.data[1] < 0) {
							float l = c.position.data[1] - height/2;
							float r = b.position.data[1] + b.size.data[1] / 2;
							float dist = l - r;
							this->position->data[1] -= dist;
							this->delta.data[1] -= dist;
						}
					}

					// Gestion collision z
					this->redoZ();
					c.position = *this->pos;
					if (c.collide(b)) {
						// Collision d'un bloc venant de la gauche vers la droite
						if (delta.data[2] > 0) {
							float l = b.position.data[2] - b.size.data[2] / 2;
							float r = c.position.data[2] + c.size.data[2] / 2;
							float dist = r - l;
							this->position->data[2] -= dist;
							this->delta.data[2] -= dist;
						}
						// Collision d'un bloc venant de la droite vers la gauche
						if (delta.data[2] < 0) {
							float l = c.position.data[2] - c.size.data[2] / 2;
							float r = b.position.data[2] + b.size.data[2] / 2;
							float dist = l - r;
							this->position->data[2] -= dist;
							this->delta.data[2] -= dist;
						}
					}
				};

				std::function<void(Cylinder, Cylinder)> funcCylinder = [this, dt](Hitbox::Cylinder c1, Hitbox::Cylinder c2) {
					this->reverseDelta();

					// Gestion collision y
					this->redoY();
					c1.position = *this->pos;
					if (c1.collide(c2)) {
						// Collision d'un bloc venant de la gauche vers la droite
						if (delta.data[1] > 0) {
							float l = c2.position.data[1] - c2.size.data[1] / 2;
							float r = c1.position.data[1] + height / 2;
							float dist = r - l;
							this->position->data[1] -= dist;
							this->delta.data[1] -= dist;
						}
						// Collision d'un bloc venant de la droite vers la gauche
						if (delta.data[1] < 0) {
							float l = c1.position.data[1] - height / 2;
							float r = c2.position.data[1] + c2.size.data[1] / 2;
							float dist = l - r;
							this->position->data[1] -= dist;
							this->delta.data[1] -= dist;
						}
					}

					// Gestion collision x & z
					this->redoX();
					this->redoZ();
					if (c1.collide(c2)) {
						Matrix::Vec<3> dir = c2.position - c1.position;
						dir.data[1] = 0;
						dir.normalize();
						Vec<3> res1 = c1.position + dir;
						Vec<3> res2 = c2.position - dir;
						res1.data[1] = 0;
						res2.data[1] = 0;
						Vec<3> res3 = res2 - res1;
						this->position += res3;
						this->delta += res3;
					}
				}
				bundle.collide(hitbox, funcBox, funcCylinder);
			}
		}
	};
}