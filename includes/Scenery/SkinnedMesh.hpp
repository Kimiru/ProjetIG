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

		void addPolygon(int nbrSide, int nbrPoly, int map[]);
		void addPolygon(int nbrSide, int nbrPoly, std::initializer_list<int> map);

		void addQuadStrip(int nodes, int map[]);
		void addQuadStrip(int nodes, std::initializer_list<int> map);

		void init(int verticesAmount, const Vertex sourceVertices[],
			int weights[],
			int amountBones);

		void compileSkeleton();
		void build();
		void draw();

	};

}