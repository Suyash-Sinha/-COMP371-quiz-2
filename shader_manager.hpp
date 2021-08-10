#pragma once

#include <initializer_list>
#include <string>
#include <unordered_map>

#include <GLFW/glfw3.h>
#include <glm/mat4x4.hpp>

class ShaderManager {
public:
	ShaderManager();
	~ShaderManager();
public:
	void appendShader(std::string const& name, GLenum type, std::string const& path);
	void deleteShaders();
public:
	void createProgram(std::string const& name, std::initializer_list<std::string> shaderNames);
	void deletePrograms();
	GLuint getCurrentProgram();
	GLuint getProgram(std::string const& name);
	void useProgram(std::string const& name);
public:
	GLint getUniformLocation(std::string const& uniformName, std::string const& programName, GLuint program);
	void setUniform(std::string const& uniformName, std::string const& programName, glm::mat4 value);
	void setUniform(std::string const& uniformName, std::string const& programName, glm::vec4 value);
	void setUniform(std::string const& uniformName, std::string const& programName, glm::vec3 value);
	void setUniform(std::string const& uniformName, std::string const& programName, GLint value);
	void setUniform(std::string const& uniformName, std::string const& programName, GLfloat value);
	void setUniform(std::string const& uniformName, std::string const& programName, GLboolean value);
private:
	GLuint currentProgram = 0;
	std::string currentProgramName;
	std::unordered_map<std::string, GLuint> programs;
	std::unordered_map<std::string, GLuint> shaders;
	std::unordered_map<std::string, GLint> uniforms;
};
