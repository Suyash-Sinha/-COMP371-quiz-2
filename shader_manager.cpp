#include <cstdio>
#include <cstring>
#include <glm/gtc/type_ptr.hpp>
#include <initializer_list>
#include <unordered_map>

#include <glad.h>

#include "shader_manager.hpp"
#include "utility.hpp"

// This class handles everything from shader creation to uniform setting.
ShaderManager::ShaderManager() {
    shaders.clear();
    programs.clear();
    return;
}
ShaderManager::~ShaderManager() {
    deletePrograms();
    deleteShaders();
}
// Appends a shader that is stored in a hash map for future bindings.
void ShaderManager::appendShader(std::string const& name, GLenum type, std::string const& path) {
    auto shaderTypeToString = [](GLenum shaderType) {
        switch (shaderType) {
        case GL_VERTEX_SHADER: return std::string("GL_VERTEX_SHADER");
        case GL_FRAGMENT_SHADER: return std::string("GL_FRAGMENT_SHADER");
        default: return std::string("GL_UNKNOWN_SHADER");
        }
    };
    auto eraseTerminatingNewline = [](char* x) {
        for (int i = strlen(x); i >= 1; i -= 1) {
            if (x[i] == '\n') x[i] = '\0';
            if (x[i - 1] != '\n' && x[i - 1] != '\x20') break;
        }
    };
    GLuint const shader = glCreateShader(type);
    char const* shaderSource = readFile(path.c_str());
    glShaderSource(shader, 1, &shaderSource, NULL);
    printf("Compiling %s %s (%s)\n",
        shaderTypeToString(type).c_str(), name.c_str(), path.c_str());
    glCompileShader(shader);
    char infoLog[1024];
    glGetShaderInfoLog(shader, sizeof infoLog, NULL, infoLog);
    eraseTerminatingNewline(infoLog);
    assertFatal(strlen(infoLog) == 0, "Could not compile shader %s: %s\n",
        name.c_str(), infoLog);
    shaders[name] = shader;
}
void ShaderManager::deleteShaders() {
    printf("Deleting shaders (%lu)\n", shaders.size());
    for (auto& pair : shaders) {
        printf("Deleting shader %s\n", pair.first.c_str());
        GLuint const shader = pair.second;
        glDeleteShader(shader);
    }
}
void ShaderManager::createProgram(std::string const& name, std::initializer_list<std::string> shaderNames) {
    auto eraseTerminatingNewline = [](char* x) {
        for (int i = strlen(x); i >= 1; i -= 1) {
            if (x[i] == '\n') x[i] = '\0';
            if (x[i - 1] != '\n' && x[i - 1] != '\x20') break;
        }
    };
    printf("Creating program %s\n", name.c_str());
    GLuint const program = glCreateProgram();
    programs[name] = program;
    for (auto& shaderName : shaderNames) {
        auto item = shaders.find(shaderName);
        assertFatal(item != shaders.end(), "Could not attach non-existent shader %s\n",
            shaderName.c_str());
        GLuint const shader = item->second;
        printf("Attaching shader %s to program %s\n",
            shaderName.c_str(), name.c_str());
        glAttachShader(program, shader);
    }
    glLinkProgram(program);
    char infoLog[1024];
    glGetProgramInfoLog(program, sizeof infoLog, NULL, infoLog);
    eraseTerminatingNewline(infoLog);
    assertFatal(strlen(infoLog) == 0, "Could not link program %s: %s\n",
        name.c_str(), infoLog);
    for (auto& shaderName : shaderNames) {
        GLuint const shader = shaders.find(shaderName)->second;
        printf("Detaching shader %s from program %s\n",
            shaderName.c_str(), name.c_str());
        glDetachShader(program, shader);
    }
}
void ShaderManager::deletePrograms() {
    printf("Deleting programs (%lu)\n", programs.size());
    for (auto& pair : programs) {
        printf("Deleting program %s\n", pair.first.c_str());
        glDeleteProgram(pair.second);
    }
}
GLuint ShaderManager::getCurrentProgram() {
    return currentProgram;
}
GLuint ShaderManager::getProgram(std::string const& name) {
    if (name == currentProgramName) return currentProgram;
    auto item = programs.find(name);
    assertFatal(item != programs.end(), "Could not get program %s\n",
        name.c_str());
    return item->second;
}
void ShaderManager::useProgram(std::string const& name) {
    GLuint const program = getProgram(name);
    currentProgramName = name;
    if (currentProgram != program) glUseProgram(program);
    currentProgram = program;
}
// Utility function to fetch and cache uniform locations.
GLint ShaderManager::getUniformLocation(std::string const& uniformName, std::string const& programName, GLuint program) {
    std::string key = programName + ":" + uniformName;
    auto item = uniforms.find(key);
    if (item != uniforms.end()) return item->second;
    printf("Fetching uniform %s from program %s\n",
        uniformName.c_str(), programName.c_str());
    GLint const location = glGetUniformLocation(program, uniformName.c_str());
    if (location == -1)
        printf("Uniform %s is inactive or non-existent in program %s\n",
            uniformName.c_str(), programName.c_str());
    uniforms[key] = location;
    return location;
}
// Function overloading is very useful in this case. The same function can be used for any and every type of GLM values.
// And of course, each value may be handled its own way.
void ShaderManager::setUniform(std::string const& uniformName, std::string const& programName, glm::mat4 value) {
    useProgram(programName);
    GLuint const program = getCurrentProgram();
    GLint const location = getUniformLocation(uniformName, programName, program);
    if (location == -1) return;
    glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value));
}
void ShaderManager::setUniform(std::string const& uniformName, std::string const& programName, glm::vec4 value) {
    useProgram(programName);
    GLuint const program = getCurrentProgram();
    GLint const location = getUniformLocation(uniformName, programName, program);
    if (location == -1) return;
    glUniform4fv(location, 1, glm::value_ptr(value));
}
void ShaderManager::setUniform(std::string const& uniformName, std::string const& programName, glm::vec3 value) {
    useProgram(programName);
    GLuint const program = getCurrentProgram();
    GLint const location = getUniformLocation(uniformName, programName, program);
    if (location == -1) return;
    glUniform3fv(location, 1, glm::value_ptr(value));
}
void ShaderManager::setUniform(std::string const& uniformName, std::string const& programName, GLint value) {
    useProgram(programName);
    GLuint const program = getCurrentProgram();
    GLint const location = getUniformLocation(uniformName, programName, program);
    if (location == -1) return;
    glUniform1i(location, value);
}
void ShaderManager::setUniform(std::string const& uniformName, std::string const& programName, GLfloat value) {
    useProgram(programName);
    GLuint const program = getCurrentProgram();
    GLint const location = getUniformLocation(uniformName, programName, program);
    if (location == -1) return;
    glUniform1f(location, value);
}
void ShaderManager::setUniform(std::string const& uniformName, std::string const& programName, GLboolean value) {
    useProgram(programName);
    GLuint const program = getCurrentProgram();
    GLint const location = getUniformLocation(uniformName, programName, program);
    if (location == -1) return;
    glUniform1i(location, value);
}
