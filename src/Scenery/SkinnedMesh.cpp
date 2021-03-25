#include <Scenery/SkinnedMesh.hpp>


void Scenery::Skeleton::addBone(Bone* bone)
{
	bones.push_back(bone);
}

Scenery::Skeleton& Scenery::Skeleton::operator<<(Bone* bone)
{
	addBone(bone);
	return *this;
}

Scenery::Bone* Scenery::Skeleton::operator[](int index)
{
	return bones[index];
}

void Scenery::Skeleton::build()
{

	bones[0]->build();

}

void Scenery::Bone::build()
{
	Object::build();

	if (previousBone != NULL)
		transformationMatrix = previousBone->transformationMatrix * transformationMatrix;

	for (Object* child : children) {
		Bone* bone = (Bone*)child;
		bone->previousBone = this;
		bone->build();
	}

}

void Scenery::SkinnedMesh::draw()
{

	skeleton.build();

}
