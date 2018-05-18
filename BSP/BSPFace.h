//
// Created by edems on 2018.05.18..
//

#ifndef TESSELERATION_BSPFACE_H
#define TESSELERATION_BSPFACE_H

#define LUMP_VERTICES 10
#define LUMP_FACES 13

class BSPFace {
public:
    int texture;
    int effect;
    int type;
    int vertex;
    int n_vertexes;
    int meshvert;
    int n_meshverts;
    int lm_index;
    int lm_start[2];
    int lm_size[2];
    float lm_origin[3];
    float lm_vecs[2][3];
    float normal[3];
    int size[2];
};


#endif //TESSELERATION_BSPFACE_H
