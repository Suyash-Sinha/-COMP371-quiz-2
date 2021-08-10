#pragma once

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

#include "render_object.hpp"

class Grid : RenderObject {
public:
	glm::vec3 position = glm::vec3(0, -3.0f, 0);
public:
	Grid(int width, int height, GLfloat sideLength = 1.0f, glm::vec4 color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
	~Grid();
public:
	void render();
};