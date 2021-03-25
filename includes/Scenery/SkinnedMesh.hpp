#pragma once

#include <Scenery/Object.hpp>
#include <Scenery/Triangle.hpp>
#include <vector>


namespace Scenery {

	class Bone : public Object {

	public:

		Bone* previousBone = NULL;

		void build();

	};

	class Skeleton : public Object {

	public:

		std::vector<Bone*> bones;

		void addBone(Bone* bone);

		Skeleton& operator<<(Bone* bone);
		Bone* operator[](int index);

		void build();

	};

	class SkinnedMesh : public Object {

	public:

		Skeleton skeleton;

		int verticesAmount;
		Vertex** sourceVertices, ** altered;
		int triangleAmount, ** trianglesMap;
		Triangle* triangles;

		void draw();

	};

}