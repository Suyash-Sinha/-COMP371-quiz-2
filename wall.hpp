#pragma once

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

#include "cluster.hpp"
#include "render_object.hpp"

class Wall : RenderObject {
public:
	glm::vec3 position = glm::vec3(0, 0, 0);
public:
	Wall(Cluster *cluster, glm::vec3 position, glm::vec4 color = glm::vec4(1.0f, 1.0f, 0.0f, 1.0f));
	~Wall();
public:
	void render();
};