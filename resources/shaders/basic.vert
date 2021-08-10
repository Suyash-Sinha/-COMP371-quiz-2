#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec4 color;
out vec4 vertColor;

uniform mat4 viewProjection;
uniform mat4 world;
uniform mat4 object;

void main()
{
	vertColor = color;
    gl_Position = viewProjection * world * object * vec4(position.x, position.y, position.z, 1.0);
}