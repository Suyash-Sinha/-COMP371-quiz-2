#include <glm/glm.hpp>

#include "arrow.hpp"

Arrow::Arrow(glm::vec4 color, GLfloat length) : RenderObject({ OGLVertexAttribute(0, 3, GL_FLOAT, GL_FALSE), OGLVertexAttribute(1, 4, GL_FLOAT, GL_FALSE) }) {
	std::vector<GLfloat> vertices = {
		0, 0, 0, color.x, color.y, color.z, color.w,
		0, 0, length, color.x, color.y, color.z, color.w,
		0.1f, 0, length - 0.2f, color.x, color.y, color.z, color.w,
		-0.1f, 0, length - 0.2f, color.x, color.y, color.z, color.w
	};

	std::vector<GLuint> indices = {0, 1, 1, 2, 1, 3};
	updateVertices(vertices);
	updateIndices(indices);
}
Arrow::~Arrow() {
	return;
}
void Arrow::render() {
	RenderObject::render(GL_LINES);
}