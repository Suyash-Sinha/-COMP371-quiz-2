#include <cstdio>

#include "stb_image.h"

#include "texture_manager.hpp"
#include "utility.hpp"

TextureManager::TextureManager() {
    return;
}
TextureManager::~TextureManager() {
    printf("Deleting textures (%lu)\n", textures.size());
    for (auto& pair : textures) {
        printf("Deleting texture %s\n", pair.first.c_str());
        glDeleteTextures(1, &pair.second.identifier);
    }
}
void TextureManager::loadTexture(std::string const& name, GLenum type, std::string const& path) {
    struct Texture texture = { 0 };
    int channelCount = 0;
    printf("Loading GL_TEXTURE_2D %s from %s\n", name.c_str(), path.c_str());
    unsigned char* buffer = stbi_load(path.c_str(), &texture.size[0], &texture.size[1], &channelCount, 0);
    assertFatal(buffer != NULL, "Texture %s at %s could not be loaded\n", name.c_str(), path.c_str());
    switch (channelCount) {
    case 3: texture.format = GL_RGB; break;
    case 4: texture.format = GL_RGBA; break;
    default:
        assertFatal("Texture %s has less than 3 channels (%d)\n", name.c_str(), channelCount);
    }
    texture.type = type;
    glGenTextures(1, &texture.identifier);
    glBindTexture(type, texture.identifier);
    glTexImage2D(type, 0, texture.format, texture.size[0], texture.size[1], 0, texture.format, GL_UNSIGNED_BYTE, buffer);
    stbi_image_free(buffer);
    switch (type) {
    case GL_TEXTURE_2D:
        glTexParameteri(type, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(type, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(type, GL_TEXTURE_MAG_FILTER, GL_NEAREST_MIPMAP_NEAREST);
        glTexParameteri(type, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        break;
    default: break;
    }
    glGenerateMipmap(type);
    textures[name] = texture;
}
void TextureManager::generateCubemap(std::string const& name) {
    struct Texture texture = { 0 };
    texture.type = GL_TEXTURE_CUBE_MAP;
    texture.size[0] = 2048;
    texture.size[1] = 2048;
    glGenTextures(1, &texture.identifier);
    glBindTexture(texture.type, texture.identifier);
    for (unsigned int i = 0; i < 6; ++i)
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_DEPTH_COMPONENT, texture.size[0], texture.size[1], 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
    glTexParameteri(texture.type, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(texture.type, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(texture.type, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(texture.type, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(texture.type, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    textures[name] = texture;
}
TextureManager::Texture& TextureManager::getTexture(std::string const& name) {
    auto item = textures.find(name);
    assertFatal(item != textures.end(), "Could not get texture %s\n",
        name.c_str());
    return item->second;
}
void TextureManager::bindTextureToUnit(GLint unit, std::string const& name) {
    struct Texture const& texture = getTexture(name);
    printf("Binding %s %s to unit %d\n", textureTypeToString(texture.type).c_str(), name.c_str(), unit);
    glActiveTexture(GL_TEXTURE0 + unit);
    glBindTexture(texture.type, texture.identifier);
}
std::string TextureManager::textureTypeToString(GLenum type) {
    switch (type) {
    case GL_TEXTURE_2D: return std::string("GL_TEXTURE_2D");
    case GL_TEXTURE_CUBE_MAP: return std::string("GL_TEXTURE_CUBE_MAP");
    default: return std::string("GL_UNKNOWN_TEXTURE");
    }
}
