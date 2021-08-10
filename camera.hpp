#pragma once

#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

const float M_PI = glm::pi<float>();

class Camera {
public:
	glm::vec3 const WORLD_UP = glm::vec3(0, 1, 0);
	double const ZOOM_SPEED = 80.0f;
	double const MOUSE_SENSITIVITY = 0.05f;
public:
	glm::vec3 forward = glm::vec3(0, 0, 0);
	glm::vec3 position = glm::vec3(0, 1, 5);
	glm::vec3 right = glm::vec3(0, 0, 0);
public:
	bool dirty = true;
public:
	float pitch = 0.0f;
	float yaw = 0.0f;
public:
	glm::mat4 projection;
	glm::mat4 view;
	glm::mat4 viewProjection;
public:
	Camera(glm::mat4 projection, glm::vec2 rotation);
	~Camera();
public:
	void setProjection(glm::mat4 projection);
	void setRotation(glm::vec2 rotation);
	void rotate(glm::vec2 mouseDelta);
	void update(double currentTime);
};