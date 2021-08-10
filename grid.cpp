#include "grid.hpp"

Grid::Grid(int width, int height, GLfloat sideLength, glm::vec4 color) : RenderObject({ 
	OGLVertexAttribute(0, 3, GL_FLOAT, GL_FALSE), OGLVertexAttribute(1, 4, GL_FLOAT, GL_FALSE), OGLVertexAttribute(2, 2, GL_FLOAT, GL_FALSE), OGLVertexAttribute(3, 3, GL_FLOAT, GL_FALSE) }) {
	std::vector<GLfloat> vertices;
	std::vector<GLuint> indices;
	GLuint indexOffset = 0;
	for (int i = 0; i < width; i += 1) {
		for (int j = 0; j < height; j += 1) {
			GLfloat x = ((GLfloat)i - (GLfloat)width / 2.0f) * sideLength + position.x;
			GLfloat y = position.y;
			GLfloat z = ((GLfloat)j - (GLfloat)height / 2.0f) * sideLength  + position.z;
			GLfloat ii[] = { 
				x, y, z, color.x, color.y, color.z, color.w, 0, 0, 0, 1.0f, 0,
				x, y, z + sideLength, color.x, color.y, color.z, color.w, 0, 1.0f, 0, 1.0f, 0,
				x + sideLength, y, z + sideLength, color.x, color.y, color.z, color.w, 1.0f, 1.0f, 0, 1.0f, 0,
				x + sideLength, y, z, color.x, color.y, color.z, color.w, 1.0f, 0.0f, 0, 1.0f, 0,
			};

			vertices.insert(vertices.end(), std::begin(ii), std::end(ii));
			GLuint jj[] = { indexOffset + 3, indexOffset + 1, indexOffset, indexOffset + 2, indexOffset + 1, indexOffset + 3 };
			indices.insert(indices.end(), std::begin(jj), std::end(jj));
			indexOffset += 4;
		}
	}
	updateVertices(vertices);
	updateIndices(indices);
}
Grid::~Grid() {
	return;
}
void Grid::render() {
	RenderObject::render(GL_TRIANGLES);
}