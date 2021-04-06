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
	rotation.built = false;
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
	int amountBones)
{
	init(verticesAmount, sourceVertices, weights, amountBones);
}

void Scenery::SkinnedMesh::addPolygon(int nbrSide, int nbrPoly, int map[]) {
	int tot = nbrSide * nbrPoly;
	int triPerPoly = nbrSide - 2;
	if (triPerPoly < 1) return;


	for (int i = 0; i < tot; i += nbrSide) {
		for (int j = 1; j < nbrSide - 1; j++) {
			Triangle t;
			t.localMaterial = localMaterial;
			t._1 = &altered[map[i]];
			t._2 = &altered[map[i + j]];
			t._3 = &altered[map[i + j + 1]];
			if (t.localMaterial != NULL)
				materedTriangles[t.localMaterial].push_back(t);
			else
				triangles.push_back(t);
		}
	}
}

void Scenery::SkinnedMesh::addPolygon(int nbrSide, int nbrPoly, std::initializer_list<int> map)
{
	int tot = nbrSide * nbrPoly;
	int triPerPoly = nbrSide - 2;
	if (triPerPoly < 1) return;

	auto it = map.begin();

	for (int i = 0; i < tot; i += nbrSide) {
		for (int j = 1; j < nbrSide - 1; j++) {
			Triangle t;
			t.localMaterial = localMaterial;
			t._1 = &altered[*it];
			t._2 = &altered[*(it + j)];
			t._3 = &altered[*(it + j + 1)];
			if (t.localMaterial != NULL)
				materedTriangles[t.localMaterial].push_back(t);
			else
				triangles.push_back(t);
		}
		it += nbrSide;
	}
}


void Scenery::SkinnedMesh::init(
	int verticesAmount, const Vertex sourceVertices[],
	int weights[],
	int amountBones)
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


	this->amountBones = amountBones;
	bones = new Bone[amountBones];

	for (int i = 0; i < amountBones; i++)
		this->skeleton.addBone(bones + i);

	inited = true;
}

void Scenery::SkinnedMesh::addQuadStrip(int nodes, int map[])
{
	if (nodes < 4 || nodes % 2 != 0) return;

	for (int i = 0; i < nodes - 2; i += 2)
		addPolygon(4, 1, { map[i], map[i + 2], map[i + 3], map[i + 1] });
}

void Scenery::SkinnedMesh::addQuadStrip(int nodes, std::initializer_list<int> map)
{
	if (nodes < 4 || nodes % 2 != 0) return;

	for (auto it = map.begin(); it + 2 != map.end(); it += 2) {
		addPolygon(4, 1, { *it, *(it + 2), *(it + 3), *(it + 1) });
	}
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
		for (Triangle t : triangles) {
			t.renormalize();
			t.draw();
		}
		Triangle::end();
		for (auto mater : materedTriangles) {
			Material::save();
			Material::base();
			mater.first->use();
			Triangle::start();
			for (Triangle t : mater.second) {
				t.renormalize();
				t.draw();
			}
			Triangle::end();
			Material::restore();
		}
	}

}
