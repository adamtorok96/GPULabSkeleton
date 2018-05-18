#version 430

out vec4 outColor;

void main()
{
	outColor = vec4(
	    gl_PrimitiveID % 3 == 0 ? 1.0f : 0.0f,
	    gl_PrimitiveID % 3 == 1 ? 1.0f : 0.0f,
	    gl_PrimitiveID % 3 == 2 ? 1.0f : 0.0f,
	1.0);
}