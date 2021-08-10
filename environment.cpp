#include "environment.h"

Environment::Environment(glm::vec4 color, glm::vec3 position) : RenderObject({
	OGLVertexAttribute(0, 3, GL_FLOAT, GL_FALSE), OGLVertexAttribute(1, 4, GL_FLOAT, GL_FALSE), OGLVertexAttribute(2, 2, GL_FLOAT, GL_FALSE), OGLVertexAttribute(3, 3, GL_FLOAT, GL_FALSE) }) {
	this->position = position;
	GLfloat const s = -25;
	std::vector<GLfloat> vertices = {
		s, -s, -s, color.x, color.y, color.z, color.w, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,
		s, -s, s, color.x, color.y, color.z, color.w, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f,
		s, s, s, color.x, color.y, color.z, color.w, 1.0f, 1.0f, -1.0f, 0.0f, 0.0f,
		s, s, -s, color.x, color.y, color.z, color.w, 1.0f, 0.0f, -1.0f, 0.0f, 0.0f,

		-s, -s, -s, color.x, color.y, color.z, color.w, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
		-s, -s, s, color.x, color.y, color.z, color.w, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
		s, -s, s, color.x, color.y, color.z, color.w, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f,
		s, -s, -s, color.x, color.y, color.z, color.w, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,

		-s, s, -s, color.x, color.y, color.z, color.w, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
		-s, s, s, color.x, color.y, color.z, color.w, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f,
		-s, -s, s, color.x, color.y, color.z, color.w, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
		-s, -s, -s, color.x, color.y, color.z, color.w, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f,

		s, s, -s, color.x, color.y, color.z, color.w, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f,
		s, s, s, color.x, color.y, color.z, color.w, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f,
		-s, s, s, color.x, color.y, color.z, color.w, 1.0f, 1.0f, 0.0f, -1.0f, 0.0f,
		-s, s, -s, color.x, color.y, color.z, color.w, 1.0f, 0.0f, 0.0f, -1.0f, 0.0f,

		s, s, s, color.x, color.y, color.z, color.w, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f,
		s, -s, s, color.x, color.y, color.z, color.w, 0.0f, 1.0f, 0.0f, 0.0f, -1.0f,
		-s, -s, s, color.x, color.y, color.z, color.w, 1.0f, 1.0f, 0.0f, 0.0f, -1.0f,
		-s, s, s, color.x, color.y, color.z, color.w, 1.0f, 0.0f, 0.0f, 0.0f, -1.0f,

		s, -s, -s, color.x, color.y, color.z, color.w, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,
		s, s, -s, color.x, color.y, color.z, color.w, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
		-s, s, -s, color.x, color.y, color.z, color.w, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
		-s, -s, -s, color.x, color.y, color.z, color.w, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
	};
	// Using an index array to not have to re-use vertices over and over again for triangles
	// that may share them. This saves up quite a bit of space (over 50% memory save).
	std::vector<GLuint> indices;
	for (GLuint i = 0; i < 24; i += 4) {
		GLuint jj[] = { i, i + 1, i + 3, i + 3, i + 1, i + 2 };
		indices.insert(indices.end(), std::begin(jj), std::end(jj));
	}
	updateVertices(vertices);
	updateIndices(indices);
}
Environment::~Environment() {
	return;
}
void Environment::render() {
	RenderObject::render();
}
void Environment::setPosition(glm::vec3 position) {
	this->position = position;
}