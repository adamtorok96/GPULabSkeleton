#version 330

uniform mat4 MV;

in vec3 pos;
in vec4 textureCoords;
in vec3 normal;
in int color[4];

void main()
{
	gl_Position = MV * vec4(pos, 1.0f);
}