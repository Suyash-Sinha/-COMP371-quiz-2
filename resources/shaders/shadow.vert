#version 330 core
layout (location = 0) in vec3 position;

uniform mat4 object;

void main()
{
    gl_Position = object * vec4(position, 1.0);
}  