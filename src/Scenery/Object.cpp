#include <Scenery/Object.hpp>


Scenery::Object::Object() {
	scale.data[0] = 1;
	scale.data[1] = 1;
	scale.data[2] = 1;
}

void Scenery::Object::add(Object* child)
{
	children.push_back(child);
}

void Scenery::Object::remove(int index) {
	children.erase(children.begin() + index);
}

void Scenery::Object::remove(std::string name)
{
	int size = children.size();
	for (int i = 0; i < size; i++) {
		if (children[i]->name == name) {
			remove(i--);
			size--;
		}
	}
}

void Scenery::Object::build()
{
	transformationMatrix = Mat<4>::id();

	if (buildOrder == BuildOrder::GL) {
		if (!translation.all(0)) {
			Mat<4> translationMatrix = Mat<4>::translate(translation.data);
			transformationMatrix = transformationMatrix * translationMatrix;
		}
		if (rotation.isRotation()) {
			Mat<4> rotationMatrix = rotation.getMatrix();
			transformationMatrix = transformationMatrix * rotationMatrix;
		}
		if (!translation.all(1)) {
			Mat<4> scaleMatrix = Mat<4>::scale(scale.data);
			transformationMatrix = transformationMatrix * scaleMatrix;
		}
	}
	else {
		if (!translation.all(1)) {
			Mat<4> scaleMatrix = Mat<4>::scale(scale.data);
			transformationMatrix = transformationMatrix * scaleMatrix;
		}
		if (rotation.isRotation()) {
			Mat<4> rotationMatrix = rotation.getMatrix();
			transformationMatrix = transformationMatrix * rotationMatrix;
		}
		if (!translation.all(0)) {
			Mat<4> translationMatrix = Mat<4>::translate(translation.data);
			transformationMatrix = transformationMatrix * translationMatrix;
		}
	}


	built = true;
}

Vec<4> Scenery::Object::applyTransformation(Vec<4> v) {
	if (built) {
		v = transformationMatrix * v;
	}
	else {
		Mat<4> rotationMatrix_1 = rotation.getMatrixStep(0);
		Mat<4> rotationMatrix_2 = rotation.getMatrixStep(1);
		Mat<4> rotationMatrix_3 = rotation.getMatrixStep(2);
		Mat<4> scaleMatrix = Mat<4>::scale(scale.data);

		v += (Vec<4>) translation;
		v = rotationMatrix_1 * v;
		v = rotationMatrix_2 * v;
		v = rotationMatrix_3 * v;
		v = scaleMatrix * v;
	}

	return v;
}



void Scenery::Object::render()
{
	glPushMatrix();
	if (built) {
		glMultMatrixf((const float*)transformationMatrix.data);
	}
	else {
		glTranslatef(translation.data[0], translation.data[1], translation.data[2]);
		rotation.applyGLRotate();
		glScalef(scale.data[0], scale.data[1], scale.data[2]);
	}

	if (material != NULL) {
		glPushAttrib(GL_LIGHTING_BIT);
		material->use();
	}

	draw();

	for (Object* child : children)
		child->render();

	if (material != NULL) {
		glPopAttrib();
	}

	glPopMatrix();

}

void Scenery::Object::draw() {}

void Scenery::Object::update(float dt)
{

	for (Object* child : children)
		child->update(dt);

}
