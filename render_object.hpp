#pragma once

#include <initializer_list>
#include <vector>

#include <GLFW/glfw3.h>

class OGLVertexAttribute {
public:
    GLuint index;
    GLint size;
    GLenum type;
    GLboolean normalized;
public:
    OGLVertexAttribute(GLuint index, GLint size, GLenum type, GLboolean normalized);
};
class RenderObject {
public:
    RenderObject(std::initializer_list<OGLVertexAttribute> attributes);
    ~RenderObject();
public:
    void render(GLenum mode = GL_TRIANGLES, GLuint indexOffset = 0, GLuint indexCount = 0);
public:
    void updateIndices(std::vector<GLuint>& indices);
    void updateVertices(std::vector<GLfloat>& vertices);
private:
    GLuint indexBuffer = 0;
    GLuint vertexArray = 0;
    GLuint vertexBuffer = 0;
private:
    unsigned int indexBufferSize = 0;
};
