#pragma once

#include <string>
#include <unordered_map>

#include "glad.h"

class TextureManager {
public:
    struct Texture {
        GLenum format;
        GLuint identifier;
        int size[2];
        GLenum type;
    };
public:
    TextureManager();
    ~TextureManager();
public:
    void loadTexture(std::string const& name, GLenum type, std::string const& path);
    void generateCubemap(std::string const& name);
    struct Texture& getTexture(std::string const& name);
    void bindTextureToUnit(GLint unit, std::string const& name);
private:
    std::unordered_map<std::string, struct Texture> textures;
private:
    std::string textureTypeToString(GLenum type);
};
