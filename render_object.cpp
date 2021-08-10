#include <cstdio>
#include <cstddef>
#include <initializer_list>
#include <vector>

#include <glad.h>

#include "render_object.hpp"
#include "utility.hpp"

// A class that encapsulates one OpenGL vertex attribute.
OGLVertexAttribute::OGLVertexAttribute(GLuint index, GLint size, GLenum type, GLboolean normalized) {
    this->index = index;
    this->size = size;
    this->type = type;
    this->normalized = normalized;
}
RenderObject::RenderObject(std::initializer_list<OGLVertexAttribute> attributes) {
    auto getSizeOfType = [](GLenum type) {
        switch (type) {
        case GL_BYTE: return (GLsizei)sizeof(GLbyte);
        case GL_UNSIGNED_BYTE: return (GLsizei)sizeof(GLubyte);
        case GL_SHORT: return (GLsizei)sizeof(GLshort);
        case GL_UNSIGNED_SHORT: return (GLsizei)sizeof(GLushort);
        case GL_INT: return (GLsizei)sizeof(GLint);
        case GL_UNSIGNED_INT: return (GLsizei)sizeof(GLuint);
        case GL_FLOAT: return (GLsizei)sizeof(GLfloat);
        default:
            assertFatal(false, "Could not get size of unknown type\n");
            return (GLsizei)0;
        }
    };
    glGenVertexArrays(1, &vertexArray);
    glBindVertexArray(vertexArray);
    glGenBuffers(1, &indexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
    glGenBuffers(1, &vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    GLsizei stride = 0;
    // We are basically dynamically generating the stride of the vertex buffer by 
    // adding up the size of each vertex attribute, saves up a lot of heartache.
    if (attributes.size() > 1) {
        for (auto& attribute : attributes) {
            stride += attribute.size * getSizeOfType(attribute.type);
        }
    }
    uintptr_t pointer = 0;
    for (auto& attribute : attributes) {
        // Dynamically defining vertex attributes.
        glEnableVertexAttribArray(attribute.index);
        glVertexAttribPointer(
            attribute.index,
            attribute.size,
            attribute.type,
            attribute.normalized,
            stride,
            (void*)pointer);
        pointer += attribute.size * getSizeOfType(attribute.type);
    }
}
RenderObject::~RenderObject() {
    glDeleteBuffers(1, &indexBuffer);
    glDeleteBuffers(1, &vertexBuffer);
    glDeleteVertexArrays(1, &vertexArray);
}
void RenderObject::render(GLenum mode, GLuint indexOffset, GLuint indexCount) {
    glBindVertexArray(vertexArray);
    glDrawElements(mode, indexCount == 0 ? indexBufferSize : indexCount,
        GL_UNSIGNED_INT, reinterpret_cast<void*>(indexOffset * sizeof(GLuint)));
}
// Helper functions to update the buffers.
void RenderObject::updateIndices(std::vector<GLuint>& indices) {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
        indices.size() * sizeof(GLuint), &indices[0], GL_DYNAMIC_DRAW);
    indexBufferSize = indices.size();
}
void RenderObject::updateVertices(std::vector<GLfloat>& vertices) {
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER,
        vertices.size() * sizeof(GLuint), &vertices[0], GL_DYNAMIC_DRAW);
}
