#version 430

out vec4 outColor;

uniform int mOffset;

void main()
{
	outColor = vec4(
	    abs(sin(gl_FragCoord.x) * 5),
	    ((int(gl_FragCoord.x) + mOffset) % 600) / 600.0f,
	    0.0,
	    1.0);
}