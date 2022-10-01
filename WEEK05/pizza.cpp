//#include <iostream>

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <math.h>

static float X = 0.0;
static float Y = 0.0;
static float Z = -15.0;

static float angle = 0.0;		  // Rotation.angle
static int isAnimate = 0;		  // Animated?
static int animationPeriod = 100; // Time interval between frames.

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
	glRotatef(angle, 0.0, 0.0, 1.0);
	glColor3f(1, 0, 0);
	gluPartialDisk(qobj, 0.0, 10.0, 1000, 1, 0.0, 60.0);
	glPopMatrix();

	glPushMatrix();
	glRotatef(angle, 0.0, 0.0, 1.0);
	glRotatef(60, 0, 0, 1);
	glColor3f(0, 1, 0);
	gluPartialDisk(qobj, 0.0, 10.0, 1000, 1, 0.0, 60.0);
	glPopMatrix();

	glPushMatrix();
	glRotatef(angle, 0.0, 0.0, 1.0);
	glRotatef(60, 0, 0, -1);
	glColor3f(0, 0, 1);
	gluPartialDisk(qobj, 0.0, 10.0, 1000, 1, 0.0, 60.0);
	glPopMatrix();

	glPushMatrix();
	glRotatef(angle, 0.0, 0.0, 1.0);
	glRotatef(120, 0, 0, 1);
	glColor3f(0, 0.5, 0.5);
	gluPartialDisk(qobj, 0.0, 10.0, 1000, 1, 0.0, 60.0);
	glPopMatrix();

	glPushMatrix();
	glRotatef(angle, 0.0, 0.0, 1.0);
	glRotatef(120, 0, 0, -1);
	glColor3f(0.9, 0.7, 0.3);
	gluPartialDisk(qobj, 0.0, 10.0, 1000, 1, 0.0, 60.0);
	glPopMatrix();

	glPushMatrix();
	glRotatef(angle, 0.0, 0.0, 1.0);
	glRotatef(180, 0, 0, 1);
	glColor3f(0.5, 0.5, 0.5);
	gluPartialDisk(qobj, 0.0, 10.0, 1000, 1, 0.0, 60.0);
	glPopMatrix();

	glFlush();
}

// Routine to increase the rotation angle.
void increaseAngle(void)
{
	angle += 5.0;
	if (angle > 360.0)
		angle -= 360.0;
}

// Timer function.
void animate(int value)
{
	if (isAnimate)
	{
		increaseAngle();

		glutPostRedisplay();
		glutTimerFunc(animationPeriod, animate, 1);
	}
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
	// glOrtho(-5.0, 5.0, -5.0, 5.0, 5.0, 100.0);

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
		X += 0.5;
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
	case ' ':
		if (isAnimate)
			isAnimate = 0;
		else
		{
			isAnimate = 1;
			animate(1);
		}
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