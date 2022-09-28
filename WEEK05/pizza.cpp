/////////////////////////////////          
// box.cpp
//
// This program draws a wire box.
//
// Sumanta Guha.
/////////////////////////////////

//#include <iostream>

#include <GL/glew.h>
#include <GL/freeglut.h> 
#include <math.h>

static float X = 0.0;
static float Y = 0.0;
static float Z = -15.0;

static GLUquadricObj *qobj;

// Drawing routine.
void drawScene(void)
{
	qobj = gluNewQuadric();
	gluQuadricDrawStyle(qobj, GLU_LINE);
	
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0, 0.0, 0.0);
	glLoadIdentity();

	// Modeling transformations.
	glTranslatef(X, Y, Z);
	glPushMatrix();
	glColor3f(1, 0, 0);
	gluPartialDisk(qobj, 0.0, 10.0, 1000, 1, 0.0, 60.0);
	glPopMatrix();
	
	glPushMatrix();
	glRotatef(60, 0, 0, 1);
	glColor3f(0, 1, 0);
	gluPartialDisk(qobj, 0.0, 10.0, 1000, 1, 0.0, 60.0);
	glPopMatrix();
	
	glPushMatrix();
	glRotatef(60, 0, 0, -1);
	glColor3f(0, 0, 1);
	gluPartialDisk(qobj, 0.0, 10.0, 1000, 1, 0.0, 60.0);
	glPopMatrix();
	
	glPushMatrix();
	glRotatef(120, 0, 0, 1);
	glColor3f(0, 0.5, 0.5);
	gluPartialDisk(qobj, 0.0, 10.0, 1000, 1, 0.0, 60.0);
	glPopMatrix();
	
	glPushMatrix();
	glRotatef(120, 0, 0, -1);
	glColor3f(0.9, 0.7, 0.3);
	gluPartialDisk(qobj, 0.0, 10.0, 1000, 1, 0.0, 60.0);
	glPopMatrix();
	
	glPushMatrix();
	glRotatef(180, 0, 0, 1);
	glColor3f(0.5, 0.5, 0.5);
	gluPartialDisk(qobj, 0.0, 10.0, 1000, 1, 0.0, 60.0);
	glPopMatrix();

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
	glFrustum(-5.0, 5.0, -5.0, 5.0, 5.0, 100.0);
    //glOrtho(-5.0, 5.0, -5.0, 5.0, 5.0, 100.0);

	glMatrixMode(GL_MODELVIEW);
}

// Keyboard input processing routine.
void keyInput(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 27:
		exit(0);
		break;
	case 'a':
		X+=0.5;
		glutPostRedisplay();
		break;
	case 'd':
		X -= 0.5;
		glutPostRedisplay();
		break;
	case 's':
		Y -= 0.5;
		glutPostRedisplay();
		break;
	case 'w':
		Y += 0.5;
		glutPostRedisplay();
		break;
	case 'q':
		Z -= 0.5;
		glutPostRedisplay();
		break;
	case 'e':
		Z += 0.5;
		glutPostRedisplay();
		break;
	default:
		break;
	}
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
	glutCreateWindow("box.cpp");
	glutDisplayFunc(drawScene);
	glutReshapeFunc(resize);
	glutKeyboardFunc(keyInput);

	glewExperimental = GL_TRUE;
	glewInit();

	setup();

	glutMainLoop();
}