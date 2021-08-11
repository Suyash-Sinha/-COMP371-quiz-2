#include <glm/ext/matrix_transform.hpp>

#include "cluster.hpp"

// The cluster is essentially a collection of cubes following the principles of hierarchical modeling.
// This allows each cube to be positioned at a distinct offset but also allows every cube to move and rotate
// with the other cubes of the cluster.
Cluster::Cluster() {
}
Cluster::Cluster(glm::vec3 position, glm::vec3 rotation, float scale) {
	this->position = position;
	this->rotation = rotation;
	this->scale = scale;
	generateCluster();
}
Cluster::~Cluster() {
	return;
}
// Utility function to append a randomly colored cube to the cluster
void Cluster::appendCube(glm::vec3 offset) {
	float const R = (float)(rand() % 255) / 255.0f;
	float const G = (float)(rand() % 255) / 255.0f;
	float const B = (float)(rand() % 255) / 255.0f;
	cubes.push_back(new Cube(glm::vec4(R, G, B, 1.0f), offset));
}
void Cluster::generateCluster() {
	glm::vec3 const UP = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::vec3 const DOWN = glm::vec3(0.0f, -1.0f, 0.0f);
	glm::vec3 const LEFT = glm::vec3(-1.0f, 0.0f, 0.0f);
	glm::vec3 const RIGHT = glm::vec3(1.0f, 0.0f, 0.0f);
	glm::vec3 const FORWARD = glm::vec3(0.0f, 0.0f, 1.0f);
	glm::vec3 const BACKWARD = glm::vec3(0.0f, 0.0f, -1.0f);
	float const maxPlaneOffset = 2.0f;
	// This algorithm randomly generates a cluster of cubes by randomly selecting a cube in the cluster, a face of that cube,
	// checking if that face has a cube in front of it and finally placing a new cube in the cluster.

	glm::vec3 const offsets[] = { UP, DOWN, LEFT, RIGHT, FORWARD, BACKWARD };
	std::vector<glm::vec3> coordinates = { glm::vec3(0.0f, 0.0f, 0.0f) };
	appendCube(glm::vec3(0.0f, 0.0f, 0.0f));
	while (coordinates.size() < 9) {
		int const coordinateCount = coordinates.size();
		// Randomly select a cube.
		glm::vec3 randomCoordinate = coordinates[rand() % coordinateCount];
		// Place a cube on a randomly selected face of that cube.
		glm::vec3 newCoordinate = randomCoordinate + offsets[rand() % sizeof offsets / sizeof * offsets];
		// Check if the new cube goes up the max X length of the cluster.
		if (newCoordinate.x > maxPlaneOffset || newCoordinate.x < -maxPlaneOffset) {
			continue;
		}
		// Check if the new cube goes up the max Y length of the cluster.
		if (newCoordinate.y > maxPlaneOffset || newCoordinate.y < -maxPlaneOffset) {
			continue;
		}
		// Check if the new cube is over an already existing cube.
		if (std::find(coordinates.begin(), coordinates.end(), newCoordinate) != coordinates.end()) {
			continue;
		} else {
			// Add the cube.
			coordinates.push_back(newCoordinate);
			appendCube(newCoordinate);
		}
	}
}
void Cluster::render(ShaderManager* shaderMan, std::string const& programName) {
	// Render every cube of the cluster separately.
	for (Cube *cube : cubes) {
		const glm::mat4 i = glm::mat4(1.0f);
		// The order of matrix multiplication matters.
		glm::mat4 transform = 
		glm::translate(i, position) * // Step 4: Translate cluster
		glm::rotate(i, rotation.x, glm::vec3(1.0f, 0, 0)) * // Step 3: Rotate cluster around x-axis
		glm::rotate(i, rotation.y, glm::vec3(0, 1.0f, 0)) * // Step 3: Rotate cluster around y-axis
		glm::rotate(i, rotation.z, glm::vec3(0, 0, 1.0f)) * // Step 3: Rotate cluster around y-axis
		glm::scale(i, glm::vec3(scale)) * // Step 2: Scale cluster by a constant
		glm::translate(i, cube->position); // Step 1: Translate cube by offset
		shaderMan->setUniform("object", programName, transform);
		//shaderMan->setUniform("object","basic" , transform);		
		cube->render();
	}
}

void Cluster::setPosition(glm::vec3 position) {
	this->position = position;
}
void Cluster::setObject(int i) {
	switch (i)
	{
		//creating first number 5
	case 0:
		cubes.push_back(new Cube(glm::vec4(0.0f, 0.0f, 1.0f, 1.0f), glm::vec3(0.0f, 0.0f, 0.0f)));
		cubes.push_back(new Cube(glm::vec4(0.0f, 0.0f, 1.0f, 1.0f), glm::vec3(1.0f, 0.0f, 0.0f)));
		cubes.push_back(new Cube(glm::vec4(0.0f, 0.0f, 1.0f, 1.0f), glm::vec3(2.0f, 0.0f, 0.0f)));
		cubes.push_back(new Cube(glm::vec4(0.0f, 0.0f, 1.0f, 1.0f), glm::vec3(2.0f, -1.0f, 0.0f)));
		cubes.push_back(new Cube(glm::vec4(0.0f, 0.0f, 1.0f, 1.0f), glm::vec3(2.0f, -2.0f, 0.0f)));
		cubes.push_back(new Cube(glm::vec4(0.0f, 0.0f, 1.0f, 1.0f), glm::vec3(1.0f, -2.0f, 0.0f)));
		cubes.push_back(new Cube(glm::vec4(0.0f, 0.0f, 1.0f, 1.0f), glm::vec3(0.0f, -2.0f, 0.0f)));
		cubes.push_back(new Cube(glm::vec4(0.0f, 0.0f, 1.0f, 1.0f), glm::vec3(-1.0f, -2.0f, 0.0f)));
		cubes.push_back(new Cube(glm::vec4(0.0f, 0.0f, 1.0f, 1.0f), glm::vec3(-2.0f, -2.0f, 0.0f)));
		cubes.push_back(new Cube(glm::vec4(0.0f, 0.0f, 1.0f, 1.0f), glm::vec3(-1.0f, 0.0f, 0.0f)));
		cubes.push_back(new Cube(glm::vec4(0.0f, 0.0f, 1.0f, 1.0f), glm::vec3(-2.0f, 0.0f, 0.0f)));
		cubes.push_back(new Cube(glm::vec4(0.0f, 0.0f, 1.0f, 1.0f), glm::vec3(-2.0f, 1.0f, 0.0f)));
		cubes.push_back(new Cube(glm::vec4(0.0f, 0.0f, 1.0f, 1.0f), glm::vec3(-2.0f, 2.0f, 0.0f)));
		cubes.push_back(new Cube(glm::vec4(0.0f, 0.0f, 1.0f, 1.0f), glm::vec3(-1.0f, 2.0f, 0.0f)));
		cubes.push_back(new Cube(glm::vec4(0.0f, 0.0f, 1.0f, 1.0f), glm::vec3(0.0f, 2.0f, 0.0f)));
		cubes.push_back(new Cube(glm::vec4(0.0f, 0.0f, 1.0f, 1.0f), glm::vec3(1.0f, 2.0f, 0.0f)));
		cubes.push_back(new Cube(glm::vec4(0.0f, 0.0f, 1.0f, 1.0f), glm::vec3(2.0f, 2.0f, 0.0f)));
		break;
		//creating second number 0
	case 1:
		cubes.push_back(new Cube(glm::vec4(1.0f, 0.0f, 1.0f, 1.0f), glm::vec3(-2.0f, 2.0f, 0.0f)));
		cubes.push_back(new Cube(glm::vec4(1.0f, 0.0f, 1.0f, 1.0f), glm::vec3(2.0f, 2.0f, 0.0f)));
		cubes.push_back(new Cube(glm::vec4(1.0f, 0.0f, 1.0f, 1.0f), glm::vec3(1.0f, 2.0f, 0.0f)));
		cubes.push_back(new Cube(glm::vec4(1.0f, 0.0f, 1.0f, 1.0f), glm::vec3(0.0f, 2.0f, 0.0f)));
		cubes.push_back(new Cube(glm::vec4(1.0f, 0.0f, 1.0f, 1.0f), glm::vec3(-1.0f, 2.0f, 0.0f)));
		cubes.push_back(new Cube(glm::vec4(1.0f, 0.0f, 1.0f, 1.0f), glm::vec3(-2.0f, -2.0f, 0.0f)));
		cubes.push_back(new Cube(glm::vec4(1.0f, 0.0f, 1.0f, 1.0f), glm::vec3(0.0f, -2.0f, 0.0f)));
		cubes.push_back(new Cube(glm::vec4(1.0f, 0.0f, 1.0f, 1.0f), glm::vec3(2.0f, -2.0f, 0.0f)));
		cubes.push_back(new Cube(glm::vec4(1.0f, 0.0f, 1.0f, 1.0f), glm::vec3(-2.0f, 1.0f, 0.0f)));
		cubes.push_back(new Cube(glm::vec4(1.0f, 0.0f, 1.0f, 1.0f), glm::vec3(2.0f, 1.0f, 0.0f)));
		cubes.push_back(new Cube(glm::vec4(1.0f, 0.0f, 1.0f, 1.0f), glm::vec3(-2.0f, 0.0f, 0.0f)));
		cubes.push_back(new Cube(glm::vec4(1.0f, 0.0f, 1.0f, 1.0f), glm::vec3(2.0f, 0.0f, 0.0f)));
		cubes.push_back(new Cube(glm::vec4(1.0f, 0.0f, 1.0f, 1.0f), glm::vec3(-2.0f, -1.0f, 0.0f)));
		cubes.push_back(new Cube(glm::vec4(1.0f, 0.0f, 1.0f, 1.0f), glm::vec3(2.0f, -1.0f, 0.0f)));
		cubes.push_back(new Cube(glm::vec4(1.0f, 0.0f, 1.0f, 1.0f), glm::vec3(1.0f, -2.0f, 0.0f)));
		cubes.push_back(new Cube(glm::vec4(1.0f, 0.0f, 1.0f, 1.0f), glm::vec3(-1.0f, -2.0f, 0.0f)));
		break;
		//creating third number 4
	case 2:

		cubes.push_back(new Cube(glm::vec4(1.0f, 1.0f, 0.0f, 1.0f), glm::vec3(2.0f, 2.0f, 0.0f)));
		cubes.push_back(new Cube(glm::vec4(1.0f, 1.0f, 0.0f, 1.0f), glm::vec3(-2.0f, 2.0f, 0.0f)));
		cubes.push_back(new Cube(glm::vec4(1.0f, 1.0f, 0.0f, 1.0f), glm::vec3(2.0f, 1.0f, 0.0f)));
		cubes.push_back(new Cube(glm::vec4(1.0f, 1.0f, 0.0f, 1.0f), glm::vec3(-2.0f, 1.0f, 0.0f)));
		cubes.push_back(new Cube(glm::vec4(1.0f, 1.0f, 0.0f, 1.0f), glm::vec3(0.0f, 0.0f, 0.0f)));
		cubes.push_back(new Cube(glm::vec4(1.0f, 1.0f, 0.0f, 1.0f), glm::vec3(0.0f, 0.0f, 0.0f)));
		cubes.push_back(new Cube(glm::vec4(1.0f, 1.0f, 0.0f, 1.0f), glm::vec3(2.0f, -1.0f, 0.0f)));
		cubes.push_back(new Cube(glm::vec4(1.0f, 1.0f, 0.0f, 1.0f), glm::vec3(2.0f, -2.0f, 0.0f)));
		cubes.push_back(new Cube(glm::vec4(1.0f, 1.0f, 0.0f, 1.0f), glm::vec3(1.0f, 0.0f, 0.0f)));
		cubes.push_back(new Cube(glm::vec4(1.0f, 1.0f, 0.0f, 1.0f), glm::vec3(2.0f, 0.0f, 0.0f)));
		cubes.push_back(new Cube(glm::vec4(1.0f, 1.0f, 0.0f, 1.0f), glm::vec3(-1.0f, 0.0f, 0.0f)));
		cubes.push_back(new Cube(glm::vec4(1.0f, 1.0f, 0.0f, 1.0f), glm::vec3(-2.0f, 0.0f, 0.0f)));
		break;
		//creating fourth number 9
	case 3:
		cubes.push_back(new Cube(glm::vec4(0.0f, 1.0f, 0.0f, 1.0f), glm::vec3(0.0f, 0.0f, 0.0f)));
		cubes.push_back(new Cube(glm::vec4(0.0f, 1.0f, 0.0f, 1.0f), glm::vec3(1.0f, 0.0f, 0.0f)));
		cubes.push_back(new Cube(glm::vec4(0.0f, 1.0f, 0.0f, 1.0f), glm::vec3(2.0f, 0.0f, 0.0f)));
		cubes.push_back(new Cube(glm::vec4(0.0f, 1.0f, 0.0f, 1.0f), glm::vec3(2.0f, -1.0f, 0.0f)));
		cubes.push_back(new Cube(glm::vec4(0.0f, 1.0f, 0.0f, 1.0f), glm::vec3(2.0f, -2.0f, 0.0f)));
		cubes.push_back(new Cube(glm::vec4(0.0f, 1.0f, 0.0f, 1.0f), glm::vec3(2.0f, 1.0f, 0.0f)));
		cubes.push_back(new Cube(glm::vec4(0.0f, 1.0f, 0.0f, 1.0f), glm::vec3(-1.0f, 0.0f, 0.0f)));
		cubes.push_back(new Cube(glm::vec4(0.0f, 1.0f, 0.0f, 1.0f), glm::vec3(-2.0f, 0.0f, 0.0f)));
		cubes.push_back(new Cube(glm::vec4(0.0f, 1.0f, 0.0f, 1.0f), glm::vec3(-2.0f, 1.0f, 0.0f)));
		cubes.push_back(new Cube(glm::vec4(0.0f, 1.0f, 0.0f, 1.0f), glm::vec3(-2.0f, 2.0f, 0.0f)));
		cubes.push_back(new Cube(glm::vec4(0.0f, 1.0f, 0.0f, 1.0f), glm::vec3(-1.0f, 2.0f, 0.0f)));
		cubes.push_back(new Cube(glm::vec4(0.0f, 1.0f, 0.0f, 1.0f), glm::vec3(0.0f, 2.0f, 0.0f)));
		cubes.push_back(new Cube(glm::vec4(0.0f, 1.0f, 0.0f, 1.0f), glm::vec3(1.0f, 2.0f, 0.0f)));
		cubes.push_back(new Cube(glm::vec4(0.0f, 1.0f, 0.0f, 1.0f), glm::vec3(2.0f, 2.0f, 0.0f)));
		break;
		//creating skateboard with wheel
	case 4:
		cubes.push_back(new Cube(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f)));
		cubes.push_back(new Cube(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), glm::vec3(1.0f, 1.0f, 0.0f)));
		cubes.push_back(new Cube(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), glm::vec3(2.0f, 1.0f, 0.0f)));
		cubes.push_back(new Cube(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), glm::vec3(3.0f, 1.0f, 0.0f)));
		cubes.push_back(new Cube(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), glm::vec3(4.0f, 1.0f, 0.0f)));
		cubes.push_back(new Cube(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), glm::vec3(5.0f, 1.0f, 0.0f)));
		cubes.push_back(new Cube(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), glm::vec3(6.0f, 1.0f, 0.0f)));
		cubes.push_back(new Cube(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), glm::vec3(7.0f, 1.0f, 0.0f)));
		cubes.push_back(new Cube(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), glm::vec3(8.0f, 1.0f, 0.0f)));
		cubes.push_back(new Cube(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), glm::vec3(9.0f, 1.0f, 0.0f)));
		cubes.push_back(new Cube(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), glm::vec3(10.0f, 1.0f, 0.0f)));
		cubes.push_back(new Cube(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), glm::vec3(11.0f, 1.0f, 0.0f)));
		cubes.push_back(new Cube(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), glm::vec3(12.0f, 1.0f, 0.0f)));
		cubes.push_back(new Cube(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), glm::vec3(13.0f, 1.0f, 0.0f)));

		cubes.push_back(new Cube(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), glm::vec3(-0.0f, 1.0f, 0.0f)));
		cubes.push_back(new Cube(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), glm::vec3(-1.0f, 1.0f, 0.0f)));
		cubes.push_back(new Cube(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), glm::vec3(-2.0f, 1.0f, 0.0f)));
		cubes.push_back(new Cube(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), glm::vec3(-3.0f, 1.0f, 0.0f)));
		cubes.push_back(new Cube(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), glm::vec3(-4.0f, 1.0f, 0.0f)));
		cubes.push_back(new Cube(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), glm::vec3(-5.0f, 1.0f, 0.0f)));
		cubes.push_back(new Cube(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), glm::vec3(-6.0f, 1.0f, 0.0f)));
		cubes.push_back(new Cube(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), glm::vec3(-7.0f, 1.0f, 0.0f)));
		cubes.push_back(new Cube(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), glm::vec3(-8.0f, 1.0f, 0.0f)));
		cubes.push_back(new Cube(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), glm::vec3(-9.0f, 1.0f, 0.0f)));
		cubes.push_back(new Cube(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), glm::vec3(-10.0f, 1.0f, 0.0f)));
		cubes.push_back(new Cube(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), glm::vec3(-11.0f, 1.0f, 0.0f)));
		cubes.push_back(new Cube(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), glm::vec3(-12.0f, 1.0f, 0.0f)));
		cubes.push_back(new Cube(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), glm::vec3(-13.0f, 1.0f, 0.0f)));

		cubes.push_back(new Cube(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 1.0f)));
		cubes.push_back(new Cube(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f)));
		cubes.push_back(new Cube(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), glm::vec3(2.0f, 1.0f, 1.0f)));
		cubes.push_back(new Cube(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), glm::vec3(3.0f, 1.0f, 1.0f)));
		cubes.push_back(new Cube(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), glm::vec3(4.0f, 1.0f, 1.0f)));
		cubes.push_back(new Cube(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), glm::vec3(5.0f, 1.0f, 1.0f)));
		cubes.push_back(new Cube(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), glm::vec3(6.0f, 1.0f, 1.0f)));
		cubes.push_back(new Cube(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), glm::vec3(7.0f, 1.0f, 1.0f)));
		cubes.push_back(new Cube(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), glm::vec3(8.0f, 1.0f, 1.0f)));
		cubes.push_back(new Cube(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), glm::vec3(9.0f, 1.0f, 1.0f)));
		cubes.push_back(new Cube(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), glm::vec3(10.0f, 1.0f, 1.0f)));
		cubes.push_back(new Cube(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), glm::vec3(11.0f, 1.0f, 1.0f)));
		cubes.push_back(new Cube(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), glm::vec3(12.0f, 1.0f, 1.0f)));
		cubes.push_back(new Cube(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), glm::vec3(13.0f, 1.0f, 1.0f)));

		cubes.push_back(new Cube(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), glm::vec3(-0.0f, 1.0f, 1.0f)));
		cubes.push_back(new Cube(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), glm::vec3(-1.0f, 1.0f, 1.0f)));
		cubes.push_back(new Cube(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), glm::vec3(-2.0f, 1.0f, 1.0f)));
		cubes.push_back(new Cube(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), glm::vec3(-3.0f, 1.0f, 1.0f)));
		cubes.push_back(new Cube(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), glm::vec3(-4.0f, 1.0f, 1.0f)));
		cubes.push_back(new Cube(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), glm::vec3(-5.0f, 1.0f, 1.0f)));
		cubes.push_back(new Cube(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), glm::vec3(-6.0f, 1.0f, 1.0f)));
		cubes.push_back(new Cube(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), glm::vec3(-7.0f, 1.0f, 1.0f)));
		cubes.push_back(new Cube(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), glm::vec3(-8.0f, 1.0f, 1.0f)));
		cubes.push_back(new Cube(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), glm::vec3(-9.0f, 1.0f, 1.0f)));
		cubes.push_back(new Cube(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), glm::vec3(-10.0f, 1.0f, 1.0f)));
		cubes.push_back(new Cube(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), glm::vec3(-11.0f, 1.0f, 1.0f)));
		cubes.push_back(new Cube(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), glm::vec3(-12.0f, 1.0f, 1.0f)));
		cubes.push_back(new Cube(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), glm::vec3(-13.0f, 1.0f, 1.0f)));

		cubes.push_back(new Cube(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 1.0f, -1.0f)));
		cubes.push_back(new Cube(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), glm::vec3(1.0f, 1.0f, -1.0f)));
		cubes.push_back(new Cube(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), glm::vec3(2.0f, 1.0f, -1.0f)));
		cubes.push_back(new Cube(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), glm::vec3(3.0f, 1.0f, -1.0f)));
		cubes.push_back(new Cube(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), glm::vec3(4.0f, 1.0f, -1.0f)));
		cubes.push_back(new Cube(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), glm::vec3(5.0f, 1.0f, -1.0f)));
		cubes.push_back(new Cube(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), glm::vec3(6.0f, 1.0f, -1.0f)));
		cubes.push_back(new Cube(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), glm::vec3(7.0f, 1.0f, -1.0f)));
		cubes.push_back(new Cube(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), glm::vec3(8.0f, 1.0f, -1.0f)));
		cubes.push_back(new Cube(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), glm::vec3(9.0f, 1.0f, -1.0f)));
		cubes.push_back(new Cube(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), glm::vec3(10.0f, 1.0f, -1.0f)));
		cubes.push_back(new Cube(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), glm::vec3(11.0f, 1.0f, -1.0f)));
		cubes.push_back(new Cube(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), glm::vec3(12.0f, 1.0f, -1.0f)));
		cubes.push_back(new Cube(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), glm::vec3(13.0f, 1.0f, -1.0f)));

		cubes.push_back(new Cube(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), glm::vec3(-0.0f, 1.0f, -1.0f)));
		cubes.push_back(new Cube(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), glm::vec3(-1.0f, 1.0f, -1.0f)));
		cubes.push_back(new Cube(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), glm::vec3(-2.0f, 1.0f, -1.0f)));
		cubes.push_back(new Cube(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), glm::vec3(-3.0f, 1.0f, -1.0f)));
		cubes.push_back(new Cube(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), glm::vec3(-4.0f, 1.0f, -1.0f)));
		cubes.push_back(new Cube(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), glm::vec3(-5.0f, 1.0f, -1.0f)));
		cubes.push_back(new Cube(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), glm::vec3(-6.0f, 1.0f, -1.0f)));
		cubes.push_back(new Cube(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), glm::vec3(-7.0f, 1.0f, -1.0f)));
		cubes.push_back(new Cube(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), glm::vec3(-8.0f, 1.0f, -1.0f)));
		cubes.push_back(new Cube(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), glm::vec3(-9.0f, 1.0f, -1.0f)));
		cubes.push_back(new Cube(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), glm::vec3(-10.0f, 1.0f, -1.0f)));
		cubes.push_back(new Cube(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), glm::vec3(-11.0f, 1.0f, -1.0f)));
		cubes.push_back(new Cube(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), glm::vec3(-12.0f, 1.0f, -1.0f)));
		cubes.push_back(new Cube(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), glm::vec3(-13.0f, 1.0f, -1.0f)));

		cubes.push_back(new Cube(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec3(11.0f, 0.0f, -1.0f)));
		cubes.push_back(new Cube(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec3(11.0f, 0.0f, 1.0f)));
		cubes.push_back(new Cube(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec3(-11.0f, 0.0f, -1.0f)));
		cubes.push_back(new Cube(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec3(-11.0f, 0.0f, 1.0f)));



		break;

	default:
		break;
	}


}