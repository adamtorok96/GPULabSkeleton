#version 330

uniform mat4 MV;

in vec2 pos;

void main()
{
	gl_Position = MV * vec4(pos, 0.0f, 1.0f);
}