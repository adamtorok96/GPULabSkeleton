//
// Created by edems on 2018.05.18..
//

#include "BSP.h"

BSP::BSP() {

}

void BSP::load(const string &filename) {
    printf("load: %s\n", filename.c_str());
    FILE * f = fopen(filename.c_str(), "rb");

    printf("lol\n");
    if( f == nullptr ) {
        fclose(f);
        printf("fuck\n");

        throw exception();
    }

    fread(&header, sizeof(BSPHeader), 1, f);

    int n = 0;
    for(auto lump : header.lumps) {
        printf("%d: o: %d l: %d\n", n++, lump.offset, lump.length);
    }

    printf("%c%c%c%c\n", header.id[0], header.id[1], header.id[2], header.id[3]);

    printf("Vertices: %zu\n", getVertexCount());
    printf("Faces: %zu\n", getFaceCount());

    // Vertices
    vertices = new BSPVertex[getVertexCount()];

    fseek(f, SEEK_SET, header.lumps[LUMP_VERTICES].offset);
    fread(vertices, sizeof(BSPVertex), getVertexCount(), f);

    // Faces
    faces = new BSPFace[getFaceCount()];

    fseek(f, SEEK_SET, header.lumps[LUMP_FACES].offset);
    fread(faces, sizeof(BSPFace), getFaceCount(), f);

    fclose(f);

    loadToGPU();
}

BSP::~BSP() {
    delete[] vertices;
    delete[] faces;
}

void BSP::loadToGPU() {
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glGenBuffers(1, &vba);

    glBindBuffer(GL_ARRAY_BUFFER, vba);
    glBufferData(GL_ARRAY_BUFFER, header.lumps[LUMP_VERTICES].length, &vertices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, nullptr);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
    glVertexAttribPointer(3, 4, GL_UNSIGNED_BYTE, GL_FALSE, 0, nullptr);

    glBindVertexArray(0);
}



void BSP::draw() {
    glBindVertexArray(vao);

    for(size_t i = 0; i < getFaceCount(); i++) {
        glDrawArrays(GL_TRIANGLES, faces[i].vertex, faces[i].n_vertexes);
    }

    glBindVertexArray(0);
}

size_t BSP::getVertexCount() {
    return header.lumps[LUMP_VERTICES].length / sizeof(BSPVertex);
}

size_t BSP::getFaceCount() {
    return header.lumps[LUMP_FACES].length / sizeof(BSPFace);
}


