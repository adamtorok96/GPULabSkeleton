#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/gtc/matrix_transform.hpp>

#include <cstdio>
#include <algorithm>

#include "shader.hpp"


const unsigned int windowWidth = 600;
const unsigned int windowHeight = 600;

unsigned int offset = 0;

Shader shader;

GLuint vao;
GLuint vertexBuffer;

#define PPV 2
#define nVertices 4

#define A 0.0f
#define B 1.0f

float vertices[PPV * nVertices] = {
        A, A,
        B, A,
        B, B,
        A, B,
  //      0.2f, 0.2f,
};

void onInitialization()
{
    glewExperimental = GL_TRUE;

    if (glewInit() != GLEW_OK)
    {
        printf("Cannot initialize GLEW\n");
        exit(-1);
    }

    glGetError();

    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

    shader.loadShader(GL_VERTEX_SHADER, "../shaders/vertex.glsl");
    shader.loadShader(GL_FRAGMENT_SHADER, "../shaders/fragment.glsl");
    shader.compile();

    // Single triangle patch Vertex Array Object
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glGenBuffers(1, &vertexBuffer);

    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * PPV * nVertices, &vertices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, PPV, GL_FLOAT, GL_FALSE, 0, nullptr);

    glBindVertexArray(0);
}

void onDisplay()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::mat4 MV = glm::ortho(0.0f, 1.0f, 0.0f, 1.0f);

    //glPatchParameteri(GL_PATCH_VERTICES, 4);
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    //glPointSize(5.0f);

    shader.enable();
    shader.setUniformMat4("MV", MV);
    shader.setUniform1i("mOffset", offset);

    glBindVertexArray(vao);

    glDrawArrays(GL_TRIANGLE_FAN, 0, nVertices);

    glBindVertexArray(0);

    shader.disable();

    glutSwapBuffers();
}

void onKeyboard(unsigned char key, int pX, int pY) {
    switch (key)
    {
        case 27: glutExit(); break;

        default:break;
    }
}

void onMouse(int button, int state, int x, int y) {
}

void onIdle()
{
    glutPostRedisplay();

    offset++;
}

int main(int argc, char* argv[])
{
    glutInit(&argc, argv);

    glutInitContextVersion(3, 3);
    glutInitWindowSize(windowWidth, windowHeight);
    glutInitWindowPosition(100, 100);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
    glutCreateWindow(argv[0]);
    glewExperimental = GL_TRUE;

    glewInit();


    printf("GL Vendor    : %s\n", glGetString(GL_VENDOR));
    printf("GL Renderer  : %s\n", glGetString(GL_RENDERER));
    printf("GL Version (string)  : %s\n", glGetString(GL_VERSION));

    GLint major, minor;

    glGetIntegerv(GL_MAJOR_VERSION, &major);
    glGetIntegerv(GL_MINOR_VERSION, &minor);

    printf("GL Version (integer) : %d.%d\n", major, minor);
    printf("GLSL Version : %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));

    onInitialization();
    glutDisplayFunc(onDisplay);
    glutKeyboardFunc(onKeyboard);
    glutMouseFunc(onMouse);
    glutIdleFunc(onIdle);
    glutMainLoop();

    return 0;
}

