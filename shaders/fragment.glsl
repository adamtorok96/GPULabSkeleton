#version 430

out vec4 outColor;

uniform int mOffset;

void main()
{
    vec2 pos = vec2(gl_FragCoord.x, gl_FragCoord.y);
    vec2 center = vec2(300, 300);

	outColor = vec4(
	    0.0f,
	    1.0f - (length(center - pos) / 300.f),
	    (length(center - pos) / 600.f),
	    1.0
    );
}