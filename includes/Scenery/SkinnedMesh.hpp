#pragma once

#include <Scenery/Object.hpp>
#include <Scenery/Triangle.hpp>
#include <Scenery/Vertex.hpp>
#include <vector>
#include <map>
#include <array>
#include <memory>

namespace Scenery {

	class Bone : public Object {

	public:

		Bone* previousBone = NULL;

		float boneScale[3] = { .1, .5, .1 };

		Bone() {}

		/**
		 * Recompute the bone position relative to the skeleton 
		 */
		void build();

		void draw() {
			glPushMatrix();
			glTranslatef(0, boneScale[1] / 2, 0);
			glScalef(boneScale[0], boneScale[1], boneScale[2]);
			glutSolidCube(1);
			glPopMatrix();
		}

		void setScale(std::initializer_list<float> list) {
			int index = 0;
			auto it = list.begin();
			while (it != list.end() && index < 3)
				boneScale[index++] = *it++;
		}

		/**
		 * Reset the rotation of the bone
		 */
		void reset();

	};

	class Skeleton : public Object {

	public:

		std::vector<Bone*> bones;
		std::vector<Mat<4>> inverts;

		Skeleton() {}

		void addBone(Bone* bone);

		Skeleton& operator<<(Bone* bone);
		Bone* operator[](int index);

		/**
		 * Build all bones
		 */
		void build();

		/**
		 * Save all inverted matrix of the skeleton
		 */
		void save();

		/**
		 * Reset all the bones
		 */
		void reset();
	};

	class SkinnedMesh : public Object {

	public:

		Skeleton skeleton;

		bool inited = false, displayBones = false;

		int verticesAmount = 0, triangleAmount = 0, amountBones = 0;

		int* weights = NULL;
		Vertex* sourceVertices = NULL, * altered = NULL;
		std::vector<Triangle> triangles;
		std::map<Material*, std::vector<Triangle>> materedTriangles;
		Bone* bones = NULL;

		Material* localMaterial = NULL; // A local material for to be added triangle 

		SkinnedMesh() {}
		SkinnedMesh(
			int verticesAmount, const Vertex sourceVertices[],
			int weights[],
			int amountBones);

		~SkinnedMesh() {
			if (inited) {
				delete[] weights;
				delete[] sourceVertices;
				delete[] altered;
				delete[] bones;
			}
		}

		Bone& operator[](int index) {
			return bones[index];
		}

		/**
		 * Add polygons of given arity, map contains the indexes of the vertex.
		 */
		void addPolygon(int nbrSide, int nbrPoly, int map[]);
		void addPolygon(int nbrSide, int nbrPoly, std::initializer_list<int> map);

		/**
		 * Add quadStrip with given nodes, map contains the indexes of the vertex.
		 */
		void addQuadStrip(int nodes, int map[]);
		void addQuadStrip(int nodes, std::initializer_list<int> map);

		/**
		 * Initialize the mesh with vertices a certain amount of bones and a bone attributed to each vertice
		 */
		void init(int verticesAmount, const Vertex sourceVertices[],
			int weights[],
			int amountBones);

		/**
		 * Build and save the skeleton
		 */
		void compileSkeleton();

		/**
		 * Update the vertices position
		 */
		void build();

		/**
		 * Render all the meshed triangles
		 */
		void draw();

	};

}