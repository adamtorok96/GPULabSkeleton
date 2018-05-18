#version 330

// 4 vertices per-primitive -- 2 for the line (1,2) and 2 for adjacency (0,3)
layout (lines_adjacency) in;

// Standard fare for drawing lines
layout (line_strip, max_vertices = 6) out;

float L(int i, float t) {
    float Li = 1.0f;

    for(int j = 0; j < 3; j++) {
        if (j != i)
            Li *= (t - (j+1.0f)) / ((i+1.0f) - (j+1.0f));
    }

    return Li;
}

vec4 r(float t) {
    vec4 v;

    for(int i = 0; i < 3; i++) {
        v += gl_in[i].gl_Position * L(i, t);
    }

    return v;
}

void main (void) {
  // The two vertices adjacent to the line that you are currently processing
  //vec4 prev_vtx = gl_in[0].gl_Position;
  //vec4 next_vtx = gl_in[3].gl_Position;


    for(float i = 0.0f; i < 3.0f; i += 0.5f) {
        gl_Position = r(i);
        EmitVertex();
    }

/*
    gl_Position = gl_in[0].gl_Position;
    EmitVertex();

    gl_Position = gl_in[1].gl_Position; // First vertex in the line
    EmitVertex();

/*
     vec4 v = 0.5f * (
            (gl_in[2].gl_Position - gl_in[1].gl_Position) +
            (gl_in[1].gl_Position - gl_in[0].gl_Position)
        );

        gl_Position = normalize(v);
        EmitVertex();
*/
    /*gl_Position = gl_in[2].gl_Position; // Second vertex in the line
    EmitVertex();

    gl_Position = gl_in[3].gl_Position; // Second vertex in the line
    EmitVertex();
    */


/*
    vec4 v = 0.5f * (
        (gl_in[2].gl_Position - gl_in[1].gl_Position) +
        (gl_in[1].gl_Position - gl_in[0].gl_Position)
    );

    gl_Position = v;
    EmitVertex();

    gl_Position = v;
    EmitVertex();
*/
}