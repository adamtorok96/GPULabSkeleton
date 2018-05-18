#version 330

layout (lines_adjacency) in;
layout (line_strip, max_vertices = 200) out;

float GetT(float t, vec2 p0, vec2 p1) {
    float a = pow((p1.x - p0.x), 2.0f) + pow((p1.y - p0.y), 2.0f);
    float b = pow(a, 0.5f);
    float c = pow(b, 0.9f);

    return (c + t);
}

vec2 getPos(float t) {
    float s = 0.5f;

    vec4 a = vec4(pow(t, 3), t * t, t, 1);

    mat4 b;
    b[0] = vec4(-s, 2 - s, s - 2, s);
    b[1] = vec4(2 * s, s - 3, 3 - 2 * s, -s);
    b[2] = vec4(-s, 0, s, 0);
    b[3] = vec4(0, 1, 0, 0);

    mat4 c;
    c[0] = vec4(gl_in[0].gl_Position.xy, 0.0f, 1.0f);
    c[1] = vec4(gl_in[1].gl_Position.xy, 0.0f, 1.0f);
    c[2] = vec4(gl_in[2].gl_Position.xy, 0.0f, 1.0f);
    c[3] = vec4(gl_in[3].gl_Position.xy, 0.0f, 1.0f);

    return (a * b * c).xy;
}

void main (void) {
    float t0 = 0.0f;
    float t1 = GetT(t0, gl_in[0].gl_Position.xy, gl_in[1].gl_Position.xy);
    float t2 = GetT(t1, gl_in[1].gl_Position.xy, gl_in[2].gl_Position.xy);
    float t3 = GetT(t2, gl_in[2].gl_Position.xy, gl_in[3].gl_Position.xy);

    for(float t = t1; t < t2; t += ((t2 - t1) / 10.0f)) {
        vec2 A1 = (t1 - t) / (t1 - t0) * gl_in[0].gl_Position.xy + (t - t0) / (t1 - t0) * gl_in[1].gl_Position.xy;
        vec2 A2 = (t2 - t) / (t2 - t1) * gl_in[1].gl_Position.xy + (t - t1) / (t2 - t1) * gl_in[2].gl_Position.xy;
        vec2 A3 = (t3 - t) / (t3 - t2) * gl_in[2].gl_Position.xy + (t - t2) / (t3 - t2) * gl_in[3].gl_Position.xy;

        vec2 B1 = (t2 - t) / (t2 - t0) * A1 + (t - t0) / (t2 - t0) * A2;
        vec2 B2 = (t3 - t) / (t3 - t1) * A2 + (t - t1) / (t3 - t1) * A3;

        vec2 C = (t2 - t) / (t2 - t1) * B1 + (t - t1) / (t2 - t1) * B2;

        gl_Position = vec4(C, 0.0f, 1.0f);
        EmitVertex();
    }
}