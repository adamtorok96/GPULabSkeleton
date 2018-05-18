//
// Created by edems on 2018.05.18..
//

#ifndef TESSELERATION_BSP_H
#define TESSELERATION_BSP_H

using namespace std;

#include <string>
#include <utility>
#include <GL/glew.h>

#include "BSPHeader.h"
#include "BSPVertex.h"
#include "BSPFace.h"

class BSP {
    BSPHeader header;
    BSPVertex * vertices;
    BSPFace * faces;

    GLuint vao;
    GLuint vba;

    void loadToGPU();

public:
    BSP();
    ~BSP();

    void load(const string &filename);
    void draw();

    size_t getVertexCount();
    size_t getFaceCount();
};


#endif //TESSELERATION_BSP_H
