#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/gtc/matrix_transform.hpp>

#include <cstdio>
#include <algorithm>

#include "shader.hpp"


const unsigned int windowWidth = 600;
const unsigned int windowHeight = 600;

Shader shader;
Shader pointsShader;

GLuint vao;
GLuint vertexBuffer;

class CPoint {
    float x, y;

public:

    CPoint(float x, float y) : x{x}, y{y} {};
};

std::vector<CPoint> points;

#define PPV 2

void loadPoints() {
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * PPV * points.size(), &points[0], GL_STATIC_DRAW);
}

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
    shader.loadShader(GL_GEOMETRY_SHADER, "../shaders/geometry.glsl");
    shader.loadShader(GL_FRAGMENT_SHADER, "../shaders/fragment.glsl");
    shader.compile();

    pointsShader.loadShader(GL_VERTEX_SHADER, "../shaders/points.vertex.glsl");
    pointsShader.loadShader(GL_FRAGMENT_SHADER, "../shaders/points.fragment.glsl");
    pointsShader.compile();

    // Single triangle patch Vertex Array Object
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glGenBuffers(1, &vertexBuffer);

    loadPoints();

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, PPV, GL_FLOAT, GL_FALSE, 0, nullptr);

    glBindVertexArray(0);
}

void onDisplay()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::mat4 MV = glm::ortho(0.0f, 1.0f, 0.0f, 1.0f);

    glPatchParameteri(GL_PATCH_VERTICES, 4);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glPointSize(5.0f);

    glBindVertexArray(vao);

    // Draw lines
    shader.enable();
    shader.setUniformMat4("MV", MV);

    glDrawArrays(GL_LINE_STRIP_ADJACENCY, 0, static_cast<GLsizei>(points.size()));

    shader.disable();

    // Draw points
    pointsShader.enable();
    pointsShader.setUniformMat4("MV", MV);

    glDrawArrays(GL_POINTS, 0, static_cast<GLsizei>(points.size()));

    pointsShader.disable();

    glBindVertexArray(0);

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
    if ( button == GLUT_LEFT_BUTTON && state == GLUT_DOWN ) {
        points.emplace_back(x / 600.0f, 1.0f - (y / 600.0f));

        loadPoints();
    }
}

void onIdle()
{
    glutPostRedisplay();
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

