/*  Kelompok 4
    Wahyu Putra Ramadhan / 5221600007
    Restu Dwi Octavriandi / 5221600013
    GameTech A 2021
    WORKSHOP GRAFIKA KOMPUTER
*/
#include <string.h>
#include <math.h>
#include <time.h>
#include <GL/glew.h>
#include <GL/freeglut.h>
#define STB_IMAGE_IMPLEMENTATION

/////////////////////////////////////Textures/////////////////////////////////////
#include <stb/stb_image.h>
GLuint texture; // the array for our texture

// define glu objects
GLUquadricObj *Cylinder;
GLUquadricObj *Disk;
struct tm *newtime;
time_t ltime;
int M_TWOPI = 0;
GLfloat rx, ry, rz, angle;
bool isLightEnable = false;

void Print(float x, float y, char *str)
{
    int l, i;
    l = strlen(str);
    glRasterPos3f(x, y, -5);
    for (i = 0; i < l; i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, str[i]);
    }
}

void loadTextureFromFile(const char *filename, unsigned int texture)
{
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load and generate the texture
    int width, height, nrChannels;
    unsigned char *data = stbi_load(filename, &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0,
                     GL_RGB, GL_UNSIGNED_BYTE, data);
    }
    else
    {
        printf("Gagal untuk meload texture, hehe><");
    }
    stbi_image_free(data);
}

const char *filename1 = "pepe-frog.jpeg";
unsigned int tob[1];

void textureSetup()
{
    glEnable(GL_TEXTURE_2D);

    glGenTextures(1, &tob[0]);

    loadTextureFromFile(filename1, tob[0]);
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
    glClearColor(1.0, 1.0, 1.0, 0.0);
    Cylinder = gluNewQuadric();
    Disk = gluNewQuadric();
    textureSetup();
}

void Draw_gear(void)
{
    glPushMatrix();

    glEnable(GL_TEXTURE_GEN_S); // enable texture coordinate generation
    glEnable(GL_TEXTURE_GEN_T);
    gluQuadricTexture(Disk, GL_TRUE);
    glBindTexture(GL_TEXTURE_2D, tob[0]);

    gluDisk(Disk, 0, 2.5, 32, 16);

    glDisable(GL_TEXTURE_GEN_S); // disable texture coordinate generation
    glDisable(GL_TEXTURE_GEN_T);
    gluQuadricTexture(Disk, GL_FALSE);

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

    gluQuadricTexture(Cylinder, GL_TRUE); ///
    glBindTexture(GL_TEXTURE_2D, tob[0]); ///

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

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);

    if (isLightEnable)
    {
        glEnable(GL_COLOR_MATERIAL);
        glEnable(GL_LIGHTING);  // Enable lighting
        glEnable(GL_LIGHT0);    // Enable light #0
        glEnable(GL_NORMALIZE); // Automatically normalize normals
    }
    else if (!isLightEnable)
    {
        glDisable(GL_COLOR_MATERIAL);
        glDisable(GL_LIGHTING);  // Enable lighting
        glDisable(GL_LIGHT0);    // Enable light #0
        glDisable(GL_NORMALIZE); // Automatically normalize normals
    }

    glShadeModel(GL_SMOOTH); // Enable smooth shading

    glEnable(GL_TEXTURE_2D);

    // Add ambient light
    GLfloat ambientColor[] = {0.2f, 0.2f, 0.2f, 1.0f}; // Color (0.2, 0.2, 0.2)
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientColor);

    // Add positioned light
    GLfloat lightColor0[] = {0.5f, 0.5f, 0.5f, 1.0f}; // Color (0.5, 0.5, 0.5)
    GLfloat lightPos0[] = {0.0f, 0.0f, -5.0f, 1.0f};  // Positioned at (0, 0, -5)
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor0);
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos0);

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

void keyInput(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 27:
        exit(0);
        break;
    case 'q':
        if (isLightEnable)
            isLightEnable = false;
        else if (!isLightEnable)
            isLightEnable = true;
        glutPostRedisplay();
        break;
    default:
        break;
    }
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(50, 50);
    glutCreateWindow(argv[0]);
    glutSetWindowTitle("Project02 ComGraph");
    Setup();
    glutDisplayFunc(display_clock);
    glutReshapeFunc(resize);
    glutKeyboardFunc(keyInput);
    glutTimerFunc(10, TimeEvent, 1);
    glutMainLoop();

    return 0;
}