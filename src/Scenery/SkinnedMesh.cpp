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

void Scenery::Skeleton::save()
{
	for (unsigned i = 0; i < bones.size(); i++)
		inverts.push_back(!bones[i]->transformationMatrix);
}

void Scenery::Bone::build()
{
	Object::build();

	if (previousBone != NULL)
		transformationMatrix = transformationMatrix * previousBone->transformationMatrix;

	for (Object* child : children) {
		Bone* bone = (Bone*)child;
		bone->previousBone = this;
		bone->build();
	}

}

Scenery::SkinnedMesh::SkinnedMesh(
	int verticesAmount, const Vertex sourceVertices[], int weights[],
	int triangleAmount, int trianglesMap[],
	int amountBones)
{
	init(verticesAmount, sourceVertices, weights, triangleAmount, trianglesMap, amountBones);
}

void Scenery::SkinnedMesh::init(int verticesAmount, const Vertex sourceVertices[], int weights[], int triangleAmount, int trianglesMap[], int amountBones)
{

	this->verticesAmount = verticesAmount;
	this->triangleAmount = triangleAmount;

	this->sourceVertices = new Vertex[verticesAmount];
	for (int i = 0; i < verticesAmount; i++)
		this->sourceVertices[i] = sourceVertices[i];

	altered = new Vertex[verticesAmount];

	this->weights = new int[verticesAmount];
	for (int i = 0; i < verticesAmount; i++)
		this->weights[i] = weights[i];

	this->trianglesMap = new int[triangleAmount * 3];
	for (int i = 0; i < triangleAmount * 3; i++)
		this->trianglesMap[i] = trianglesMap[i];

	triangles = new Triangle[triangleAmount];

	this->amountBones = amountBones;
	bones = new Bone[amountBones];

	for (int i = 0; i < amountBones; i++)
		this->skeleton.addBone(bones + i);

	for (int index = 0; index < triangleAmount; index++) {
		int trueIndex = index * 3;
		triangles[index]._1 = &this->altered[this->trianglesMap[trueIndex]];
		triangles[index]._2 = &this->altered[this->trianglesMap[trueIndex + 1]];
		triangles[index]._3 = &this->altered[this->trianglesMap[trueIndex + 2]];
	}

	inited = true;
}

void Scenery::SkinnedMesh::compileSkeleton()
{
	skeleton.build();
	skeleton.save();
}

void Scenery::SkinnedMesh::build()
{
	Object::build();

	skeleton.build();

	for (int i = 0; i < verticesAmount; i++) {
		int weight = weights[i];
		altered[i].position = skeleton.inverts[weight] * bones[weight].transformationMatrix * ((Vec<4>)sourceVertices[i].position << 1);
	}

}

void Scenery::SkinnedMesh::draw()
{
	if (!inited) return;

	if (displayBones)
		for (int i = 0; i < amountBones; i++) {
			glPushMatrix();
			glMultMatrixf((float*)bones[i].transformationMatrix.data);
			bones[i].draw();
			glPopMatrix();
		}
	else {
		Triangle::start();
		for (int i = 0; i < triangleAmount; i++) {
			triangles[i].renormalize();
			triangles[i].draw();
		}
		Triangle::end();
	}

}
