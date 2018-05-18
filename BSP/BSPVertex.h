//
// Created by edems on 2018.05.18..
//

#ifndef TESSELERATION_BSPVERTEX_H
#define TESSELERATION_BSPVERTEX_H


class BSPVertex {
public:
    float position[3];
    float textureCoordinates[2][2]; //	Vertex texture coordinates. 0=surface, 1=lightmap.
    float normal[3];
    unsigned char color[4];
};


#endif //TESSELERATION_BSPVERTEX_H
