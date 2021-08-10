#pragma once

#include <glm/vec4.hpp>

#include "render_object.hpp"

class Arrow : RenderObject {
public:
	Arrow(glm::vec4 color, GLfloat length);
	~Arrow();
public:
	void render();
};