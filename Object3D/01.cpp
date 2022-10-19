#include <GL/glew.h>
#include <GL/freeglut.h>

// Titik 3D dinyatakan dengan :
// P(x,y,z)
typedef struct
{
    float x, y, z;
} point3D_t;

// Implementasi Definisi Dari
// Struktur Faces
typedef struct
{
    int NumberofVertices;
    short int pnt[32];
} face_t;

// Implementasi Definisi Dari
// Struktur Obyek 3D
typedef struct
{
    int NumberofVertices;
    point3D_t pnt[100];
    int NumberofFaces;
    face_t fc[32];
} object3D_t;

static float X = 0.0;
static float Y = 0.0;
static float Z = -15.0;

void draw(object3D_t obj, int n, int m)
{
    int i;
    glBegin(GL_LINE_LOOP);
    for (i = 0; i < n; i++)
    {
        // glVertex3f(objpnt[i], obj[i].y, obj[i].z);
    }
    glEnd();
}

// Drawing routine.
void drawScene(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0, 0.0, 0.0);
    glLoadIdentity();
    glTranslatef(X, Y, Z);
    object3D_t prisma = {5,
                         {{0, 150, 0}, {100, 0, 0}, {0, 0, 100}, {-100, 0, 0}, {0, 0, -100}},
                         5,
                         {{3, {0, 1, 2}}, {3, {0, 2, 3}}, {3, {0, 3, 4}}, {3, {0, 4, 1}}, {4, {1, 4, 3, 2}}}};

    draw(prisma, 5, 5);

    glFlush();
}

// Initialization routine.
void setup(void)
{
    glClearColor(1.0, 1.0, 1.0, 0.0);
}

// OpenGL window reshape routine.
void resize(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-150.0, 150.0, -150.0, 150.0, 150.0, 200.0);
    glMatrixMode(GL_MODELVIEW);
}

// Main routine.
int main(int argc, char **argv)
{
    glutInit(&argc, argv);

    glutInitContextVersion(4, 3);
    glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);

    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("3LeggedStool.cpp");
    glutDisplayFunc(drawScene);
    glutReshapeFunc(resize);

    glewExperimental = GL_TRUE;
    glewInit();

    setup();

    glutMainLoop();
}
