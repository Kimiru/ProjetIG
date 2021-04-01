#pragma once

#include <Scenery/Object.hpp>
#include <Scenery/Triangle.hpp>
#include <Scenery/Vertex.hpp>
#include <vector>
#include <array>
#include <memory>

namespace Scenery {

	class Bone : public Object {

	public:

		Bone* previousBone = NULL;

		Bone() { buildOrder = BuildOrder::Matrix; }

		void build();

		void draw() {
			glPushMatrix();
			glTranslatef(0, .25, 0);
			glScalef(.1, .5, .1);
			glutSolidCube(1);
			glPopMatrix();
		}

	};

	class Skeleton : public Object {

	public:

		std::vector<Bone*> bones;
		std::vector<Mat<4>> inverts;

		Skeleton() {}

		void addBone(Bone* bone);

		Skeleton& operator<<(Bone* bone);
		Bone* operator[](int index);

		void build();
		void save();
	};

	class SkinnedMesh : public Object {

	public:

		Skeleton skeleton;

		bool inited = false, displayBones = false;

		int verticesAmount = 0, triangleAmount = 0, amountBones = 0;

		int* weights = NULL, * trianglesMap = NULL;
		Vertex* sourceVertices = NULL, * altered = NULL;
		Triangle* triangles = NULL;
		Bone* bones = NULL;

		SkinnedMesh() {}
		SkinnedMesh(
			int verticesAmount, const Vertex sourceVertices[], int weights[],
			int triangleAmount, int trianglesMap[],
			int amountBones);

		~SkinnedMesh() {
			if (inited) {
				delete[] trianglesMap;
				delete[] weights;
				delete[] sourceVertices;
				delete[] altered;
				delete[] triangles;
				delete[] bones;
			}
		}

		Bone& operator[](int index) {
			return bones[index];
		}

		void init(int verticesAmount, const Vertex sourceVertices[], int weights[],
			int triangleAmount, int trianglesMap[],
			int amountBones);

		void compileSkeleton();
		void build();
		void draw();

	};

}