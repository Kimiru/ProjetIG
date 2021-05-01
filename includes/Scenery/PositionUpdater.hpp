#pragma once

#include <Matrix/Vec.hpp>
#include <Scenery/Hitbox.hpp>

namespace Scenery {

	class PositionUpdater {

	public:

		Matrix::Vec<3> vel, acc, drag, minDrag, delta, lastPos;
		Matrix::Vec<3>* pos;

		PositionUpdater() { pos = NULL; }
		PositionUpdater(Matrix::Vec<3>* pos) : pos(pos) {}

		/**
		 * Compute the relative movement function of
		 * the velocity, the acceleration, the drag and the deltaTime
		 * deleta = vel*dt + acc*dt + min(vel*drag, mindrag)*dt
		 */
		void computeDelta(float dt);

		/**
		 * Apply the delta to the pos
		 * Saving the last pos
		 */
		void applyDelta();
		/**
		 * Reverse pos to the last pos
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
		 * Update the pos
		 * Calculate the delta and apply it
		 */
		void update(float dt);

		/**
		 * Update the pos
		 * Calculate the delta and apply it
		 * Check for collisions between
		 */
		void update(float dt, Hitbox::Box hitbox, Hitbox::HitboxBundle bundle, Matrix::Vec<3> dir) {
			update(dt);
			hitbox.setPosition(*pos);
			collide(hitbox, bundle, dir);

		}
		void update(float dt, Hitbox::Cylinder hitbox, Hitbox::HitboxBundle bundle, Matrix::Vec<3> dir) {
			update(dt);
			hitbox.setPosition(*pos);
			collide(hitbox, bundle, dir);
		}

		void collide(Hitbox::Box hitbox, Hitbox::HitboxBundle bundle, Matrix::Vec<3> dir) {
			std::function<void(Hitbox::Box, Hitbox::Box)> func = [this, dir](Hitbox::Box b1, Hitbox::Box b2) {
				this->reverseDelta();

				// Gestion collision x
				this->redoX();
				b1.setPosition(*this->pos);
				if (dir.data[0] && b1.collide(b2)) {
					// Collision d'un bloc venant de la gauche vers la droite
					if (delta.data[0] > 0) {
						float l = b2.position.data[0] - b2.size.data[0] / 2;
						float r = b1.position.data[0] + b1.size.data[0] / 2;
						float dist = r - l;
						this->pos->data[0] -= dist;
						this->delta.data[0] -= dist;
					}
					// Collision d'un bloc venant de la droite vers la gauche
					else if (delta.data[0] < 0) {
						float l = b1.position.data[0] - b1.size.data[0] / 2;
						float r = b2.position.data[0] + b2.size.data[0] / 2;
						float dist = l - r;
						this->pos->data[0] -= dist;
						this->delta.data[0] -= dist;
					}
					this->vel.data[0] = 0;
				}

				// Gestion collision y
				this->redoY();
				b1.setPosition(*this->pos);
				if (dir.data[1] && b1.collide(b2)) {
					// Collision d'un bloc venant de la gauche vers la droite
					if (delta.data[1] > 0) {
						float l = b2.position.data[1] - b2.size.data[1] / 2;
						float r = b1.position.data[1] + b1.size.data[1] / 2;
						float dist = r - l;
						this->pos->data[1] -= dist;
						this->delta.data[1] -= dist;
					}
					// Collision d'un bloc venant de la droite vers la gauche
					else if (delta.data[1] < 0) {
						float l = b1.position.data[1] - b1.size.data[1] / 2;
						float r = b2.position.data[1] + b2.size.data[1] / 2;
						float dist = l - r;
						this->pos->data[1] -= dist;
						this->delta.data[1] -= dist;
					}
					this->vel.data[1] = 0;
				}

				// Gestion collision z
				this->redoZ();
				b1.setPosition(*this->pos);
				if (dir.data[2] && b1.collide(b2)) {
					// Collision d'un bloc venant de la gauche vers la droite
					if (delta.data[2] > 0) {
						float l = b2.position.data[2] - b2.size.data[2] / 2;
						float r = b1.position.data[2] + b1.size.data[2] / 2;
						float dist = r - l;
						this->pos->data[2] -= dist;
						this->delta.data[2] -= dist;
					}
					// Collision d'un bloc venant de la droite vers la gauche
					else if (delta.data[2] < 0) {
						float l = b1.position.data[2] - b1.size.data[2] / 2;
						float r = b2.position.data[2] + b2.size.data[2] / 2;
						float dist = l - r;
						this->pos->data[2] -= dist;
						this->delta.data[2] -= dist;
					}
					this->vel.data[2] = 0;
				}
				b1.setPosition(*this->pos);
			};
			bundle.collide(hitbox, func);
		}

		void collide(Hitbox::Cylinder hitbox, Hitbox::HitboxBundle bundle, Matrix::Vec<3> dir) {
			std::function<void(Hitbox::Cylinder, Hitbox::Box)> funcBox = [this, dir](Hitbox::Cylinder c, Hitbox::Box b) {
				auto rd2 = this->delta * 2;

				this->reverseDelta();
				c.setPosition(*this->pos);
				// Gestion collision x

				this->redoX();
				c.setPosition(*this->pos);
				if (dir.data[0] && c.collide(b)) {
					// Collision d'un bloc venant de la gauche vers la droite
					if (delta.data[0] > 0) {
						float l = b.position.data[0] - b.size.data[0] / 2;
						float r = c.position.data[0] + c.radius;
						float dist = l - r;
						this->pos->data[0] += dist;
						this->delta.data[0] += dist;
						this->vel.data[0] = 0;
					}
					// Collision d'un bloc venant de la droite vers la gauche
					else if (delta.data[0] < 0) {
						float l = c.position.data[0] - c.radius;
						float r = b.position.data[0] + b.size.data[0] / 2;
						float dist = l - r;
						this->pos->data[0] -= dist;
						this->delta.data[0] -= dist;
						this->vel.data[0] = 0;
					}
				}


				// Gestion collision y
				this->redoY();
				c.setPosition(*this->pos);
				if (dir.data[1] && c.collide(b)) {
					// Collision d'un bloc venant du bas vers le haut
					if (delta.data[1] > 0) {
						float l = b.position.data[1] - b.size.data[1] / 2;
						float r = c.position.data[1] + c.height / 2;
						float dist = l - r;
						this->pos->data[1] += dist;
						this->delta.data[1] += dist;
						this->vel.data[1] = 0;
					}
					// Collision d'un bloc venant du haut vers le bas
					else if (delta.data[1] < 0) {
						float l = c.position.data[1] - c.height / 2;
						float r = b.position.data[1] + b.size.data[1] / 2;
						float dist = l - r;
						this->pos->data[1] -= dist;
						this->delta.data[1] -= dist;
						this->vel.data[1] = 0;
					}
				}

				// Gestion collision z
				this->redoZ();
				c.setPosition(*this->pos);
				if (dir.data[2] && c.collide(b)) {
					// Collision d'un bloc venant de la gauche vers la droite
					if (delta.data[2] > 0) {
						float l = b.position.data[2] - b.size.data[2] / 2;
						float r = c.position.data[2] + c.radius;
						float dist = l - r;
						this->pos->data[2] += dist;
						this->delta.data[2] += dist;
						this->vel.data[2] = 0;
					}
					// Collision d'un bloc venant de la droite vers la gauche
					else if (delta.data[2] < 0) {
						float l = c.position.data[2] - c.radius;
						float r = b.position.data[2] + b.size.data[2] / 2;
						float dist = l - r;
						this->pos->data[2] -= dist;
						this->delta.data[2] -= dist;
						this->vel.data[2] = 0;
					}
				}
				c.setPosition(*this->pos);
			};

			std::function<void(Hitbox::Cylinder, Hitbox::Cylinder)> funcCylinder = [this, dir](Hitbox::Cylinder c1, Hitbox::Cylinder c2) {
				this->reverseDelta();

				// Gestion collision y
				this->redoY();
				c1.setPosition(*this->pos);
				if (dir.data[1] && c1.collide(c2)) {
					// Collision d'un bloc venant de la gauche vers la droite
					if (delta.data[1] > 0) {
						float l = c2.position.data[1] - c2.height / 2;
						float r = c1.position.data[1] + c1.height / 2;
						float dist = l - r;
						this->pos->data[1] += dist;
						this->delta.data[1] += dist;
					}
					// Collision d'un bloc venant de la droite vers la gauche
					else if (delta.data[1] < 0) {
						float l = c1.position.data[1] - c1.height / 2;
						float r = c2.position.data[1] + c2.height / 2;
						float dist = l - r;
						this->pos->data[1] -= dist;
						this->delta.data[1] -= dist;
					}
					this->vel.data[2] = 0;
				}

				// Gestion collision x & z
				this->redoX();
				this->redoZ();
				c1.setPosition(*this->pos);
				if ((dir.data[0] || dir.data[2]) && c1.collide(c2)) {
					Matrix::Vec<3> dir = c2.position - c1.position;
					dir.data[1] = 0;
					dir.normalize();
					Matrix::Vec<3> res1 = c1.position + dir;
					Matrix::Vec<3> res2 = c2.position - dir;
					res1.data[1] = 0;
					res2.data[1] = 0;
					Matrix::Vec<3> res3 = res2 - res1;
					*this->pos += res3;
					this->delta += res3;
				}
				c1.setPosition(*this->pos);

			};
			bundle.collide(hitbox, funcBox, funcCylinder);
		}
	};
}