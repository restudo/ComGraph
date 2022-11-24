/*  Kelompok 4
    Wahyu Putra Ramadhan / 5221600007
    Restu Dwi Octavriandi / 5221600013
    GameTech A 2021
    WORKSHOP GRAFIKA KOMPUTER
*/

#include <math.h>
#include <time.h>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <stb/stb_image.h>

#include "SOIL.h"

// define glu objects
GLUquadricObj *Cylinder;
GLUquadricObj *Disk;
struct tm *newtime;
time_t ltime;
int M_TWOPI = 0;
GLfloat rx, ry, rz, angle;
GLuint tex_ID;

void Print(float x, float y, char *str)
{
    int l, i;
    l = strlen(str);
    glRasterPos3f(x, y, -15);
    for (i = 0; i < l; i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, str[i]);
    }
}

static void TimeEvent(int timeEvent)
{
    rx = 30 * cos(angle);
    ry = 30 * sin(angle);
    rz = 30 * cos(angle);
    angle += 0.01;
    if (angle > M_TWOPI)
        angle = 0;
    glutPostRedisplay();
    glutTimerFunc(100, TimeEvent, 1);
}

void Setup(void)
{
    // texture
    tex_ID = SOIL_load_OGL_texture(
        "twitter-card.jpg",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_POWER_OF_TWO | SOIL_FLAG_MIPMAPS | SOIL_FLAG_DDS_LOAD_DIRECT);

    glClearColor(1.0, 1.0, 1.0, 0.0);
    Cylinder = gluNewQuadric();
    Disk = gluNewQuadric();

    glEnable(GL_TEXTURE_2D);
    gluQuadricTexture(Disk, true);
    glBindTexture(GL_TEXTURE_2D, tex_ID);
}

void Draw_gear(void)
{
    glPushMatrix();
    gluDisk(Disk, 0, 2.5, 32, 16);
    glPopMatrix();
}

void Draw_clock(GLfloat x, GLfloat y, GLfloat z)
{
    glPushMatrix();
    glTranslatef(x, y, z);
    glRotatef(180, 1.0, 0.0, 0.0);

    // Draw clock face
    glPushMatrix();
    glColor3f(0.0, 0.2, 0.4);
    glTranslatef(0, 0, 1.0);
    gluDisk(Disk, 0, 6.75, 32, 16);
    glPopMatrix();

    // Draw hour hand
    glPushMatrix();
    glColor3f(0.8, 0.8, 0.8);
    glTranslatef(0, 0, 0.0);
    // newtime->tm_hour
    glRotatef((360 / 12) * newtime->tm_hour, 0.0, 0.0, 1.0);

    // Draw Gear
    glPushMatrix();
    glTranslatef(0.0, 0.0, 2.0);
    glScalef(0.37, 0.37, 1.0);
    Draw_gear();
    glPopMatrix();

    glRotatef(90, 1.0, 0.0, 0.0);
    gluCylinder(Cylinder, 0.5, 0, 4, 16, 16);
    glPopMatrix();

    // Draw minute hand
    glPushMatrix();
    glColor3f(4.5, 4.5, 4.5);
    glTranslatef(0, 0, 0.0);
    // newtime->tm_min
    glRotatef((360 / 60) * newtime->tm_min, 0.0, 0.0, 1.0);

    // Draw Gear
    glPushMatrix();
    glTranslatef(0.0, 0.0, 3.0);
    glScalef(0.37, 0.37, 1.0);
    Draw_gear();
    glPopMatrix();

    glRotatef(90, 1.0, 0.0, 0.0);
    gluCylinder(Cylinder, 0.37, 0, 5, 16, 16);
    glPopMatrix();

    // Draw second hand
    glPushMatrix();
    glColor3f(1.0, 0.5, 0.5);
    glTranslatef(0, 0, 0.0);
    // newtime->tm_sec
    glRotatef((360 / 60) * newtime->tm_sec, 0.0, 0.0, 1.0);

    // Draw Gear
    glPushMatrix();
    glTranslatef(0.0, 0.0, 4.0);
    glScalef(0.25, 0.25, 1.0);
    Draw_gear();
    glPopMatrix();

    glRotatef(90, 1.0, 0.0, 0.0);
    gluCylinder(Cylinder, 0.22, 0, 6, 16, 16);
    glPopMatrix();

    // Draw Outer Circle & sec ticks
    for (int sec_ticks = 0; sec_ticks < 60; sec_ticks++)
    {
        glPushMatrix();
        glRotatef((360 / 60) * sec_ticks, 0.0, 0.0, 1.0);
        glColor3f(0.9, 0.9, 0.9);
        glTranslatef(5.8, 0.0, 0.0);
        glutSolidCube(1.0);
        glPopMatrix();

        glPushMatrix();
        glRotatef((360 / 60) * sec_ticks, 0.0, 0.0, 1.0);
        glColor3f(0.0, 0.0, 0.0);
        glTranslatef(6.0, 0.0, 0.0);
        glScalef(2, 0.2, 1);
        glutSolidCube(0.25);
        glPopMatrix();
    }

    for (int four_ticks = 0; four_ticks < 4; four_ticks++)
    {
        glPushMatrix();
        glRotatef((360 / 4) * four_ticks, 0.0, 0.0, 2.0);
        glColor3f(0.0, 0.0, 0.0);
        glTranslatef(5.7, 0.0, 0.0);
        glScalef(4.0, 0.5, 1);
        glutSolidCube(0.25);
        glPopMatrix();
    }

    for (int twelve_ticks = 0; twelve_ticks < 12; twelve_ticks++)
    {
        glPushMatrix();
        glRotatef((360 / 12) * twelve_ticks, 0.0, 0.0, 2.0);
        glColor3f(0.0, 0.0, 0.0);
        glTranslatef(5.8, 0.0, 0.0);
        glScalef(3.0, 0.4, 1);
        glutSolidCube(0.25);
        glPopMatrix();
    }
    glPopMatrix();
}

void display_clock()
{
    time(&ltime);                // Get time
    newtime = localtime(&ltime); // Convert to local time
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Put view state on screen / print
    glColor3f(0.0, 0.0, 0.0);
    Print(0.0, -7.0, asctime(newtime));
    Draw_clock(0.0, 2.0, -1.0);
    glutSwapBuffers();
}

void resize(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glOrtho(-12.0, 12.0, -12.0, 12.0, 1.0, 60.0);

    // glFrustum(-12.0, 12.0, -12.0, 12.0, 1.0, 60.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(50, 50);
    glutCreateWindow(argv[0]);
    glutSetWindowTitle("Project01 ComGraph");
    Setup();
    glutDisplayFunc(display_clock);
    glutReshapeFunc(resize);
    glutTimerFunc(10, TimeEvent, 1);
    glutMainLoop();

    // glDeleteTextures(1, &texture);

    return 0;
}