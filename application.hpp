#pragma once

#include <GLFW/glfw3.h>
#include"environment.h"
#include "arrow.hpp"
#include "camera.hpp"
#include "cluster.hpp"
#include "cube.hpp"
#include "grid.hpp"
#include "scheduler.hpp"
#include "shader_manager.hpp"
#include "texture_manager.hpp"
#include "wall.hpp"

enum RotationMode {
	ROTATE_X,
	ROTATE_Y,
	ROTATE_Z
};
class Application {
public:
	double const UPDATE_INTERVAL = 1.0 / 30.0;
	char const* WINDOW_TITLE = "COMP371	QUIZ #2";
	glm::vec3 INITIAL_CLUSTER_POSITIONS[5] = {
		glm::vec3(-10.5f,5 , 0),
		glm::vec3(-3.5f, 5 , 0),
		glm::vec3(3.5f,  5, 0),
		glm::vec3(10.5f, 5, 0),
		glm::vec3(0, 1, 0)
	};
	/*glm::vec3 INITIAL_WALL_POSITIONS[5] = {
		glm::vec3(0, 0, -7.0f),
		glm::vec3(25.0f, 0, 23.0f),
		glm::vec3(-25.0f, 0, 23.0f),
		glm::vec3(25.0f, 0, -27.0f),
		glm::vec3(-25.0f, 0, -27.0f)
	};*/
	glm::vec3 LIGHT_POSITION = glm::vec3(0, 24.5, 0);
	GLfloat SHADOWMAP_FAR_PLANE = 25.0f;
public:
	Scheduler scheduler = Scheduler(UPDATE_INTERVAL);
	GLFWwindow* window = nullptr;
	glm::dvec2 lastMousePos = glm::dvec2(0, 0);
	int windowSize[2] = { 1024, 768 };
	int topcam=0;
public:
	Camera* camera;
	Grid* grid;
	Environment* env;
	ShaderManager *shaderMan;
	TextureManager* textureMan;
	Arrow *xAxis, *yAxis, *zAxis;
	Cube* lightCube;
public:
	glm::vec2 worldRotation = glm::vec2(0, 0);
	Cluster *clusters;
	int currentCluster = 0;
	Wall **walls;
	GLuint depthFBO;
	std::vector<glm::mat4> shadowTransforms;
	RotationMode rotationMode;
public:
	bool temp=false;
	bool enableTextures = true;
	bool enableShadows = true;
	bool enableSmoothMoves = false;
public: 
	Application();
	~Application();
public:
	void handleMouse();
	void handleKeyboard();
	void render();
	void renderShadowMap();
	void update();
private:
	void initialiseGLFW();
	void initialiseOpenGL();
	void initialiseOpenGLShaders();
	void initialiseScene();
	void initialiseTextures();
};