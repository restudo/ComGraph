
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <math.h>
using namespace std;

typedef struct
{
    float x;
    float y;
} point2D_t;

typedef struct
{
    float x;
    float y;
    float z;
} point3D_t;

typedef struct
{
    int NumberofVertices;
    short int pnt[32];
} face_t;

typedef struct
{
    int NumberofVertices;
    point3D_t pnt[100];
    int NumberofFaces;
    face_t fc[32];
} object3D_t;

typedef struct
{
    float v[4];
} vector3D_t;

typedef struct
{
    float m[4][4];
} matrix3D_t;

typedef struct
{
    float r;
    float g;
    float b;
} color_t;

// vektor 2d ke 3d
point2D_t Vector2Point2D(vector3D_t vec)
{
    point2D_t pnt;
    pnt.x = vec.v[0];
    pnt.y = vec.v[1];
    return pnt;
}

// vektor 3d ke 3d
vector3D_t Point2Vector(point3D_t pnt)
{
    vector3D_t vec;
    vec.v[0] = pnt.x;
    vec.v[1] = pnt.y;
    vec.v[2] = pnt.z;
    vec.v[3] = 1.;
    return vec;
}

matrix3D_t createIdentity()
{
    matrix3D_t u;
    int i, j;
    for (i = 0; i < 4; i++)
    {
        for (j = 0; j < 4; j++)
        {
            u.m[i][j] = 0.;
        }
        u.m[i][i] = 1.;
    }
    return u;
}

matrix3D_t rotationXMTX(float theta)
{
    matrix3D_t rotate = createIdentity();
    float cs = cos(theta);
    float sn = sin(theta);

    rotate.m[0][0] = cs;
    rotate.m[0][1] = -sn;
    rotate.m[1][0] = sn;
    rotate.m[1][1] = cs;

    return rotate;
}

matrix3D_t rotationYMTX(float theta)
{
    matrix3D_t rotate = createIdentity();
    float cs = cos(theta);
    float sn = sin(theta);

    rotate.m[0][0] = cs;
    rotate.m[0][2] = -sn;
    rotate.m[2][0] = sn;
    rotate.m[2][2] = cs;

    return rotate;
}

matrix3D_t scalingMTX(float sx, float sy, float sz)
{
    matrix3D_t r = createIdentity();

    r.m[0][0] = sx;
    r.m[1][1] = sy;
    r.m[2][2] = sz;

    return r;
}

// operator aritmatika matrix3D
matrix3D_t operator*(matrix3D_t a, matrix3D_t b)
{
    matrix3D_t c; // c=a*b
    int i, j, k;
    for (i = 0; i < 4; i++)
    {
        for (j = 0; j < 4; j++)
        {
            c.m[i][j] = 0;
            for (k = 0; k < 4; k++)
            {
                c.m[i][j] += a.m[i][k] * b.m[k][j];
            }
        }
    }
    return c;
}

// operator aritmatika vector3D
vector3D_t operator*(matrix3D_t a, vector3D_t b)
{
    vector3D_t c; // c=a*b
    int i, j;
    for (i = 0; i < 4; i++)
    {
        c.v[i] = 0;
        for (j = 0; j < 4; j++)
            c.v[i] += a.m[i][j] * b.v[j];
    }
    return c;
}

vector3D_t operator^(vector3D_t a, vector3D_t b)
{
    vector3D_t c; // c=a*b
    c.v[0] = a.v[1] * b.v[2] - a.v[2] * b.v[1];
    c.v[1] = a.v[2] * b.v[0] - a.v[0] * b.v[2];
    c.v[2] = a.v[0] * b.v[1] - a.v[1] * b.v[0];
    c.v[3] = 1.;
    return c;
}

vector3D_t operator-(vector3D_t a, vector3D_t b)
{
    vector3D_t c; // c=a*b
    for (int i = 0; i < 3; i++)
        c.v[i] = a.v[i] - b.v[i];
    c.v[3] = 1.;
    return c;
}

void drawPolygon(point2D_t shp[], int n)
{
    int i;
    glBegin(GL_LINE_LOOP);
    for (i = 0; i < n; i++)
    {
        glVertex2f(shp[i].x, shp[i].y);
    }
    glEnd();
}

void drawObject3D(object3D_t object, matrix3D_t mat)
{
    vector3D_t vec[100], vecbuff[32], vecNormal;
    point2D_t titik2D[100];
    int i, j;

    for (i = 0; i < object.NumberofVertices; i++)
    {
        vec[i] = Point2Vector(object.pnt[i]);
        vec[i] = mat * vec[i];
    }

    // sisi visible
    for (i = 0; i < object.NumberofFaces; i++)
    {
        for (j = 0; j < object.fc[i].NumberofVertices; j++)
        {
            vecbuff[j] = vec[object.fc[i].pnt[j]];
        }
        vecNormal = (vecbuff[1] - vecbuff[0]) ^ (vecbuff[2] - vecbuff[0]);
        if (vecNormal.v[2] > 0)
        {
            for (j = 0; j < object.fc[i].NumberofVertices; j++)
            {
                titik2D[j] = Vector2Point2D(vec[object.fc[i].pnt[j]]);
            }
            drawPolygon(titik2D, object.fc[i].NumberofVertices);
        }
    }
}

void setColor(float r, float g, float b)
{
    glColor3f(r, g, b);
}

void draw()
{
    float theta = 0.5;
    matrix3D_t tilting = rotationXMTX(theta) * rotationYMTX(-theta);
    matrix3D_t mat;
    object3D_t prisma = {5, {{0, 100, 0}, {100, 0, 0}, {0, 0, 100}, {-100, 0, 0}, {0, 0, -100}}, 5, {{3, {0, 1, 2}}, {3, {0, 2, 3}}, {3, {0, 3, 4}}, {3, {0, 4, 1}}, {4, {1, 4, 3, 2}}}};
    setColor(1.0, 1.0, 1.0);

    mat = tilting * scalingMTX(2.0, 2.0, 2.0);
    drawObject3D(prisma, mat);
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    draw();
    glutSwapBuffers();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowPosition(150, 150);
    glutInitWindowSize(640, 480);

    glutCreateWindow("Object Graphic 3D 1");
    glClearColor(0.0, 0.0, 0.0, 0.0);
    gluOrtho2D(-320.0, 320.0, -240.0, 240.0);
    glutIdleFunc(display);
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}