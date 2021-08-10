#pragma once

#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>

#include "shader_manager.hpp"
#include "render_object.hpp"

class Cube : RenderObject {
public:
	glm::vec3 position = glm::vec3(0, 0, 0);
public:
	Cube(glm::vec4 color, glm::vec3 position = glm::vec3(0, 0, 0));
	~Cube();
public:
	void render();
	void setPosition(glm::vec3 position);
};