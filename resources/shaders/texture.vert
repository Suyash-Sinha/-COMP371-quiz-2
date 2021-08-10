#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec4 color;
layout (location = 2) in vec2 texCoord;
layout (location = 3) in vec3 normal;
out vec3 vertNormal;
out vec4 vertColor;
out vec2 vertTexCoord;
out vec3 fragPosition;
out vec3 vertLightPosition;

uniform mat4 viewProjection;
uniform mat4 world;
uniform mat4 object;

void main()
{
	vertColor = color;
	vertTexCoord = texCoord;
	vertNormal = mat3(transpose(inverse(object))) * normal;
	fragPosition = (object * vec4(position, 1.0)).xyz;
    gl_Position = viewProjection * world * object * vec4(position, 1.0);
}