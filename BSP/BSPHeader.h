//
// Created by edems on 2018.05.18..
//

#ifndef TESSELERATION_BSPHEADER_H
#define TESSELERATION_BSPHEADER_H


#include "BSPLump.h"

#define nLumps 17

class BSPHeader {
public:

    char id[4];
    int version;
    BSPLump lumps[nLumps];
};


#endif //TESSELERATION_BSPHEADER_H
